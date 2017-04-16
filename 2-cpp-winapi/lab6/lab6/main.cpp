#include <cmath>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <windows.h>

#include "resource.h"
#include "Game.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK NewGameDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK StatDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

Game game;

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
		CW_USEDEFAULT, 0, 300, 330,
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
	RECT rect;

	switch (msg)
	{
	case WM_CREATE:
		CreateConsole();
		GetClientRect(hWnd, &rect);
		game.init(hWnd);
		game.updateWindowSize(rect.right,rect.bottom);
		game.start(true,false,0);
		return 0;

	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		game.updateWindowSize(rect.right,rect.bottom);
		break;

	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={200,200};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}

	case WM_LBUTTONDOWN:
		{
		int x=LOWORD(lParam), y=HIWORD(lParam);
		game.onLClick(x,y);
		return 0;
		}

	case WM_RBUTTONDOWN:
		{
		int x=LOWORD(lParam), y=HIWORD(lParam);
		game.onRClick(x,y);
		return 0;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_GAME_NEW:
			DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_NEWGAME),hWnd,NewGameDlgProc);
			break;
		case ID_GAME_STAT:
			DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_STAT),hWnd,StatDlgProc);
			break;
		case ID_GAME_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_INFO:
			DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ABOUT),hWnd,AboutDlgProc);
			break;
		}
		break;

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

BOOL CALLBACK NewGameDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND vs, clr;
	vs=GetDlgItem(hDlg,IDC_COMBO1);
	clr=GetDlgItem(hDlg,IDC_COMBO2);

	switch (uMsg)
	{
	case WM_INITDIALOG:
		SendMessage(vs,CB_ADDSTRING,0,(LPARAM)"Computer (random)");
		SendMessage(vs,CB_ADDSTRING,0,(LPARAM)"Computer (hard)");
		SendMessage(vs,CB_ADDSTRING,0,(LPARAM)"Another player");
		SendMessage(vs,CB_SETCURSEL,0,0);
		SendMessage(clr,CB_ADDSTRING,0,(LPARAM)"Black");
		SendMessage(clr,CB_ADDSTRING,0,(LPARAM)"Green");
		SendMessage(clr,CB_ADDSTRING,0,(LPARAM)"Blue");
		SendMessage(clr,CB_SETCURSEL,0,0);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			bool temp_comp=(SendMessage(vs,CB_GETCURSEL,0,0)==0 || SendMessage(vs,CB_GETCURSEL,0,0)==1);
			bool temp_hard=(SendMessage(vs,CB_GETCURSEL,0,0)==1);
			int temp_color;
			//cout << "FROM dialog: " << SendMessage(clr,CB_GETCURSEL,0,0) << endl; 
			if (SendMessage(clr,CB_GETCURSEL,0,0)==0)
				temp_color=0;
			else if (SendMessage(clr,CB_GETCURSEL,0,0)==1)
				temp_color=RGB(0,255,0);
			else temp_color=RGB(0,0,255);
			game.start(temp_comp,temp_hard,temp_color);
			}
		case IDCANCEL:
			EndDialog(hDlg,0);
			return true;
		}
		break;
	}
	return false;
}

BOOL CALLBACK StatDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			
		case IDCANCEL:
			EndDialog(hDlg,0);
			return true;
		}
		break;
	}
	return false;
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:		
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{		
		case IDCANCEL:
			EndDialog(hDlg,0);
			return true;
		}
		break;
	}
	return false;
}