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
		szClassName, "Main window", WS_OVERLAPPEDWINDOW,
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
	RECT rect;
	static int h, w;

	switch (msg)
	{
	case WM_CREATE:
		CreateConsole();
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
		///
		
		EndPaint(hWnd, &ps);
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
