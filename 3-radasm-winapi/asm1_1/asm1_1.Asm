.486
.model flat, stdcall                    
option casemap :none

include windows.inc     ; always first

include masm32.inc      ; StdOut, StdIn
include kernel32.inc      ; ExitProcess

includelib masm32.lib
includelib kernel32.lib

.data
    szHello      db  "Enter your string:", 13, 10, 0
    word1        db  300 dup(' ')
    buf          db  300 dup(' ')
    cur         dd  1
    wordempty   db  0
    temp        db  3 dup(?)
    tech1       db  ". ", 0  
.code

MainProc	proc
            invoke  StdOut, addr szHello
            invoke  StdIn, addr buf, 300
            mov buf[eax], 0
            lea ebx, buf
            lea edx, word1
            mov wordempty, 0    ; 0 for empty
        global:
            mov al, [ebx]    
            cmp al, 13
            je end1
            cmp al, 32
            je space
            ; have symbol - updating word1
            mov [edx], al
            inc edx
            mov wordempty, 1
            jmp cont1
        space:
            cmp wordempty, 0
            je cont1
            ; word is not empty:
            mov [edx], byte ptr 13
            inc edx
            mov [edx], byte ptr 10
            inc edx
            mov [edx], byte ptr 0
            invoke dwtoa, cur, addr temp
            invoke StdOut, addr temp
            invoke StdOut, addr tech1
            invoke StdOut, addr word1
            inc cur
            lea edx, word1
            mov wordempty, 0
            jmp cont1
        cont1:
            inc ebx
            loop global
        end1:
            cmp wordempty, 0
            je fin
            mov [edx], byte ptr 13
            inc edx
            mov [edx], byte ptr 10
            inc edx
            mov [edx], byte ptr 0
            invoke dwtoa, cur, addr temp
            invoke StdOut, addr temp
            invoke StdOut, addr tech1
            invoke StdOut, addr word1
            jmp fin
        fin:
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
