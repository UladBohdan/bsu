
// mfcFinalDoc.h : interface of the CmfcFinalDoc class
//


#pragma once

#include "Item.h"
#include "EditDlg.h"

class CmfcFinalDoc : public CDocument
{
protected: // create from serialization only
	CmfcFinalDoc();
	DECLARE_DYNCREATE(CmfcFinalDoc)

// Attributes
public:
	CArray <Item> v;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void DeleteContents();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CmfcFinalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
