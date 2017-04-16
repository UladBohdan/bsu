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

struct ROUND
{
	int x, y, r, clr;
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
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}
	
	hMainWnd = CreateWindow( 
		szClassName, "Main window", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 900, 600,
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
	static int RAD=30;
	static vector <ROUND> v;

	switch (msg)
	{
	case WM_CREATE:
		srand(time(NULL));
		return 0;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		{
			for (unsigned int i=0; i<v.size(); i++)
			{
				HBRUSH br=CreateSolidBrush(v[i].clr);
				SelectObject(hDC,br);
				Ellipse(hDC,v[i].x-v[i].r,v[i].y-v[i].r,v[i].x+v[i].r,v[i].y+v[i].r);
				DeleteObject(br);
			}
		}
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		{
			bool found=false;
			int x=LOWORD(lParam), y=HIWORD(lParam);
			for (unsigned int i=0; i<v.size(); i++)
				if ((x-v[i].x)*(x-v[i].x)+(y-v[i].y)*(y-v[i].y)<v[i].r*v[i].r)
				{
					v[i].r+=10;
					found=true;
				}
			if (!found)
			{
				ROUND temp={x,y,RAD,RGB(200,rand()%255,rand()%255)};
				v.push_back(temp);
			}
		}
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
