## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 bonus0 users  6720 Mar  6  2016 level9
  [...]
  ```
    - On a un binaire appartenant a bonus0 dans le home avec les droits SUID.

- `./level9`
  ```
  ```
  - Avec ou sans arguments, le programme n'affiche rien.

- `./level9 $(python -c 'print "A" * 200')`
  ```
  Segmentation fault (core dumped)
  ```
  - SegFault avec une string de 200 (ou moins, on cherchera l'offset tout a l'heure)

- `gdb level9`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080485f4  main
    [...]
      0x080486f6  N::N(int)
      0x080486f6  N::N(int)
      0x0804870e  N::setAnnotation(char*)
      0x0804873a  N::operator+(N&)
      0x0804874e  N::operator-(N&)
    [...]
    ```
    - C'est du C++, on a une classe en plus du main contenant:
      - Un constructeur N(int)
      - Un setter setAnnotation(char *)
      - Deux surcharges d'opérateur pour le + et le - (operator+(N&) et operator-(N&))<br/><br/>
  - `disas main`
    ```asm
    Dump of assembler code for function main:
       0x080485f4 <+0>:	push   ebp
       0x080485f5 <+1>:	mov    ebp,esp
       0x080485f7 <+3>:	push   ebx
       0x080485f8 <+4>:	and    esp,0xfffffff0
       0x080485fb <+7>:	sub    esp,0x20
       0x080485fe <+10>:	cmp    DWORD PTR [ebp+0x8],0x1
       0x08048602 <+14>:	jg     0x8048610 <main+28>
       0x08048604 <+16>:	mov    DWORD PTR [esp],0x1
       0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
       0x08048610 <+28>:	mov    DWORD PTR [esp],0x6c
       0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
       0x0804861c <+40>:	mov    ebx,eax
       0x0804861e <+42>:	mov    DWORD PTR [esp+0x4],0x5
       0x08048626 <+50>:	mov    DWORD PTR [esp],ebx
       0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
       0x0804862e <+58>:	mov    DWORD PTR [esp+0x1c],ebx
       0x08048632 <+62>:	mov    DWORD PTR [esp],0x6c
       0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
       0x0804863e <+74>:	mov    ebx,eax
       0x08048640 <+76>:	mov    DWORD PTR [esp+0x4],0x6
       0x08048648 <+84>:	mov    DWORD PTR [esp],ebx
       0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
       0x08048650 <+92>:	mov    DWORD PTR [esp+0x18],ebx
       0x08048654 <+96>:	mov    eax,DWORD PTR [esp+0x1c]
       0x08048658 <+100>:	mov    DWORD PTR [esp+0x14],eax
       0x0804865c <+104>:	mov    eax,DWORD PTR [esp+0x18]
       0x08048660 <+108>:	mov    DWORD PTR [esp+0x10],eax
       0x08048664 <+112>:	mov    eax,DWORD PTR [ebp+0xc]
       0x08048667 <+115>:	add    eax,0x4
       0x0804866a <+118>:	mov    eax,DWORD PTR [eax]
       0x0804866c <+120>:	mov    DWORD PTR [esp+0x4],eax
       0x08048670 <+124>:	mov    eax,DWORD PTR [esp+0x14]
       0x08048674 <+128>:	mov    DWORD PTR [esp],eax
       0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
       0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
       0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
       0x08048682 <+142>:	mov    edx,DWORD PTR [eax]
       0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14]
       0x08048688 <+148>:	mov    DWORD PTR [esp+0x4],eax
       0x0804868c <+152>:	mov    eax,DWORD PTR [esp+0x10]
       0x08048690 <+156>:	mov    DWORD PTR [esp],eax
       0x08048693 <+159>:	call   edx
       0x08048695 <+161>:	mov    ebx,DWORD PTR [ebp-0x4]
       0x08048698 <+164>:	leave
       0x08048699 <+165>:	ret
    End of assembler dump.
    ```
    - <+0> ... <+7>
      - Initialisation de le mémoire, libère 32 octets pour la stack et aligne la mémoire<br/><br/>
    - <+10> ... <+23>
      - Compare ebp + 8 (argc) avec 0x1 (1)
      - Conditional Jump if Greater: si argc > 1, jump a <main +28>, sinon:
        - Stocke 0x1 (1) sur la stack (à esp)
        - Call _exit() avec l'argument placé sur la stack (eax = _exit(1))<br/><br/>
    - <+28> ... <+58>
      - Stocke 0x6c (108) sur la stack (à esp)
      - Call _Znwj ([new()](https://reverseengineering.stackexchange.com/questions/4402/what-is-operator-newunsigned-int)) avec les arguments sur la stack (eax = new(108)) => C'est la taille allouée pour une instance de N.
      - Stocke eax (le retour du new) dans ebx
      - Stocke 0x5 (5) sur la stack (à esp + 4)
      - Stocke ebx (le retour du new) sur la stack (à esp)
      - Call _ZN1NC2Ei() (le constructeur) avec les arguments placés sur la stack (a = new N(5))
      - Stocke ebx (l'instance N qu'on vient de créer) sur la stack (à esp + 28)<br/><br/>
    - <+62> ... <+87>
      - Stocke 0x6c (108) sur la stack (à esp)
      - Call new() avec l'argument stocké sur la stack (eax = new(108))
      - Copie eax (le retour de new) dans ebx
      - Stocke 0x6 (6) sur la stack (à esp + 4)
      - Stocke ebx (le retour du new) sur la stack (à esp)
      - Call le constructeur avec les arguments placés sur la stack (b = new N(6))
      - Stocke ebx (l'instance N qu'on vient de créer) sur la stack (à esp + 24)<br/><br/>
    - <+96> ... <+108>
      - Stocke la valeur à esp + 28 (N(5)) dans eax
      - Fait pointer eax sur esp + 28 (a = N(5))
      - Stocke eax (le pointeur sur a) sur la stack (à esp + 20)
      - Fait pointer eax sur esp + 24 (b = N(6))
      - Stocke eax (le pointeur sur b) sur la stack (à esp + 16)<br/><br/>
    - <+112> ... <+131>
      - Stocke ebp + 12 (&argv) dans eax
      - ajoute 4 à eax pour pointer sur argv[1]
      - Stocke la valeur à l'adresse de eax (argv[1]) dans eax
      - Stocke eax (argv[1]) sur la stack (à esp + 4)
      - Récupère esp + 20 (le pointeur sur a) dans eax et le stocke sur la stack (à esp)
      - Call _ZN1N13setAnnotationEPc (N::setAnnotation) avec les arguments placés sur la stack:
        - setAnnotation(&a, argv[1]) => a->setAnnotation(argv[1])<br/><br/>
    - <+136> ... <+159>
      - Stocke esp + 16 (b_ptr) dans eax
      - Déréférence eax et stocke le résultat dans eax (eax = *b_ptr = N(6))
      - Déréférence eax et stocke le résultat dans edx 
        - edx pointe sur la prèmiere méthode dans la virtual table: operator+()
      - Stocke esp + 20 (a_ptr) dans eax
      - Stocke eax (&a) sur la stack (à esp + 4)
      - Stocke esp + 16 (b_ptr) dans eax
      - Stocke eax (&b) sur la stack (à esp)
      - Call edx avec les arguments placés sur la stack
        - (operator+(&b, &a)) = b->operator+(&a) = b + a
      - Stocke a (ebp - 4 = esp + 32 - 4 = esp + 28)dans ebx<br/><br/>
    - <+161> ... <+165>
      - return eax (b + a)
      - réinitialisation de la mémoire, fin d'exécution<br/><br/>
   
  - `disas 'N::N(int)`
    ```asm
    Dump of assembler code for function _ZN1NC2Ei:
       0x080486f6 <+0>:	push   ebp
       0x080486f7 <+1>:	mov    ebp,esp
       0x080486f9 <+3>:	mov    eax,DWORD PTR [ebp+0x8]
       0x080486fc <+6>:	mov    DWORD PTR [eax],0x8048848
       0x08048702 <+12>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048705 <+15>:	mov    edx,DWORD PTR [ebp+0xc]
       0x08048708 <+18>:	mov    DWORD PTR [eax+0x68],edx
       0x0804870b <+21>:	pop    ebp
       0x0804870c <+22>:	ret
    End of assembler dump.
    ```
    - Set this->operator+ comme la premiere entrée de la [virtualtable](https://en.wikipedia.org/wiki/Virtual_method_table#Multiple_inheritance_and_thunks)
    - assigne argv[1] a la première property (&argv + 68) => this->value = argv[1]
  - `disas 'N::setAnnotation(char*)'`
    ```asm
    Dump of assembler code for function _ZN1N13setAnnotationEPc:
       0x0804870e <+0>:	push   ebp
       0x0804870f <+1>:	mov    ebp,esp
       0x08048711 <+3>:	sub    esp,0x18
       0x08048714 <+6>:	mov    eax,DWORD PTR [ebp+0xc]
       0x08048717 <+9>:	mov    DWORD PTR [esp],eax
       0x0804871a <+12>:	call   0x8048520 <strlen@plt>
       0x0804871f <+17>:	mov    edx,DWORD PTR [ebp+0x8]
       0x08048722 <+20>:	add    edx,0x4
       0x08048725 <+23>:	mov    DWORD PTR [esp+0x8],eax
       0x08048729 <+27>:	mov    eax,DWORD PTR [ebp+0xc]
       0x0804872c <+30>:	mov    DWORD PTR [esp+0x4],eax
       0x08048730 <+34>:	mov    DWORD PTR [esp],edx
       0x08048733 <+37>:	call   0x8048510 <memcpy@plt>
       0x08048738 <+42>:	leave
       0x08048739 <+43>:	ret
    End of assembler dump.
    ```
  - `disas 'N::operator+(N&)'`
    ```asm
    Dump of assembler code for function _ZN1NplERS_:
       0x0804873a <+0>:	push   ebp
       0x0804873b <+1>:	mov    ebp,esp
       0x0804873d <+3>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048740 <+6>:	mov    edx,DWORD PTR [eax+0x68]
       0x08048743 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
       0x08048746 <+12>:	mov    eax,DWORD PTR [eax+0x68]
       0x08048749 <+15>:	add    eax,edx
       0x0804874b <+17>:	pop    ebp
       0x0804874c <+18>:	ret
    End of assembler dump.
    ```
    - return (&argv + 68) + (&argv1 + 68) == this->value + argv[1]->value
  - `disas 'N::operator-(N&)'`
    ```asm
    Dump of assembler code for function _ZN1NmiERS_:
       0x0804874e <+0>:	push   ebp
       0x0804874f <+1>:	mov    ebp,esp
       0x08048751 <+3>:	mov    eax,DWORD PTR [ebp+0x8]
       0x08048754 <+6>:	mov    edx,DWORD PTR [eax+0x68]
       0x08048757 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
       0x0804875a <+12>:	mov    eax,DWORD PTR [eax+0x68]
       0x0804875d <+15>:	mov    ecx,edx
       0x0804875f <+17>:	sub    ecx,eax
       0x08048761 <+19>:	mov    eax,ecx
       0x08048763 <+21>:	pop    ebp
       0x08048764 <+22>:	ret
    End of assembler dump.
    ```
    - return (&argv + 68) - (&argv1 + 68) == this->value - argv[1]->value
