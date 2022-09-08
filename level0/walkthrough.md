## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0  
  [...]
  ```
  - On a un binaire appartenant a level1 dans le home avec les droits SUID

- `./level0`
  ```
    Segmentation fault (core dumped)
  ```
  - Le binaire Segfault sans argument

- `./level0 test`
  ```
    No !
  ```
  - Le binaire affiche "No !\n" avec un argument

- `gdb level0`
  - `set disassembly-flavor intel`
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x08048ec0 <+0>:	push   ebp
       0x08048ec1 <+1>:	mov    ebp,esp
       0x08048ec3 <+3>:	and    esp,0xfffffff0
       0x08048ec6 <+6>:	sub    esp,0x20
       0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
       0x08048ecc <+12>:	add    eax,0x4
       0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
       0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
       0x08048ed4 <+20>:	call   0x8049710 <atoi>
       0x08048ed9 <+25>:	cmp    eax,0x1a7
       0x08048ede <+30>:	jne    0x8048f58 <main+152>
       0x08048ee0 <+32>:	mov    DWORD PTR [esp],0x80c5348
       0x08048ee7 <+39>:	call   0x8050bf0 <strdup>
       0x08048eec <+44>:	mov    DWORD PTR [esp+0x10],eax
       0x08048ef0 <+48>:	mov    DWORD PTR [esp+0x14],0x0
       0x08048ef8 <+56>:	call   0x8054680 <getegid>
       0x08048efd <+61>:	mov    DWORD PTR [esp+0x1c],eax
       0x08048f01 <+65>:	call   0x8054670 <geteuid>
       0x08048f06 <+70>:	mov    DWORD PTR [esp+0x18],eax
       0x08048f0a <+74>:	mov    eax,DWORD PTR [esp+0x1c]
       0x08048f0e <+78>:	mov    DWORD PTR [esp+0x8],eax
       0x08048f12 <+82>:	mov    eax,DWORD PTR [esp+0x1c]
       0x08048f16 <+86>:	mov    DWORD PTR [esp+0x4],eax
       0x08048f1a <+90>:	mov    eax,DWORD PTR [esp+0x1c]
       0x08048f1e <+94>:	mov    DWORD PTR [esp],eax
       0x08048f21 <+97>:	call   0x8054700 <setresgid>
       0x08048f26 <+102>:	mov    eax,DWORD PTR [esp+0x18]
       0x08048f2a <+106>:	mov    DWORD PTR [esp+0x8],eax
       0x08048f2e <+110>:	mov    eax,DWORD PTR [esp+0x18]
       0x08048f32 <+114>:	mov    DWORD PTR [esp+0x4],eax
       0x08048f36 <+118>:	mov    eax,DWORD PTR [esp+0x18]
       0x08048f3a <+122>:	mov    DWORD PTR [esp],eax
       0x08048f3d <+125>:	call   0x8054690 <setresuid>
       0x08048f42 <+130>:	lea    eax,[esp+0x10]
       0x08048f46 <+134>:	mov    DWORD PTR [esp+0x4],eax
       0x08048f4a <+138>:	mov    DWORD PTR [esp],0x80c5348
       0x08048f51 <+145>:	call   0x8054640 <execv>
       0x08048f56 <+150>:	jmp    0x8048f80 <main+192>
       0x08048f58 <+152>:	mov    eax,ds:0x80ee170
       0x08048f5d <+157>:	mov    edx,eax
       0x08048f5f <+159>:	mov    eax,0x80c5350
       0x08048f64 <+164>:	mov    DWORD PTR [esp+0xc],edx
       0x08048f68 <+168>:	mov    DWORD PTR [esp+0x8],0x5
       0x08048f70 <+176>:	mov    DWORD PTR [esp+0x4],0x1
       0x08048f78 <+184>:	mov    DWORD PTR [esp],eax
       0x08048f7b <+187>:	call   0x804a230 <fwrite>
       0x08048f80 <+192>:	mov    eax,0x0
       0x08048f85 <+197>:	leave
       0x08048f86 <+198>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+6>
      - Initialisation de la mémoire (libère 32 octets pour la stack et aligne la mémoire)<br/><br/>
    - <+9> ... <+17>
      - Fait pointer eax sur argv[1] et stocke sa valeur dans esp<br/><br/>
    - <+20> ... <+30>
      - Call atoi() avec la valeur dans esp (argv[1]) et stocke son retour dans eax
      - Comparaison entre eax (le retour de atoi) et 0x1a7 (423)
      - Jump à <+152> si le cmp n'est pas vrai<br/><br/>
    - <+32> ... <+48>
      - Stocke l'adresse 0x80c5348 dans esp
        - `x/s 0x80c5348`
          - 0x80c5348:	 "/bin/sh"
            - esp contient l'adresse de "/bin/sh"
      - Call strdup avec la valeur à l'adresse de esp et stocke son retour dans eax
      - Stocke la valeur de eax (le retour de strdup) dans la stack (à esp + 16)
      - Stocke un pointeur NULL dans la stack (esp + 20)<br/><br/>
    - <+56> ... <+70>
      - Call getgid() et stocke son retour dans la stack (à esp + 28)
      - Call getuid() et stocke son retour dans la stack (à esp + 24)<br/><br/>
    - <+74> ... <+97>
      - Stocke la valeur à esp + 28 (le retour de getgid) plusieurs fois dans la stack (à esp, esp + 4 et esp + 8)
      - Call setresgid() avec les parametres stockés dans la stack<br/><br/>
    - <+102> ... <+125>
      - Stocke la valeur à esp + 24 (le retour de getuid) plusieurs fois dans la stack (à esp, esp + 4 et esp + 8)
      - Call setresgid() avec les parametres stockés dans la stack<br/><br/>
    - <+130> ... <+145>
      - Stocke l'adresse de esp + 16 dans eax
      - Stocke l'adresse de eax dans la stack (à esp + 4)
      - Stocke l'adresse 0x80c5348 (l'adresse de la string "/bin/sh") dans la stack (à esp)
      - Call execv() avec les parametres stockés la stack<br/><br/>
    - <+150>
      - Jump à <+192><br/><br/>
    - <+152> ... <+187>   (Jump conditionnel depuis <+30>)
      - Stocke la valeur du registre data segment à l'adresse 0x80c5348 dans eax, puis dans edx
        - `x/s 0x80c5348`
          - `0x80ee170 <stderr>:	 "\240\347\016\b@\350\016\b\340\350\016\b"`
      - Stocke la valeur à l'adresse 0x80c5350 dans eax
        - `x/s 0x80c5350`
          - `0x80c5350:	 "No !\n"`
      - Stocke la valeur de edx (stderr) dans la stack (à esp + 12)
      - Stocke 0x5 (5) dans la stack (à esp + 8)
      - Stocke 0x1 (1) dans la stack (à esp + 4)
      - Stocke la valeur de eax ("No !\n") dans la stack (à esp)
      - Call fwrite() avec les parametres stockés dans la stack<br/><br/>
    - <+192> ... <+198>   (Jump inconditionnel depuis <+150>)
      - réinitialisation de la mémoire, fin d'exécution<br/><br/>

On comprend donc que la fonction main attend un argument, va exécuter atoi dessus et lancer un shell si le retour d'atoi est égal à 423, sinon afficher "No !\n" sur la sortie d'erreur. Puisque le binaire à les droits SUID, le shell sera lancé en tant que level1.

## Exploit
- `./level0 423`
  - `whoami`
    ```
      level1
    ```

  - `cat /home/user/level1/.pass`
    ```
      1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
    ```
