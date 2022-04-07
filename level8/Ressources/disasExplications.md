(gdb) disas main
Dump of assembler code for function main:
# initialisation de la fonction
	push   ebp
	mov    ebp,esp

#
	push   edi
	push   esi

# allignement
	and    esp,0xfffffff0

# 160 bytes rajouté a la pile
	sub    esp,0xa0

# saut a main+17
	jmp    0x8048575 <main+17>

# rien ne se passe et passe a l'instruction suivante
	nop

# initialisation des variables de printf puis exectuté: ecx -> service -> [esp+0x8], edx -> auth -> [esp+0x4] et eax -> "%p, %p \n" -> [esp].
	mov    ecx,DWORD PTR ds:0x8049ab0
	mov    edx,DWORD PTR ds:0x8049aac
	mov    eax,0x8048810
	mov    DWORD PTR [esp+0x8],ecx
	mov    DWORD PTR [esp+0x4],edx
	mov    DWORD PTR [esp],eax
	call   0x8048410 <printf@plt>

# les variables de fgets sont initialisé: eax -> stdin -> [esp+0x8], 0x80 -> [esp+0x4] et [esp+0x20] -> [esp] puis appel a fgets
	mov    eax,ds:0x8049a80
	mov    DWORD PTR [esp+0x8],eax
	mov    DWORD PTR [esp+0x4],0x80
	lea    eax,[esp+0x20]
	mov    DWORD PTR [esp],eax
	call   0x8048440 <fgets@plt>

# si le retour de fgets est egale a 0, saut a main+456
	test   eax,eax
	je     0x804872c <main+456>

# REPZ repete l'instruction jusqu'à ce que CX = 0 ou tant que l'indicateur ZF = 0.
# CMPS compare deux chaînes. Cette instruction compare deux éléments de données d'un octet, mot ou mot double, pointés par les registres DS:SI et ES:DI et définit les drapeaux en conséquence
# cela correspond a faire un strncmp(), ici sur le buffer et sur "auth " avec une length de 0x5 -> 5
	lea    eax,[esp+0x20]
	mov    edx,eax
	mov    eax,0x8048819
	mov    ecx,0x5
	mov    esi,edx
	mov    edi,eax
	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]

   (gdb) x/s 0x8048819
0x8048819:	 "auth "

# dl va être egale a 1 si esi > edi et al a 1 si l'inverse
	seta   dl
	setb   al
   
# regarde si la comparaison a été concluente sinon jump -> main+222
	mov    ecx,edx
	sub    cl,al
	mov    eax,ecx
	movsx  eax,al
	test   eax,eax
	jne    0x8048642 <main+222>

# auth = malloc(4)
	mov    DWORD PTR [esp],0x4
	call   0x8048470 <malloc@plt>
	mov    ds:0x8049aac,eax
	mov    eax,ds:0x8049aac

   (gdb) x/s 0x8049aac
0x8049aac <auth>:	 ""

# eax prend le buffer + 5, [esp+0x1c] = -1, edx = buffer +5, ecx = -1, 
	mov    DWORD PTR [eax],0x0 
	lea    eax,[esp+0x20]
	add    eax,0x5
	mov    DWORD PTR [esp+0x1c],0xffffffff
	mov    edx,eax
	mov    eax,0x0
	mov    ecx,DWORD PTR [esp+0x1c]
	mov    edi,edx

# repnz scas -> strlen(edi = buffer+5)
	repnz scas al,BYTE PTR es:[edi]
	mov    eax,ecx
	not    eax
	sub    eax,0x1

# strlen(buffer+5) > 0x1e = 30, si vrai saut a main + 222
	cmp    eax,0x1e
	ja     0x8048642 <main+222>

# initialisation des variables de strcpy pour donner strcpy(auth, buffer + 5)
	lea    eax,[esp+0x20]
	lea    edx,[eax+0x5]
	mov    eax,ds:0x8049aac
	mov    DWORD PTR [esp+0x4],edx
	mov    DWORD PTR [esp],eax
	call   0x8048460 <strcpy@plt>

# même chose que plus haut mais avec "reset" au lieux de "auth " cette fois si => strncmp(buffer, "reset", 5) et si différent saut a main+276
	lea    eax,[esp+0x20]
	mov    edx,eax
	mov    eax,0x804881f
	mov    ecx,0x5
	mov    esi,edx
	mov    edi,eax
	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	seta   dl
	setb   al
	mov    ecx,edx
	sub    cl,al
	mov    eax,ecx
	movsx  eax,al
	test   eax,eax
	jne    0x8048678 <main+276>

# free(auth)
	mov    eax,ds:0x8049aac
	mov    DWORD PTR [esp],eax
	call   0x8048420 <free@plt>

# idem avec "service" => strncmp(buffer, "service", 6) et si différent saut a main+276
	lea    eax,[esp+0x20]
	mov    edx,eax
	mov    eax,0x8048825
	mov    ecx,0x6
	mov    esi,edx
	mov    edi,eax
	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	seta   dl
	setb   al
	mov    ecx,edx
	sub    cl,al
	mov    eax,ecx
	movsx  eax,al
	test   eax,eax
	jne    0x80486b5 <main+337>

# service = strdup(buffer + 7)
	lea    eax,[esp+0x20]
	add    eax,0x7
	mov    DWORD PTR [esp],eax
	call   0x8048430 <strdup@plt>
	mov    ds:0x8049ab0,eax

# idem avec "login" => strncmp(buffer, "login", 6) et si différent saut a main+16
	lea    eax,[esp+0x20]
	mov    edx,eax
	mov    eax,0x804882d
	mov    ecx,0x5
	mov    esi,edx
	mov    edi,eax
	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	seta   dl
	setb   al
	mov    ecx,edx
	sub    cl,al
	mov    eax,ecx
	movsx  eax,al
	test   eax,eax
	jne    0x8048574 <main+16>

# eax pointe sur auth+32 et est ensuite tester pour savoir si il est eax est egale a 0 si oui main+411
	mov    eax,ds:0x8049aac
	mov    eax,DWORD PTR [eax+0x20]
	test   eax,eax
	je     0x80486ff <main+411>

# appel system avec "/bin/sh"
	mov    DWORD PTR [esp],0x8048833
	call   0x8048480 <system@plt>

# jump a main +16
	jmp    0x8048574 <main+16>

# fwrite("Password:\n", 1, 10, stdout)
	mov    eax,ds:0x8049aa0
	mov    edx,eax
	mov    eax,0x804883b
	mov    DWORD PTR [esp+0xc],edx
	mov    DWORD PTR [esp+0x8],0xa
	mov    DWORD PTR [esp+0x4],0x1
	mov    DWORD PTR [esp],eax
	call   0x8048450 <fwrite@plt>

# jump a main +16
	jmp    0x8048574 <main+16>

# rien
	nop

# 0 du return
	mov    eax,0x0

# récuperation des anciennes valeurs
	lea    esp,[ebp-0x8]
	pop    esi
	pop    edi
	pop    ebp

# return 
	ret    
End of assembler dump.
(gdb) 
