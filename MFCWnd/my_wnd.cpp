#include "stdafx.h"
#include "my_wnd.h"

#define ID_MY_LIST 8888

IMPLEMENT_DYNAMIC(My_wnd, CWnd)

BEGIN_MESSAGE_MAP(My_wnd, CWnd)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(123, OnBtnSort)
END_MESSAGE_MAP()

My_wnd::My_wnd()
{

}

My_wnd::~My_wnd()
{

}

int My_wnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    //LV_DISPINFO

    if (CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }
    
    m_ListController.CreateListCtrl(this, ID_MY_LIST);
        

    const wchar_t chars[] = { L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l',
        L'm', L'n', L'o', L'p', L'q', L'r',
        L's', L't', L'u', L'v', L'w', L'x', L'y', L'z' };

    srand((int)time(0));
    for (int m = 0; m < 100000; ++m)
    {
        wchar_t word[20] = {0};

        int n = rand() % 19 + 1;
        for (int i = 0; i < n; ++i)
        {
            int j = rand() % 26;
            word[i] = chars[j];
        }

        m_ListController.AddWord(CWord(word, L"[&&&]", L"v. ÄãºÃ", 0.0f, L"2012-3-5", L""));
    }

    m_SortBtn.Create(_T("ÅÅÐò"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect(10,10,100,30), this, 123);

    return 0;
}

void My_wnd::OnSize(UINT nType, int cx, int cy)
{
    CRect rc_client;
    GetClientRect(&rc_client);

    CRect rcList(0, 30, rc_client.Width(), rc_client.Height());
    m_ListController.MoveWindow(rcList);
}

void My_wnd::OnBtnSort()
{
    m_ListController.Sort();
}