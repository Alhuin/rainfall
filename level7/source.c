#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char c[68];

void m(void) {
  printf("%s - %d\n", c, time(0));
}

int main(int argc, char **argv) {
  int *a;
  int *b;
  
  a = malloc(8);
  b = malloc(8);
  a[0] = 1;
  a[1] = malloc(8);
  b[0] = 2;
  b[1] = malloc(8);

  /*    Debugging for the walkthrough
  printf("\na\t(%p)\t=\t%p\na[0]\t(%p)\t=\t%d\na[1]\t(%p)\t=\t%p\n\n", &a, a, &a[0], a[0], &a[1], a[1]);
  printf("\nb\t(%p)\t=\t%p\nb[0]\t(%p)\t=\t%d\nb[1]\t(%p)\t=\t%p\n\n", &b, b, &b[0], b[0], &b[1], b[1]);
  printf("strcpy(%p, %s)\n", a[1], av[1]);
  */
  strcpy(a[1], argv[1]);

  /*
  printf("\na\t(%p)\t=\t%p\na[0]\t(%p)\t=\t%d\na[1]\t(%p)\t=\t%p\n\n", &a, a, &a[0], a[0], &a[1], a[1]);
  printf("\nb\t(%p)\t=\t%p\nb[0]\t(%p)\t=\t%d\nb[1]\t(%p)\t=\t%p\n\n", &b, b, &b[0], b[0], &b[1], b[1]);
  printf("strcpy(%p, %s)\n", a[1], av[1]);
  strcpy(b[1], argv[2]);
  */

  fgets(c, 68, fopen("/home/user/level8/.pass", "r"));
  puts("~~");
  
  return(0);
}
