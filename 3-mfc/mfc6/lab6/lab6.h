
// lab6.h : main header file for the lab6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Clab6App:
// See lab6.cpp for the implementation of this class
//

class Clab6App : public CWinApp
{
public:
	Clab6App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Clab6App theApp;
