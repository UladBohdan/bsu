
// mfcFinalView.h : interface of the CmfcFinalView class
//

#pragma once

#include "resource.h"
#include "afxwin.h"

#include "DiagramDlg.h"

class CmfcFinalView : public CFormView
{
protected: // create from serialization only
	CmfcFinalView();
	DECLARE_DYNCREATE(CmfcFinalView)

public:
	enum{ IDD = IDD_MFCFINAL_FORM };

// Attributes
public:
	CmfcFinalDoc* GetDocument() const;

// Operations
public:
	void AddItem();
	void ChangeItem();
	void RemoveItem();
	void ShowDiagram();

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CmfcFinalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	CListBox list;
};

#ifndef _DEBUG  // debug version in mfcFinalView.cpp
inline CmfcFinalDoc* CmfcFinalView::GetDocument() const
   { return reinterpret_cast<CmfcFinalDoc*>(m_pDocument); }
#endif

