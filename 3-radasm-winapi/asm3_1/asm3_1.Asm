.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include comdlg32.inc
   include gdi32.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib comdlg32.lib
   includelib gdi32.lib


WinMain         proto :DWORD,:DWORD,:DWORD,:DWORD
MoveDlgProc     proto :HWND,:UINT,:WPARAM,:LPARAM

IDR_MENU    equ 10000
IDM_COLOR   equ 10001
IDM_HOR     equ 10002
IDM_VERT    equ 10003
IDM_FILE    equ 10004

IDD_MOVEDLG equ 1000
IDC_LST1    equ 1001
IDC_OK      equ 1002
IDC_CANCEL  equ 1003

.const
    ClassName    db  "MainWinClass",0
    AppName      db  "Main Window",0
    val1         db  "+150", 0
    val2         db  "+300", 0
    val3         db  "-150", 0
     
.data
    values      dd  150, 300, -150

.data?
   hInstance    HINSTANCE   ?
   CommandLine  LPSTR       ?
   
   file     OPENFILENAME    <>
   clr      CHOOSECOLOR     <>
   ps       PAINTSTRUCT     <>
   rect     RECT            <>
   
   buf      db  500 dup(?)
   clrs     dd  16  dup(?)
   
   hpen     dd  ?
   hbrush   dd  ? 
   hDC      dd  ?
   hList    dd  ?
   hButton  dd  ?
   x        dd  ?
   y        dd  ?
   wdth     dd  ?
   hght     dd  ?
   
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

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.IF uMsg==WM_DESTROY
	    invoke DeleteObject,hpen
	    invoke DeleteObject,hbrush
		invoke PostQuitMessage,NULL
		
	.ELSEIF uMsg==WM_CREATE
		invoke CreatePen,PS_NULL,0,0FFFFFFh
        mov hpen, eax
        
    .elseif uMsg==WM_PAINT
        invoke BeginPaint,hWnd,addr ps
        mov hDC, eax
        invoke SelectObject,hDC,hbrush
        invoke SelectObject,hDC,hpen
        invoke GetClientRect,hWnd,addr rect        
        invoke Rectangle,hDC,rect.left,rect.top,rect.right,rect.bottom
        invoke EndPaint,hDC,addr ps
 
	.ELSEIF uMsg==WM_COMMAND
	    mov eax, wParam
	    and eax, 0FFFFh
	    .if eax==IDM_COLOR
	        mov clr.lStructSize, sizeof clr
	        mov clr.lpCustColors, offset clrs
	        mov clr.Flags, CC_RGBINIT or CC_PREVENTFULLOPEN
	        invoke ChooseColor,addr clr
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
	            mov eax, clr.rgbResult
	            mov [ebx], eax
	            invoke DeleteObject,hbrush
	            invoke CreateSolidBrush,clr.rgbResult
	            mov hbrush, eax
	            invoke InvalidateRect,hWnd,NULL,TRUE
	        .endif
	        	        
	    .elseif (eax==IDM_HOR || eax==IDM_VERT)
	            mov edi, eax
	            invoke DialogBoxParam,hInstance,IDD_MOVEDLG,NULL,MoveDlgProc,NULL
	            mov esi, eax   
	            .if esi!=-1
                    invoke GetWindowRect,hWnd,addr rect
                    mov eax, rect.right
	                sub eax, rect.left
	                mov wdth, eax
	                mov eax, rect.bottom
	                sub eax, rect.top
	                mov hght, eax
	                .if edi==IDM_HOR
	                    mov eax, rect.left
	                    add eax, esi
	                    mov x, eax
	                    mov eax, rect.top
	                    mov y, eax
	                .elseif
	                    mov eax, rect.left
	                    mov x, eax
	                    mov eax, rect.top
	                    add eax, esi
	                    mov y, eax
	                .endif
	                invoke MoveWindow,hWnd,x,y,wdth,hght,TRUE
	            .endif
	    .elseif eax==IDM_FILE
	        mov file.lStructSize, sizeof file    
	        mov file.lpstrFile, offset buf
	        mov file.nMaxFile, MAX_PATH
	        invoke GetOpenFileName, addr file
	        .if eax==TRUE
	            invoke SetWindowText,hWnd,file.lpstrFile
	        .endif
	    .endif
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	xor eax,eax
	ret
WndProc endp

MoveDlgProc proc    hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM 
    
    mov eax, uMsg
    .if eax==WM_INITDIALOG
        invoke GetDlgItem,hDlg,IDC_LST1
        mov hList, eax
        invoke SendMessage,hList,LB_ADDSTRING,0,offset val1
        invoke SendMessage,hList,LB_ADDSTRING,0,offset val2
        invoke SendMessage,hList,LB_ADDSTRING,0,offset val3
        invoke SendMessage,hList,LB_SETCURSEL,0,0
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax, 0FFFFh
        .if eax==IDC_OK
            invoke SendMessage,hList,LB_GETCURSEL,0,0
            .if eax==LB_ERR
                    invoke EndDialog,hDlg,-1
            .elseif
                    invoke EndDialog,hDlg,values[eax*4]
            .endif
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
MoveDlgProc endp

end start
