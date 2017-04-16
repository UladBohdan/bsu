#pragma once

#include "Item.h"

// EditDlg dialog

class EditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditDlg)

public:
	EditDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL OnInitDialog();
	void OnOK();
	virtual ~EditDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };
	Item x;
	bool changed;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
