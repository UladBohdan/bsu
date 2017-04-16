// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcFinal.h"
#include "EditDlg.h"
#include "afxdialogex.h"


// EditDlg dialog

IMPLEMENT_DYNAMIC(EditDlg, CDialogEx)

EditDlg::EditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditDlg::IDD, pParent)
{

}

EditDlg::~EditDlg()
{
}

void EditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	if (pDX->m_bSaveAndValidate==FALSE)
	{
		DDX_Text(pDX, IDC_SURNAME, x.sur);
		DDX_Text(pDX, IDC_DEPARTMENT, x.depart);
		if (x.sal==0)
			DDX_Text(pDX, IDC_SALARY, (CString)"");
		else
			DDX_Text(pDX, IDC_SALARY, x.sal);
	}
	else
	{
		x.sal=GetDlgItemInt(IDC_SALARY,FALSE,FALSE);
		DDV_MinMaxInt(pDX,x.sal,200,3000);
		char buf[300];
		GetDlgItemText(IDC_SURNAME,buf,300);
		DDV_MinMaxInt(pDX,strlen(buf),1,50);
		x.sur=(CString)buf;
		GetDlgItemText(IDC_DEPARTMENT,buf,300);
		DDV_MinMaxInt(pDX,strlen(buf),1,50);
		x.depart=(CString)buf;
		changed=true;
	}
	return;
}


BEGIN_MESSAGE_MAP(EditDlg, CDialogEx)
END_MESSAGE_MAP()


// EditDlg message handlers

BOOL EditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	changed=false;
	UpdateData(FALSE);
	return TRUE;
}

void EditDlg::OnOK()
{
	if (!UpdateData(TRUE))
		return;
	if (changed)
		CDialog::OnOK();
	else
		CDialog::OnCancel();
	return;
}