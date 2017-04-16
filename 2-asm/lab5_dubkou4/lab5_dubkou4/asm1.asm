.486
PUBLIC _check
.model flat
.data
		a	dd	0
.code
_check	PROC
		push ebp
		mov ebp, esp
		mov ecx, [ebp+8]
		mov a, ecx
		dec ecx
	rep1:
		inc ecx
		mov al, [ecx]
		cmp al, 0
		je ok1
		cmp al, 48
		jl endnot16
		cmp al, 102
		jg endnot16
		cmp al, 58
		jl rep1
		cmp al, 97
		jl endnot16
		jmp rep1
	ok1:
		mov eax, 0
		xor ebx, ebx
		mov ecx, a
		dec ecx
	rep2:
		inc ecx
		mov bl,	[ecx]
		cmp bl, 0 
		je end1
		cmp bl, 57
		jle way48
		sub bl, 87
		jmp general
	way48:
		sub bl, 48
	general:
		imul eax, 16
		add eax, ebx
		jmp rep2
		
	endnot16:
		mov eax, -1
	end1:
		pop ebp
		ret
_check	ENDP

end