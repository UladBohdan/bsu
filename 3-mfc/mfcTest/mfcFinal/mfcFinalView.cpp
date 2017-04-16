
// mfcFinalView.cpp : implementation of the CmfcFinalView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfcFinal.h"
#endif

#include "mfcFinalDoc.h"
#include "mfcFinalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcFinalView

IMPLEMENT_DYNCREATE(CmfcFinalView, CFormView)

BEGIN_MESSAGE_MAP(CmfcFinalView, CFormView)
	ON_COMMAND(IDC_ADDDATA,&CmfcFinalView::AddItem)
	ON_COMMAND(IDC_CHANGEDATA,&CmfcFinalView::ChangeItem)
	ON_COMMAND(IDC_REMOVEDATA,&CmfcFinalView::RemoveItem)
	ON_COMMAND(IDC_DIAGRAM,&CmfcFinalView::ShowDiagram)
END_MESSAGE_MAP()

// CmfcFinalView construction/destruction

CmfcFinalView::CmfcFinalView()
	: CFormView(CmfcFinalView::IDD)
{
	// TODO: add construction code here

}

CmfcFinalView::~CmfcFinalView()
{
}

void CmfcFinalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, list);
}

BOOL CmfcFinalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CmfcFinalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	CmfcFinalDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	list.ResetContent();
	for (int i=0; i<pDoc->v.GetSize(); i++)
		list.AddString(pDoc->v[i].str());
}


// CmfcFinalView diagnostics

#ifdef _DEBUG
void CmfcFinalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CmfcFinalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CmfcFinalDoc* CmfcFinalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcFinalDoc)));
	return (CmfcFinalDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcFinalView message handlers


void CmfcFinalView::AddItem()
{
	CmfcFinalDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	EditDlg dlg;
	dlg.x=Item("","",0);
	if (dlg.DoModal()==IDOK)
	{
		pDoc->v.Add(dlg.x);
		list.AddString(dlg.x.str());
		pDoc->SetModifiedFlag();
	}
	return;
}

void CmfcFinalView::ChangeItem()
{
	CmfcFinalDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int n=list.GetCurSel();
	if (n==LB_ERR)
	{
		MessageBox(TEXT("Choose an item to be modified!"));
		return;
	}
	EditDlg dlg;
	dlg.x=pDoc->v[n];
	if (dlg.DoModal()==IDOK)
	{
		pDoc->v[n]=dlg.x;
		list.DeleteString(n);
		list.InsertString(n,dlg.x.str());
		pDoc->SetModifiedFlag(TRUE);
	}
	return;
}

void CmfcFinalView::RemoveItem()
{
	CmfcFinalDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int n=list.GetCurSel();
	if (n==LB_ERR)
	{
		MessageBox(TEXT("Choose an item to be removed!"));
		return;
	}
	pDoc->v.RemoveAt(n);
	list.DeleteString(n);
	pDoc->SetModifiedFlag(TRUE);
	return;
}

void CmfcFinalView::ShowDiagram()
{
	CmfcFinalDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DiagramDlg dlg;
	dlg.values.clear();
	for (int i=0; i<pDoc->v.GetSize(); i++)
		dlg.values[pDoc->v[i].depart]++;
	dlg.DoModal();
	return;
}