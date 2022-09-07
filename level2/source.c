#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p() {
    char buffer[76]
    void *eip;

    fflush(stdout);
    gets(buffer)
    eip = __builtin_return_address(0);
    if ((eip & 0xb0000000) == 0xb0000000) {
        printf("%p\n", eip);
        exit(1);
    }
    puts(buffer);
    strdup(buffer);
}

int main(int argc, char **argv) {
    p();
    return 0;
}