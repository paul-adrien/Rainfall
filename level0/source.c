#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av) {
    char *args[2];
    int n = atoi(av[0]);

    if (n == 423) {
        args[0] = strdup("/bin/sh");
        args[1] = 0;

        gid_t gid = getgid();
        uid_t uid = getuid();

        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);

        execv("/bin/sh", args);
    } else {
        fwrite("NO !\n", 1, 5, stderr);
    }
    return (0);
}