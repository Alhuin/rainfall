## Analyse
- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 bonus3 users  5664 Mar  6  2016 bonus2
  [...]
  - On a un binaire appartenant à bonus3 dans le home avec les droits SUID.

- `./bonus2`
- `./bonus2 test`
  ```
  ```
  - Le programme termine sans rien afficher avec 0 ou 1 argument
- `./bonus2 test test`
  ```
  Hello test
  ```
  - Avec deux arguments, affiche "Hello [argv[2]]"

- `./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Hello Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab`
  ```
  Segmentation fault (core dumped)
  ```
  - Avec des input trop longs on SegFault<br/><br/>
- `gdb bonus2`
  - `set disassembly-flavor intel`
  - `info function`
    ```
    [...]
      0x08048484  greetuser
      0x08048529  main
    [...]
    ```
    - On trouve une fonction greetuser() en plus du main

  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x08048529 <+0>:     push   ebp
       0x0804852a <+1>:     mov    ebp,esp
       0x0804852c <+3>:     push   edi
       0x0804852d <+4>:     push   esi
       0x0804852e <+5>:     push   ebx
       0x0804852f <+6>:     and    esp,0xfffffff0
       0x08048532 <+9>:     sub    esp,0xa0
       0x08048538 <+15>:    cmp    DWORD PTR [ebp+0x8],0x3
       0x0804853c <+19>:    je     0x8048548 <main+31>
       0x0804853e <+21>:    mov    eax,0x1
       0x08048543 <+26>:    jmp    0x8048630 <main+263>
       0x08048548 <+31>:    lea    ebx,[esp+0x50]
       0x0804854c <+35>:    mov    eax,0x0
       0x08048551 <+40>:    mov    edx,0x13
       0x08048556 <+45>:    mov    edi,ebx
       0x08048558 <+47>:    mov    ecx,edx
       0x0804855a <+49>:    rep stos DWORD PTR es:[edi],eax
       0x0804855c <+51>:    mov    eax,DWORD PTR [ebp+0xc]
       0x0804855f <+54>:    add    eax,0x4
       0x08048562 <+57>:    mov    eax,DWORD PTR [eax]
       0x08048564 <+59>:    mov    DWORD PTR [esp+0x8],0x28
       0x0804856c <+67>:    mov    DWORD PTR [esp+0x4],eax
       0x08048570 <+71>:    lea    eax,[esp+0x50]
       0x08048574 <+75>:    mov    DWORD PTR [esp],eax
       0x08048577 <+78>:    call   0x80483c0 <strncpy@plt>
       0x0804857c <+83>:    mov    eax,DWORD PTR [ebp+0xc]
       0x0804857f <+86>:    add    eax,0x8
       0x08048582 <+89>:    mov    eax,DWORD PTR [eax]
       0x08048584 <+91>:    mov    DWORD PTR [esp+0x8],0x20
       0x0804858c <+99>:    mov    DWORD PTR [esp+0x4],eax
       0x08048590 <+103>:   lea    eax,[esp+0x50]
       0x08048594 <+107>:   add    eax,0x28
       0x08048597 <+110>:   mov    DWORD PTR [esp],eax
       0x0804859a <+113>:   call   0x80483c0 <strncpy@plt>
       0x0804859f <+118>:   mov    DWORD PTR [esp],0x8048738
       0x080485a6 <+125>:   call   0x8048380 <getenv@plt>
       0x080485ab <+130>:   mov    DWORD PTR [esp+0x9c],eax
       0x080485b2 <+137>:   cmp    DWORD PTR [esp+0x9c],0x0
       0x080485ba <+145>:   je     0x8048618 <main+239>
       0x080485bc <+147>:   mov    DWORD PTR [esp+0x8],0x2
       0x080485c4 <+155>:   mov    DWORD PTR [esp+0x4],0x804873d
       0x080485cc <+163>:   mov    eax,DWORD PTR [esp+0x9c]
       0x080485d3 <+170>:   mov    DWORD PTR [esp],eax
       0x080485d6 <+173>:   call   0x8048360 <memcmp@plt>
       0x080485db <+178>:   test   eax,eax
       0x080485dd <+180>:   jne    0x80485eb <main+194>
       0x080485df <+182>:   mov    DWORD PTR ds:0x8049988,0x1
       0x080485e9 <+192>:   jmp    0x8048618 <main+239>
       0x080485eb <+194>:   mov    DWORD PTR [esp+0x8],0x2
       0x080485f3 <+202>:   mov    DWORD PTR [esp+0x4],0x8048740
       0x080485fb <+210>:   mov    eax,DWORD PTR [esp+0x9c]
       0x08048602 <+217>:   mov    DWORD PTR [esp],eax
       0x08048605 <+220>:   call   0x8048360 <memcmp@plt>
       0x0804860a <+225>:   test   eax,eax
       0x0804860c <+227>:   jne    0x8048618 <main+239>
       0x0804860e <+229>:   mov    DWORD PTR ds:0x8049988,0x2
       0x08048618 <+239>:   mov    edx,esp
       0x0804861a <+241>:   lea    ebx,[esp+0x50]
       0x0804861e <+245>:   mov    eax,0x13
       0x08048623 <+250>:   mov    edi,edx
       0x08048625 <+252>:   mov    esi,ebx
       0x08048627 <+254>:   mov    ecx,eax
       0x08048629 <+256>:   rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
       0x0804862b <+258>:   call   0x8048484 <greetuser>
       0x08048630 <+263>:   lea    esp,[ebp-0xc]
       0x08048633 <+266>:   pop    ebx
       0x08048634 <+267>:   pop    esi
       0x08048635 <+268>:   pop    edi
       0x08048636 <+269>:   pop    ebp
       0x08048637 <+270>:   ret    
    End of assembler dump.
    ```
    - <+0>...<+9>
      - Initialisation la mémoire, alignement de la stack et libère 160 octets pour le stack.<br/><br/>
    - <+15>... <+26>
      - Compare argc à 3
      - Si argc == 3 jump a l'instruction <main+31>
      - EAX = 1
      - Jump a <main+263> (pour ensuite retourner 1)<br/><br/>
    - <+31>...<+49>
      - Stocke un pointeur a esp + 0x50 (80) dans EBX
      - Met 0 dans EAX
      - Met 0x13(19) dans EDX 
      - Met le EBX dans EDI (ESP + 0x50)
      - Met EDX dans ECI (0x13)
      - [Equivalent d'un appel a memset](https://www.web-dev-qa-db-fra.com/fr/assembly/que-fait-la-sequence-dinstructions-dassemblage-rep-stos-x86/971024388/) avec en argument EBX, EAX, EDX.
        - EDX va attribuer 4 octets pour chaque iteration donc la  taille du memset va etre de (19 - 1) * 4 = 72. Nous retirons 1 iterations car il est indiqué que la boucle s'arrête dès que la valeur vaut 0.
        - memset(a, '\0', 72) -> ce qui va remplir le buffer sur a avec des '\0' sur une taille de 72 octets et renvoi un poineur sur a.<br/><br/>
    - <+51>...<+83>
      - Stocke le pointeur sur argv dans EAX
      - Ajoute à EAX pour pointer sur argv[1]
      - Stocke argv[1] dans EAX
      - Stocke 0x28 (40) en 3eme argument
      - Stocke argv[1] (EAX) en 2nd argument
      - Stocke un pointeur sur esp+0x50 notre buffer qu'on a memset
      - Exécute strncpy(a, argv[1], 40)<br/><br/>
    - <+83>...<+113>
      - idem de que precedement avec differents arguments
      - strncpy(&a[40], argv[2], 32)<br/><br/>
    - <+118>...<+125>
      - Appel getenv avec la valeur à 0x8048738
        - `x/s 0x8048738`
          ```
          0x8048738:       "LANG"
          ```
      <br/>
    - <+130>...<+145>
      - Stocke le retour de getenv("LANG") dans esp+0x9c
      - Compare la valeur à 0
      - Si le retour du getenv est 0 on jump a l'instruction <main+239><br/><br/>
    - <+147>...<+173>
      - Stocke la valeur 2 comme 3eme argument
      - Stocke la valeur à 0x804873d en 2nd argument
      - `x/s 0x804873d`
        ```
        0x804873d:       "fi"
        ```
      - Stocke le retour de getenv en premier argument
      - Appelle memcmp(env, "fi", 2)<br/><br/>
    - <+178>...<+180>
      - [Compare EAX a 0](https://www.developpez.net/forums/d25009/autres-langages/assembleur/x86-32-bits-64-bits/quoi-sert-l-instruction-test-eax-eax/)
      - Si EAX n'est pas egal a 0 jump a l'instruction <main+194><br/><br/>
    - <+182>...<+192>
      - Stocke 1 dans la variable globale 0x8049988
        - `x/s 0x8049988`
          ```
          0x8049988 <language>:    ""
          ```
      - Jump à l'instruction <main+239><br/><br/>
    - <+194>...<+220>
      - Stocke la valeur 2 comme 3eme argument
      - Stocke la valeur à 0x8048740 en 2nd argument
        - `x/s 0x8049988`
          ```
          0x8048740:       "nl"
          ```
      - Stocke le retour de getenv en premier argument
      - Appelle memcmp(env, "nl", 2)<br/><br/>
    - <+225>...<+229>
      - Compare EAX a 0
      - Si EAX n'est pas egal a 0 jump a l'instruction <main+239>
      - Stocke 2 dans la variable globale à 
        - `x/s 0x8049988`
          ```
          0x8049988 <language>:    ""
          ```
          <br/>
    - <+239>...<+258>
      - Copie le premier buffer a esp+0x50 dans esp pour pour l'appeler en argument de greetuser.
        - https://stackoverflow.com/questions/27804852/assembly-rep-movs-mechanism
        - https://news.ycombinator.com/item?id=12048651<br/><br/>
  - `disas greetuser`
    ```asm
    Dump of assembler code for function greetuser:
       0x08048484 <+0>:     push   ebp
       0x08048485 <+1>:     mov    ebp,esp
       0x08048487 <+3>:     sub    esp,0x58
       0x0804848a <+6>:     mov    eax,ds:0x8049988
       0x0804848f <+11>:    cmp    eax,0x1
       0x08048492 <+14>:    je     0x80484ba <greetuser+54>
       0x08048494 <+16>:    cmp    eax,0x2
       0x08048497 <+19>:    je     0x80484e9 <greetuser+101>
       0x08048499 <+21>:    test   eax,eax
       0x0804849b <+23>:    jne    0x804850a <greetuser+134>
       0x0804849d <+25>:    mov    edx,0x8048710
       0x080484a2 <+30>:    lea    eax,[ebp-0x48]
       0x080484a5 <+33>:    mov    ecx,DWORD PTR [edx]
       0x080484a7 <+35>:    mov    DWORD PTR [eax],ecx
       0x080484a9 <+37>:    movzx  ecx,WORD PTR [edx+0x4]
       0x080484ad <+41>:    mov    WORD PTR [eax+0x4],cx
       0x080484b1 <+45>:    movzx  edx,BYTE PTR [edx+0x6]
       0x080484b5 <+49>:    mov    BYTE PTR [eax+0x6],dl
       0x080484b8 <+52>:    jmp    0x804850a <greetuser+134>
       0x080484ba <+54>:    mov    edx,0x8048717
       0x080484bf <+59>:    lea    eax,[ebp-0x48]
       0x080484c2 <+62>:    mov    ecx,DWORD PTR [edx]
       0x080484c4 <+64>:    mov    DWORD PTR [eax],ecx
       0x080484c6 <+66>:    mov    ecx,DWORD PTR [edx+0x4]
       0x080484c9 <+69>:    mov    DWORD PTR [eax+0x4],ecx
       0x080484cc <+72>:    mov    ecx,DWORD PTR [edx+0x8]
       0x080484cf <+75>:    mov    DWORD PTR [eax+0x8],ecx
       0x080484d2 <+78>:    mov    ecx,DWORD PTR [edx+0xc]
       0x080484d5 <+81>:    mov    DWORD PTR [eax+0xc],ecx
       0x080484d8 <+84>:    movzx  ecx,WORD PTR [edx+0x10]
       0x080484dc <+88>:    mov    WORD PTR [eax+0x10],cx
       0x080484e0 <+92>:    movzx  edx,BYTE PTR [edx+0x12]
       0x080484e4 <+96>:    mov    BYTE PTR [eax+0x12],dl
       0x080484e7 <+99>:    jmp    0x804850a <greetuser+134>
       0x080484e9 <+101>:   mov    edx,0x804872a
       0x080484ee <+106>:   lea    eax,[ebp-0x48]
       0x080484f1 <+109>:   mov    ecx,DWORD PTR [edx]
       0x080484f3 <+111>:   mov    DWORD PTR [eax],ecx
       0x080484f5 <+113>:   mov    ecx,DWORD PTR [edx+0x4]
       0x080484f8 <+116>:   mov    DWORD PTR [eax+0x4],ecx
       0x080484fb <+119>:   mov    ecx,DWORD PTR [edx+0x8]
       0x080484fe <+122>:   mov    DWORD PTR [eax+0x8],ecx
       0x08048501 <+125>:   movzx  edx,WORD PTR [edx+0xc]
       0x08048505 <+129>:   mov    WORD PTR [eax+0xc],dx
       0x08048509 <+133>:   nop
       0x0804850a <+134>:   lea    eax,[ebp+0x8]
       0x0804850d <+137>:   mov    DWORD PTR [esp+0x4],eax
       0x08048511 <+141>:   lea    eax,[ebp-0x48]
       0x08048514 <+144>:   mov    DWORD PTR [esp],eax
       0x08048517 <+147>:   call   0x8048370 <strcat@plt>
       0x0804851c <+152>:   lea    eax,[ebp-0x48]
       0x0804851f <+155>:   mov    DWORD PTR [esp],eax
       0x08048522 <+158>:   call   0x8048390 <puts@plt>
       0x08048527 <+163>:   leave  
       0x08048528 <+164>:   ret    
    End of assembler dump.
    ```
    - <+0>...<+3>
      - Initialise la mémoire, aligne la stack et alloue 88 bytes.<br/><br/>
    - <+6>...<+23>
      - Met la variable globale 0x8049988 (<language>) dans EAX
      - Compare cette valeur avec 1
      - Si la variable globale language est égale à 1, jump à <greetuser+54>
      - Compare language avec 2 
      - Si la variable globale language est égale a 2 jump à <greetuser+101>
      - Compare language avec 0
      - Si la variable globale language n'est pas égale a 0 jump à <greetuser+134><br/><br/>
    - <+25>...<+52>
      - [Équivalent à strcpy](https://www.esaracco.fr/documentation/assembly/assembly/copie-de-chaine.html)(buffer, "Hello ") 
      - https://www.gladir.com/LEXIQUE/ASM/movzx.htm
      - Stocke la valeur à 0x8048710 dans EDX
        - `x/s 0x8048710`
          ```
          0x8048710:       "Hello "
          ```
      - jump a <greetuser+134><br/><br/>
    - <+54>...<+99>
      - Équivalent à strcpy(buffer,valeur à 0x8048717)
        - `x/s 0x8048717`
          ```
          0x8048717:       "Hyvää päivää "
          ```
        <br/>
    - <+101>...<+133>
      - Équivalent à strcpy(buffer, valeur à 0x804872a)
      - `x/s 0x804872a`
        ```
        0x804872a:       "Goedemiddag! "
        ```
        <br/>
    - <+134>...<+147>
      - Stocke l'argument de la fonction en 2nd argument
      - Stocke notre buffer en premier argument
      - Appelle strcat(buffer, arg)<br/><br/>
    - <+152>...<+158>
      - Stocke buffer en argument
      - Appelle puts(buffer)<br/><br/>

    - <+163>...<+164>
      - Return eax (le retour de puts)
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>
## Exploit
