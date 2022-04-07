Dump of assembler code for function main:
   0x0804847c <+0>:	push   ebp
   0x0804847d <+1>:	mov    ebp,esp
   0x0804847f <+3>:	and    esp,0xfffffff0
   0x08048482 <+6>:	sub    esp,0x20
   0x08048485 <+9>:	mov    DWORD PTR [esp],0x40
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    DWORD PTR [esp+0x1c],eax
   0x08048495 <+25>:	mov    DWORD PTR [esp],0x4
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    DWORD PTR [esp+0x18],eax
   0x080484a5 <+41>:	mov    edx,0x8048468
   0x080484aa <+46>:	mov    eax,DWORD PTR [esp+0x18]
   0x080484ae <+50>:	mov    DWORD PTR [eax],edx
   0x080484b0 <+52>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080484b3 <+55>:	add    eax,0x4
   0x080484b6 <+58>:	mov    eax,DWORD PTR [eax]
   0x080484b8 <+60>:	mov    edx,eax
   0x080484ba <+62>:	mov    eax,DWORD PTR [esp+0x1c]
   0x080484be <+66>:	mov    DWORD PTR [esp+0x4],edx
   0x080484c2 <+70>:	mov    DWORD PTR [esp],eax
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    eax,DWORD PTR [esp+0x18]
   0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
   0x080484d0 <+84>:	call   eax
   0x080484d2 <+86>:	leave  
   0x080484d3 <+87>:	ret    
End of assembler dump.
(gdb) disas n
Dump of assembler code for function n:
   0x08048454 <+0>:	push   ebp
   0x08048455 <+1>:	mov    ebp,esp
   0x08048457 <+3>:	sub    esp,0x18
   0x0804845a <+6>:	mov    DWORD PTR [esp],0x80485b0
   0x08048461 <+13>:	call   0x8048370 <system@plt>
   0x08048466 <+18>:	leave  
   0x08048467 <+19>:	ret    
End of assembler dump.
(gdb) disas m
Dump of assembler code for function m:
   0x08048468 <+0>:	push   ebp
   0x08048469 <+1>:	mov    ebp,esp
   0x0804846b <+3>:	sub    esp,0x18
   0x0804846e <+6>:	mov    DWORD PTR [esp],0x80485d1
   0x08048475 <+13>:	call   0x8048360 <puts@plt>
   0x0804847a <+18>:	leave  
   0x0804847b <+19>:	ret    
End of assembler dump.


#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# arrondissement de la pile du pointeur de la pile au mutltiple de 16 le plus proche
	and    esp,0xfffffff0

# on soustrait au registre 0x20 => 32 octet donc on agrandit la pile de 32 octets
	sub    esp,0x20

# alloue avec malloc 64 octets et stock la valeur de retour à [esp+0x1c] qui correspond a esp + 28 (28/4=7eme place de la pile)
	mov    DWORD PTR [esp],0x40
	call   0x8048350 <malloc@plt>
	mov    DWORD PTR [esp+0x1c],eax

# alloue avec malloc 4 octets et stock la valeur de retour à [esp+0x1c] qui correspond a esp + 24 (24/4=6eme place de la pile)
	mov    DWORD PTR [esp],0x4
	call   0x8048350 <malloc@plt>
	mov    DWORD PTR [esp+0x18],eax

# recupere l'adresse de m()
	mov    edx,0x8048468

x/s 0x8048468
0x8048468 <m>:	 "..."

# eax pointe sur [esp+0x18] puis eax pointe sur edx donc sur m() 
	mov    eax,DWORD PTR [esp+0x18]
	mov    DWORD PTR [eax],edx

# on recupere argv et on prend av[1] (+ 4 => passage au suivant) et eax pointe sur av[1] puis edx pointe sur av[1]
	mov    eax,DWORD PTR [ebp+0xc]
	add    eax,0x4
	mov    eax,DWORD PTR [eax]
   mov    edx,eax

# on recupere le pointeur du retour du malloc 64 dans eax
	mov    eax,DWORD PTR [esp+0x1c]

# edx = av[1] et eax = malloc 64 sont initialisé pour ensuite être utiliser dasn strcpy -> strcpy(malloc(64), av[1])
	mov    DWORD PTR [esp+0x4],edx
	mov    DWORD PTR [esp],eax
	call   0x8048340 <strcpy@plt>

# on recupère l'adresse du malloc 4
	mov    eax,DWORD PTR [esp+0x18]

# récupération de l'adresse de m() puis est executé
   0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
   0x080484d0 <+84>:	call   eax


## M

# initialisation de la pile
   0x08048468 <+0>:	push   ebp
   0x08048469 <+1>:	mov    ebp,esp

# 24 octets d'aloué dans la pile
   0x0804846b <+3>:	sub    esp,0x18

# initialisation de 0x80485d1:	 "Nope" puis appel de puts avec => puts("Nope")
   0x0804846e <+6>:	mov    DWORD PTR [esp],0x80485d1
   0x08048475 <+13>:	call   0x8048360 <puts@plt>

# fin de la fonction
   0x0804847a <+18>:	leave  
   0x0804847b <+19>:	ret   

## N

# même fonction sauf que c'est system() qui est appeler avec 
(gdb) x/s 0x80485b0
0x80485b0:	 "/bin/cat /home/user/level7/.pass"