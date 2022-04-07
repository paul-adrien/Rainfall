#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int m = 0;

int n(void) {
    char str[512];

    fgets(str, 512, stdin);
    p(str);
    if (m == 16930116) {
        system("/bin/cat /home/user/level5/.pass");
    };
    return(0);
}

int p(char *str) {
    printf(str);
    return(0);
}

int main(void) {
    n();
    return(0);
}