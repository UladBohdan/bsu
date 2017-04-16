#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
#include <windows.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

	switch (msg)
	{
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={300,300};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		{
			int w=rect.right, h=rect.bottom, k=rect.right/25;

			HPEN hPen1=CreatePen(PS_DASHDOT,1,RGB(10,10,10));
			SelectObject(hDC,hPen1);
			MoveToEx(hDC,rect.right/2,0,NULL);
			LineTo(hDC,rect.right/2,rect.bottom);
			MoveToEx(hDC,0,rect.bottom/2,NULL);
			LineTo(hDC,rect.right,rect.bottom/2);

			HPEN hPen2=CreatePen(PS_INSIDEFRAME,2,RGB(255,0,0));
			SelectObject(hDC,hPen2);
			Ellipse(hDC,k,k,w/2-k,h/2-k);
			hPen2=CreatePen(PS_INSIDEFRAME,2,RGB(0,255,0));
			SelectObject(hDC,hPen2);
			Rectangle(hDC,k,k+h/2,w/2-k,h-k);
			hPen2=CreatePen(PS_INSIDEFRAME,2,RGB(0,0,255));
			SelectObject(hDC,hPen2);
			POINT arr1[4]={ {3*w/4,k}, {w-k,h/4}, {3*w/4,h/2-k}, {w/2+k,h/4} };
			Polygon(hDC,arr1,4);
			hPen2=CreatePen(PS_INSIDEFRAME,2,RGB(255,50,0));
			SelectObject(hDC,hPen2);
			Pie(hDC,2*k,h/2+k,w-k,3*h/2-3*k, w,h-k,w,h-k-(0.5773*(w/2-2*k)));

			RECT temp={0,0,w/2,h/2};
			DrawText(hDC,"Ellipse",-1,&temp,DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			SetRect(&temp,w/2,0,w,h/2);
			DrawText(hDC,"Rhombus",-1,&temp,DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			SetRect(&temp,0,h/2,w/2,h);
			DrawText(hDC,"Rectangle",-1,&temp,DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			SetRect(&temp,w/2,h/2,w,h);
			DrawText(hDC,"Pie",-1,&temp,DT_SINGLELINE | DT_VCENTER | DT_CENTER);

			DeleteObject(hPen1);
			DeleteObject(hPen2);
		}
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
