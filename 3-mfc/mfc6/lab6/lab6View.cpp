
// lab6View.cpp : implementation of the Clab6View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab6.h"
#endif

#include "lab6Doc.h"
#include "lab6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab6View

IMPLEMENT_DYNCREATE(Clab6View, CFormView)

BEGIN_MESSAGE_MAP(Clab6View, CFormView)
	ON_BN_CLICKED(IDC_ADD, &Clab6View::AddUpdate)
	ON_BN_CLICKED(IDC_REMOVE, &Clab6View::Remove)
	ON_LBN_SELCHANGE(IDC_LIST, &Clab6View::OnLbnSelchangeList)
	ON_EN_CHANGE(IDC_WORD, &Clab6View::OnEnChangeWord)
END_MESSAGE_MAP()

// Clab6View construction/destruction

Clab6View::Clab6View()
	: CFormView(Clab6View::IDD)
	, word(_T(""))
	, defin(_T(""))
{
	// TODO: add construction code here
	adding=false;
}

Clab6View::~Clab6View()
{
}

void Clab6View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WORD, word);
	DDX_Text(pDX, IDC_DEFINITION, defin);
	DDX_Control(pDX, IDC_LIST, list);

	//if (adding) 
//	{
		DDV_MaxChars(pDX,word,15);
		DDV_MaxChars(pDX,defin,15);
		if (word.GetLength()<2 || defin.GetLength()<2) 
		{
			MessageBox("Minimum length of the string is 2.","Mistake",true);
			pDX->Fail();
		}
//	}
}

BOOL Clab6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void Clab6View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	list.ResetContent();
	CString key, val;
	CMapStringToString& map = GetDocument()->dict;
	POSITION pos = map.GetStartPosition();
	while (pos!=NULL)
	{
		map.GetNextAssoc(pos,key,val);
		CString temp=key+" : "+val;
		list.AddString(temp);
	}
	pos=map.GetStartPosition();
	if (pos!=NULL)
		map.GetNextAssoc(pos,word,defin);
	else 
	{
		word="";
		defin="";
	}
	UpdateData(FALSE);
}


// Clab6View diagnostics

#ifdef _DEBUG
void Clab6View::AssertValid() const
{
	CFormView::AssertValid();
}

void Clab6View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

Clab6Doc* Clab6View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab6Doc)));
	return (Clab6Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab6View message handlers


void Clab6View::AddUpdate()
{
	// TODO: Add your control notification handler code here
	adding=true;
	if (!UpdateData(TRUE))
		return;
	int n = FindKeyInList(word);
	if (n!=LB_ERR)
		list.DeleteString(n);
	CString s = word + " : " + defin;
	list.AddString(s);
	list.SetCurSel(n);
	GetDocument()->dict[word]=defin;
	GetDocument()->SetModifiedFlag();
	adding=false;
}


void Clab6View::Remove()
{
	// TODO: Add your control notification handler code here
	if (list.GetCurSel()==LB_ERR)
	{
		MessageBox("Nothing is selected","Error.",true);
		return;
	}
	OnLbnSelchangeList();
	int n=FindKeyInList(word);
	list.DeleteString(n);
	GetDocument()->dict.RemoveKey(word);
	word="";
	defin="";
	UpdateData(FALSE);
	GetDocument()->SetModifiedFlag();
}


int Clab6View::FindKeyInList(CString& key)
{
	CString value;
	if (GetDocument()->dict.Lookup(key,value)!=TRUE)
		return LB_ERR;
	CString s=key+ " : " +value;
	int index=-1;
	CString s1("");
	do
	{
		index=list.FindStringExact(index,s);
		list.GetText(index,s1);
		if (s==s1)
			break;
	}
	while (true);
	list.SetTopIndex(index);
	list.SetCurSel(index);
	return index;
}


void Clab6View::OnLbnSelchangeList()
{
	int n=list.GetCurSel();
	if (n==LB_ERR)
		return;
	CMapStringToString& map = GetDocument()->dict;
	POSITION pos = map.GetStartPosition();
	CString text;
	list.GetText(n,text);
	while (pos!=NULL)
	{
		map.GetNextAssoc(pos,word,defin);
		if ( (word+" : "+defin) == text)
			break;
	}
	UpdateData(FALSE);
}


void Clab6View::OnEnChangeWord()
{
	if (!UpdateData(TRUE))
		return;
	int n = list.FindString(0,word);
	if (n!=LB_ERR)
		list.SetCurSel(n);
	UpdateData(FALSE);
}
