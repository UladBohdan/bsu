.486
.model flat, stdcall                    
option casemap :none

; 4.	Найти сумму цифр натурального числа.

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
    szHello     db  "Enter your number: ", 0
    szAns       db  "Sum of digits: ", 0
    buf         db  300 dup(' ')
    
.code

MainProc	proc
            invoke  StdOut, addr szHello
            invoke  StdIn, addr buf, 300
            invoke atol, addr buf ; answer in eax
            xor ebx, ebx
        loop1:
            mov ecx, 10
            cdq
            idiv ecx
            add ebx, edx
            cmp eax, 0
            je end1
            jmp loop1
        end1:
            invoke dwtoa, ebx, addr buf
            invoke StdOut, addr szAns
            invoke StdOut, addr buf
            invoke StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
