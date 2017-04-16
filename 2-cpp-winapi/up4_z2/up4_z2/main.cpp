#include <algorithm>
#include <cmath>
#include <deque>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
#include <windows.h>

#include "resource.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

static int thick;

struct ONE {
	BOOL rect;
	int x1, y1, x2, y2;
	int th;
	int pclr, bclr;
};

void CreateConsole()
{
	if (AllocConsole()) 
	{ 
		int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 4); 
		*stdout = *(::_fdopen(hCrt, "w")); 
		::setvbuf(stdout, NULL, _IONBF, 0); 
		*stderr = *(::_fdopen(hCrt, "w")); 
		::setvbuf(stderr, NULL, _IONBF, 0);
		std::ios::sync_with_stdio();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd;  
	char szClassName[] = "MyClass";
	MSG msg;
	WNDCLASSEX wc;
	
	wc.cbSize        = sizeof(wc);		
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = szClassName;
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}
	
	hMainWnd = CreateWindow( 
		szClassName, "Micropaint", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
	);
	
	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, nCmdShow); 

	while (GetMessage(&msg, NULL, 0, 0))  {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	static int h, w;
	static HMENU contxt;
	static BOOL rectdraw=true, tracking=false;
	static int penclr=0, brushclr=RGB(255,255,255);
	static CHOOSECOLOR cc;
	static COLORREF clrs[16];
	static vector <ONE> v;
	static HPEN pen, hDotPen;
	static HBRUSH brush, hOldBrush;
	static int x1t, y1t, x2t, y2t;

	switch (msg)
	{
	case WM_CREATE:
		contxt=LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MENU2));
		contxt=GetSubMenu(contxt,NULL);
		cc.lStructSize=sizeof(CHOOSECOLOR);
		cc.hwndOwner=hWnd;
		cc.lpCustColors=(LPDWORD)clrs;
		cc.Flags=CC_FULLOPEN|CC_SOLIDCOLOR;
		thick=1;
		hDotPen=CreatePen(PS_DOT,1,0);
		//CreateConsole();
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={0,0};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (unsigned int i=0; i<v.size(); i++)
		{
			pen=CreatePen(PS_SOLID,v[i].th,v[i].pclr);
			SelectObject(hDC,pen);
			brush=CreateSolidBrush(v[i].bclr);
			SelectObject(hDC,brush);
			if (v[i].rect)
				Rectangle(hDC,v[i].x1,v[i].y1,v[i].x2,v[i].y2);
			else
				Ellipse(hDC,v[i].x1,v[i].y1,v[i].x2,v[i].y2);
		}
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_RBUTTONDOWN:
		{
			POINT p={LOWORD(lParam),HIWORD(lParam)};
			ClientToScreen(hWnd,&p);
			TrackPopupMenuEx(contxt,NULL,p.x,p.y,hWnd,NULL);
		}
		return 0;

	case WM_LBUTTONDOWN:
		hDC=GetDC(hWnd);
		tracking=true;
		SetROP2(hDC,R2_NOTXORPEN);
		x1t=x2t=LOWORD(lParam);
		y1t=y2t=HIWORD(lParam);
		rectdraw ? Rectangle(hDC,x1t,y1t,x2t,y2t) : Ellipse(hDC,x1t,y1t,x2t,y2t);
		ReleaseDC(hWnd,hDC);
		break;

	case WM_LBUTTONUP:
		if (tracking)
		{
			hDC=GetDC(hWnd);
			tracking=false;
			SetROP2(hDC,R2_COPYPEN);
			ONE temp={rectdraw,x1t,y1t,x2t,y2t,thick,penclr,brushclr};
			v.push_back(temp);
			ReleaseDC(hWnd,hDC);
			InvalidateRect(hWnd,NULL,true);
		}
		break;

	case WM_MOUSEMOVE:
		if (tracking)
		{
			hDC=GetDC(hWnd);
			SelectObject(hDC,hDotPen);
			rectdraw ? Rectangle(hDC,x1t,y1t,x2t,y2t) : Ellipse(hDC,x1t,y1t,x2t,y2t);
			x2t=LOWORD(lParam);
			y2t=HIWORD(lParam);
			rectdraw ? Rectangle(hDC,x1t,y1t,x2t,y2t) : Ellipse(hDC,x1t,y1t,x2t,y2t);
			ReleaseDC(hWnd,hDC);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_SWITCH:
			rectdraw ? rectdraw=false : rectdraw=true;
			break;
		case ID_PENCOLOR:
			if (ChooseColor(&cc))
				penclr=cc.rgbResult;
			break;
		case ID_BRUSHCOLOR:
			if (ChooseColor(&cc))
				brushclr=cc.rgbResult;
			break;
		case ID_PENTHICKNESS:
			DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DlgProc);
			break;
		}
		return 0;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

    case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:		
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{		
		case IDOK:
			if (IsDlgButtonChecked(hDlg,IDC_RADIO1))
				thick=1;
			else if (IsDlgButtonChecked(hDlg,IDC_RADIO2))
				thick=2;
			else if (IsDlgButtonChecked(hDlg,IDC_RADIO3))
				thick=3;
		case IDCANCEL:
			EndDialog(hDlg,0);
			return true;
		}
		break;
	}
	return false;
}