#pragma once

#include "MyList.h"
#include "WordListController.h"

class My_wnd : public CWnd
{
public:
    My_wnd();
    ~My_wnd();

private:
    CString m_cpt_text;;

    CWordListController m_ListController;
    CButton m_SortBtn;

    void OnBtnSort();


protected:
    DECLARE_DYNAMIC(My_wnd)

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()
};