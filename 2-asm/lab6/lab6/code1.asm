.386

PUBLIC @init@8
PUBLIC @center@0
PUBLIC @closetoav@0
PUBLIC @secondless@0
PUBLIC @freqrep@0

.model flat
.data
		b	dd	100 dup(1)
		a	dd	0
		n	dd	0
		nls	dd	0
		val	dd	0
		ind	dd	0
		mx	dd	0
		tmp	dd	0

.code

@init@8	proc
		mov a, ecx
		mov n, edx
		mov nls, edx
		dec nls
		mov ecx, edx
		mov ebx, a
		lea edx, b
	copy1:
		mov eax, [ebx]
		mov [edx], eax
		add ebx, 4
		add edx, 4
		loop copy1

		CALL sort

		ret
@init@8	endp

@center@0	PROC
		lea ebx, b
		mov eax, n
		cdq
		mov esi, 2
		idiv esi
		mov ecx, [ebx+eax*4]
		mov val, ecx
		CALL find_val
		mov eax, ind
		imul eax, 4
		add eax, a
		ret
@center@0	ENDP

@secondless@0	PROC
		lea ebx, b
		mov ecx, [ebx+4]
		mov val, ecx
		CALL find_val
		mov eax, ind
		imul eax, 4
		add eax, a
		ret
@secondless@0	ENDP

@closetoav@0	PROC
		lea ebx, b
		xor eax, eax
		mov ecx, n
	sum1:
		add eax, [ebx]
		add ebx, 4
		loop sum1
			; average*n value is in eax
		mov esi, 0
		mov ecx, nls
		lea ebx, b
	find1av:
		mov edi, [ebx+esi*4]
		imul edi, n
		cmp edi, eax
		jge way3av 
		mov edx, [ebx+esi*4+4]
		imul edx, n
		cmp eax, edx
		jge way2av
		mov tmp, eax
		mov edi, [ebx+esi*4]
		imul edi, n
		sub tmp, edi
		mov edi, tmp
		sub edx, eax
		cmp edi, edx
		jg way1av
		mov edx, [ebx+esi*4]
		mov val, edx
		jmp exit1av
	  way1av:
		mov edx, [ebx+esi*4+4]
		mov val, edx
		jmp exit1av
	way2av:
		inc esi
		loop find1av
	  way3av:
		mov edi, [ebx+esi*4]
		mov val, edi
		jmp exit1av

	exit1av:
		CALL find_val
		mov eax, ind
		imul eax, 4
		add eax, a
		ret
@closetoav@0	ENDP


@freqrep@0	PROC
		lea ebx, b
		mov ecx, n
		mov edx, 786454
		mov [ebx+ecx*4], edx 
		xor edi, edi
		mov edx, [ebx]
		mov val, edx
		mov mx, 1
	look1rep:
		inc edi
		add ebx, 4
		cmp edx, [ebx]
		je eq1x
		cmp mx, edi
		jge difbad1
		mov mx, edi
		mov val, edx
		mov edx, [ebx]
		xor edi, edi
		jmp newlooprep
	  eq1x:
		jmp newlooprep
	  difbad1:
		xor edi, edi
		mov edx, [ebx]
		jmp newlooprep
	  newlooprep:
		loop look1rep

		mov eax, mx
		cmp eax, 1
		je notreps
		CALL find_val
		mov eax, ind
		imul eax, 4
		add eax, a
		ret
	notreps:
		mov eax, a
		sub eax, 8
		ret
@freqrep@0	ENDP


sort	PROC	; sorting B array
		
		xor esi, esi	; like pos
		mov edi, n		; global cycle
	rep1sort:
		dec edi
		xor esi, esi
	rep2sort:
		jmp cmprandswap
	returnhome:
		inc esi
		cmp esi, nls
		jne rep2sort
		cmp edi, 0
		je endsort
		jmp rep1sort

	cmprandswap:
		lea ebx, b
		mov eax, [ebx+esi*4]
		mov edx, [ebx+esi*4+4]
		cmp eax, edx
		jle returnhome
		mov [ebx+esi*4], edx
		mov [ebx+esi*4+4], eax
		jmp returnhome

	endsort:
		ret
sort	ENDP

find_val	PROC	; looking for val in A-array - saves index to ind
		mov ecx, n
		mov ebx, a
		mov ind, 0
		mov edx, val
	find1val:
		cmp edx, [ebx]
		jne way2
		jmp end_find
	way2:
		inc ind
		add ebx, 4
		loop find1val
	end_find:
		ret
find_val	ENDP

end