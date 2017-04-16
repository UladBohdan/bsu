// DiagramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcFinal.h"
#include "DiagramDlg.h"
#include "afxdialogex.h"


// DiagramDlg dialog

IMPLEMENT_DYNAMIC(DiagramDlg, CDialogEx)

DiagramDlg::DiagramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DiagramDlg::IDD, pParent)
{
}

DiagramDlg::~DiagramDlg()
{
}

void DiagramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DiagramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DiagramDlg message handlers

void DiagramDlg::OnPaint()
{
	if (values.empty())
		return;
	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	double w1=(rect.right-40)*1./values.size();
	int mx=0;
	for (std::map<CString,int>::iterator i=values.begin(); i!=values.end(); i++)
		if (i->second>mx)
			mx=i->second;
	double h1;
	if (mx==0)
		h1=0;
	else
		h1=(rect.bottom-60)*1./mx;
	srand(time(NULL));
	int c=0;
	for(std::map<CString, int>::iterator i=values.begin(); i!=values.end(); i++)
	{	
		HBRUSH hBrush = CreateSolidBrush(RGB(rand()%255,rand()%255,rand()%255));
		SelectObject(dc,hBrush);
		dc.Rectangle(20+c*w1,rect.bottom-45,20+(c+1)*w1,rect.bottom-50-(i->second*h1) );
		RECT rect2={20+c*w1,rect.bottom-45,20+(c+1)*w1,rect.bottom-20};
		dc.DrawText(i->first,&rect2,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		char buf[30];
		sprintf(buf,"%d",i->second);
		RECT rect3={20+c*w1,rect.bottom-20,20+(c+1)*w1,rect.bottom};
		dc.DrawText((CString)buf,&rect3,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		DeleteObject(hBrush);
		c++;
	}
	return;
}
