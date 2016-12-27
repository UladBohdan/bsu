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
	space	db	32

.data
    szText1		db  "Your string:", 13, 10, 0
    str1		db	100 dup(0)
    str2		db	100 dup(0)
    len			dd	0
    len2		dd	0
    number		dd	0
    ans			db	20 dup(?)
    buf			db  300 dup(' ')

.code

MainProc	proc
            invoke  StdOut, addr szText1
            invoke	StdIn, addr str1, LengthOf str1
            dec eax
            dec eax
            lea ebx, str1
            add ebx, eax
            mov dl, space
            mov [ebx], dl
            inc eax           
            mov len, eax
      		inc ebx
      		mov dl, 0
      		mov [ebx], dl
            
            lea ebx, str1
            mov ecx, len
       	rep1:
       		mov dl, byte ptr [ebx]
       		cmp dl, space
       		je checkword
       		
       		lea edx, str2
       		add edx, len2
       		mov al, [ebx]
       		mov [edx], al
       		inc len2
       		jmp fin1
       		
       	checkword:
       		push ebx
       		push ecx
       		CALL onlyDigits
       		pop ecx
       		pop ebx
       		mov len2, 0
       		cmp eax, 0
       		je fin1
       		inc number
       		jmp fin1 
       		
       	fin1:
       		inc ebx
       		loop rep1
            
            
            invoke dwtoa, number, addr ans
            invoke StdOut, addr ans
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

onlyDigits	proc
			mov ecx, len2
			xor eax, eax
			lea ebx, str2
		rep3:
			mov dl, [ebx]
			cmp dl, 48
			jl fin2
			cmp dl, 57
			jg fin2
			inc ebx
			loop rep3
			
			mov eax, 1
		fin2:
			ret
onlyDigits endp

end MainProc
