#include <afxwin.h>
#include <afxdlgs.h>
#include <stack>

#include "resource.h"
#include "Dialog.h"

class MyWin : public CFrameWnd
{
public:
	MyWin(char*);
	int color, value, i;
	void OnPaint();
	void OnTimer(UINT);
	void OnRButtonDown(UINT, CPoint);
	void Color();
	DECLARE_MESSAGE_MAP();	// объявление Карты сообщений
};

MyWin::MyWin(char* title)
{
	Create(NULL,title);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	SetMenu(&menu);
	value=5;
	color=0;
	i=2*value;
}

BEGIN_MESSAGE_MAP(MyWin,CFrameWnd)	// определение Карты сообщений
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CHOOSECOLOR, &MyWin::Color)
END_MESSAGE_MAP()

void MyWin::OnPaint()
{
	CPaintDC dc(this);
	SetTextColor(dc,color);
	HBRUSH hbrush=CreateSolidBrush(color);
	SelectObject(dc,hbrush);
	HPEN hpen=CreatePen(NULL,0,color);
	SelectObject(dc,hpen);
	RECT rect;
	GetClientRect(&rect);
	int w1=(rect.right-100)/(2.*value-1);
	int h1=(rect.bottom-100)/(1.*value);
	int left=50;
	char buf[50];
	sprintf(buf,"Height of the pyramid: %d",value);
	dc.TextOutA(20,rect.bottom-35,buf,strlen(buf));
	for (int j=1; j<=min(value,i-1); j++)
	{
		dc.Rectangle(left,rect.bottom-50,left+w1,rect.bottom-50-h1*j);
		left+=w1;
	}
	if (i>value+1)
		for (int j=value-1; j>2*value-i; j--)
		{
			dc.Rectangle(left,rect.bottom-50,left+w1,rect.bottom-50-h1*j);
			left+=w1;
		}
	if (i==2*value)
		KillTimer(0);
	DeleteObject(hbrush);
	DeleteObject(hpen);
}

void MyWin::OnTimer(UINT nIDEvent)
{
	InvalidateRect(NULL,TRUE);
	i++;
}

void MyWin::OnRButtonDown(UINT, CPoint)
{
	CMyDialog dlg;
	dlg.val=value;
	if (dlg.DoModal()==IDOK)
	{
		value=dlg.val;
		i=1;
		SetTimer(0,300,0);
	}
}

void MyWin::Color()
{
	CColorDialog cc(color,CC_RGBINIT);
	if (cc.DoModal()==IDOK)
	{
		color=cc.m_cc.rgbResult;
		static std::stack <int> st;
		for (int j=15; j>=0; j--)
			st.push(cc.m_cc.lpCustColors[j]);
		st.push(color);
		for (int j=0; j<16; j++)
		{
			cc.m_cc.lpCustColors[j]=st.top();
			st.pop();
		}
		i=1;
		SetTimer(0,300,0);
	}
}

class MyApp:CWinApp
{
public:
	BOOL InitInstance();
};

BOOL MyApp::InitInstance()
{
	m_pMainWnd = new MyWin("Hello!!!");
	m_pMainWnd->ShowWindow(SW_NORMAL);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

MyApp app;