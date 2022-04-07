(gdb) info functions
...
0x08048484  greetuser
0x08048529  main
...

## MAIN

# initialisation de la pile
	push   ebp
	mov    ebp,esp

# sauvegarde edi, edx, ebx
	push   edi
	push   esi
	push   ebx

# alignement
	and    esp,0xfffffff0

# 160 octets pour les variables locale
	sub    esp,0xa0

# compare ac ([ebp+0x8]) à 3 et si egale saut a 31 sinon return(1)
	cmp    DWORD PTR [ebp+0x8],0x3
	je     0x8048548 <main+31>
	mov    eax,0x1
	jmp    0x8048630 <main+263>

# correspond a un memset avec 4octet a chaque répétion de ecx (https://stackoverflow.com/questions/3818856/what-does-the-rep-stos-x86-assembly-instruction-sequence-do) memset(buffer, 0, 76) répétition 4*0x13(19) = 76
	lea    ebx,[esp+0x50]
	mov    eax,0x0
	mov    edx,0x13
	mov    edi,ebx
	mov    ecx,edx
	rep stos DWORD PTR es:[edi],eax

# 40, av[1], buffer => strncpy(buffer, av[1], 40)
	mov    eax,DWORD PTR [ebp+0xc]
	add    eax,0x4
	mov    eax,DWORD PTR [eax]
	mov    DWORD PTR [esp+0x8],0x28
	mov    DWORD PTR [esp+0x4],eax
	lea    eax,[esp+0x50]
	mov    DWORD PTR [esp],eax
	call   0x80483c0 <strncpy@plt>

# 32, av[2], buffer[40] => strncpy(buffer[40], av[2], 32)
	mov    eax,DWORD PTR [ebp+0xc]
	add    eax,0x8
	mov    eax,DWORD PTR [eax]
	mov    DWORD PTR [esp+0x8],0x20
	mov    DWORD PTR [esp+0x4],eax
	lea    eax,[esp+0x50]
	add    eax,0x28
	mov    DWORD PTR [esp],eax
	call   0x80483c0 <strncpy@plt>

# getenv("LANG")
	mov    DWORD PTR [esp],0x8048738
	call   0x8048380 <getenv@plt>
	 x/s 0x8048738
0x8048738:	 "LANG"

# si getenv return 0 saut a 239
	mov    DWORD PTR [esp+0x9c],eax
	cmp    DWORD PTR [esp+0x9c],0x0
	je     0x8048618 <main+239>

# memcmp(LANG, "fi", 2)
	mov    DWORD PTR [esp+0x8],0x2
	mov    DWORD PTR [esp+0x4],0x804873d
(gdb) x/s 0x804873d
0x804873d:	 "fi"
	mov    eax,DWORD PTR [esp+0x9c]
	mov    DWORD PTR [esp],eax
	call   0x8048360 <memcmp@plt>

# si egale a 0 donc egale language = 1 et saut a 239 sinon 194
	test   eax,eax
	jne    0x80485eb <main+194>
	mov    DWORD PTR ds:0x8049988,0x1
(gdb) x/s 0x8049988
0x8049988 <language>:	 ""
	jmp    0x8048618 <main+239>

# idem mais  memcmp(LANG, "nl", 2) et language =2 sans saut a 194 car pas d'autre test
	mov    DWORD PTR [esp+0x8],0x2
	mov    DWORD PTR [esp+0x4],0x8048740
 x/s 0x8048740
0x8048740:	 "nl"
	mov    eax,DWORD PTR [esp+0x9c]
	mov    DWORD PTR [esp],eax
	call   0x8048360 <memcmp@plt>
	test   eax,eax
	jne    0x8048618 <main+239>
	mov    DWORD PTR ds:0x8049988,0x2

# cope du buffer dans esp puis appel de greetuser(buffer)
	mov    edx,esp
	lea    ebx,[esp+0x50]
	mov    eax,0x13
	mov    edi,edx
	mov    esi,ebx
	mov    ecx,eax
	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
	call   0x8048484 <greetuser>

# fin de la fonction
	lea    esp,[ebp-0xc]
	pop    ebx
	pop    esi
	pop    edi
	pop    ebp
	ret   


## GREETUSER

# initialisation de la fonction
	push   ebp
	mov    ebp,esp

# 88 octets pour les variables locale
	sub    esp,0x58

# si language = 1 => saut a +54 sinon si = 2 saut a 101 sinon si != 0 saut a 134
	mov    eax,ds:0x8049988
	cmp    eax,0x1
	je     0x80484ba <greetuser+54>
	cmp    eax,0x2
	je     0x80484e9 <greetuser+101>
	test   eax,eax
	jne    0x804850a <greetuser+134>
(gdb) x/s 0x8049988
0x8049988 <language>:	 ""

# equivalent a un strcpy(buffer, "Hello ") puis saut a 134
	mov    edx,0x8048710
	lea    eax,[ebp-0x48]
	mov    ecx,DWORD PTR [edx]
	mov    DWORD PTR [eax],ecx
	movzx  ecx,WORD PTR [edx+0x4]
	mov    WORD PTR [eax+0x4],cx
	movzx  edx,BYTE PTR [edx+0x6]
	mov    BYTE PTR [eax+0x6],dl
	jmp    0x804850a <greetuser+134>
(gdb) x/s 0x8048710
0x8048710:	 "Hello "

# idem mais strcpy(buffer, "Hyvää päivää ") puis saut a 134
	mov    edx,0x8048717
	lea    eax,[ebp-0x48]
	mov    ecx,DWORD PTR [edx]
	mov    DWORD PTR [eax],ecx
	mov    ecx,DWORD PTR [edx+0x4]
	mov    DWORD PTR [eax+0x4],ecx
	mov    ecx,DWORD PTR [edx+0x8]
	mov    DWORD PTR [eax+0x8],ecx
	mov    ecx,DWORD PTR [edx+0xc]
	mov    DWORD PTR [eax+0xc],ecx
	movzx  ecx,WORD PTR [edx+0x10]
	mov    WORD PTR [eax+0x10],cx
	movzx  edx,BYTE PTR [edx+0x12]
	mov    BYTE PTR [eax+0x12],dl
	jmp    0x804850a <greetuser+134>
(gdb) x/s 0x8048717
0x8048717:	 "Hyvää päivää "

# idem mais strcpy(buffer, "Goedemiddag ")
	mov    edx,0x804872a
	lea    eax,[ebp-0x48]
	mov    ecx,DWORD PTR [edx]
	mov    DWORD PTR [eax],ecx
	mov    ecx,DWORD PTR [edx+0x4]
	mov    DWORD PTR [eax+0x4],ecx
	mov    ecx,DWORD PTR [edx+0x8]
	mov    DWORD PTR [eax+0x8],ecx
	movzx  edx,WORD PTR [edx+0xc]
	mov    WORD PTR [eax+0xc],dx
(gdb) x/s 0x804872a
0x804872a:	 "Goedemiddag! "

# strcat(buffer, buffer2)
	nop
	lea    eax,[ebp+0x8]
	mov    DWORD PTR [esp+0x4],eax
	lea    eax,[ebp-0x48]
	mov    DWORD PTR [esp],eax
	call   0x8048370 <strcat@plt>

# puts(buffer)
	lea    eax,[ebp-0x48]
	mov    DWORD PTR [esp],eax
	call   0x8048390 <puts@plt>

# fin de la fonction
	leave  
	ret 