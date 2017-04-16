#include <afxwin.h>
#include "stdafx.h"

#include "resource.h"
#include "AddValueDlg.h"

BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_EDIT1,50);
	return TRUE;
}

void CMyDialog::OnOK()
{
	val=GetDlgItemInt(IDC_EDIT1);
	CDialog::OnOK();
}