#include <stdio.h>

void run() {
    fwrite("Good... Wait what?\n", 19, 1, stdout);
    system("/bin/sh");
    return();
}

int main() {
    char str[76];

    gets(str);
    return(0);
}
