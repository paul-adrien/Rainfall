#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int p(void) {
    char            str[76];
    void            *ptr;

    fflush(stdout);
    gets(str);
    if (((unsigned int)ptr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", ptr);
        exit(1);
    }
    puts(str);
    strdup(str);
}

int main(void) {
    p();
}