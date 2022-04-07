(gdb) info functions
...
0x080484b4  p
0x0804851e  pp
0x080485a4  main
...

## MAIN

# initialisation de la pile, alignement
	push   ebp
	mov    ebp,esp
	and    esp,0xfffffff0

# 64 octets pour les variables locales
	sub    esp,0x40

# appel de pp() avec en paramettre un buffer
	lea    eax,[esp+0x16]
	mov    DWORD PTR [esp],eax
	call   0x804851e <pp>

# appel de puts avec un buffer de taille 0x40 - 0x16 = 42
	lea    eax,[esp+0x16]
	mov    DWORD PTR [esp],eax
	call   0x80483b0 <puts@plt>

# return (0)
	mov    eax,0x0
	leave  
	ret  


## PP

# initialisation de la fonction
	push   ebp
	mov    ebp,esp

# sauvegarde des anciens edi et edx puis allocation de 80 octets
	push   edi
	push   ebx
	sub    esp,0x50

# appel de p() avec en variables buffer1[20] et " - "
	mov    DWORD PTR [esp+0x4],0x80486a0
	lea    eax,[ebp-0x30]
	mov    DWORD PTR [esp],eax
	call   0x80484b4 <p>

# appel de p() avec en variables buffer2[28] et " - "
	mov    DWORD PTR [esp+0x4],0x80486a0
	lea    eax,[ebp-0x1c]
	mov    DWORD PTR [esp],eax
	call   0x80484b4 <p>
# les deux ont une taille de 20 et car 48 - 28 = 20 et il reste ensuite 28

# strcpy(buffer3, buffer1)
	lea    eax,[ebp-0x30]
	mov    DWORD PTR [esp+0x4],eax
	mov    eax,DWORD PTR [ebp+0x8]
	mov    DWORD PTR [esp],eax
	call   0x80483a0 <strcpy@plt>

# strlen(buffer)
	mov    ebx,0x80486a4
	mov    eax,DWORD PTR [ebp+0x8]
	mov    DWORD PTR [ebp-0x3c],0xffffffff
	mov    edx,eax
	mov    eax,0x0
	mov    ecx,DWORD PTR [ebp-0x3c]
	mov    edi,edx
	repnz scas al,BYTE PTR es:[edi]
	mov    eax,ecx
	not    eax
	sub    eax,0x1
	add    eax,DWORD PTR [ebp+0x8]
	movzx  edx,WORD PTR [ebx]
	mov    WORD PTR [eax],dx

# strcat(buffer3, buffer2)
	lea    eax,[ebp-0x1c]
	mov    DWORD PTR [esp+0x4],eax
	mov    eax,DWORD PTR [ebp+0x8]
	mov    DWORD PTR [esp],eax
	call   0x8048390 <strcat@plt>

# récuperation de ebx, edi et ebp
	add    esp,0x50
	pop    ebx
	pop    edi
	pop    ebp
	ret    


## P

# initialisation de la fonction
	push   ebp
	mov    ebp,esp

# 4120 octets pour les variables locale
	sub    esp,0x1018

# puts()
	mov    eax,DWORD PTR [ebp+0xc]
	mov    DWORD PTR [esp],eax
	call   0x80483b0 <puts@plt>

# read(0, buffer, 4096)
	mov    DWORD PTR [esp+0x8],0x1000
	lea    eax,[ebp-0x1008]
	mov    DWORD PTR [esp+0x4],eax
	mov    DWORD PTR [esp],0x0
	call   0x8048380 <read@plt>

# strchr(buffer, 10)
	mov    DWORD PTR [esp+0x4],0xa
	lea    eax,[ebp-0x1008]
	mov    DWORD PTR [esp],eax
	call   0x80483d0 <strchr@plt>

# strncpy(ptr, buffer, 20)
	mov    BYTE PTR [eax],0x0
	lea    eax,[ebp-0x1008]
	mov    DWORD PTR [esp+0x8],0x14
	mov    DWORD PTR [esp+0x4],eax
	mov    eax,DWORD PTR [ebp+0x8]
	mov    DWORD PTR [esp],eax
	call   0x80483f0 <strncpy@plt>

# fin de la fonction
	leave  
	ret  