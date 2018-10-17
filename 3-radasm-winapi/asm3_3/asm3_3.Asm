.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include gdi32.inc
   include comdlg32.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib gdi32.lib
   includelib comdlg32.lib


WinMain proto :DWORD,:DWORD,:DWORD,:DWORD


.data
    ClassName   db  "MainWinClass",0
    AppName     db  "Main Window",0
    strText     db  "Text ... Text ... Text",0
    nameFont    db  "Times New Roman",0
 
.data?
    hInstance       HINSTANCE   ?
    CommandLine     LPSTR       ?
    cc              CHOOSECOLOR <>
    ps              PAINTSTRUCT <>
    rect            RECT        <>
    
    hDC     HDC     ?
    hfont   HFONT   ?
    
    clrs    dd  16 dup(?)

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
	mov   wc.lpszMenuName,NULL
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

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.if uMsg==WM_DESTROY
	    invoke DeleteObject,hfont
		invoke PostQuitMessage,NULL
	.elseif uMsg==WM_CREATE
	    invoke CreateFont,60,0,0,0,0,FALSE,0,0,0,0,0,0,0,addr nameFont
	    mov hfont,eax
	    
	.elseif uMsg==WM_PAINT
	    invoke BeginPaint,hWnd,addr ps
	    mov hDC, eax
	    invoke GetClientRect,hWnd,addr rect
	    invoke SetBkMode,hDC,TRANSPARENT
	    invoke SelectObject,hDC,hfont
	    invoke SetTextColor,hDC,cc.rgbResult
	    invoke DrawText,hDC,addr strText,-1,addr rect,DT_CENTER or DT_SINGLELINE or DT_VCENTER
	    invoke EndPaint,hDC,addr ps
	    
    .elseif uMsg==WM_RBUTTONDOWN
        mov cc.lStructSize, sizeof cc
		mov cc.lpCustColors, offset clrs
		mov cc.Flags, CC_RGBINIT or CC_PREVENTFULLOPEN
	    invoke ChooseColor, addr cc
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
	.else
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	xor eax,eax
	ret
WndProc endp


end start
