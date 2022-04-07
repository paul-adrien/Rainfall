#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int language = 0;

void	greetuser(char *buffer) {
	char buffer2[64]; // 0x48 - 8 les deux variables dans la pile

	if (language == 1) {
		strcpy(buffer, "Hyvää päivää ");
	} else if (language == 2) {
		strcpy(buffer, "Goedemiddag ");
	} else if (language == 0) {
		strcpy(buffer, "Hello ");
	}
	strcat(buffer2, buffer);
	puts(buffer2);
}

int			main(int ac, char **av) {
	char	buffer[72]; // 2 strncpy de 40 et 32
	char	*LANG;

	if (ac != 3) {
		return (1);
	}

	memset(buffer, 0, 76);
	strncpy(buffer, av[1], 40);
	strncpy(buffer, av[2], 32);
	LANG = getenv("LANG");
	if (LANG != 0) {
		if (memcmp(LANG, "fi", 2) == 0) {
			language = 1;
		} else if (memcmp(LANG, "nl", 2) == 0) {
			language = 2;
		}
	}
	greetuser(buffer);
	return (0);
}