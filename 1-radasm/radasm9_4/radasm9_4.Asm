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
	endr		db	13,10,0
	cd1			db	'!',13,10,0
	cd2			db	"!!!",13,10,0

.data
    szText1		db	"Input your matrix:", 13, 10, 0
    szText2		db	"Sum in each row:",13,10,0
    buf			db	300 dup(' ')
    tempstr		db	20 dup(0)
    ans			dd	20 dup(0)
    n			dd	0
	pos			dd	0
	temp		dd	0
.code

MainProc	proc
            invoke  StdOut, addr szText1
        rep1:
            invoke StdIn, addr buf, SizeOf buf
            lea ebx, buf
            mov cl, 13
            cmp [ebx], cl
            je fin1
            CALL sumToANS
            jmp rep1
        fin1:
        	invoke StdOut, addr szText2
        rep2:
        	mov eax, n
        	cmp pos, eax
        	je fin2
        	lea ebx, ans
        	mov ecx, pos
        	mov eax, [ebx+ecx*4]
        	mov temp, eax
        	invoke dwtoa, temp, addr buf
        	invoke StdOut, addr buf
        	invoke StdOut, addr endr
        	inc pos
        	jmp rep2
     	fin2:  
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

sumToANS	proc
			xor edi, edi
			lea ebx, buf
			lea edx, tempstr
		rep3:
			mov cl, 32
			cmp [ebx], cl
			je havenum
			mov cl, 13
			cmp [ebx], cl
			je havefinnum
			mov cl, [ebx]
			mov [edx], cl
			inc edx
			inc ebx
			jmp rep3
		havenum:
			mov cl, 0
			mov [edx], cl
			push ebx
			push edi
			xor eax, eax
			invoke atol, addr tempstr
			pop edi
			pop ebx
			add edi, eax
			lea edx, tempstr
			inc ebx
			jmp rep3
		havefinnum:
			mov cl, 0
			mov [edx], cl
			xor eax, eax
			invoke atol, addr tempstr 
			add edi, eax
			
			lea ebx, ans		
			mov ecx, n
			mov [ebx+ecx*4], edi
			inc n
			ret
sumToANS endp

end MainProc
