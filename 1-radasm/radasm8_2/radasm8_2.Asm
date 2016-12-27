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
    szHelloWorld        db  	"Your int number:", 13, 10, 0
    buf                 db  	300 dup(0)
    ans					db		50 dup(?)	; pairs p:alpha
    pos					dd		0
    x					dd		?
    divOn				dd		2
    fin_ans				dd		200 dup(0)
    temp				dd		?
    str1				db		20 dup(0)
    str2				db		20 dup(0)
.code

MainProc	proc
            invoke  StdOut, addr szHelloWorld
            invoke StdIn, addr buf, 300
            invoke atol, addr buf
            mov x, eax
    rep1:
        	mov eax, 1
        	cmp x, eax
        	je fin1
            
            mov esi, 0
            mov ecx, divOn    
            mov eax, x
        rep2:
        	cdq
            idiv ecx
            cmp edx, 0
            jne contin1
            
            mov x, eax
            inc esi
            jmp rep2
            
        contin1:
        	cmp esi, 0
        	je contin2
    		
            lea ebx, ans
            add ebx, pos
            mov eax, divOn
            mov [ebx], eax
            inc ebx
            mov [ebx], esi
            add pos, 2
        contin2:
    		inc divOn
    		jmp rep1
    
    fin1:
    		; formatting an answer in fin_ans
    		lea ebx, fin_ans
    		lea edx, buf
    		lea edi, fin_ans
    		mov cl, 13
    	rep3:
    		cmp [edx], cl
    		je cont4
    		mov al, [edx]
    		mov [ebx], al
    		inc edx
    		inc ebx
    		jmp rep3
    	cont4:
    		mov al, 3dh
    		mov [ebx], al
    		inc ebx
    		
    		mov edi, 0
    global_rep1:
    		mov ecx, pos
    		cmp ecx, 0
    		je glob_fin1
    		sub ecx, 2
    		mov pos, ecx
    		
    		lea edx, ans
    		xor eax, eax
    		mov al, byte ptr [edx+edi]
    		mov temp, eax
    		invoke dwtoa, temp, addr str1
    		lea edx, ans
    		xor eax, eax
    		inc edi
    		mov al, byte ptr [edx+edi]
    		inc edi
    		mov temp, eax
    		invoke dwtoa, temp, addr str2
    		mov cl, 0
    		lea edx, str1
    	rep5:
    		cmp [edx], cl
    		je cont6
    		mov al, [edx]
    		mov [ebx], al
    		inc edx
    		inc ebx
    		jmp rep5
    	cont6:
    		mov al, 5eh
    		mov [ebx], al
    		inc ebx
    		lea edx, str2
    	rep6:
    		cmp [edx], cl
    		je cont7
    		mov al, [edx]
    		mov [ebx], al
    		inc ebx
    		inc edx
    		jmp rep6
    		
    	cont7:
    	
    		mov al, 2ah
    		mov [ebx], al
    		inc ebx
    		jmp global_rep1
    		
    glob_fin1:
    		dec ebx
    		mov al, 0
    		mov [ebx], al
    		invoke StdOut, addr fin_ans
    		
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
