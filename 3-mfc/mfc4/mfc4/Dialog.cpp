#include <afxwin.h>

#include "resource.h"
#include "Dialog.h"

BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_EDIT1,val);
	return TRUE;
}

void CMyDialog::OnOK()
{
	val=GetDlgItemInt(IDC_EDIT1);
	CDialog::OnOK();
}