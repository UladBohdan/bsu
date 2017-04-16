.486
PUBLIC _cont@8
.model flat
.data
		a	dd	0
		b	dd	0
		cc	db	40 dup(?)
.code
_cont@8	PROC
		push ebp
		mov ebp, esp
		mov eax, dword ptr [esp+8]
		mov a, eax
		mov eax, dword ptr [esp+12]
		mov b, eax
		mov ebx, a
		lea ecx, cc
	rep1:
		mov al, [ebx]
		cmp al, 0
		je end1
		mov [ecx], al
		inc ebx
		inc ecx
		jmp rep1
	end1:
		mov ebx, b
	rep2:
		mov al, [ebx]
		cmp al, 0
		je end2
		mov [ecx], al
		inc ebx
		inc ecx
		jmp rep2
	end2:
		mov al, 0
		mov [ecx], al
		lea eax, cc
		pop ebp
		ret 8
_cont@8	ENDP

end