.386
PUBLIC @sumdig@8
.model flat

.data
		a	dd	0
		n	dd	0
		ind	dd	0
		sum	dd	100000
		cur	dd	0
.code

@sumdig@8	PROC
		mov a, ecx
		mov n, edx
		mov ecx, n
		mov ebx, a
		xor esi, esi
	countsum:			; for each a[i]
		mov cur, 0
		mov eax, [ebx+esi*4]
	  divten:
	    cdq
		mov edi, 10
		idiv edi
		add cur, edx
		cmp eax, 0
		jne divten

		mov eax, cur
		cmp eax, sum
		jge contloop
		mov sum, eax
		mov ind, esi

	  contloop:
		inc esi
		loop countsum
		
		mov eax, ind
		imul eax, 4
		add eax, a
		ret
@sumdig@8	ENDP

end