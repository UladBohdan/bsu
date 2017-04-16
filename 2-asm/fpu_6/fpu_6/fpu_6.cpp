#include <windows.h>
#include <ios>
#include <stdlib.h>
#include <stdio.h>

#include "resource.h"

using namespace std;

//extern "C" void _stdcall func(float, float*);

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		static float x, a[3];
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			char num[20];
			GetDlgItemText(hDlg,IDC_EDIT1,num,20);
			x=atof(num);
			__asm
			{
				finit
				fld x
				fmul x
				fst a[0]

				finit 
				fld1
				fld x
				fabs
				fyl2x
				fst a[4]

				finit
				fld x
				fsin
				fst a[8]
			}
			sprintf(num,"%f",a[0]);
			SetDlgItemText(hDlg, IDC_EDIT2, (LPCSTR)num);
			sprintf(num,"%f",a[1]);
			SetDlgItemText(hDlg, IDC_EDIT3, (LPCSTR)num);
			sprintf(num,"%f",a[2]);
			SetDlgItemText(hDlg, IDC_EDIT4, (LPCSTR)num);
		}
		break;
	}
	return FALSE;
}