#bonus3

$ ./bonus3
$ ./bonus3 test
$ ./bonus3 test test

Apres une analyse avec gdb du main, on obtient les informations suivantes:

Le programme a besoin d'un argument minimum, le programme lit aussi aussi le fichier .pass pour le niveau suivant et le stocke dans un buffer avec un fread().

Après le programme appel atoi() avec le av[1] et utilise le resultat pour index du buffer et insert un byte null.

Après le programme fait une comparaison entre le buffer et av[1] et si c'est égale, il appelle un shell.

Tout simplement si on envoie une chaine vide, atoi va retourner 0 donc mettre remplacer le premier byte du buffer par un byte null donc le buffer sera une chaine vide.
On obtient donc un buffer egale a av[1].

$ ./bonus3 ""
$ whoami
$ end
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
