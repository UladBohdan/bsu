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

struct lesson
{
	string aud, name, type;
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
		szClassName, "Timetable", WS_OVERLAPPEDWINDOW,
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
	static vector <vector <lesson> > v (6);
	static int maxles=0;
	static int FORDAYS=50, BRD=1;
	static LOGFONT lf;
	static HFONT font1, font2, fontvert;
	static char* day[6]={"Mon","Tue","Wed","Thu","Fri","Sat"};

	switch (msg)
	{
	case WM_CREATE:
		{
			//CreateConsole();
			ifstream fin("lessons.txt");
			string temp;
			queue <string> q;
			while (!fin.eof())
			{
				fin >> temp;
				q.push(temp);
			}
			int pos=-1;
			while (!q.empty())
			{
				if (q.front().length()==1)
				{
					q.pop();
					pos++;
				}
				else
				{
					lesson t;
					t.name=q.front(); q.pop();
					t.type=q.front(); q.pop();
					t.aud=q.front(); q.pop();
					v[pos].push_back(t);
				}
			}
			for (int i=0; i<6; i++)
				if (v[i].size()>maxles)
					maxles=v[i].size();

			lf.lfCharSet=DEFAULT_CHARSET;
			lf.lfPitchAndFamily=DEFAULT_PITCH;
			strcpy(lf.lfFaceName,"Times New Roman");
			lf.lfHeight=20;
			lf.lfWeight=FW_BOLD;
			font1=CreateFontIndirect(&lf);
			lf.lfHeight=17;
			font2=CreateFontIndirect(&lf);
			lf.lfHeight=15;
			lf.lfEscapement=900;
			fontvert=CreateFontIndirect(&lf);
		}
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={800,400};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		{
			int w=rect.right, h=rect.bottom, w1=(w-FORDAYS)/maxles, h1=h/6;
			for (unsigned int i=0; i<6; i++)
			{
				SelectObject(hDC,fontvert);
				RECT dayrect={10,i*h1+5,FORDAYS,(i+1)*h1+30};
				DrawText(hDC,day[i],-1,&dayrect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				for (unsigned int j=0; j<v[i].size(); j++)
				{
					RECT temp={FORDAYS+j*w1+BRD,i*h1+BRD,FORDAYS+(j+1)*w1-BRD,(i+1)*h1-BRD};
					RECT up={temp.left,temp.top,temp.right,temp.bottom-(h1-2*BRD)/2};
					RECT down={temp.left,temp.top+(h1-2*BRD)/2,temp.right,temp.bottom};
					HBRUSH brush=CreateSolidBrush(v[i][j].type=="lect" ? RGB(240,85,45) : RGB(246,218,100));
					FillRect(hDC,&temp,brush);
					SetBkMode(hDC,TRANSPARENT);
					SelectObject(hDC,font2);
					DrawText(hDC,(LPCSTR)(v[i][j].aud.c_str()),-1,&down,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					SelectObject(hDC,font1);
					DrawText(hDC,(LPCSTR)(v[i][j].name.c_str()),-1,&up,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					DeleteObject(brush);
				}
			}
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
