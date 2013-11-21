// AgInMFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AgInMFC.h"
#include "AgInMFCDlg.h"

#include "InstallDesktopTipWnd.h"
#include "DesktopIconTracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAgInMFCApp

BEGIN_MESSAGE_MAP(CAgInMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAgInMFCApp construction

CAgInMFCApp::CAgInMFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAgInMFCApp object

CAgInMFCApp theApp;


// CAgInMFCApp initialization

BOOL CAgInMFCApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    //注册窗口类
    WNDCLASS cls;
    ZeroMemory(&cls, sizeof(WNDCLASS));
    cls.lpfnWndProc = ::DefWindowProc;
    cls.style = CS_DBLCLKS;
    cls.hInstance = AfxGetInstanceHandle();
    cls.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    cls.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    cls.lpszClassName = L"InstallDesktopTipWnd";
    VERIFY(AfxRegisterClass(&cls));

    CInstallDesktopTipWnd* pWnd = new CInstallDesktopTipWnd;

    CRect rcIcon;
    HWND hDeskListView;
    BOOL bRet= CDesktopIconTracker::GetIconRect(L"有道词典", &rcIcon, hDeskListView);

    int deltaX = rcIcon.Width() / 2 + 25;
    int deltaY = rcIcon.Height() / 2;


    CRect rc_frame_wnd(rcIcon.left + deltaX, rcIcon.top + deltaY, rcIcon.left + WND_X + deltaX, rcIcon.top + WND_Y + deltaY);
    const DWORD style = WS_POPUP;

    CPoint pt(rc_frame_wnd.left, rc_frame_wnd.top);
    HWND hTopWnd = WindowFromPoint(pt);
    CRect topWndRect;
    GetWindowRect(hTopWnd, &topWndRect);


    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    if ( (w == topWndRect.Width() && h == topWndRect.Height()) 
         || !PtInRect(&topWndRect, pt) )
    {
        pWnd->CreateEx(WS_EX_TOOLWINDOW, L"InstallDesktopTipWnd", NULL, style, rc_frame_wnd, NULL, 0, NULL);
        m_pMainWnd = pWnd;

        pWnd->ShowWindow(SW_SHOW);
        pWnd->UpdateWindow();
    }

    return TRUE;
}
