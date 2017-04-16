
// mfc5View.h : interface of the Cmfc5View class
//

#pragma once

#include <algorithm>

class Cmfc5View : public CView
{
protected: // create from serialization only
	Cmfc5View();
	DECLARE_DYNCREATE(Cmfc5View)

// Attributes
public:
	Cmfc5Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Cmfc5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfc5View.cpp
inline Cmfc5Doc* Cmfc5View::GetDocument() const
   { return reinterpret_cast<Cmfc5Doc*>(m_pDocument); }
#endif

