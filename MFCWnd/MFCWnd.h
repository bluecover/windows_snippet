// MFCWnd.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "my_wnd.h"


// CMFCWndApp:
// �йش����ʵ�֣������ MFCWnd.cpp
//

class CMFCWndApp : public CWinApp
{
public:
	CMFCWndApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

    My_wnd m_myWnd;
};

extern CMFCWndApp theApp;