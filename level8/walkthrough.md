## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level9 users  6057 Mar  6  2016 level8
  [...]
  ```
    - On a un binaire appartenant a level8 dans le home avec les droits SUID.

- `./level6`
  ```
  (nil), (nil)
  
  ```
  - Avec ou sans arguments, le programme à l'air de lancer une boucle qui affiche "(nil), (nil)" et attend un input sur stdin.

- `gdb level8`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x08048564  main
    [...]
    ```
    - on ne trouve que la fonction main décalrée dans le binaire
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x08048564 <+0>:	push   ebp
       0x08048565 <+1>:	mov    ebp,esp
       0x08048567 <+3>:	push   edi
       0x08048568 <+4>:	push   esi
       0x08048569 <+5>:	and    esp,0xfffffff0
       0x0804856c <+8>:	sub    esp,0xa0
       0x08048572 <+14>:	jmp    0x8048575 <main+17>
       0x08048574 <+16>:	nop
       0x08048575 <+17>:	mov    ecx,DWORD PTR ds:0x8049ab0
       0x0804857b <+23>:	mov    edx,DWORD PTR ds:0x8049aac
       0x08048581 <+29>:	mov    eax,0x8048810
       0x08048586 <+34>:	mov    DWORD PTR [esp+0x8],ecx
       0x0804858a <+38>:	mov    DWORD PTR [esp+0x4],edx
       0x0804858e <+42>:	mov    DWORD PTR [esp],eax
       0x08048591 <+45>:	call   0x8048410 <printf@plt>
       0x08048596 <+50>:	mov    eax,ds:0x8049a80
       0x0804859b <+55>:	mov    DWORD PTR [esp+0x8],eax
       0x0804859f <+59>:	mov    DWORD PTR [esp+0x4],0x80
       0x080485a7 <+67>:	lea    eax,[esp+0x20]
       0x080485ab <+71>:	mov    DWORD PTR [esp],eax
       0x080485ae <+74>:	call   0x8048440 <fgets@plt>
       0x080485b3 <+79>:	test   eax,eax
       0x080485b5 <+81>:	je     0x804872c <main+456>
       0x080485bb <+87>:	lea    eax,[esp+0x20]
       0x080485bf <+91>:	mov    edx,eax
       0x080485c1 <+93>:	mov    eax,0x8048819
       0x080485c6 <+98>:	mov    ecx,0x5
       0x080485cb <+103>:	mov    esi,edx
       0x080485cd <+105>:	mov    edi,eax
       0x080485cf <+107>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
       0x080485d1 <+109>:	seta   dl
       0x080485d4 <+112>:	setb   al
       0x080485d7 <+115>:	mov    ecx,edx
       0x080485d9 <+117>:	sub    cl,al
       0x080485db <+119>:	mov    eax,ecx
       0x080485dd <+121>:	movsx  eax,al
       0x080485e0 <+124>:	test   eax,eax
       0x080485e2 <+126>:	jne    0x8048642 <main+222>
       0x080485e4 <+128>:	mov    DWORD PTR [esp],0x4
       0x080485eb <+135>:	call   0x8048470 <malloc@plt>
       0x080485f0 <+140>:	mov    ds:0x8049aac,eax
       0x080485f5 <+145>:	mov    eax,ds:0x8049aac
       0x080485fa <+150>:	mov    DWORD PTR [eax],0x0
       0x08048600 <+156>:	lea    eax,[esp+0x20]
       0x08048604 <+160>:	add    eax,0x5
       0x08048607 <+163>:	mov    DWORD PTR [esp+0x1c],0xffffffff
       0x0804860f <+171>:	mov    edx,eax
       0x08048611 <+173>:	mov    eax,0x0
       0x08048616 <+178>:	mov    ecx,DWORD PTR [esp+0x1c]
       0x0804861a <+182>:	mov    edi,edx
       0x0804861c <+184>:	repnz scas al,BYTE PTR es:[edi]
       0x0804861e <+186>:	mov    eax,ecx
       0x08048620 <+188>:	not    eax
       0x08048622 <+190>:	sub    eax,0x1
       0x08048625 <+193>:	cmp    eax,0x1e
       0x08048628 <+196>:	ja     0x8048642 <main+222>
       0x0804862a <+198>:	lea    eax,[esp+0x20]
       0x0804862e <+202>:	lea    edx,[eax+0x5]
       0x08048631 <+205>:	mov    eax,ds:0x8049aac
       0x08048636 <+210>:	mov    DWORD PTR [esp+0x4],edx
       0x0804863a <+214>:	mov    DWORD PTR [esp],eax
       0x0804863d <+217>:	call   0x8048460 <strcpy@plt>
       0x08048642 <+222>:	lea    eax,[esp+0x20]
       0x08048646 <+226>:	mov    edx,eax
       0x08048648 <+228>:	mov    eax,0x804881f
       0x0804864d <+233>:	mov    ecx,0x5
       0x08048652 <+238>:	mov    esi,edx
       0x08048654 <+240>:	mov    edi,eax
       0x08048656 <+242>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
       0x08048658 <+244>:	seta   dl
       0x0804865b <+247>:	setb   al
       0x0804865e <+250>:	mov    ecx,edx
       0x08048660 <+252>:	sub    cl,al
       0x08048662 <+254>:	mov    eax,ecx
       0x08048664 <+256>:	movsx  eax,al
       0x08048667 <+259>:	test   eax,eax
       0x08048669 <+261>:	jne    0x8048678 <main+276>
       0x0804866b <+263>:	mov    eax,ds:0x8049aac
       0x08048670 <+268>:	mov    DWORD PTR [esp],eax
       0x08048673 <+271>:	call   0x8048420 <free@plt>
       0x08048678 <+276>:	lea    eax,[esp+0x20]
       0x0804867c <+280>:	mov    edx,eax
       0x0804867e <+282>:	mov    eax,0x8048825
       0x08048683 <+287>:	mov    ecx,0x6
       0x08048688 <+292>:	mov    esi,edx
       0x0804868a <+294>:	mov    edi,eax
       0x0804868c <+296>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
       0x0804868e <+298>:	seta   dl
       0x08048691 <+301>:	setb   al
       0x08048694 <+304>:	mov    ecx,edx
       0x08048696 <+306>:	sub    cl,al
       0x08048698 <+308>:	mov    eax,ecx
       0x0804869a <+310>:	movsx  eax,al
       0x0804869d <+313>:	test   eax,eax
       0x0804869f <+315>:	jne    0x80486b5 <main+337>
       0x080486a1 <+317>:	lea    eax,[esp+0x20]
       0x080486a5 <+321>:	add    eax,0x7
       0x080486a8 <+324>:	mov    DWORD PTR [esp],eax
       0x080486ab <+327>:	call   0x8048430 <strdup@plt>
       0x080486b0 <+332>:	mov    ds:0x8049ab0,eax
       0x080486b5 <+337>:	lea    eax,[esp+0x20]
       0x080486b9 <+341>:	mov    edx,eax
       0x080486bb <+343>:	mov    eax,0x804882d
       0x080486c0 <+348>:	mov    ecx,0x5
       0x080486c5 <+353>:	mov    esi,edx
       0x080486c7 <+355>:	mov    edi,eax
       0x080486c9 <+357>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
       0x080486cb <+359>:	seta   dl
       0x080486ce <+362>:	setb   al
       0x080486d1 <+365>:	mov    ecx,edx
       0x080486d3 <+367>:	sub    cl,al
       0x080486d5 <+369>:	mov    eax,ecx
       0x080486d7 <+371>:	movsx  eax,al
       0x080486da <+374>:	test   eax,eax
       0x080486dc <+376>:	jne    0x8048574 <main+16>
       0x080486e2 <+382>:	mov    eax,ds:0x8049aac
       0x080486e7 <+387>:	mov    eax,DWORD PTR [eax+0x20]
       0x080486ea <+390>:	test   eax,eax
       0x080486ec <+392>:	je     0x80486ff <main+411>
       0x080486ee <+394>:	mov    DWORD PTR [esp],0x8048833
       0x080486f5 <+401>:	call   0x8048480 <system@plt>
       0x080486fa <+406>:	jmp    0x8048574 <main+16>
       0x080486ff <+411>:	mov    eax,ds:0x8049aa0
       0x08048704 <+416>:	mov    edx,eax
       0x08048706 <+418>:	mov    eax,0x804883b
       0x0804870b <+423>:	mov    DWORD PTR [esp+0xc],edx
       0x0804870f <+427>:	mov    DWORD PTR [esp+0x8],0xa
       0x08048717 <+435>:	mov    DWORD PTR [esp+0x4],0x1
       0x0804871f <+443>:	mov    DWORD PTR [esp],eax
       0x08048722 <+446>:	call   0x8048450 <fwrite@plt>
       0x08048727 <+451>:	jmp    0x8048574 <main+16>
       0x0804872c <+456>:	nop
       0x0804872d <+457>:	mov    eax,0x0
       0x08048732 <+462>:	lea    esp,[ebp-0x8]
       0x08048735 <+465>:	pop    esi
       0x08048736 <+466>:	pop    edi
       0x08048737 <+467>:	pop    ebp
       0x08048738 <+468>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+8>
      - Initialisation de la mémoire:
        - push ebp sur la stack
        - déplace ebp sur le nouvel esp
        - push les [Destination et Source Indexes](https://stackoverflow.com/questions/1856320/purpose-of-esi-edi-registers) (EDI, ESI)
        - aligne la mémoire et libère 160 octects pour la stack<br/><br/>
    - <+14> ... <+16>
      - JMP à <+17>
      - No operation<br/><br/>
    - <+17> ... <+45>
      - Stocke dans ecx la valeur du data segment register 0x8049ab0
        - `x/s 0x8049ab0`
          ```asm
          0x8049ab0 <service>:	 ""
          ```
      - Stocke dans edx la valeur du data segment register 0x8049aac
        - `x/s 0x8049aac`
          ```asm
          0x8049aac <auth>:	 ""
          ```
      - Stocke la valeur à 0x8048810 dans eax
        - `x/s 0x8048810`
        ```asm
        0x8048810:	 "%p, %p \n"
        ```
      - Place ecx (la globale <service>) sur la stack (à esp + 8)
      - Place edx (la globale <auth>) sur la stack (à esp + 4)
      - Place eax ("%p, %p \n") sur la stack (à esp)
      - Call printf() avec les arguments stockés sur la stack (eax = printf("%p, %p \n", auth, service))<br/><br/>
    - <+50> ... <+74>
      - Stocke dans eax la valeur du data segment register 0x8049a80
        - `x/s 0x8049a80`
          ```asm
          0x8049a80 <stdin@@GLIBC_2.0>:	 ""
          ```
      - Place eax (<stdin>) sur la stack (à esp + 8)
      - Place 0x80 (128) sur la stack (à esp + 4)
      - Fait pointer eax sur esp + 32
      - Place eax (l'adresse de esp+32) sur la stack (à esp)
      - Call fgets avec les arguments stockés sur la stack (eax = fgets(&esp+32, 128, stdin))<br/><br/>
    - <+79> ... <+81>
      - Jump à <+456> si eax (le retour de fgets) vaut 0<br/><br/> <= Avec ce JMP à l'instruction No Op à <+456>, on sort de notre boucle infinie (cf plus bas)
    - <+87> ... <+126>
      - Fait pointer eax sur esp + 32
      - Copie eax (&esp+32) dans edx
      - Stocke la valeur à 0x8048819 dans eax
        - `x/s 0x8048819`
        ```asm
        0x8048819:	 "auth "
        ```
      - Stocke 0x5 (5) dans ecx
      - Stocke edx (le buffer a &esp + 32) dans esi (le source index)
      - Stocke eax ("auth ") dans edi (le destination index)
      - repz [cmps](https://www.tutorialspoint.com/assembly_programming/assembly_cmps_instruction.htm)
        - cmps effectue une comparaison bit à bit entre les deux uint_t pointés par uint_t *esi et uint_t *edi
        - le préfixe repz indique d'incrémenter esi et sdi et de refaire le cmps tant que les uint_t pointés sont égaux et que ecx-- est > 0, c'est grossièrement l'équivalent d'un strcnp
        - les fonctions seta (set if above) et setb (set if below) vont respectivement set dl et et al avec un booleen représentant l'écart au premier uint_t différent entre edi et esi
          - seta dl => dl = 1 if *esi > *edi else 0
          - setb al => al = 1 if *esi < *edi else 0
        - Stocke edx dans ecx (reset ecx to 5)
        - Soustrait al à cl
        - Stocke ecx (5) dans eax
        - Copie le contenu du registre 8 bits (al) dans le registre 32 bits (eax) avec une extension de signe
        - Conditional Jump if eax != 0 to <+222>
      - En C:
        ```c
        if (strncmp(input, "atuth ", 5) == 0) {
          [...]
        }
        <+222>
        ```<br/><br/>
    - <+128> ... <+196>
      - Stocke 0x4 (4) sur la stack (à esp)
      - Call malloc() avec l'argument stocké sur la stack (eax = malloc(4)) et l'assigne à la valeur du data segment register 0x8049aac
        - `x/s 0x8049aac`
          ```asm
          0x8049aac <auth>:	 ""
          ```
          (auth = malloc(4))
      - Stocke 0x0 (0) dans la valeur pointée par eax (auth[0] = 0)
      - Fait pointer eax sur esp + 32 (notre input)
      - ajoute 5 à eax (eax pointe sur input + 5)
      - Stocke 0xffffffff (-1) sur la stack (à esp + 28)
      - Stocke eax (&input+5) dans edx
      - Stocke 0x0 (0) dans eax
      - Stocke la valeur à esp + 28 (-1) dans ecx
      - Stocke edx (&input+5) dans edi
      - [repnz scas](https://stackoverflow.com/questions/26783797/repnz-scas-assembly-instruction-specifics) de edi (équivalent en C à ecx = strlen(edi))
      - Stocke ecx (strlen(input + 5)) dans eax
      - [bitwise not](https://www.felixcloutier.com/x86/not) sur eax et soustraction de 1
      - Compare eax avec 30
      - Conditional Jump if above, si eax > 30 jump à <+222>
      - En C:
        ```c
        if (strlen(input + 5) <= 30) {
          [...]
        }
        <+222>
        ```<br/><br/>
    - <+198> ... <+217>
      - Fait pointer eax sur esp + 32 (input)
      - Fait pointer edx sur eax + 5 (input + 5)
      - Stocke dans eax la valeur du data segment register 0x8049aac (<auth>)
      - Stocke edx (input + 5) sur la stack (à esp + 4)
      - Stocke eax (auth) sur la stack (à esp)
      - Call strcpy() avec les arguments stockés sur la stack (eax = strcpy(auth, input + 5))<br/><br/>
    - <+222> ... <+261>
      - Même principe que de <+128> ... <+217>: 
        - On compare les 5 premiers caractères de notre input avec la valeur à 0x804881f:
          - `x/s 0x804881f`
            ```
            0x804881f:	 "reset"
            ```
        - Puis on Jump conditionnellement à <+276> si eax (le résultat du strncmp) est différent de 0
        - En C:
          ```c
          if (strncmp(input, "reset", 5) == 0) {
            [...]
          }
          <+276>
          ```<br/><br/>
    - <+263> ... <+271>
      - Stocke dans eax la valeur du data segment register 0x8049aac (<auth>)
      - Stocke eax (auth) sur la stack (à esp)
      - Call free() avec l'argument stocké sur la stack (eax = free(auth))<br/><br/>
    - <+276> ... <+315>
      - Même principe que de <+128> ... <+217> et <+222> ... <+261>:
        - On compare les 6 premiers caractères de notre input avec la valeur à 0x8048825:
          - `x/s 0x8048825`
            ```
            0x8048825:	 "service"
            ```
        - Puis on Jump conditionnellement à <+337> si eax (le résultat du strncmp) est différent de 0
        - En C:
          ```c
          if (strncmp(input, "service", 6) == 0) {
            [...]
          }
          <+337>
          ```<br/><br/>
    - <+317> ... <+332>
      - Fait pointer eax sur esp +32 (input)
      - Ajoute 7 à eax (input + 7)
      - Stocke eax (input + 7) sur la stack (à esp)
      - Call strdup() avec l'argument stocké sur la stack (eax = strdup(input + 7))
      - Stocke eax dans le data segment register 0x8049ab0 (<service>)<br/><br/>
    - <+337> ... <+376>
      - Même principe que de <+128> ... <+217>, <+222> ... <+261> et <+276> ... <+315>:
        - On compare les 5 premiers caractères de notre input avec la valeur à 0x804882d:
          - `x/s 0x8048825`
            ```
            0x804882d:	 "login"
            ```
        - Puis on Jump conditionnellement à <+16> si eax (le résultat du strncmp) est différent de 0 <= Avec ce JMP à l'instruction No Op à <+16>, on crée une boucle infinie
        - En C:
          ```c
          if (strncmp(input, "login", 5) == 0) {
            [...]
          }
          <+16>
          ```<br/><br/>
    - <+382> ... <+392>
      - Stocke dans eax la valeur du data segment register 0x8049aac (<auth>)
      - Stocke dans eax la valeur à eax + 20 (auth[32])
      - Jump conditionnel à <+411> si eax == 0
      - En C:
        ```c
        if (auth[32] != 0) {
          [...]
        }
        <+ 411>
        ```
    - <+394> ... <+406>
      - Stocke la valeur à 0x8048833 sur la stack (à esp)
        - `x/s 0x8048833`
          ```
          0x8048833:	 "/bin/sh"
          ```
      - Call system() avec l'argument stocké sur la stack (eax = system("/bin/sh"))
      - Unconditional Jump a <+16>  <= Avec ce JMP à l'instruction No Op à <+16>, on crée une boucle infinie
    - <+411> ... <+451>
      - Stocke dans eax la valeur du data segment register 0x8049aa0
        - `x/s 0x8049aa0`
          ```
          0x8049aa0 <stdout@@GLIBC_2.0>:	 ""
          ```
      - Stocke eax (stdout) dans edx
      - Stocke la valeur à 0x804883b dans eax
        - `x/s 0x804883b`
          ```
          0x804883b:	 "Password:\n"
          ```
      - Stocke edx (stdout) sur la stack (à esp + 12)
      - Stocke 0xa (10) sur la stack (à esp + 8)
      - Stocke 0x1 (1) sur la stack (à esp + 4)
      - Stocke eax ("Password:\n") sur la stack (à esp)
      - Call fwrite() avec les les arguments stockés sur la stack (eax = fwrtite("Password:\n", 1, 10, stdout))
      - Unconditional Jump a <+16>
    - <+456> ... <+468>
      - No Operation
      - Stocke 0x0 (0) dans eax (la valeur qui sera return)
      - Réinitialisation de la mémoire, fin d'exécution
                                          
## Exploit
