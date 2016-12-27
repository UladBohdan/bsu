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
    szText1      		db  "Binary:", 13, 10, 0
    buf                 db  300 dup(' ')
    x					db 	126
    bin_len				dd	0
	binary				db	8 dup(48)
	bin_answer			db	8 dup(0)
.code

MainProc	proc
		rep1:
			sar x, 1
			jnb contin1
			
			lea ebx, binary
			add ebx, bin_len
			mov al, 49
			mov [ebx], al
			
		contin1:
			inc bin_len
			xor eax, eax
			cmp x, al
			jne rep1
			
			lea ebx, binary
			add ebx, bin_len
			dec ebx
			lea edx, bin_answer
			mov ecx, bin_len
		rep2:
			mov al, [ebx]
			mov [edx], al
			dec ebx
			inc edx
			loop rep2
			
			invoke  StdOut, addr szText1
			invoke StdOut, addr bin_answer
			
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
