.386
PUBLIC _count@12
.model flat
.code
_count@12	proc
	push ebp
	mov ebp, esp
	mov eax, dword ptr [esp+8]
	mov ebx, dword ptr [esp+12]
	imul eax, ebx
	mov ebx, dword ptr [esp+16]
	add eax, ebx
	pop ebp
	ret 12
_count@12	endp
End