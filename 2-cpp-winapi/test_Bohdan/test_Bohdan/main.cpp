#include <algorithm>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
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
	static HACCEL ac;
	
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
		szClassName, "Test WINAPI Bohdan", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
	);
	
	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, nCmdShow); 

	ac=LoadAccelerators(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_ACCELERATOR2));
	while (GetMessage(&msg, NULL, 0, 0))  {
		if (!TranslateAccelerator(hMainWnd,ac,&msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	static int h, w, w1;
	static double k;
	static char file[200];
	static OPENFILENAME ofn;
	static CHOOSECOLOR cc;
	static COLORREF clrs[16];
	static vector < pair <string, int> > v, ans;
	static vector <int> brclr;
	static fstream fin;
	static bool opened=false;

	switch (msg)
	{
	case WM_CREATE:
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.hwndOwner=hWnd;
		ofn.lpstrFile=file;
		ofn.nMaxFile=sizeof(file);
		cc.lStructSize=sizeof(CHOOSECOLOR);
		cc.hwndOwner=hWnd;
		cc.lpCustColors=(LPDWORD)clrs;
		cc.Flags=CC_FULLOPEN|CC_SOLIDCOLOR;
		//CreateConsole();
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={200,200};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		{
		hDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		h=rect.bottom;
		w=rect.right;

		MoveToEx(hDC,0,h-30,NULL);
		LineTo(hDC,w,h-30);
		if (opened)
		{
			int colnum=ans.size();
			w1=w/colnum;
			int mxcol=0;
			for (int i=0; i<colnum; i++)
				if (ans[i].second>mxcol)
					mxcol=ans[i].second;
			k=mxcol*1./(h*1.-50);
			for (int i=0; i<colnum; i++)
			{
				HBRUSH hbr=CreateSolidBrush(brclr[i]);
				SelectObject(hDC,hbr);
				Rectangle(hDC,i*w1+w1/10,  h-20-ans[i].second*1./k    ,(i+1)*w1-w1/10, h-30);
				RECT fortext={i*w1,h-29,(i+1)*w1,h-1};
				DrawText(hDC,ans[i].first.c_str(),-1,&fortext,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
			}
			int lpos;
			if (w>300 && h>ans.size()*20+100)
			{
				SelectObject(hDC,CreateSolidBrush(RGB(255,255,255)));
				if (ans[0].second<ans[ans.size()-1].second)
					lpos=10;
				else
					lpos=w-100;
				Rectangle(hDC,lpos,5,lpos+95,5+ans.size()*20);
				for (int i=0; i<ans.size(); i++)
				{
					RECT fortext={lpos+5,5+i*20,lpos+95,5+(i+1)*20};
					DrawText(hDC,ans[i].first.c_str(),-1,&fortext,DT_SINGLELINE|DT_VCENTER);
				}
			}
		}
		EndPaint(hWnd, &ps);
		}
		return 0;

	case WM_RBUTTONDOWN:
		{
			int x=LOWORD(lParam), y=HIWORD(lParam);
			for (int i=0; i<ans.size(); i++)
				if (x>i*w1+w1/10 && x<(i+1)*w1-w1/10 && y>h-20-ans[i].second*1./k && y<h-30)
				{
					ChooseColor(&cc);
					brclr[i]=cc.rgbResult;
					InvalidateRect(hWnd,NULL,true);
					break;
				}
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OPENFILE:
			{
				if (GetOpenFileName(&ofn))
				{
					string tstr;
					int tint;
					fin.open(ofn.lpstrFile);
					while (!fin.eof())
					{
						fin >> tstr >> tint;
						v.push_back(make_pair(tstr,tint));
					}
					v.pop_back();
					sort(v.begin(), v.end());
					for (int i=0; i<v.size(); i++)
						if (!ans.empty() && ans[ans.size()-1].first==v[i].first)
							ans[ans.size()-1].second+=v[i].second;
						else
							ans.push_back(v[i]);
					fin.close();
					opened=true;
					brclr.resize(ans.size());
					for (int i=0; i<brclr.size(); i++)
						brclr[i]=RGB(255,255,255);
					InvalidateRect(hWnd,NULL,true);
				}
				break;
			}
		case ID_CHANGECOLOR:
			{
				if (ChooseColor(&cc))
				{
					for (int i=0; i<brclr.size(); i++)
						brclr[i]=cc.rgbResult;
				}
				InvalidateRect(hWnd,NULL,true);
				break;
			}
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