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
		szClassName, "Timer", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 350, 350,
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
	static LOGFONT lf;
	static HFONT hf;
	static int tm=0;
	static string tm_str="0";
	static bool timer_on=false;

	switch (msg)
	{
	case WM_CREATE:
		//CreateConsole();
		strcpy(lf.lfFaceName,"Times New Roman");
		lf.lfHeight=160;
		SetTimer(hWnd,NULL,1000,NULL);
		timer_on=true;
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={0,0};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		Ellipse(hDC,10,10,rect.right-10,rect.bottom-10);
		hf=CreateFontIndirect(&lf);
		SelectObject(hDC,hf);
		DrawText(hDC,tm_str.c_str(),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		DeleteObject(hf);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		{
			string temp="";
			int t=tm++;
			while (t)
			{
				temp=(char)(t%10+48)+temp;
				t/=10;
			}
			if (temp.empty()) temp="0";
			tm_str=temp.c_str();
		}
		InvalidateRect(hWnd,NULL,true);
		return 0;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case (VK_SUBTRACT):
			if (timer_on)
			{
				timer_on=false;
				KillTimer(hWnd,NULL);
			}
			break;
		case (VK_ADD):
			if (!timer_on)
			{
				SetTimer(hWnd,NULL,1000,NULL);
				timer_on=true;
			}
			break;
		case (0x53 & VK_CONTROL):
			tm=0;
			tm_str="0";
			break;
		default:
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
