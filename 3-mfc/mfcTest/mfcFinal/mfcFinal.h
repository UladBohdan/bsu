
// mfcFinal.h : main header file for the mfcFinal application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CmfcFinalApp:
// See mfcFinal.cpp for the implementation of this class
//

class CmfcFinalApp : public CWinApp
{
public:
	CmfcFinalApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CmfcFinalApp theApp;
