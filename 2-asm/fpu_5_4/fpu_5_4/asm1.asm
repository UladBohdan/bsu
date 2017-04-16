.486
PUBLIC _func@16
.model flat
.data
		cur		dq	0
		sum		dq	0
		coef	dq	0
		x		dq	0
		eps		dq	0
		k		dq	1.0
		c2		dq	2.0
		c3		dq	3.0
		c10		dq	10.0
		ans		dq	0
.code

_func@16	PROC
		push ebp
		mov ebp, esp
		finit
		fld qword ptr [ebp+8]
		fstp x
		fld qword ptr [ebp+16]
		fstp eps

	rep1:
		finit
		fld k
		fadd c3
		fld st(0)
		fmul
		fld1
		fdivr
		fst cur
		
		finit
		fld k
		fld1
		fadd
		fst k
		
		finit
		fld sum
		fld cur
		fadd
		fst sum
		
		finit
		fld eps
		fld cur
		fabs
		fcom eps
		fstsw ax
		sahf
		jc fin1
		jmp rep1

	fin1:
		finit
		fld x
		fabs
		fadd c2
		fsqrt
		fld x
		fdiv
		fst coef

		finit
		fld sum
		fmul coef
		fst ans
		lea eax, ans

		pop ebp
		ret 16
_func@16	ENDP

end