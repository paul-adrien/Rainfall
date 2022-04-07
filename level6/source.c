#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void m(void) {
	puts("Nope");
}

void n(void) {
	system("/bin/cat /home/user/level7/.pass");
}

int main(int ac, char **av) {
    char *cpy;
    int *func;
    
    cpy = malloc(64);
    func = malloc(4);

    *func = (void *)m;
    strcpy(cpy, av[1]);

    int (*func)();
    return (0);
}