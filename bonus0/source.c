#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char		*p(char *buffer, char *str)
{
	char	buffer2[4096];

	puts (str);
	read(0, buffer2, 4096);
	*strchr(buffer2, '\n') = 0; // car 10 en ascii correspond a une fin de ligne
	return (strncpy(buffer, buffer2, 20));
}

char			*pp(char *buffer)
{
	char		buffer1[20];
	char		buffer2[20];

	p(buffer1, " - ");
	p(buffer2, " - ");
	strcpy(buffer, buffer1);
	buffer[strlen(buffer)] = ' ';
	return (strcat(buffer, buffer2));
}

int			main(void)
{
	char	buffer[42];

	pp(buffer);
	puts(buffer);
	return (0);
}