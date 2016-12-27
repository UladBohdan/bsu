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

.data
    szText1		db  "Two numbers (through enter):", 13, 10, 0
    szText2		db	"GCD: ", 0
    buf			db  300 dup(' ')
	a			dd	0
	b			dd	0
	ans			dd	0			
.code

MainProc	proc
			CALL readIn
			
			mov eax, a
			mov ebx, b
		rep1:
			cmp ebx, 0
			je fin1
			cdq
		;	mov ebx, eax
			idiv ebx
			mov eax, ebx
			mov ebx, edx
			jmp rep1
		fin1:
			mov ans, eax
			
			CALL writeOut
MainProc    endp

readIn	proc
	
			invoke StdOut, addr szText1
			invoke StdIn, addr buf, 300
			invoke atol, addr buf
			mov a, eax
			invoke StdIn, addr buf, 300
			invoke atol, addr buf
			mov b, eax
			ret
readIn endp

writeOut	proc
			
			invoke StdOut, addr szText2
			invoke dwtoa, ans, addr buf
			invoke StdOut, addr buf
			invoke StdIn, addr buf, 300
			invoke ExitProcess, 0		
			ret
writeOut endp

end MainProc
