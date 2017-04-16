#include <cmath>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <windows.h>

#include "resource1.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

static int thick=1, clr2;

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
	static HACCEL ac;
	
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
		szClassName, "Main window", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 800, 310,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
	);
	
	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, nCmdShow); 

	ac = LoadAccelerators(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (GetMessage(&msg, NULL, 0, 0))  {
		if (!TranslateAccelerator(hMainWnd,ac,&msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	static int h,w,clr1,clr3,r;
	static POINT c[3];
	static int on[3]={1,1,1};
	static HMENU contxt;

	switch (msg)
	{
	case WM_CREATE:
		contxt = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU2));
		contxt = GetSubMenu(contxt,0);
		srand(time(NULL));
		clr1=RGB(rand()%255,rand()%255,rand()%255);
		clr2=RGB(rand()%255,rand()%255,rand()%255);
		clr3=RGB(rand()%255,rand()%255,rand()%255);
		GetClientRect(hWnd, &rect);
		h=rect.bottom;
		w=rect.right;
		c[0].x=w/6; c[0].y=h/2;
		c[1].x=w/2; c[1].y=h/2;
		c[2].x=5*w/6; c[2].y=h/2;
		r=h/2-60;
		return 0;
	case WM_PAINT:
		{
		hDC = BeginPaint(hWnd, &ps);

		HPEN tempPen = CreatePen(PS_SOLID,thick,0);
		SelectObject(hDC,tempPen);
		HBRUSH temp=CreateSolidBrush(clr1);
		SelectObject(hDC,temp);
		Ellipse(hDC,40+20*on[0],40+20*on[0],w/3-40-20*on[0],h-40-20*on[0]);
		temp=CreateSolidBrush(clr2);
		SelectObject(hDC,temp);
		Ellipse(hDC,w/3+40+20*on[1],40+20*on[1],2*w/3-40-20*on[1],h-40-20*on[1]);
		temp=CreateSolidBrush(clr3);
		SelectObject(hDC,temp);
		Ellipse(hDC,2*w/3+40+20*on[2],40+20*on[2],w-40-20*on[2],h-40-20*on[2]);
		
		EndPaint(hWnd, &ps);
		return 0;
		}

	case WM_LBUTTONDOWN:
		{
			int x=LOWORD(lParam), y=HIWORD(lParam);
			if ((x-c[0].x)*(x-c[0].x)+(y-c[0].y)*(y-c[0].y)<=r*r)
			{
				SetTimer(hWnd,0,200,NULL);
				on[0]=1;
			}
			else if ((x-c[1].x)*(x-c[1].x)+(y-c[1].y)*(y-c[1].y)<=r*r)
			{
				SetTimer(hWnd,1,300,NULL);
				on[1]=1;
			}
			else if ((x-c[2].x)*(x-c[2].x)+(y-c[2].y)*(y-c[2].y)<=r*r)
			{
				SetTimer(hWnd,2,400,NULL);
				on[2]=1;
			}
			return 0;
		}

	case WM_RBUTTONDOWN:
		{
			int x=LOWORD(lParam), y=HIWORD(lParam);
			if ((x-c[0].x)*(x-c[0].x)+(y-c[0].y)*(y-c[0].y)<=r*r)
			{
				KillTimer(hWnd,0);
				on[0]=1;
			}
			else if ((x-c[1].x)*(x-c[1].x)+(y-c[1].y)*(y-c[1].y)<=r*r)
			{
				KillTimer(hWnd,1);
				on[1]=1;
			}
			else if ((x-c[2].x)*(x-c[2].x)+(y-c[2].y)*(y-c[2].y)<=r*r)
			{
				KillTimer(hWnd,2);
				on[2]=1;
			} 
			else 
			{
				POINT p={x,y};
				ClientToScreen(hWnd,&p);
				TrackPopupMenuEx(contxt,NULL,p.x,p.y,hWnd,NULL);
			}
			InvalidateRect(hWnd,NULL,true);
			return 0;
		}

	case WM_TIMER:
		{
			on[wParam]*=(-1);
			InvalidateRect(hWnd,NULL,true);
			return 0;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_MAIN_STARTALL:
				SetTimer(hWnd,0,200,NULL);
				SetTimer(hWnd,1,300,NULL);
				SetTimer(hWnd,2,400,NULL);
				on[0]=1;
				on[1]=1;
				on[2]=1;
				break;
			case ID_MAIN_STOPALL:
				KillTimer(hWnd,0);
				KillTimer(hWnd,1);
				KillTimer(hWnd,2);
				on[0]=1;
				on[1]=1;
				on[2]=1;
				break;
			case ID_MAIN_EXIT:
				DestroyWindow(hWnd);
				break;
			case ID_SMTH_STOPALL:
				KillTimer(hWnd,0);
				KillTimer(hWnd,1);
				KillTimer(hWnd,2);
				on[0]=1;
				on[1]=1;
				on[2]=1;
				break;
			case ID_SMTH_CHANGECOLORS:
				srand(time(NULL));
				clr1=RGB(rand()%255,rand()%255,rand()%255);
				clr2=RGB(rand()%255,rand()%255,rand()%255);
				clr3=RGB(rand()%255,rand()%255,rand()%255);
				InvalidateRect(hWnd,NULL,true);
				break;
			case ID_ABOUT:
				DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ABOUT),hWnd,AboutDlgProc);
				InvalidateRect(hWnd,NULL,true);
				break;
			default:
				break;
			}
			return 0;
		}

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

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		if (thick==1)
			CheckRadioButton(hDlg,IDC_RADIO4,IDC_RADIO6,IDC_RADIO4);
		else if (thick==2)
			CheckRadioButton(hDlg,IDC_RADIO4,IDC_RADIO6,IDC_RADIO5);
		else if (thick==3)
			CheckRadioButton(hDlg,IDC_RADIO4,IDC_RADIO6,IDC_RADIO6);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (IsDlgButtonChecked(hDlg,IDC_RADIO4))
				thick=1;
			else if (IsDlgButtonChecked(hDlg,IDC_RADIO5))
				thick=2;
			else if (IsDlgButtonChecked(hDlg,IDC_RADIO6))
				thick=3;
			if (IsDlgButtonChecked(hDlg,IDC_RADIO1))
				clr2=RGB(255,0,0);
			else if (IsDlgButtonChecked(hDlg,IDC_RADIO2))
				clr2=RGB(0,255,0);
			else if (IsDlgButtonChecked(hDlg,IDC_RADIO3))
			{
				srand(time(NULL));
				clr2=RGB(rand()%255,rand()%255,rand()%255);
			}
		case IDCANCEL:
			EndDialog(hDlg,0);
			return true;
		}
		break;
	}
	return false;
}
