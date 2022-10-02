## Analyse
- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 end    users  5595 Mar  6  2016 bonus3
  [...]
  ```
  - On a un binaire appartenant a end dans le home avec les droits SUID.

- `./bonus3`
  ```
  Segmentation fault (core dumped)
  ```
  - Le programme se termine sans rien afficher sans arguments, ou avec plus d'un argument

- `./bonus3 test`
  ```
  
  ```
  - Le programme affiche une ligne vide avec un argument


- `./bonus3 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`
  ```
  
  ```
  - Pas de segfault sur argv[1] en vue

- `gdb bonus3`
  - `set disassembly-flavor intel`
  - `info function`
    ```
    [...]
      0x080484f4  main
    [...]
    ```
    - On ne trouve rien d'autre que la fonction main

  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x080484f4 <+0>:	push   ebp
       0x080484f5 <+1>:	mov    ebp,esp
       0x080484f7 <+3>:	push   edi
       0x080484f8 <+4>:	push   ebx
       0x080484f9 <+5>:	and    esp,0xfffffff0
       0x080484fc <+8>:	sub    esp,0xa0
       0x08048502 <+14>:	mov    edx,0x80486f0
       0x08048507 <+19>:	mov    eax,0x80486f2
       0x0804850c <+24>:	mov    DWORD PTR [esp+0x4],edx
       0x08048510 <+28>:	mov    DWORD PTR [esp],eax
       0x08048513 <+31>:	call   0x8048410 <fopen@plt>
       0x08048518 <+36>:	mov    DWORD PTR [esp+0x9c],eax
       0x0804851f <+43>:	lea    ebx,[esp+0x18]
       0x08048523 <+47>:	mov    eax,0x0
       0x08048528 <+52>:	mov    edx,0x21
       0x0804852d <+57>:	mov    edi,ebx
       0x0804852f <+59>:	mov    ecx,edx
       0x08048531 <+61>:	rep stos DWORD PTR es:[edi],eax
       0x08048533 <+63>:	cmp    DWORD PTR [esp+0x9c],0x0
       0x0804853b <+71>:	je     0x8048543 <main+79>
       0x0804853d <+73>:	cmp    DWORD PTR [ebp+0x8],0x2
       0x08048541 <+77>:	je     0x804854d <main+89>
       0x08048543 <+79>:	mov    eax,0xffffffff
       0x08048548 <+84>:	jmp    0x8048615 <main+289>
       0x0804854d <+89>:	lea    eax,[esp+0x18]
       0x08048551 <+93>:	mov    edx,DWORD PTR [esp+0x9c]
       0x08048558 <+100>:	mov    DWORD PTR [esp+0xc],edx
       0x0804855c <+104>:	mov    DWORD PTR [esp+0x8],0x42
       0x08048564 <+112>:	mov    DWORD PTR [esp+0x4],0x1
       0x0804856c <+120>:	mov    DWORD PTR [esp],eax
       0x0804856f <+123>:	call   0x80483d0 <fread@plt>
       0x08048574 <+128>:	mov    BYTE PTR [esp+0x59],0x0
       0x08048579 <+133>:	mov    eax,DWORD PTR [ebp+0xc]
       0x0804857c <+136>:	add    eax,0x4
       0x0804857f <+139>:	mov    eax,DWORD PTR [eax]
       0x08048581 <+141>:	mov    DWORD PTR [esp],eax
       0x08048584 <+144>:	call   0x8048430 <atoi@plt>
       0x08048589 <+149>:	mov    BYTE PTR [esp+eax*1+0x18],0x0
       0x0804858e <+154>:	lea    eax,[esp+0x18]
       0x08048592 <+158>:	lea    edx,[eax+0x42]
       0x08048595 <+161>:	mov    eax,DWORD PTR [esp+0x9c]
       0x0804859c <+168>:	mov    DWORD PTR [esp+0xc],eax
       0x080485a0 <+172>:	mov    DWORD PTR [esp+0x8],0x41
       0x080485a8 <+180>:	mov    DWORD PTR [esp+0x4],0x1
       0x080485b0 <+188>:	mov    DWORD PTR [esp],edx
       0x080485b3 <+191>:	call   0x80483d0 <fread@plt>
       0x080485b8 <+196>:	mov    eax,DWORD PTR [esp+0x9c]
       0x080485bf <+203>:	mov    DWORD PTR [esp],eax
       0x080485c2 <+206>:	call   0x80483c0 <fclose@plt>
       0x080485c7 <+211>:	mov    eax,DWORD PTR [ebp+0xc]
       0x080485ca <+214>:	add    eax,0x4
       0x080485cd <+217>:	mov    eax,DWORD PTR [eax]
       0x080485cf <+219>:	mov    DWORD PTR [esp+0x4],eax
       0x080485d3 <+223>:	lea    eax,[esp+0x18]
       0x080485d7 <+227>:	mov    DWORD PTR [esp],eax
       0x080485da <+230>:	call   0x80483b0 <strcmp@plt>
       0x080485df <+235>:	test   eax,eax
       0x080485e1 <+237>:	jne    0x8048601 <main+269>
       0x080485e3 <+239>:	mov    DWORD PTR [esp+0x8],0x0
       0x080485eb <+247>:	mov    DWORD PTR [esp+0x4],0x8048707
       0x080485f3 <+255>:	mov    DWORD PTR [esp],0x804870a
       0x080485fa <+262>:	call   0x8048420 <execl@plt>
       0x080485ff <+267>:	jmp    0x8048610 <main+284>
       0x08048601 <+269>:	lea    eax,[esp+0x18]
       0x08048605 <+273>:	add    eax,0x42
       0x08048608 <+276>:	mov    DWORD PTR [esp],eax
       0x0804860b <+279>:	call   0x80483e0 <puts@plt>
       0x08048610 <+284>:	mov    eax,0x0
       0x08048615 <+289>:	lea    esp,[ebp-0x8]
       0x08048618 <+292>:	pop    ebx
       0x08048619 <+293>:	pop    edi
       0x0804861a <+294>:	pop    ebp
       0x0804861b <+295>:	ret
    End of assembler dump.
    ```

  - <+0> ... <+8>
    - Initialisation de la mémoire (libère 160 octets pour la stack), alignement de la mémoire<br/><br/>
  - <+14> ... <+31>
    - Stocke la valeur à 0x80486f0 dans edx
      - `x/s 0x80486f0`
        ```
        0x80486f0:	 "r"
        ```
    - Stocke la valeur à 0x80486f2 dans eax
      - `x/s 0x80486f2`
        ```
        0x80486f2:	 "/home/user/end/.pass"
        ```
    - Place edx sur la stack (à esp + 4)
    - Place eax sur la stack (à esp)
    - Call fopen() avec les arguments placés sur la stack (eax = fopen("/home/user/end/.pass", "r"))<br/><br/>
  - <+36> ... <+61>
    - Stocke eax (le retour du fopen()) sur la stack (à esp + 156)
    - Fait pointer ebx sur esp + 24
    - Stocke 0x0 (0) dans eax
    - Stocke 0x21 (33) dans edx
    - Stocke ebx (buffer à esp + 24) dans edi
    - Stocke edx (33) dans ecx
    - [Rep stos](https://stackoverflow.com/questions/3818856/what-does-the-rep-stos-x86-assembly-instruction-sequence-do)
      - This is similar to a memset:
        > For ecx repetitions, stores the contents of eax into where edi points to, incrementing or decrementing edi (depending on the direction flag) by 4 bytes each time. Normally, this is used for a memset-type operation.
      - edx = 33, donc cette instruction va écrire 132 (33 * 4) 0 where edi is pointing (buffer à esp + 24)
        - memset(buffer, 0, 132)<br/><br/>
    - <+63> ... <+77>
      - Compare 0 avec esp + 156 (le retour du fopen(), appelons le fd)
      - Jump conditionnel à +79 si fopen("/home/user/end/.pass", "r") == 0
      - Compare 2 avec ebp + 8 (argc)
      - Jump conditionnel à +89 si argc == 2<br/><br/>
    - <+79> ... <+84>
      - Stocke 0xffffffff (-1) dans eax   <= conditional jump depuis +71
      - Jump inconditionnel à +289<br/><br/>
    - <+89> ... <+123>
      - Fait pointer eax sur esp + 24 (buffer)
      - Stocke esp + 156 (fd) dans edx
      - Place edx sur la stack (à esp + 12)
      - Place 0x42 (66) sur la stack (à esp + 8)
      - Place 0x1 (1) sur la stack (à esp + 4)
      - Place eax (buffer) sur la stack (à esp)
      - Call fread() avec les arguments placés sur la stack (eax = fread(buffer, 1, 66, fd)))<br/><br/>
    - <+128> ... <+144>
      - Stocke 0x0 (0) à esp + 89 (buffer[65 (89 - 24)] = 0)
      - Stocke ebp + 12 (&argc) dans eax
      - Add 4 à eax (&argv[1])
      - Place la valeur à argv[1] dans eax
      - Place eax sur la stack (à esp)
      - Call atoi() avec l'argument placé sur la stack (eax = atoi(argv[1]))<br/><br/>
    - <+149> ... <+191>
      - Stocke 0x0 (0) à esp (ebp - 160) + eax (le retour du atoi) * 1 + 0x18 (24) 
        - ebp - 136 + argv[1] = 0
        - esp + 24 + argv[1] = 0
        - buffer[argv[1]] = 0
      - Fait pointer eax sur esp + 24 (buffer)
      - Fait pointer edx sur eax + 66 (buffer + 66)
      - Stocke esp + 156 (fd) dans eax
      - Place eax sur la stack (à esp + 12)
      - Place 0x41 (65) sur la stack (à esp + 8)
      - Place 0x1 (1) sur la stack (à esp + 4)
      - Place edx (buffer + 66)
      - Call fread() avec les arguments placés sur la stack (eax = fread(buffer + 66, 1, 65, fd))<br/><br/>
    - <+196> ... <+206>
      - Stocke esp + 156 (fd) dans eax
      - Place eax (fd) sur la stack (à esp)
      - Call fclose() avec l'argument placé sur la stack (fclose(fd))<br/><br/>
    - <+211> ... <+230>
      - Stocke ebp + 12 (&argv) dans eax
      - Add 4 à eax (&argv[1])
      - Stocke la valeur a eax dans eax
      - Place eax sur la stack (à esp + 4)
      - Fait pointer eax sur esp + 24 (buffer)
      - Place eax (buffer) sur la stack (à esp)
      - Call strcmp() avec les arguments placés sur la stack (eax = strcmp(buffer, argv[1]))<br/><br/>
    - <+235> ... <+262>
      - Check if eax (le retour du strcmp) == 0
      - Conditional jump à +269 si eax !== 0
      - Place 0x0 (0) sur la stack (à esp + 8)
      - Place la valeur à 0x8048707 sur la stack (à esp + 4)
        - `x/s 0x8048707`
          ```
          0x8048707:	 "sh"
          ```
      - Place la valeur à 0x804870a sur la stack (à esp)
        - `x/s 0x804870a`
          ```
          0x804870a:	 "/bin/sh"
          ```
      - Call execl() avec les arguments placés sur la stack (eax = execl("/bin/sh", "sh", NULL))<br/><br/>
    - <+267> ... <+279>
      - Unconditional Jump à +284
      - Fait pointer eax sur esp + 24 (buffer)
      - Add 0x42 (66) à eax (eax = buffer[66])
      - Place la valeur à eax sur la stack (à esp)
      - Call puts avec l'argument placé sur la stack (eax = puts(buffer[66]))<br/><br/>
  - <+284>...<+295>
    - Stocke 0x0 (0) dans eax
    - Return eax (0)
    - Réinitialisation de la mémoire, fin d'exécution<br/><br/>
## Exploit
