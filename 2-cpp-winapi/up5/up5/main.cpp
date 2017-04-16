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

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static int curq, have;

struct quiz
{
	string quest;
	int var;
	string ans[10];
	bool r[10];
};

static vector <quiz> v;

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
		szClassName, "Quiz", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 450, 200,
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
	static BOOL loaded=false;
	static char file[200];
	static OPENFILENAME ofn;
	static ifstream fin;
	static string out;

	switch (msg)
	{
	case WM_CREATE:
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.hwndOwner=hWnd;
		ofn.lpstrFile=file;
		ofn.nMaxFile=sizeof(file);
		curq=0;
		have=0;
		CreateConsole();
		return 0;

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
		DrawText(hDC,out.c_str(),-1,&rect,NULL);
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LOAD:
			if (GetOpenFileName(&ofn))
			{
				loaded=true;
				char t;
				quiz temp;
				fin.open(ofn.lpstrFile);
				while (!fin.eof())
				{
					fin >> temp.quest >> temp.var;
					for (int i=0; i<temp.var; i++)
					{
						fin >> temp.ans[i] >> t;
						t=='+' ? temp.r[i]=true : temp.r[i]=false;
					}
					v.push_back(temp);
				}
				v.pop_back();
				out="Questions loaded from:\n";
				out+=ofn.lpstrFile;
				out+="\n\"Start\" to start!";
				InvalidateRect(hWnd,NULL,true);
			}
			break;
		case ID_START:
			DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DlgProc);
			break;
		case ID_EXIT:
			DestroyWindow(hWnd);
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

BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		HDC hDC;
		RECT r;
		hDC=GetDC(hDlg);
		GetClientRect(hDlg,&r);
		cout << v[curq].quest << endl;
		//TextOut(hDC,0,0,v[curq].quest.c_str(),3);
		//DrawText(hDC,v[curq].quest.c_str(),-1,&r,NULL);
	//	GetDlgItem(hDlg,MAKEINTRESOURCE(IDC_STATIC))->
			SetWindowText(GetDlgItem(hDlg,MAKEINTRESOURCE(IDC_STATIC)),v[curq].quest.c_str());
		//	SetWindowText(v[curq].quest.c_str());
		ReleaseDC(hDlg,hDC);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{		
		case IDNEXT:
			curq++;
		//	DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DlgProc);
			EndDialog(hDlg,0);
			return true;
		case IDCANCEL:
			EndDialog(hDlg,0);
			return true;
		}
		break;
	}
	return false;
}