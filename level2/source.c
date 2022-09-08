#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *p() {
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
    return(strdup(buffer));
}

int main() {
    p();
    return(0);
}
