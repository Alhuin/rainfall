## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level7 users  5274 Mar  6  2016 level6
  [...]
  ```
    - On a un binaire appartenant a level7 dans le home avec les droits SUID.

- `./level6`
  ```
  Segmentation fault (core dumped)
  ```
  - Le programme Segfault sans argument
- `./level6 test`
  ```
  Nope
  ```
  - Le programme affiche Nope avec un argument

- `gdb level6`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x08048454  n
      0x08048468  m
      0x0804847c  main
    [...]
    ```
    - on trouve une fonction n() et une fonction m() en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x0804847c <+0>:	push   ebp
       0x0804847d <+1>:	mov    ebp,esp
       0x0804847f <+3>:	and    esp,0xfffffff0
       0x08048482 <+6>:	sub    esp,0x20
       0x08048485 <+9>:	mov    DWORD PTR [esp],0x40
       0x0804848c <+16>:	call   0x8048350 <malloc@plt>
       0x08048491 <+21>:	mov    DWORD PTR [esp+0x1c],eax
       0x08048495 <+25>:	mov    DWORD PTR [esp],0x4
       0x0804849c <+32>:	call   0x8048350 <malloc@plt>
       0x080484a1 <+37>:	mov    DWORD PTR [esp+0x18],eax
       0x080484a5 <+41>:	mov    edx,0x8048468
       0x080484aa <+46>:	mov    eax,DWORD PTR [esp+0x18]
       0x080484ae <+50>:	mov    DWORD PTR [eax],edx
       0x080484b0 <+52>:	mov    eax,DWORD PTR [ebp+0xc]
       0x080484b3 <+55>:	add    eax,0x4
       0x080484b6 <+58>:	mov    eax,DWORD PTR [eax]
       0x080484b8 <+60>:	mov    edx,eax
       0x080484ba <+62>:	mov    eax,DWORD PTR [esp+0x1c]
       0x080484be <+66>:	mov    DWORD PTR [esp+0x4],edx
       0x080484c2 <+70>:	mov    DWORD PTR [esp],eax
       0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
       0x080484ca <+78>:	mov    eax,DWORD PTR [esp+0x18]
       0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
       0x080484d0 <+84>:	call   eax
       0x080484d2 <+86>:	leave
       0x080484d3 <+87>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+6>
      - Initialisation de la mémoire (libère 32 octets pour la stack), alignement de la stack<br/><br/>
    - <+9> ... <+21>
      - Stocke 0x40 (64) sur la stack (à esp)
      - Call malloc() avec l'argument stocké sur la stack
      - Stocke eax (le retour du malloc) sur la stack (à esp + 28)<br/><br/>
    - <+25> ... <+37>
      - Stocke 0x4 (4) sur la stack (a esp)
      - Call malloc() avec l'argument stocké sur la stack
      - Stocke eax (le retour du malloc) sur la stack (à esp + 24)<br/><br/>
    - <+41> ... <+73>
      - Stocke la valeur de 0x8048468 dans edx
        - `x/s 0x8048468`
          ```
          0x8048468 <m>:	 "U\211\345\203\354\030\307\004$х\004\b\350\346\376\377\377\311\303U\211\345\203\344\360\203\354 \307\004$@"
          ```
      - Fait pointer eax sur esp + 24 (le retour du malloc(4))
      - Stocke la valeur de edx (l'adresse de m()) dans eax (malloc(4) => m())
      - Fait pointer eax sur ebp + 12 (&argv)
      - Incrémente eax de 4 (&argv[1])
      - Stocke la valeur à l'adresse de eax dans eax
      - Stocke eax (argv[1]) dans edx
      - Stocke la valeur à esp + 28 (le retour du malloc(64)) dans eax
      - Stocke edx (argv[1]) sur la stack (à esp + 4)
      - Stocke eax (le retour du malloc(64)) sur la stack (à esp)
      - Call strcpy() avec les arguments stockés sur la stack<br/><br/>
    - <+78> ... <+84>
      - Stocke la valeur à esp + 24 (le malloc(4) contenant l'adresse de m()) dans eax
      - Stocke la valeur à l'adresse de eax (l'adresse de m()) dans eax
      - Call eax (donc call m())<br/><br/>
    - <+86> ... <+87>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

  - `disas m`
    ```asm
    Dump of assembler code for function m:
       0x08048468 <+0>:	push   ebp
       0x08048469 <+1>:	mov    ebp,esp
       0x0804846b <+3>:	sub    esp,0x18
       0x0804846e <+6>:	mov    DWORD PTR [esp],0x80485d1
       0x08048475 <+13>:	call   0x8048360 <puts@plt>
       0x0804847a <+18>:	leave
       0x0804847b <+19>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 24 octets pour la stack)<br/><br/>
    - <+6> ... <+13>
      - Stocke la valeur de 0x80485d1 sur la stack (à esp)
        - `x/s 0x80485d1`
          ```
          0x80485d1:	 "Nope"
          ```
      - Call puts() avec l'argument stocké sur la stack<br/><br/>
    - <+18> ... <+19>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

  - `disas n`
    ```asm
    Dump of assembler code for function n:
       0x08048454 <+0>:	push   ebp
       0x08048455 <+1>:	mov    ebp,esp
       0x08048457 <+3>:	sub    esp,0x18
       0x0804845a <+6>:	mov    DWORD PTR [esp],0x80485b0
       0x08048461 <+13>:	call   0x8048370 <system@plt>
       0x08048466 <+18>:	leave
       0x08048467 <+19>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 24 octets pour la stack)<br/><br/>
    - <+6> ... <+13>
      - Stocke la valeur de 0x80485b0 sur la stack (à esp)
        - `x/s 0x80485b0`
          ```
          0x80485b0:	 "/bin/cat /home/user/level7/.pass"
          ```
      - Call system() avec l'argument stocké sur la stack<br/><br/>
    - <+18> ... <+19>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

## Exploit

La fonction main() fait deux appels à malloc():
- malloc(64) où on va venir copier notre input avec strcpy
- malloc(4) oû on va stocker l'adresse de la fonction à exécuter à <main+84> (en l'occurence l'adresse de m())

La fonction m() affiche "Nope" et la fonction n() (qui n'est pas appelée) affiche le contenu du fichier .pass, on comprend que l'on va devoir profiter de [la vulérabilité de strcpy() à un buffer overflow](https://www.cisa.gov/uscert/bsi/articles/knowledge/coding-practices/strcpy-and-strcat) pour venir écrire l'adresse de n() dans le malloc(4).

