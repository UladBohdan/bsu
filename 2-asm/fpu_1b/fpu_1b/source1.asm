.486
PUBLIC @find_ranges@8
.model flat
.data
		a1	dd	0
		b1	dd	0
		c1	dd	0
		n1	dd	0
		arr1	dd	0
		togo	dd	-10
		sign1	db	0
		sign2	db	0
		temp	dd	0
.code

@find_ranges@8	PROC
		mov eax, dword ptr [ecx]
		mov a1, eax
		mov eax, [ecx+4]
		mov b1, eax
		mov eax, [ecx+8]
		mov c1, eax
		mov eax, [edx]
		mov n1, eax
		add edx, 4
		mov arr1, edx
		;CALL count_val
global_cycle1:
				

ret
@find_ranges@8	ENDP

end