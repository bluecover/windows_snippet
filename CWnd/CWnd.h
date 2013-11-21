// CWnd.h : main header file for the CWnd application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCWndApp:
// See CWnd.cpp for the implementation of this class
//

class CCWndApp : public CWinApp
{
public:
	CCWndApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCWndApp theApp;