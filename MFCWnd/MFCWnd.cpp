// MFCWnd.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MFCWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCWndApp

BEGIN_MESSAGE_MAP(CMFCWndApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCWndApp 构造

CMFCWndApp::CMFCWndApp()
{
    

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMFCWndApp 对象

CMFCWndApp theApp;


// CMFCWndApp 初始化

BOOL CMFCWndApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

    //注册窗口类
    WNDCLASS cls;
    ZeroMemory(&cls, sizeof(WNDCLASS));
    cls.lpfnWndProc = ::DefWindowProc;
    cls.style = CS_DBLCLKS;
    cls.hInstance = AfxGetInstanceHandle();
    cls.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    cls.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    cls.lpszClassName = L"my_wnd";
    VERIFY(AfxRegisterClass(&cls));

    CRect rc_frame_wnd(0, 0, 500, 500);
    const DWORD style = WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|0x0000C000|WS_SYSMENU|WS_OVERLAPPEDWINDOW|WS_SIZEBOX;
 
    m_myWnd.CreateEx(0, L"my_wnd", NULL, style, rc_frame_wnd, NULL, 0, NULL);
    m_pMainWnd = &m_myWnd;

    m_myWnd.CenterWindow();

    m_myWnd.ShowWindow(SW_SHOW);
    m_myWnd.UpdateWindow();

	return TRUE;
}
