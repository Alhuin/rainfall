## Analyse

- `ls -la`
  ```
  [...]
    -rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
  [...]
  ```
    - On a un binaire appartenant a level3 dans le home avec les droits SUID.

- `./level2`
  ```
    
  ```
  - Le programme attend un input
    - `test`
      - `test`
    - Le programme affiche le paramètre qu'on lui donne

- `gdb level2`
  - `set disassembly-flavor intel`
  - `info function`
    ```asm
    [...]
      0x080484b0  frame_dummy
      0x080484d4  p
      0x0804853f  main
    [...]
    ```
