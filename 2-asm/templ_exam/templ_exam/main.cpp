#include <windows.h>

#include "resource.h"

extern "C" int _fastcall func(int,int);

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
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			int a=GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			int b=GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT3, func(a,b), NULL);
		}
		break;
	}
	return FALSE;
}