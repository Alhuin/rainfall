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
  
  strcpy(a[1], argv[1]);
  strcpy(b[1], argv[2]);
  
  fgets(c, 68, fopen("/home/user/level8/.pass", "r"));
  return(0);
}
