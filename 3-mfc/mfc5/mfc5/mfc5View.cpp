
// mfc5View.cpp : implementation of the Cmfc5View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfc5.h"
#endif

#include "mfc5Doc.h"
#include "mfc5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmfc5View

IMPLEMENT_DYNCREATE(Cmfc5View, CView)

BEGIN_MESSAGE_MAP(Cmfc5View, CView)
END_MESSAGE_MAP()

// Cmfc5View construction/destruction

Cmfc5View::Cmfc5View()
{
	// TODO: add construction code here

}

Cmfc5View::~Cmfc5View()
{
}

BOOL Cmfc5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cmfc5View drawing

void Cmfc5View::OnDraw(CDC* pDC)
{
	Cmfc5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (pDoc->v.empty())
		return;
	RECT rect;
	GetClientRect(&rect);
	double w1=(rect.right-100)*1./(pDoc->v.size());
	double h1=(rect.bottom-50)*1./(*max_element(pDoc->v.begin(),pDoc->v.end()) );
	for(int i=0; i<pDoc->v.size(); i++)
	{	
		HBRUSH hBrush = CreateSolidBrush(RGB(rand()%255,rand()%255,rand()%255));
		SelectObject(*pDC,hBrush);
		pDC->Rectangle(50+i*w1,rect.bottom-35,50+(i+1)*w1,rect.bottom-35-(pDoc->v[i]*h1) );
		char buf[30];
		sprintf(buf,"%d",pDoc->v[i]);
		RECT rect2={50+i*w1,rect.bottom-35,50+(i+1)*w1,rect.bottom};
		pDC->DrawText((CString)buf,&rect2,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		DeleteObject(hBrush);
	}
	return;
}


// Cmfc5View diagnostics

#ifdef _DEBUG
void Cmfc5View::AssertValid() const
{
	CView::AssertValid();
}

void Cmfc5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmfc5Doc* Cmfc5View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmfc5Doc)));
	return (Cmfc5Doc*)m_pDocument;
}
#endif //_DEBUG


// Cmfc5View message handlers
