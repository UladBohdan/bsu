#pragma once

#include "Item.h"
#include <map>

// DiagramDlg dialog

class DiagramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DiagramDlg)

public:
	DiagramDlg(CWnd* pParent = NULL);   // standard constructor
	void OnPaint();
	virtual ~DiagramDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };
	std::map <CString,int> values;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
