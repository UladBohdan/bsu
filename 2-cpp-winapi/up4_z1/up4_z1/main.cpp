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
	static int h, w, M=1043753;
	static HMENU contxt;
	static HWND hButton[9];
	static HBRUSH bkBrush;
	static HBITMAP hbmf;
	static char file[200];
	static OPENFILENAME ofn;

	switch (msg)
	{
	case WM_CREATE:
	//	CreateConsole();
		contxt=LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MENU1));
		contxt=GetSubMenu(contxt,0);
		for (int i=0; i<9; i++)
		{
			string name="Button";
			name+=(char)(i+49);
			HMENU hMenu=CreateMenu();
			hButton[i]=CreateWindow("button",name.c_str(),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
									20,5+50*i,200,40,hWnd,(HMENU)(i),GetModuleHandle(NULL),NULL);
		}
		strcpy(file,"bk.bmp");
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.hwndOwner=hWnd;
		ofn.lpstrFile=file;
		ofn.nMaxFile=sizeof(file);
		hbmf=(HBITMAP)LoadImage((HINSTANCE)(GetWindowLong(hWnd,GWL_HINSTANCE)),file,IMAGE_BITMAP,
								0,0,LR_LOADFROMFILE);
		bkBrush=CreatePatternBrush(hbmf);
		SetClassLong(hWnd,GCL_HBRBACKGROUND,(LONG)bkBrush);
		return 0;
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={0,550};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_RBUTTONDOWN:
		{
			POINT p={LOWORD(lParam),HIWORD(lParam)};
			ClientToScreen(hWnd,&p);
			TrackPopupMenuEx(contxt,NULL,p.x,p.y,hWnd,NULL);
			return 0;
		}

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_ALLVISIBLE:
			for (int i=0; i<9; i++)
				ShowWindow(hButton[i],SW_SHOW);
			break;
		case ID_IMAGE:
			if (!GetOpenFileName(&ofn))
				strcpy(file,"bk.bmp");
			hbmf=(HBITMAP)LoadImage((HINSTANCE)(GetWindowLong(hWnd,GWL_HINSTANCE)),file,IMAGE_BITMAP,
								0,0,LR_LOADFROMFILE);
			bkBrush=CreatePatternBrush(hbmf);
			SetClassLong(hWnd,GCL_HBRBACKGROUND,(LONG)bkBrush);
			InvalidateRect(hWnd,NULL,true);
			break;
		default:
			ShowWindow((HWND)lParam,SW_HIDE);
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
