
include windows.inc
include kernel32.inc
include user32.inc
include Comctl32.inc
include shell32.inc

includelib kernel32.lib
includelib user32.lib
includelib Comctl32.lib
includelib shell32.lib

DlgProc			PROTO	:HWND,:UINT,:WPARAM,:LPARAM

.const

IDD_DIALOG1			equ 101
IDC_LST1            equ 1002
IDC_EDT1            equ 1001
IDC_BTN1            equ 1003

;#########################################################################

.data?

hInstance   dd ?
hList       dd ?
hEdit       dd ?
nIndex      dd ?
szBuffer    db 50 dup (?)
tempBuf     db 50 dup (?)

;#########################################################################

.data
szStringItem1       db  "Item1",0
szStringItem2       db  "Item2",0
szStringItem3       db  "Item3",0
