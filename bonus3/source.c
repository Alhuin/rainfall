#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int ret;
  char buffer;
  int fd = fopen("home/user/end/.pass", "r");
  
  memset(buffer, 0, 132);
  
  if (fd == 0)
    return(-1);
  
  if (argc == 2) {
    fread(buffer, 1, 66, fd);
    buffer[65] = 0;
    buffer[atoi(argv[1])] = 0;
    fread(buffer + 66, 1, 65, fd);
    fclose(fd);
  
    if (strcmp(buffer, argv[1])
      execl("/bin/sh", "sh", null)
    else
      puts(buffer[66])
  }
  
  return (0);  
}, 
