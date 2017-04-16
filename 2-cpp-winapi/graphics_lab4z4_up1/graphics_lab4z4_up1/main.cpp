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

string tostr(int a)
{
	if (a==0)
		return "+0";
	string temp="";
	bool pos=true;
	if (a<0) {
		a*=-1;
		pos=false; }
	while (a)
	{
		temp=(char)(a%10+48)+temp;
		a/=10;
	}
	pos ? temp="+"+temp : temp="-"+temp;
	return temp;
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
	HDC hDC, hDCpix;
	PAINTSTRUCT ps;
	RECT rect;
	static bool selecting, txt;
	static RECT forchart;
	static int h, w;
	static string toptext;
	static int a,b,c,xl,xr,yd,yt,ox,oy;
	static int x_start, y_start, x_temp, y_temp, x_for_text, y_for_text;

	switch (msg)
	{
	case WM_CREATE:
		{
			CreateConsole();
			a=1;
			b=0;
			c=0;
			xl=-10;
			xr=10;
			GetClientRect(hWnd,&rect);
			h=rect.bottom;
			w=rect.right;
			SetRect(&forchart,2,75,w-2,h-2);
			x_start=2;
			y_start=75;
			x_start=w-2;
			y_start=h-2;
			selecting=false;
			txt=false;
			break;
		}
	case WM_SIZE:
		x_start=2;
		y_start=75;
		x_start=w-2;
		y_start=h-2;
		txt=false;
		break;
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
			POINT Min={450,400};
			pInfo->ptMinTrackSize=Min;
			return 0;
		}
	case WM_PAINT:
		{
		hDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		h=rect.bottom;
		w=rect.right;
		Rectangle(hDC,2,75,w-2,h-2);
		SetRect(&forchart,2,75,w-2,h-2);
		int temp_e=(forchart.right-forchart.left)/(xr-xl); // how many pixels in 1 on each coord. axis
		yt=(forchart.bottom-forchart.top)/(2*temp_e);
		yd=-1*yt;

		cout << "counting ox and oy:  " << abs(xl*1./(xr-xl)) << "  " << abs(yt*1./(yd-yt)) << endl;
		oy=(forchart.right-forchart.left)*1.*abs(xl*1./(xr-xl));
		ox=(forchart.bottom-forchart.top)*1.*abs(yt*1./(yd-yt));

		toptext=" Current chart: "+tostr(a)+"x^2"+tostr(b)+"x"+tostr(c)+"\n Area: x=["+tostr(xl)+";"+tostr(xr)+"], y=["+tostr(yd)+";"+tostr(yt)
			+"]\n Press R key ro redraw chart with new random values of a,b,c"+"\n Press - to make area wider, + for opposite, U to Update";
		DrawText(hDC,toptext.c_str(),-1,&rect,NULL);

		MoveToEx(hDC,8,forchart.top+ox,NULL);
		LineTo(hDC,w-8,forchart.top+ox);
		MoveToEx(hDC,forchart.left+oy,81,NULL);
		LineTo(hDC,forchart.left+oy,h-8);
		
		int zerox=forchart.left+oy;
		int zeroy=forchart.top+ox;

		TextOut(hDC,zerox+2,forchart.top+5,"Oy",2);
		TextOut(hDC,forchart.right-25,zeroy+2,"Ox",2);
		if (temp_e>5)
		{
			for (int i=xl; i<=xr; i++)
			{
				MoveToEx(hDC,zerox+i*temp_e,zeroy-3,NULL);
				LineTo(hDC,zerox+i*temp_e,zeroy+3);
			}
			for (int i=yd; i<=yt; i++)
			{
				MoveToEx(hDC,zerox-3,zeroy-i*temp_e,NULL);
				LineTo(hDC,zerox+3,zeroy-i*temp_e);
			}
		}

		double k=(forchart.right-forchart.left)*1./(xr*1.-xl*1.);
		for (double i=xl; i<=xr; i+=0.001)
		{
			double val=a*1.*i*i+b*1.*i+c*1.;
			if (val<=yt && val>=yd)
				SetPixel(hDC,zerox+i*k,zeroy-val*k,RGB(255,0,0));
		}
		if (selecting) {
			POINT p[5]={ {x_start,y_start}, {x_start,y_temp}, {x_temp,y_temp}, {x_temp,y_start}, {x_start,y_start} };
			Polyline(hDC,p,5); }

		if (txt)
		{
			string pp=tostr((x_for_text-zerox)/temp_e)+", "+tostr((-y_for_text+zeroy)/temp_e);
			TextOut(hDC,x_for_text,y_for_text,pp.c_str(),pp.length());
		}
		EndPaint(hWnd, &ps);
		return 0;
		}

	case WM_KEYDOWN:
		txt=false;
		if (wParam==0x52)
		{
			srand(time(NULL));
			a=rand()%40-20;
			b=rand()%40-20;
			c=rand()%40-20;
			InvalidateRect(hWnd,NULL,true);
		}
		else if (wParam==VK_SUBTRACT)
		{
			xr+=5;
			xl-=5;
			InvalidateRect(hWnd,NULL,true);
		}
		else if (wParam=VK_ADD && xr>=10)
		{
			xr-=5;
			xl+=5;
			InvalidateRect(hWnd,NULL,true);
		}
		else if (wParam==0x55)
			InvalidateRect(hWnd,NULL,true);
		break;

	case WM_LBUTTONDOWN:
		x_start=LOWORD(lParam);
		y_start=HIWORD(lParam);
		if (x_start>forchart.left && x_start<forchart.right && y_start>forchart.top && y_start<forchart.bottom) 
			selecting=true;
		break;

	case WM_MOUSEMOVE:
		{
			int x=LOWORD(lParam), y=HIWORD(lParam);
			if (selecting)
			{
				if (LOWORD(lParam)>forchart.left && LOWORD(lParam)<forchart.right && HIWORD(lParam)>forchart.top && HIWORD(lParam)<forchart.bottom) 
				{
					x_temp=x;
					y_temp=y;
				}
				InvalidateRect(hWnd,NULL,true);
			}
			hDCpix=GetDC(hWnd);
			if (GetPixel(hDCpix,x,y)==RGB(255,0,0))
			{
				txt=true;
				x_for_text=x;
				y_for_text=y;
				InvalidateRect(hWnd,NULL,true);
			}
			ReleaseDC(hWnd,hDCpix);
			break;
		}

	case WM_LBUTTONUP:
		{
			if (selecting && (xr-xl>=15))
			{
				txt=false;
				if (x_temp<x_start)
				{
					swap(x_temp,x_start);
					swap(y_temp,y_start);
				}
				int temp_e=(forchart.right-forchart.left)/(xr-xl);
				xl+=(x_start-forchart.left)/temp_e;
				xr+=(x_temp-forchart.right)/temp_e;
				selecting=false;
				cout << "ZOOMING to " << x_start << " " << y_start << "   " << x_temp << " " << y_temp << endl;
				InvalidateRect(hWnd,NULL,true);
			}
			if (selecting) 
				InvalidateRect(hWnd,NULL,true);
			selecting=false;
			break;
		}

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
