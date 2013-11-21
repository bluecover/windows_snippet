// AgInMFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAgInMFCApp:
// See AgInMFC.cpp for the implementation of this class
//

class CAgInMFCApp : public CWinApp
{
public:
	CAgInMFCApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAgInMFCApp theApp;