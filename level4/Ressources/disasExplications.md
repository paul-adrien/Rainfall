(gdb) disas main
Dump of assembler code for function main:
   0x080484a7 <+0>:	push   ebp
   0x080484a8 <+1>:	mov    ebp,esp
   0x080484aa <+3>:	and    esp,0xfffffff0
   0x080484ad <+6>:	call   0x8048457 <n>
   0x080484b2 <+11>:	leave  
   0x080484b3 <+12>:	ret    
End of assembler dump.
(gdb) disas n
Dump of assembler code for function n:   
   0x08048457 <+0>:	push   ebp
   0x08048458 <+1>:	mov    ebp,esp
   0x0804845a <+3>:	sub    esp,0x218
   0x08048460 <+9>:	mov    eax,ds:0x8049804
   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x08048471 <+26>:	lea    eax,[ebp-0x208]
   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    eax,[ebp-0x208]
   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    eax,ds:0x8049810
   0x08048492 <+59>:	cmp    eax,0x1025544
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   0x080484a6 <+79>:	ret    
End of assembler dump.
(gdb) disas p
Dump of assembler code for function p:
   0x08048444 <+0>:	push   ebp
   0x08048445 <+1>:	mov    ebp,esp
   0x08048447 <+3>:	sub    esp,0x18
   0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
   0x0804844d <+9>:	mov    DWORD PTR [esp],eax
   0x08048450 <+12>:	call   0x8048340 <printf@plt>
   0x08048455 <+17>:	leave  
   0x08048456 <+18>:	ret  
End of assembler dump.


## MAIN:

#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# arrondissement de la pile du pointeur de la pile au mutltiple de 16 le plus proche
	and    esp,0xfffffff0

# appel de la fonction n
	call   0x8048457 <n>

# leave qui prepare la sortie d’une fonction en récupérant les variables enregistrées lors du début de la fonction afin de retrouver le contexte d’exécution tel qu’il avait été enregistré juste avant d’exécuter le code de la fonction, tout détruisant ce qu’il restait du stackframe et RET permet de finaliser le travail de LEAVE
	leave  
	ret  

## N

#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# on soustrait au registre 0x218 => 536 octet donc on agrandit la pile de 536 octets
	sub    esp,0x218

# récupertion de 0x8049804 dans la memoire du segment de donnée et du coup eax = stdin
	mov    eax,ds:0x8049804

(gdb) x/s 0x8049804
0x8049804 <stdin@@GLIBC_2.0>:	 ""

# initialisation des variables de fgets puis execution de cette dernière fgets(eax, OX200=512, stdin)
	mov    DWORD PTR [esp+0x8],eax
	mov    DWORD PTR [esp+0x4],0x200
	lea    eax,[ebp-0x208]
	mov    DWORD PTR [esp],eax
	call   0x8048350 <fgets@plt>

# appel de p(eax)
	lea    eax,[ebp-0x208]
	mov    DWORD PTR [esp],eax
	call   0x8048444 <p>

# récupération de la variable m puis comparé a 0x1025544 = 16930116 et si différent saut a n+78
	mov    eax,ds:0x8049810
	cmp    eax,0x1025544
	jne    0x80484a5 <n+78>

(gdb) x/s 0x8049810
0x8049810 <m>:	 ""

# récuperation de  "/bin/cat /home/user/level5/.pass" puis appel system avec cette string
	mov    DWORD PTR [esp],0x8048590
	call   0x8048360 <system@plt>
  
(gdb) x/s 0x8048590
0x8048590:	 "/bin/cat /home/user/level5/.pass"

# fin de la fonction
	leave  
	ret


## P

#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# alloue 24 octet, puis initialise la variable de printf et l'execute 
   0x08048447 <+3>:	sub    esp,0x18
   0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
   0x0804844d <+9>:	mov    DWORD PTR [esp],eax
   0x08048450 <+12>:	call   0x8048340 <printf@plt>

# fin de la fonction
   0x08048455 <+17>:	leave  
   0x08048456 <+18>:	ret    