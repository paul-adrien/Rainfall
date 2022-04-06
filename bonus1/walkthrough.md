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
