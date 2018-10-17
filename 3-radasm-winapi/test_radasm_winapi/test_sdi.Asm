.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include gdi32.inc
   include masm32.inc
   include comdlg32.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib gdi32.lib
   includelib masm32.lib
   includelib comdlg32.lib


IDR_MENU                        equ 10000
IDM_OPENFILE					equ 10009
IDM_COLOR						equ 10010
IDM_LETTER						equ 10011
IDD_LETT						equ 1000
IDC_EDT1						equ 1001
IDC_OK							equ 1002
IDC_CANCEL						equ 1003
IDC_STC1						equ 1004
IDC_CHK1                        equ 1005

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD

.data
   ClassName    db  "MainWinClass",0
   AppName      db  "Main Window",0
   
   let      db  'a'

.data?
   hInstance    HINSTANCE   ?
   CommandLine  LPSTR       ?
   hDC          HDC ?
   ps           PAINTSTRUCT <>
   rect         RECT        <>
   cc           CHOOSECOLOR <>
   ofn          OPENFILENAME <>
   
   buf      db  300 dup(?)
   path     db  300 dup(?)
   clrs     dd  16 dup(?)

   exists   db  ?
   hEdit    dd  ?
   
.code


; ---------------------------------------------------------------------------


start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	
	invoke GetCommandLine
	mov    CommandLine,eax
	
	invoke WinMain, hInstance,NULL,CommandLine, SW_SHOWDEFAULT
	invoke ExitProcess,eax

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
	
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	mov   wc.cbClsExtra,NULL
	mov   wc.cbWndExtra,NULL
	push  hInstance
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_BTNFACE+1
	mov   wc.lpszMenuName,IDR_MENU
	mov   wc.lpszClassName,OFFSET ClassName
	
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,eax
	
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	
	invoke RegisterClassEx, addr wc
	INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
           WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
           CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
           hInst,NULL
	mov   hwnd,eax
	
	invoke ShowWindow, hwnd,SW_SHOWNORMAL
	invoke UpdateWindow, hwnd
	
	.WHILE TRUE
		invoke GetMessage, ADDR msg,NULL,0,0
		.BREAK .IF (!eax)
		invoke TranslateMessage, ADDR msg
		invoke DispatchMessage, ADDR msg
	.ENDW
	
	mov     eax,msg.wParam
	ret
WinMain endp

LetterProc proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov eax, uMsg
    .if eax==WM_INITDIALOG
        invoke GetDlgItem,hDlg,IDC_EDT1
        mov hEdit, eax
        lea ebx, buf
        mov al, byte ptr let
        mov [ebx], al
        invoke SetFocus,hEdit
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax, 0FFFFh
        .if eax==IDC_OK
            invoke GetDlgItemText,hDlg,IDC_EDT1,addr buf,20
            lea ebx, buf
            mov esi, [ebx]
            invoke EndDialog,hDlg,esi
        .elseif eax==IDC_CANCEL
            invoke EndDialog,hDlg,-1
        .endif
        ret
    .elseif eax==WM_CLOSE
        invoke EndDialog,hDlg,-1
        ret
    .endif
 
    xor eax, eax
    ret

LetterProc endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.if uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
	.elseif uMsg==WM_CREATE
		;
    .elseif uMsg==WM_PAINT
        invoke BeginPaint,hWnd,offset ps
        mov hDC, eax
        invoke GetClientRect,hWnd,addr rect
        add rect.top, 50
        mov rect.bottom, 100
        invoke SetTextColor,hDC,cc.rgbResult
        invoke SetBkMode,hDC,TRANSPARENT
        invoke DrawText,hDC,ofn.lpstrFile,-1,addr rect,DT_CENTER
        lea ebx, buf
        mov [ebx], byte ptr 0
        add rect.top, 50
        add rect.bottom, 50
        invoke DrawText,hDC,addr buf,-1,addr rect,DT_CENTER
        lea ebx, buf
        lea edx, path
        mov exists, 0
        cycle2:
            mov al, [edx]
            .if ( al=='\' || al==0 )
                .if exists!=0
                    add rect.top, 50
                    add rect.bottom,50
                    mov al, 0
                    mov [ebx], al
                   ; invoke DrawText,hDC,addr buf,-1,addr rect,DT_CENTER
                   ; have a mistake here
                    mov exists, 0
                .endif
                .if al==0
                    jmp end1
                .endif
                lea ebx, buf
            .else
                mov [ebx], al
                .if al==let
                    mov exists, 1
                .endif
                inc ebx
            .endif
            inc edx
            jmp cycle2
        end1:
        
        invoke EndPaint,hDC,offset ps
        
    .elseif uMsg==WM_COMMAND
        mov eax, wParam
        and eax, 0FFFFh
        .if eax==IDM_OPENFILE
            mov ofn.lStructSize, sizeof ofn    
	        mov ofn.lpstrFile, offset path
	        mov ofn.nMaxFile, MAX_PATH
	        invoke GetOpenFileName, addr ofn
	        .if eax==TRUE
	            invoke InvalidateRect,hWnd,NULL,TRUE
	        .endif
	        
        .elseif eax==IDM_COLOR
            mov cc.lStructSize, sizeof cc
	        mov cc.lpCustColors, offset clrs
	        mov cc.Flags, CC_RGBINIT or CC_PREVENTFULLOPEN
	        invoke ChooseColor,addr cc
	        .if eax==TRUE
	            lea ebx, clrs
	            add ebx, 60
	            mov ecx, 16
	            cycle1:
	                mov eax, [ebx]
	                mov [ebx+4], eax
	                sub ebx, 4
	                loop cycle1
	            lea ebx, clrs
	            mov eax, cc.rgbResult
	            mov [ebx], eax
	            invoke InvalidateRect,hWnd,NULL,TRUE
	        .endif
	        
        .elseif eax==IDM_LETTER
            invoke DialogBoxParam,hInstance,IDD_LETT,NULL,LetterProc,NULL
            .if eax==-1
                
            .else
                mov let, al
            .endif
        .endif
    .elseif uMsg==WM_TIMER
        ;
	.else
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.endif
	
	xor eax,eax
	ret
WndProc endp


end start