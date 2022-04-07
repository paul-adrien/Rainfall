(gdb) disas main
Dump of assembler code for function main:
   0x0804853f <+0>:	push   ebp
   0x08048540 <+1>:	mov    ebp,esp
   0x08048542 <+3>:	and    esp,0xfffffff0
   0x08048545 <+6>:	call   0x80484d4 <p>
   0x0804854a <+11>:	leave  
   0x0804854b <+12>:	ret    
End of assembler dump.
(gdb) disas p
Dump of assembler code for function p:
   0x080484d4 <+0>:	push   ebp
   0x080484d5 <+1>:	mov    ebp,esp
   0x080484d7 <+3>:	sub    esp,0x68
   0x080484da <+6>:	mov    eax,ds:0x8049860
   0x080484df <+11>:	mov    DWORD PTR [esp],eax
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
   0x080484ea <+22>:	mov    DWORD PTR [esp],eax
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
   0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
   0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080484fb <+39>:	and    eax,0xb0000000
   0x08048500 <+44>:	cmp    eax,0xb0000000
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    eax,0x8048620
   0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
   0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
   0x08048513 <+63>:	mov    DWORD PTR [esp],eax
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave  
   0x0804853e <+106>:	ret    
End of assembler dump.


## MAIN:

#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# arrondissement de la pile du pointeur de la pile au mutltiple de 16 le plus proche
	and    esp,0xfffffff0

# appel de la fonction p
	call   0x80484d4 <p>

# leave qui prepare la sortie d’une fonction en récupérant les variables enregistrées lors du début de la fonction afin de retrouver le contexte d’exécution tel qu’il avait été enregistré juste avant d’exécuter le code de la fonction, tout détruisant ce qu’il restait du stackframe et RET permet de finaliser le travail de LEAVE
	leave  
	ret  

## P

#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# on soustrait au registre 0x68 => 104 octet donc on agrandit la pile de 104 octets
	sub    esp,0x68

# récupertion de 0x8049860 dans la memoire du segment de donnée
	mov    eax,ds:0x8049860
x/s 0x8049860
0x8049860 <stdout@@GLIBC_2.0>:	 ""

# initialise les variables de fflush puis l'execute (fflush(stdout))
	mov    DWORD PTR [esp],eax
	call   0x80483b0 <fflush@plt>

# eax pointe sur [ebp-0x4c] puis le pointeur est mis dans la pile pour être appelé dans gets qui est executé après
	lea    eax,[ebp-0x4c]
	mov    DWORD PTR [esp],eax
	call   0x80483c0 <gets@plt>

# stockage du retour de la fonction dans eax et dans la pile
	mov    eax,DWORD PTR [ebp+0x4]
	mov    DWORD PTR [ebp-0xc],eax
	mov    eax,DWORD PTR [ebp-0xc]

# ET logique puis comparaison pour verifier que l'adresse n'a pas été ecrasé et si c'est le cas on saut a p+83
	and    eax,0xb0000000
	cmp    eax,0xb0000000
	jne    0x8048527 <p+83>

# stockage de "(%p)\n" dans eax
	mov    eax,0x8048620
   x/s 0x8048620
0x8048620:	 "(%p)\n"

# initialisation des variables pour printf puis est executé
	mov    edx,DWORD PTR [ebp-0xc]
	mov    DWORD PTR [esp+0x4],edx
	mov    DWORD PTR [esp],eax
	call   0x80483a0 <printf@plt>

# exit(1)
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>

# on est ligne 83 la où on arrive lors de la comparaison si il y avait différence
# eax point sur [ebp-0x4c] puis définition des variables de puts puis execution 
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>

# idem avec strdup
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>

# fin de la fonction
   0x0804853d <+105>:	leave  
   0x0804853e <+106>:	ret    