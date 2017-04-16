#include <algorithm>
#include <cmath>
#include <deque>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iterator>
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
	static BOOL havefile=false;
	static int h, w, M=15;
	static OPENFILENAME ofn;
	static char szFile[100];
	static ifstream fin;
	static vector <int> v (20);

	switch (msg)
	{
	case WM_CREATE:
	//	CreateConsole();
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.hwndOwner=hWnd;
		ofn.lpstrFile=szFile;
		ofn.nMaxFile=sizeof(szFile);
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={0,0};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (havefile)
		{
			GetClientRect(hWnd, &rect);
			h=rect.bottom;
			w=rect.right;
			srand(time(NULL));
			int a=min(h,w);
			//Ellipse(hDC,M,M,a-M,a-M);
			int r=a/2-M, s=0;
			for (int i=0; i<v.size(); i++)
				s+=v[i];
			double ang=0, angold, e=2*acos(-1.)/s;
			SelectObject(hDC,CreatePen(PS_SOLID,3,RGB(255,255,255)));
			SetBkMode(hDC,TRANSPARENT);
			for (int i=0; i<v.size(); i++)
			{
				SelectObject(hDC,CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256)));
				Pie(hDC,M,M,a-M,a-M,a/2+r*cos(ang+v[i]*e),a/2+r*sin(ang+v[i]*e),a/2+r*cos(ang),a/2+r*sin(ang));
				char t[20];
				strcpy(t,"");
				TextOut(hDC,a/2+r*cos(ang+v[i]*e/2)*3/4,a/2+r*sin(ang+v[i]*e/2)*3/4,itoa(v[i],t,10),log10(v[i]*1.)+1);
				ang+=v[i]*e;
			}
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OPENFILE:
			strcpy(szFile,"");
			havefile=GetOpenFileName(&ofn);
			if (havefile)
			{
				fin.open(ofn.lpstrFile);
				istream_iterator<int>name(fin);
				istream_iterator<int>end;
				v.resize(copy(name,end,v.begin())-v.begin());
				InvalidateRect(hWnd,NULL,true);
			}
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
