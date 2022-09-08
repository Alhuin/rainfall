## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level6 users  5385 Mar  6  2016 level5
  [...]
  ```
    - On a un binaire appartenant a level6 dans le home avec les droits SUID.

- `./level5`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - `test`
    - Le programme affiche le paramètre qu'on lui donne

- `gdb level5`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080484a4  o
      0x080484c2  n
      0x08048504  main
    [...]
    ```
    - on trouve une fonction n() et une fonction o() en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x08048504 <+0>:	push   ebp
       0x08048505 <+1>:	mov    ebp,esp
       0x08048507 <+3>:	and    esp,0xfffffff0
       0x0804850a <+6>:	call   0x80484c2 <n>
       0x0804850f <+11>:	leave
       0x08048510 <+12>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire, alignement de la stack<br/><br/>
    - <+6>
      - Call la fonction n()<br/><br/>
    - <+11> ... <+12>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

  - `disas n`
    ```asm
    Dump of assembler code for function n:
       0x080484c2 <+0>:	push   ebp
       0x080484c3 <+1>:	mov    ebp,esp
       0x080484c5 <+3>:	sub    esp,0x218
       0x080484cb <+9>:	mov    eax,ds:0x8049848
       0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
       0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
       0x080484dc <+26>:	lea    eax,[ebp-0x208]
       0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
       0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
       0x080484ea <+40>:	lea    eax,[ebp-0x208]
       0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
       0x080484f3 <+49>:	call   0x8048380 <printf@plt>
       0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
       0x080484ff <+61>:	call   0x80483d0 <exit@plt>
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 536 octets pour la stack)<br/><br/>
    - <+9> ... <+35>
      - Stocke dans eax la valeur de l'adresse 0x8049848 dans le data segment register
        - `x/s 0x8049848`
          - `0x8049848 <stdin@@GLIBC_2.0>:	 ""`
      - Stocke la valeur de eax (stdin) dans la stack (à esp + 8)
      - Stocke 0x200 (512) dans la stack (à esp + 4)
      - Fait pointer eax sur ebp - 520
      - Stocke eax (l'adresse ebp - 520) dans la stack (à esp)
      - Call fgets() avec les arguments stockés dans la stack<br/><br/>
    - <+40> ... <+49>
      - Fait pointer eax sur ebp - 520 => l'adresse du retour de fgets()
      - Stocke eax (l'adresse du retour de fgets()) sur la stack (à esp)
      - Call printf avec l'argument stocké sur la stack<br/><br/>
    - <+54> ... <+61>
      - Stocke 0x1 (1) sur la stack
      - Call exit() avec l'argument stocké sur la stack

  - `disas o`
    ```asm
    Dump of assembler code for function o:
       0x080484a4 <+0>:	push   ebp
       0x080484a5 <+1>:	mov    ebp,esp
       0x080484a7 <+3>:	sub    esp,0x18
       0x080484aa <+6>:	mov    DWORD PTR [esp],0x80485f0
       0x080484b1 <+13>:	call   0x80483b0 <system@plt>
       0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
       0x080484bd <+25>:	call   0x8048390 <_exit@plt>
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 24 octets pour la stack)<br/><br/>
    - <+6> ... <+13>
      - Stocke la valeur de 0x80485f0 sur la stack (à esp)
        - `x/s 0x80485f0`
          ```
          0x80485f0:	 "/bin/sh"
          ```
      - Call system() avec l'argument stocké sur la stack (à esp)
    - <+17> ... <+18>
      - Réinitialisation de la mémoire, fin d'exécution
    - <+18> ... <+25>
      - Stocke 0x1 (1) sur la stack
      - Call _exit() avec l'argument stocké sur la stack

## Exploit

Ni main() ni n() n'appellent o(), dommage car il nous pop un shell. On remarque également qu'il n'y a pas de return(), uniquement des call à exit() donc impossible de réécrire l'eip.

- diff exit() vs _exit() ?
- modifier exit pour le faire pointer sur o() avec printf ?
