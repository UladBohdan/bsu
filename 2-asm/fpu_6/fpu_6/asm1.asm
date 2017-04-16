.486
PUBLIC _func@8
.model flat
.data
		a	dd	?	; array address
		x	dd	?	; value
.code
_func@8	PROC
		push ebp
		mov ebp, esp
		finit
		fld dword ptr [ebp+8]
		fst x
		fld dword ptr [ebp+12]
		fst a
		mov ebx, a
		
		finit
		fld x
		fmul x
		mov ebx, a
		fst [a]

		pop ebp
		ret 8

		finit 
		fld x
		fabs
		fld1
		fyl2x
		fst [a+4]

		finit
		fld x
		fsin
		fst [a+8]

		pop ebp
		ret 8
_func@8	ENDP

end