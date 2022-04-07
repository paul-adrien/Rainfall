set disassembly-flavor intel
(gdb) disas main
Dump of assembler code for function main:
   0x08048ec0 <+0>:	push   ebp
   0x08048ec1 <+1>:	mov    ebp,esp
   0x08048ec3 <+3>:	and    esp,0xfffffff0
   0x08048ec6 <+6>:	sub    esp,0x20
   0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048ecc <+12>:	add    eax,0x4
   0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
   0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
   0x08048ed4 <+20>:	call   0x8049710 <atoi>
   0x08048ed9 <+25>:	cmp    eax,0x1a7
   0x08048ede <+30>:	jne    0x8048f58 <main+152>
   0x08048ee0 <+32>:	mov    DWORD PTR [esp],0x80c5348
   0x08048ee7 <+39>:	call   0x8050bf0 <strdup>
   0x08048eec <+44>:	mov    DWORD PTR [esp+0x10],eax
   0x08048ef0 <+48>:	mov    DWORD PTR [esp+0x14],0x0
   0x08048ef8 <+56>:	call   0x8054680 <getegid>
   0x08048efd <+61>:	mov    DWORD PTR [esp+0x1c],eax
   0x08048f01 <+65>:	call   0x8054670 <geteuid>
   0x08048f06 <+70>:	mov    DWORD PTR [esp+0x18],eax
   0x08048f0a <+74>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048f0e <+78>:	mov    DWORD PTR [esp+0x8],eax
   0x08048f12 <+82>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048f16 <+86>:	mov    DWORD PTR [esp+0x4],eax
   0x08048f1a <+90>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048f1e <+94>:	mov    DWORD PTR [esp],eax
   0x08048f21 <+97>:	call   0x8054700 <setresgid>
   0x08048f26 <+102>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048f2a <+106>:	mov    DWORD PTR [esp+0x8],eax
   0x08048f2e <+110>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048f32 <+114>:	mov    DWORD PTR [esp+0x4],eax
   0x08048f36 <+118>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048f3a <+122>:	mov    DWORD PTR [esp],eax
   0x08048f3d <+125>:	call   0x8054690 <setresuid>
   0x08048f42 <+130>:	lea    eax,[esp+0x10]
   0x08048f46 <+134>:	mov    DWORD PTR [esp+0x4],eax
   0x08048f4a <+138>:	mov    DWORD PTR [esp],0x80c5348
   0x08048f51 <+145>:	call   0x8054640 <execv>
   0x08048f56 <+150>:	jmp    0x8048f80 <main+192>
   0x08048f58 <+152>:	mov    eax,ds:0x80ee170
   0x08048f5d <+157>:	mov    edx,eax
   0x08048f5f <+159>:	mov    eax,0x80c5350
   0x08048f64 <+164>:	mov    DWORD PTR [esp+0xc],edx
   0x08048f68 <+168>:	mov    DWORD PTR [esp+0x8],0x5
   0x08048f70 <+176>:	mov    DWORD PTR [esp+0x4],0x1
   0x08048f78 <+184>:	mov    DWORD PTR [esp],eax
   0x08048f7b <+187>:	call   0x804a230 <fwrite>
   0x08048f80 <+192>:	mov    eax,0x0
   0x08048f85 <+197>:	leave  
   0x08048f86 <+198>:	ret 



#   initialistation du début de la pile
	push   ebp
	mov    ebp,esp

# arrondissement de la pile du pointeur de la pile au mutltiple de 16 le plus proche
	and    esp,0xfffffff0

# on soustrait au registre 0x20 => 32 octet donc on agrandit la pile de 32 octets
	sub    esp,0x20

# on stock dans eax une variable de type DWORD (double word == 32bits) qui est a l'adresse [ebp+0xc] donc le haut de la pile + 12, ce qui correspond a récupérer une variable local
    mov    eax,DWORD PTR [ebp+0xc]

# le pointeur eax est décalé de 4 octet, la taille de la variable
	add    eax,0x4

# ces 4 lignes récupère les variable qui sont envoyer a la fonction lors de l'execution pour ensuite être mise dans la pile, au dessus de esp
	mov    eax,DWORD PTR [ebp+0xc]
	add    eax,0x4
	mov    eax,DWORD PTR [eax]
	mov    DWORD PTR [esp],eax

# atoi sur la valeur la variable dans eax
	call   0x8049710 <atoi>

# comparaison du retour d'atoi a 0x1a7 => 423
	cmp    eax,0x1a7

# si non égale à, saut a main+152
	jne    0x8048f58 <main+152>

# appel a strdup avec '/bin/sh'
	mov    DWORD PTR [esp],0x80c5348
	call   0x8050bf0 <strdup>

x/s 0x80c5348
0x80c5348:	 "/bin/sh"

# stockage du retour dans la pile
	mov    DWORD PTR [esp+0x10],eax

# 0 a esp+14
	mov    DWORD PTR [esp+0x14],0x0

# appel de getgit et getuid et sockage des retour dans la pile
	call   0x8054680 <getegid>
	mov    DWORD PTR [esp+0x1c],eax
	call   0x8054670 <geteuid>
	mov    DWORD PTR [esp+0x18],eax

# initilisation de 3 arguments dans la pile puis appel de setresgid avec ces 3 derniers
	mov    eax,DWORD PTR [esp+0x1c]
   	mov    DWORD PTR [esp+0x8],eax
   	mov    eax,DWORD PTR [esp+0x1c]
   	mov    DWORD PTR [esp+0x4],eax
   	mov    eax,DWORD PTR [esp+0x1c]
   	mov    DWORD PTR [esp],eax
   	call   0x8054700 <setresgid>

# idem pour setresuid
    mov    eax,DWORD PTR [esp+0x18]
    mov    DWORD PTR [esp+0x8],eax
    mov    eax,DWORD PTR [esp+0x18]
    mov    DWORD PTR [esp+0x4],eax
    mov    eax,DWORD PTR [esp+0x18]
    mov    DWORD PTR [esp],eax
    call   0x8054690 <setresuid>

# lea pointe l'adresse [esp+0x10] sur eax
	lea    eax,[esp+0x10]

# initialise les deux arguments pour la fonction execv puis l'execute
	mov    DWORD PTR [esp+0x4],eax
	mov    DWORD PTR [esp],0x80c5348
	call   0x8054640 <execv>

# saut a main+192
	jmp    0x8048f80 <main+192>

# ce qui suit a aurait été exeuté si la comparaison plus haute avait été differente car il y avait un saut a main+152

# recuperation dans eax de la zone memoire 0x80ee170
	mov    eax,ds:0x80ee170

# stockage dans edx eax puis ont met 0x80c5350 => "No !\n" dans eax
	mov    edx,eax
	mov    eax,0x80c5350

# on initialise les variables de la fonction fwrite puis elle est executé
	mov    DWORD PTR [esp+0xc],edx
	mov    DWORD PTR [esp+0x8],0x5
	mov    DWORD PTR [esp+0x4],0x1
	mov    DWORD PTR [esp],eax
	call   0x804a230 <fwrite>

# eax a 0 puis leave qui prepare la sortie d’une fonction en récupérant les variables enregistrées lors du début de la fonction afin de retrouver le contexte d’exécution tel qu’il avait été enregistré juste avant d’exécuter le code de la fonction, tout détruisant ce qu’il restait du stackframe et RET permet de finaliser le travail de LEAVE
	mov    eax,0x0
	leave  
	ret  