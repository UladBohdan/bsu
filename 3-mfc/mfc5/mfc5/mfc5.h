
// mfc5.h : main header file for the mfc5 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <afxdlgs.h>
#include "AddValueDlg.h"


// Cmfc5App:
// See mfc5.cpp for the implementation of this class
//

class Cmfc5App : public CWinApp
{
public:
	Cmfc5App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cmfc5App theApp;
