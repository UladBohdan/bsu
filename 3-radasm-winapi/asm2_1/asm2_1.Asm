.386
.model flat,stdcall
option casemap:none

include asm2_1.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov    hInstance,eax
	invoke GetCommandLine
	invoke InitCommonControls
	mov		CommandLine,eax
	invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	invoke ExitProcess,eax

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL	wc:WNDCLASSEX
	LOCAL	msg:MSG

	mov		wc.cbSize,sizeof WNDCLASSEX
	mov		wc.style,CS_HREDRAW or CS_VREDRAW
	mov		wc.lpfnWndProc,offset WndProc
	mov		wc.cbClsExtra,NULL
	mov		wc.cbWndExtra,DLGWINDOWEXTRA
	push	hInst
	pop		wc.hInstance
	mov		wc.hbrBackground,COLOR_BTNFACE+1
	mov		wc.lpszMenuName,IDM_MENU
	mov		wc.lpszClassName,offset ClassName
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov		wc.hIcon,eax
	mov		wc.hIconSm,eax
	invoke LoadCursor,NULL,IDC_ARROW
	mov		wc.hCursor,eax
	invoke RegisterClassEx,addr wc
	invoke CreateDialogParam,hInstance,IDD_DIALOG,NULL,addr WndProc,NULL
	invoke ShowWindow,hWnd,SW_SHOWNORMAL
	invoke UpdateWindow,hWnd
	.while TRUE
		invoke GetMessage,addr msg,NULL,0,0
	  .BREAK .if !eax
		invoke TranslateMessage,addr msg
		invoke DispatchMessage,addr msg
	.endw
	mov		eax,msg.wParam
	ret

WinMain endp

RemoveProc proc hDlg:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

    mov eax, uMsg
    .if eax==WM_INITDIALOG
        ret
    .elseif eax==WM_COMMAND
        mov eax,wParam
        and eax,0FFFFh
        .if eax==IDC_BTN1
            invoke GetDlgItemText,hDlg,IDC_EDT2,addr buf,50
            lea ebx, buf
            .if (byte ptr [ebx] == 0)
                invoke EndDialog,hDlg,-1
                ret
            .endif
            invoke GetDlgItemInt,hDlg,IDC_EDT2,NULL,FALSE
            mov n, eax
            .if n==0
                invoke EndDialog,hDlg,-1
            .elseif
                dec n
                invoke EndDialog,hDlg,n
            .endif
            ret
        .elseif eax==IDC_BTN2
            invoke EndDialog,hDlg,-1
            ret
        .endif 
    .elseif eax==WM_CLOSE
        invoke EndDialog,hDlg,-1
        ret       
    .endif
    xor eax, eax
    ret
RemoveProc endp

WndProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	mov		eax,uMsg
	.if eax==WM_INITDIALOG
		push	hWin
		pop		hWnd
	.elseif eax==WM_COMMAND
		mov		eax,wParam
		and		eax,0FFFFh
		.if eax==IDM_FILE_EXIT
			invoke SendMessage,hWin,WM_CLOSE,0,0
		.elseif (eax==IDM_ADD) || (eax==IDC_BTN3)
		    invoke GetDlgItemText,hWin,IDC_EDT1,addr buf,50
		    lea ebx, buf
		    .if byte ptr [ebx]==0
		        invoke MessageBox,0,addr txtErr2,addr txtErr,0
		    .elseif
		        invoke GetDlgItem,hWin,IDC_LST1
		        mov hList, eax
		        invoke SendMessage,hList,LB_ADDSTRING,0,addr buf
		        lea ebx, buf
		        mov al, 0
		        mov [ebx], al
		        invoke SetDlgItemText,hWin,IDC_EDT1,addr buf
		    .endif
		    invoke GetDlgItem,hWin,IDC_EDT1
		    mov hEdit, eax
		    invoke SetFocus,hEdit
		.elseif (eax==IDM_REMOVE) || (eax==IDC_BTN4)
		    invoke DialogBoxParam,hInstance,IDD_DLG1,NULL,addr RemoveProc,NULL
		    mov n, eax
		    cmp eax, -1
		    je finx
		    invoke GetDlgItem,hWin,IDC_LST1
		    mov hList, eax
		    invoke SendMessage,hList,LB_GETCOUNT,0,0
		    dec eax
		    cmp n, eax
		    jg fin1x
		    invoke SendMessage,hList,LB_DELETESTRING,n,0
		    jmp finx
		   fin1x:
		    invoke MessageBox,0,addr txtErr1,addr txtErr,0
		    jmp finx
		   finx:
		.elseif eax==IDM_HELP_ABOUT
			invoke ShellAbout,hWin,addr AppName,addr AboutMsg,NULL
		.endif
	.elseif eax==WM_CLOSE
		invoke DestroyWindow,hWin
	.elseif uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
	.else
		invoke DefWindowProc,hWin,uMsg,wParam,lParam
		ret
	.endif
	xor    eax,eax
	ret

WndProc endp

end start
