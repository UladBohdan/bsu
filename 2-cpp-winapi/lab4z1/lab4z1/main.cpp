#include <algorithm>
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

const double PI=3.1415926;

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
		szClassName, "Main window", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 800, 500,
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
	static int h,w,color;
	static double ang1=0,ang2=PI,ax=0,t=0,v=5;
	static int pos=0;
	static string s;

	switch (msg)
	{
	case WM_CREATE:
		srand(time(NULL));
		GetClientRect(hWnd, &rect);
		h=rect.bottom;
		color=RGB(0,0,0);
		w=rect.right;	
		SetTimer(hWnd,NULL,50,NULL);
		return 0;
	case WM_PAINT:
		{
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		h=rect.bottom;
		w=rect.right;
		double axtemp=ax;
		s=" acceleration: ";
		if (axtemp<0.0)
		{
			s+="-";
			axtemp*=(-1);
		}
		s+=(char)((int)(axtemp)+48);
		s+=".";
		s+=(char)((int)(axtemp*10)%10+48);
		TextOut(hDC,0,0,s.c_str(),s.length());
		MoveToEx(hDC,0,h-30,NULL);
		LineTo(hDC,w,h-30);

		POINT pt[9]={ {-80+pos,h-70}, {-280+pos,h-70}, {-280+pos,h-150}, {-80+pos,h-150}, {-80+pos,h-220}, {0+pos,h-220}, {0+pos,h-70}, 
						{-80+pos,h-70}, {-80+pos,h-150} };
		Arc(hDC,-250+pos,h-110,-170+pos,h-30,-300,h-70,w+300,h-70);
		Arc(hDC,-120+pos,h-110,-40+pos,h-30,-300,h-70,w+300,h-70);
		if (ang1<PI)
		{
			MoveToEx(hDC,-210+pos,h-70,NULL);
			LineTo(hDC,-210+pos+cos(ang1)*40,h-70+sin(ang1)*40); 
		}
		if (ang2<PI)
		{
			MoveToEx(hDC,-80+pos,h-70,NULL);
			LineTo(hDC,-80+pos+cos(ang2)*40,h-70+sin(ang2)*40);
		}
		Polyline(hDC,pt,9);
		RECT clr={-275+pos,h-145,-85+pos,h-75};
		FillRect(hDC,&clr,(HBRUSH)CreateSolidBrush(color));
		EndPaint(hWnd, &ps);
		return 0;
		}

	case WM_TIMER:
		v=max(0,v+ax/10);
		pos+=v;
		ang1+=(PI*v/90);
		ang2+=(PI*v/90);
		color+=RGB(1,1,1);
		if (ang1>=2*PI) ang1-=2*PI;
		if (ang2>=2*PI) ang2-=2*PI;
		if (pos>w+285) 
		{
			pos=0;
			color=RGB(0,0,0);
		}
		InvalidateRect(hWnd,NULL,true);
		return 0;

	case WM_CHAR:
		if (wParam=='+')
			ax=min(1.0,ax+0.1);
		else if (wParam=='-')
			ax=max(-1.0,ax-0.1);
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
