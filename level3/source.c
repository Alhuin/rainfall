#include <stdio.h>
#include <stdlib.h>

int		m = 0;

int		v()
{
	char	buffer[520];

	fgets(buffer, 512, stdin);
	printf(buffer);
	if (m == 64)
	{
		fwrite("Wait what?!\n", 12, 1, stdout);
		system("/bin/sh");
	}
	return (0);
}

int		main(int argc, char **argv)
{
	v();
	return (0);
}
