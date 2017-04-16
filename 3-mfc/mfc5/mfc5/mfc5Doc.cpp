
// mfc5Doc.cpp : implementation of the Cmfc5Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfc5.h"
#endif

#include "mfc5Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cmfc5Doc

IMPLEMENT_DYNCREATE(Cmfc5Doc, CDocument)

BEGIN_MESSAGE_MAP(Cmfc5Doc, CDocument)
	ON_COMMAND(ID_ADDVALUE,&Cmfc5Doc::AddValue)
END_MESSAGE_MAP()


// Cmfc5Doc construction/destruction

Cmfc5Doc::Cmfc5Doc()
{
	// TODO: add one-time construction code here
}

Cmfc5Doc::~Cmfc5Doc()
{
}

BOOL Cmfc5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void Cmfc5Doc::DeleteContents()
{
	v.clear();
	CDocument::DeleteContents();
	return;
}


// Cmfc5Doc serialization

void Cmfc5Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << v.size();
		for (std::vector<int>::iterator i=v.begin(); i!=v.end(); i++)
			ar << *i;
	}
	else
	{
		// TODO: add loading code here
		int x;
		ar >> x;
		v.resize(x);
		for (std::vector<int>::iterator i=v.begin(); i!=v.end(); i++)
			ar >> *i;
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cmfc5Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cmfc5Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cmfc5Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cmfc5Doc diagnostics

#ifdef _DEBUG
void Cmfc5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cmfc5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cmfc5Doc commands

void Cmfc5Doc::AddValue()
{
	CMyDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		v.push_back(dlg.val);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}
	return;
}
