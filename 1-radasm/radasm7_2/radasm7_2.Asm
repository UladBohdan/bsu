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
	c1					db	120

.data
    szHelloWorld        db  "ASCII table:", 13, 10, "(some of symbols are unvisible)", 13, 10, 0
    enterToExit         db  "Press enter to exit", 13, 10, 0
    row					db	19 dup(9), 13, 10, 0
    buf                 db  300 dup(' ')
    symb				db	0
.code

MainProc	proc
            invoke  StdOut, addr szHelloWorld
     rep1:
      	 	lea ebx, row
      	 	mov al, symb
      	 	mov ecx, 10
      	 rep2:
    		mov [ebx], al
    		inc al
    		add ebx, 2
    		loop rep2
    		invoke StdOut, addr row
    		add symb, 10
    		mov al, symb
    		sub al, 127
    		cmp al, c1
    		jge fin1		
    		jmp rep1	
			
         fin1:
            invoke StdOut, addr enterToExit
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc