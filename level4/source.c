#include <stdio.h>
#include <stdlib.h>

int m = 0;

int p(char *buffer)
{
	printf(buffer);
	return (0);
}

int n()
{
	char	buffer[520];

	fgets(buffer, 512, stdin);
	p(buffer);
	if (m == 16930116) {
    system("/bin/cat /home/user/level5/.pass");
  }
	return (0);
}

int main(int argc, char **argv)
{
	n();
	return (0);
}
