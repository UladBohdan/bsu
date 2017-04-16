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

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}
	
	hMainWnd = CreateWindow( 
		szClassName, "Traffic light", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 100, 400,
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
	RECT rect;
	static int h,w,t=0;
	static int type=0;
	static HBRUSH r,g,y;

	switch (msg)
	{
	case WM_CREATE:
		r=CreateSolidBrush(RGB(255,0,0));
		g=CreateSolidBrush(RGB(0,255,0));
		y=CreateSolidBrush(RGB(255,255,0));
		SetTimer(hWnd,NULL,600,NULL);
		return 0;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		h=rect.bottom;
		w=rect.right;
		Ellipse(hDC,10,10,w-10,h/3-10);
		Ellipse(hDC,10,h/3+10,w-10,2*h/3-10);
		Ellipse(hDC,10,2*h/3+10,w-10,h-10);
		switch (type)
		{
		case(0):
			SelectObject(hDC,g);
			Ellipse(hDC,10,2*h/3+10,w-10,h-10);
			break;
		case (1):
			SelectObject(hDC,y);
			Ellipse(hDC,10,h/3+10,w-10,2*h/3-10);
			break;
		case (3):
			SelectObject(hDC,r);
			Ellipse(hDC,10,10,w-10,h/3-10);
			break;
		case (4):
			SelectObject(hDC,r);
			Ellipse(hDC,10,10,w-10,h/3-10);
			SelectObject(hDC,y);
			Ellipse(hDC,10,h/3+10,w-10,2*h/3-10);
			break;
		default:
			break;
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		if (t<5)
			type=0;
		else if (t==5 || t==7 || t==9)
			type=1;
		else if (t==6 || t==8)
			type=2;
		else if (t>=10 && t<=14)
			type=3;
		else
			type=4;
		t++;
		t%=17;
		InvalidateRect(hWnd,NULL,true);
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
