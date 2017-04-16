.386
PUBLIC @divs@8
.model flat
.data
		ans	dd	0
.code
@divs@8	PROC
		mov ebx, ecx
		mov edi, edx
		mov esi, 0
	rep1:
		inc esi
		cmp esi, edi
		je end1
		mov eax, edi
		cdq
		idiv esi
		cmp edx, 0
		jne rep1
		mov [ebx], esi
		inc ans
		add ebx, 4
		jmp rep1

	end1:
		mov [ebx], edi
		inc ans
		mov eax, ans
		ret
@divs@8	ENDP
end