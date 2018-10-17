.386
.model flat, stdcall  ;32 bit memory model
option casemap :none  ;case sensitive

include asm2_0.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov		hInstance,eax

    invoke InitCommonControls
	invoke DialogBoxParam,hInstance,IDD_DIALOG1,NULL,addr DlgProc,NULL
	invoke ExitProcess,0

;########################################################################

DlgProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	mov		eax,uMsg
	.if eax==WM_INITDIALOG
        invoke  GetDlgItem, hWin, IDC_LST1
        mov     hList, eax
        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szStringItem1
        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szStringItem2
        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szStringItem3
        invoke  GetDlgItem, hWin, IDC_EDT1
        mov     hEdit, eax 

	.elseif eax==WM_COMMAND
        mov     eax, wParam
        mov     bx, ax	; LOWORD(wParam) - control identifier
        shr     eax, 16	; HIWORD(wParam) -  notification code 
	    .if (bx==IDC_LST1) && (ax==LBN_SELCHANGE)
   	            invoke  SendMessage, hList, LB_GETCURSEL, 0, 0
   	            mov     nIndex,eax
                invoke  SendMessage, hList, LB_GETTEXT, nIndex, addr szBuffer
   	            invoke  SendMessage, hEdit, WM_SETTEXT, 0, addr szBuffer
    	        pop     eax
    	.elseif (bx==IDC_BTN1) && (ax==BN_CLICKED)
    	      ;  invoke  SendMessage,hEdit, LB_GETCURSEL, 0, 0
    	      ;  mov nIndex, eax
    	        invoke GetDlgItem, hWin, IDC_EDT1
    	        mov hEdit, eax
    	        invoke  SendMessage, hEdit, WM_GETTEXT, 0, addr tempBuf
    	        invoke  GetDlgItem, hWin, IDC_LST1
                mov     hList, eax
    	        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset tempBuf
        .endif

	.elseif eax==WM_CLOSE
		invoke EndDialog,hWin,0
	.else
		mov		eax,FALSE
		ret
	.endif
	mov		eax,TRUE
	ret

DlgProc endp

end start
