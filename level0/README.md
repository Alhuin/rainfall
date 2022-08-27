- `$ ls -la`
  ```
  [...]
    -rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
  [...]
  ```
  - On a un binaire appartenant a level1 dans le home
 
- `$ ./level0`
  ```
    Segmentation fault (core dumped)
  ```

- `$ ./level0 test`
  ```
    No !
  ```

- `$ gdb level0`
  - `$ disas main`
    ```
      Dump of assembler code for function main:
    [...]
      0x08048ed4 <+20>:	call   0x8049710 <atoi>
      0x08048ed9 <+25>:	cmp    $0x1a7,%eax
    [...]
    ```
    - On a un call a atoi, puis un call a cmp avec le résultat et 0x1a7 (423)

- `$ ./level0 423`
  - `$ whoami`
  ```
    level1
  ```
