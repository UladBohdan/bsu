.486
.model flat, stdcall                    
option casemap :none

include windows.inc     ; always first

include masm32.inc
include gdi32.inc
include user32.inc
include kernel32.inc

includelib masm32.lib
includelib gdi32.lib
includelib user32.lib
includelib kernel32.lib

.const
	double10	dd	10.5
	tab			db	9
	half		dd	0.5
	endr		db	13,10,0
	log2e		dq	1.44269504089
	c100		dq	10.0
	c1000		dq	1000.0
.data
    szText1		db	"x",9,"log2 x",9,"ln x",9,"e^x",9,"a^x",13,10,0
    szText2		db	"Enter a (int) for a^x:",13,10,0
    buf			db	300 dup(?)
	a			dd	?
	x			dd	1.0
	temp		dq	?
	log2a		dq	?
	deg			dq	?
	intdeg		dq	?
.code

MainProc	proc
            invoke StdOut, addr szText2
            invoke StdIn, addr buf, 300
            invoke atol, addr buf
            mov a, eax
            finit
            fld1
            fild a
            fyl2x
            fst log2a
            invoke StdOut, addr szText1            
        rep1:
       		mov ecx, double10
       		cmp x, ecx
       		je fin1
       		CALL outRow
       		finit
       		fld x
       		fld half
       		fadd
       		fst x
       		jmp rep1	
            
        fin1:
       		invoke StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

outRow	proc
			finit
			fld x
			fstp temp
			invoke FloatToStr,	temp, addr buf
			invoke StdOut, addr buf
			invoke StdOut, addr tab
			;log2a
			finit
			fld1
			fld x
			fyl2x
			fld c1000
			fmul
			frndint
			fld c1000
			fdiv
			fst temp
			invoke FloatToStr, temp, addr buf
			invoke StdOut, addr buf
			invoke StdOut, addr tab
			;ln
			finit
			fld temp
			fld log2e
			fdiv
			fld c1000
			fmul
			frndint
			fld c1000
			fdiv
			fst temp
			invoke FloatToStr, temp, addr buf
			invoke StdOut, addr buf
			invoke StdOut, addr tab
			;e^x
			finit
			fld x
			fmul log2e
			fst deg
			fsub half
			frndint
			fst intdeg
			finit
			fld deg
			fsub intdeg
			f2xm1
			fld1
			fadd
			fst temp
			finit
			fld intdeg
			fld1
			fscale
			fld temp
			fmul
			fld c100
			fmul
			frndint
			fld c100
			fdiv
			fst temp
			invoke FloatToStr, temp, addr buf
			invoke StdOut, addr buf
			invoke StdOut, addr tab
			;a^x
			finit
			fld x
			fmul log2a
			fst deg
			fsub half
			frndint
			fst intdeg
			finit
			fld deg
			fsub intdeg
			f2xm1
			fld1
			fadd
			fst temp
			finit
			fld intdeg
			fld1
			fscale
			fld temp
			fmul
			fld c1000
			fmul
			frndint
			fld c1000
			fdiv
			fst temp
			invoke FloatToStr, temp, addr buf
			invoke StdOut, addr buf
			invoke StdOut, addr tab
			invoke StdOut, addr endr
			ret
outRow endp

end MainProc
