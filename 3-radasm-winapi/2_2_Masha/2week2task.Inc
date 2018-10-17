include windows.inc
include user32.inc
include kernel32.inc
include shell32.inc
include comctl32.inc
include comdlg32.inc
include masm32.inc

includelib user32.lib
includelib kernel32.lib
includelib shell32.lib
includelib comctl32.lib
includelib comdlg32.lib
includelib masm32.lib

WinMain				PROTO :DWORD,:DWORD,:DWORD,:DWORD
WndProc				PROTO :DWORD,:DWORD,:DWORD,:DWORD

IDD_DIALOG			equ 1000

IDM_MENU			equ 10000
IDM_FILE_EXIT		equ 10001
IDM_HELP_ABOUT		equ 10101

IDC_BTN1 equ 1001
IDC_BTN2 equ 1002
IDC_BTN3 equ 1003
IDC_BTN4 equ 1004
IDC_BTN5 equ 1005

.const

ClassName			db 'DLGCLASS',0
AppName				db 'Dialog as main',0
AboutMsg			db 'MASM32 RadASM Dialog as main',13,10,'Copyright © MASM32 2001',0
n                   dd  7
STR1                db  "BUTTON",0

.const
STR2        db  "Push",0

.data?

hInstance			dd ?
CommandLine			dd ?
hWnd				dd ?
hButton             dd ?
temp                dw ?
rect        RECT    <>

.data
i       dd  11001
left    dd  20
