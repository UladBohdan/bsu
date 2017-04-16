// mfc5Doc.h : interface of the Cmfc5Doc class
//

#pragma once

#include <vector>

class Cmfc5Doc : public CDocument
{
protected: // create from serialization only
	Cmfc5Doc();
	DECLARE_DYNCREATE(Cmfc5Doc)

// Attributes
public:
	std::vector <int> v;
// Operations
public:
	afx_msg void AddValue();
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cmfc5Doc();
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
