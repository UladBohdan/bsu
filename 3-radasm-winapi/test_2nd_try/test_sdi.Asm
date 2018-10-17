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


IDD_SZDLG						equ 1000
IDC_WIDTH						equ 1001
IDC_OK							equ 1002
IDC_CANCEL						equ 1003
IDC_STC1						equ 1004
IDC_STC2						equ 1006
IDC_HEIGHT						equ 1007
IDR_MENU                        equ 10000
IDM_COLOR                       equ 10010
IDM_SZDLG                       equ 10011

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD

.data
   ClassName    db  "MainWinClass",0
   AppName      db  "Ellipse&Colors - RadASM",0
   szWrong      db  "Wrong value.",0
   
   w        dd  200
   h        dd  200

.data?
   hInstance    HINSTANCE   ?
   CommandLine  LPSTR       ?
   hDC          HDC ?
   ps           PAINTSTRUCT <>
   cc           CHOOSECOLOR <>
   
   buf      db  300 dup(?)
   path     db  300 dup(?)
   clrs     dd  16 dup(?)

   hEdit1       dd  ?
   hEdit2       dd  ?
   hBrush       dd  ?
   hPen         dd  ?
   
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

SizesProc proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov eax, uMsg
    .if eax==WM_INITDIALOG
        invoke GetDlgItem,hDlg,IDC_WIDTH
        mov hEdit1, eax
        invoke GetDlgItem,hDlg,IDC_HEIGHT
        mov hEdit2, eax
        invoke SetDlgItemInt,hDlg,IDC_WIDTH,w,TRUE
        invoke SetDlgItemInt,hDlg,IDC_HEIGHT,h,TRUE
        invoke SetFocus,hEdit1
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax, 0FFFFh
        .if eax==IDC_OK
            invoke GetDlgItemInt,hDlg,IDC_WIDTH,NULL,TRUE
            mov w, eax
            invoke GetDlgItemInt,hDlg,IDC_HEIGHT,NULL,TRUE
            mov h, eax
            invoke EndDialog,hDlg,1
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

SizesProc endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.if uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
	.elseif uMsg==WM_CREATE
		mov cc.rgbResult, 0
    .elseif uMsg==WM_PAINT
        invoke BeginPaint,hWnd,offset ps
        mov hDC, eax
        
        invoke CreatePen,PS_SOLID,5,0989690h
        mov hPen, eax
        invoke SelectObject,hDC,hPen
        invoke CreateSolidBrush,0989690h
        mov hBrush, eax
        invoke SelectObject,hDC,hBrush
        mov esi, w
        add esi, 20
        mov edi, h
        add edi, 5
        invoke Ellipse,hDC,20,5,esi,edi
        invoke DeleteObject,hBrush 
        invoke DeleteObject,hPen
      
        invoke CreatePen,PS_SOLID,5,cc.rgbResult
        mov hPen, eax
        invoke SelectObject,hDC,hPen
        invoke CreateSolidBrush,0FFFFFFh
        mov hBrush, eax
        invoke SelectObject,hDC,hBrush
        mov esi, w
        add esi, 10
        mov edi, h
        add edi, 10
        invoke Ellipse,hDC,10,10,esi,edi
        invoke DeleteObject,hBrush
        invoke DeleteObject,hPen
        
        invoke EndPaint,hDC,offset ps
        
    .elseif uMsg==WM_COMMAND
        mov eax, wParam
        and eax, 0FFFFh
        .if eax==IDM_COLOR
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
	        
        .elseif eax==IDM_SZDLG
            invoke DialogBoxParam,hInstance,IDD_SZDLG,NULL,SizesProc,NULL
            .if eax==1
                invoke InvalidateRect,hWnd,NULL,TRUE
            .endif
        .endif
	.else
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.endif
	
	xor eax,eax
	ret
WndProc endp


end start