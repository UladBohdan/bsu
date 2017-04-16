
// lab6View.h : interface of the Clab6View class
//

#pragma once

#include "resource.h"
#include "afxwin.h"


class Clab6View : public CFormView
{
protected: // create from serialization only
	Clab6View();
	DECLARE_DYNCREATE(Clab6View)

public:
	enum{ IDD = IDD_LAB6_FORM };

// Attributes
public:
	Clab6Doc* GetDocument() const;
	bool adding;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~Clab6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString word;
	CString defin;
	CListBox list;
	afx_msg void AddUpdate();
	afx_msg void Remove();
	int FindKeyInList(CString& key);
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnEnChangeWord();
};

#ifndef _DEBUG  // debug version in lab6View.cpp
inline Clab6Doc* Clab6View::GetDocument() const
   { return reinterpret_cast<Clab6Doc*>(m_pDocument); }
#endif

