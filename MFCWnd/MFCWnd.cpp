// MFCWnd.cpp : ����Ӧ�ó��������Ϊ��
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


// CMFCWndApp ����

CMFCWndApp::CMFCWndApp()
{
    

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCWndApp ����

CMFCWndApp theApp;


// CMFCWndApp ��ʼ��

BOOL CMFCWndApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

    //ע�ᴰ����
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
