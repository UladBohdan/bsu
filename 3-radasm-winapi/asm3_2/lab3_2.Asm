.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include gdi32.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib gdi32.lib


WinMain proto :DWORD,:DWORD,:DWORD,:DWORD


.data
    ClassName    db  "MainWinClass",0
    AppName      db  "Traffic lights",0
    i       dd  0
               ;r y g
    val     dd  0,0,1,
                0,0,1,
                0,0,1,
                0,0,0,
                0,0,1,
                0,0,0,
                0,0,1,
                0,1,0,
                0,1,0,
                0,1,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,1,0,
                1,1,0,

.data?
   hInstance    HINSTANCE   ?
   CommandLine  LPSTR       ?
   hDC          HDC         ?
   ps           PAINTSTRUCT <>
   rect         RECT        <>
   rect2        RECT        <>
   hbrush1      HBRUSH      ?
   hbrush2      HBRUSH      ?
   hbrush3      HBRUSH      ?
   redBrush     HBRUSH      ?
   yellowBrush  HBRUSH      ?
   greenBrush   HBRUSH      ?
   whiteBrush   HBRUSH      ?
   hpen         HPEN        ?
   
   k    dd  ?
   h    dd  ?
   x1   dd  ?
   y1   dd  ?
   x2   dd  ?
   y2   dd  ?

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
	    invoke DeleteObject,hpen
	    invoke DeleteObject,hbrush1
	    invoke DeleteObject,hbrush2
	    invoke DeleteObject,hbrush3
	    invoke DeleteObject,redBrush
	    invoke DeleteObject,greenBrush
	    invoke DeleteObject,yellowBrush
	    invoke KillTimer,hWnd,1
		invoke PostQuitMessage,NULL
	.elseif uMsg==WM_CREATE
	    invoke MoveWindow,hWnd,50,50,200,550,TRUE
		invoke CreatePen,PS_NULL,0,0FFFFFFh
		mov hpen, eax
		invoke CreateSolidBrush,00000FFh
		mov redBrush, eax
		invoke CreateSolidBrush,000FFFFh
		mov yellowBrush, eax
		invoke CreateSolidBrush,000FF00h
		mov greenBrush, eax
		invoke CreateSolidBrush,0FFFFFFh
		mov whiteBrush, eax
	    push whiteBrush
		pop hbrush1
		push whiteBrush
		pop hbrush2
		push whiteBrush
		pop hbrush3
		invoke SetTimer,hWnd,1,700,0
    .elseif uMsg==WM_PAINT
        invoke BeginPaint,hWnd,addr ps
        mov hDC, eax
        
        invoke SelectObject,hDC,hpen
        invoke GetClientRect,hWnd,addr rect2
        mov eax, rect2.right
        sub eax, rect2.left
        mov ecx, 50
        cdq
        idiv ecx
        mov k, eax
        mov eax, rect2.bottom
        sub eax, rect2.top
        mov ecx, 3
        cdq
        idiv ecx
        sub eax, k
        sub eax, k
        mov h, eax
        
        mov ebx, k
        mov x1, ebx
        mov y1, ebx
        mov ebx, rect2.right
        sub ebx, k
        mov x2, ebx
        mov ebx, h
        add ebx, k
        mov y2, ebx
        invoke SelectObject,hDC,hbrush1
        invoke Rectangle,hDC,x1,y1,x2,y2
        
        mov ebx, h
        add ebx, k
        add y1, ebx
        add y2, ebx
        invoke SelectObject,hDC,hbrush2
        invoke Rectangle,hDC,x1,y1,x2,y2
        
        mov ebx, h
        add ebx, k
        add y1, ebx
        add y2, ebx
        invoke SelectObject,hDC,hbrush3
        invoke Rectangle,hDC,x1,y1,x2,y2
        invoke EndPaint,hDC,addr ps
    .elseif uMsg==WM_TIMER
        mov ebx, i
        imul ebx, 12
        mov ecx, val[ebx]
        .if ecx==0
            push whiteBrush
            pop hbrush1
        .elseif
            push redBrush
            pop hbrush1
        .endif
        mov ecx, val[ebx+4]
        .if ecx==0
            push whiteBrush
            pop hbrush2
        .elseif
            push yellowBrush
            pop hbrush2
        .endif
        mov ecx, val[ebx+8]
        .if ecx==0
            push whiteBrush
            pop hbrush3
        .elseif
            push greenBrush
            pop hbrush3
        .endif
        inc i
        .if i==15
            mov i, 0
        .endif
        invoke InvalidateRect,hWnd,0,TRUE
	.else
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.endif
	
	xor eax,eax
	ret
WndProc endp


end start
