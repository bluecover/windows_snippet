/********************************************************************
	filename: 	WordListController.cpp	
	created:	2012/03/05
	author:		ZhaoHao
	purpose:	
*********************************************************************/
#include "stdafx.h"
#include "WordListController.h"
#include <algorithm>

const DWORD CWordListController::ms_dwListStyle
    = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_OWNERDRAWFIXED/* | LVS_OWNERDATA*/;
const DWORD CWordListController::ms_dwListStyleEx 
    = LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_DOUBLEBUFFER;

IMPLEMENT_DYNAMIC(CWordListController, CListCtrl)

BEGIN_MESSAGE_MAP(CWordListController, CListCtrl)
    ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnSelectionChange)
    ON_NOTIFY_REFLECT(LVN_GETDISPINFO, GetDisplayInfo)
END_MESSAGE_MAP()

CWordListController::CWordListController() : 
    m_vecColumnStyles(COLUMN_MAX)
{
    
}

CWordListController::~CWordListController()
{
    for (ColumnStyleList::iterator it = m_vecColumnStyles.begin();
         it != m_vecColumnStyles.end();
         ++it)
    {
        delete (*it);
    }
    m_vecColumnStyles.clear();
    m_vecWordListAll.clear();
}


BOOL CWordListController::CreateListCtrl(CWnd* pParent, int nID)
{
    if (!Create(ms_dwListStyle, CRect(0,0,0,0), pParent, nID))
    {
        return FALSE;
    }

    ListView_SetExtendedListViewStyle(GetSafeHwnd(), ms_dwListStyleEx);
    ModifyStyle(NULL, LVS_SHOWSELALWAYS);

    m_imgList.Create(2, 18, ILC_COLOR16|ILC_MASK, 18, 1);
    SetImageList(&m_imgList, LVSIL_SMALL);

    InsertColumn(COLUMN_NUMBER, _T(""), LVCFMT_CENTER, 50);
    m_vecColumnStyles[COLUMN_NUMBER] = new CColumnStyle_CheckBox;

    InsertColumn(COLUMN_NAME, _T("单 词"), LVCFMT_CENTER, 90);
    m_vecColumnStyles[COLUMN_NAME] = new CColumnStyle_Text;
    
    InsertColumn(COLUMN_SOUNDMARK, _T("音 标"), LVCFMT_CENTER, 90);
    m_vecColumnStyles[COLUMN_SOUNDMARK] = new CColumnStyle_Text;
    m_vecColumnStyles[COLUMN_SOUNDMARK]->SetFont(100, _T("微软雅黑"));

    InsertColumn(COLUMN_EXPLANATION, _T("解 释"), LVCFMT_CENTER, 220);
    m_vecColumnStyles[COLUMN_EXPLANATION] = new CColumnStyle_Text;
    m_vecColumnStyles[COLUMN_EXPLANATION]->SetFont(100, _T("宋体"));

    InsertColumn(COLUMN_PROGRESS, _T("复习完成度"), LVCFMT_CENTER, 100);
    m_vecColumnStyles[COLUMN_PROGRESS] = new CColumnStyle_Progress;

    InsertColumn(COLUMN_COLLECT_TIME, _T("收藏时间"), LVCFMT_CENTER, 90);
    m_vecColumnStyles[COLUMN_COLLECT_TIME] = new CColumnStyle_Text;

    InsertColumn(COLUMN_CATEGORY, _T("分类"), LVCFMT_CENTER, 60);    
    m_vecColumnStyles[COLUMN_CATEGORY] = new CColumnStyle_Text;

    m_vecWordListAll.reserve(10000);

    return TRUE;
}

void CWordListController::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    int nItem = lpDrawItemStruct->itemID;
    COLORREF crBkgnd = GetSysColor(COLOR_WINDOW);
    if (GetItemState(nItem, LVIS_SELECTED))
    {
        crBkgnd = GetSysColor(COLOR_HIGHLIGHT); // 选中高亮

        COLORREF crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
        pDC->SetTextColor(crText);

    }
    else
    {
        COLORREF crText = GetSysColor(COLOR_WINDOWTEXT);
        pDC->SetTextColor(crText);
    }
    pDC->FillSolidRect(&lpDrawItemStruct->rcItem, crBkgnd);
    pDC->SetBkMode(TRANSPARENT);

    for (size_t i = 0; i < m_vecColumnStyles.size(); ++i)
    {
        CRect rcLable;
        GetSubItemRect(nItem, (int)i, LVIR_LABEL, rcLable);
        CRect rcBound;
        GetSubItemRect(nItem, (int)i, LVIR_BOUNDS, rcBound);

        m_vecColumnStyles[i]->DrawItem(*this, nItem, (int)i, rcBound, rcLable, pDC);
    }
}

VOID CWordListController::GetDisplayInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFOW* pDispInfo = (NMLVDISPINFOW*)pNMHDR;
    LV_ITEMW* pItem= &(pDispInfo)->item;

    int iItemIndx = pItem->iItem; 
    if (iItemIndx >= (int)m_vecIndexList.size())
    {
        return;
    }

    CWord& word = m_vecWordListAll[m_vecIndexList[iItemIndx]];

    int iSubItem = pItem->iSubItem;
    if (pItem->mask & LVIF_TEXT)
    {
        CString strItem;
        switch (iSubItem)
        {
        case COLUMN_NUMBER:
            strItem.Format(L"%d", iItemIndx + 1);
            break;
        case COLUMN_NAME:
            strItem = word.m_strName;
            break;
        case COLUMN_SOUNDMARK:
            strItem = word.m_strSoundmark;;
            break;
        case COLUMN_EXPLANATION:
            strItem = word.m_strExplanation;
            break;
        case COLUMN_COLLECT_TIME:
            strItem = word.m_strCollectTime;
            break;
        case COLUMN_CATEGORY:
            strItem = word.m_strCategory;
            break;
        }

        memcpy(pItem->pszText, strItem.GetString(), strItem.GetLength() * sizeof(TCHAR));
        *(pItem->pszText + strItem.GetLength()) = 0;
    }
}

void CWordListController::AddWord(const CWord& newWord)
{
    m_vecWordListAll.push_back(newWord);
    SetItemCount((int)m_vecWordListAll.size());

    m_vecIndexList.push_back(m_vecWordListAll.size() - 1);

    int iIndex = (int)m_vecWordListAll.size();

    CString csTemp;
    csTemp.Format(_T("%d"), iIndex);
    InsertItem(iIndex, csTemp);
}

CWordListController::WordList& CWordListController::GetDisplayList()
{
    return m_vecWordListAll;
}

VOID CWordListController::OnSelectionChange(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pnmlv = (LPNMLISTVIEW)pNMHDR;
    
    int index = pnmlv->iItem;
    if (index < 0 || index >= (int)m_vecIndexList.size())
    {
        for (IndexList::iterator it = m_vecIndexList.begin();
            it != m_vecIndexList.end();
            ++it)
        {
            m_vecWordListAll[*it].m_bIsChecked = false;
        }
        *pResult = 0;
        return;
    }

    if (pnmlv->uChanged & LVIF_STATE)
    {
        BOOL bSel = (GetItemState(pnmlv->iItem, LVIS_SELECTED) == LVIS_SELECTED);
        m_vecWordListAll[m_vecIndexList[index]].m_bIsChecked = bSel? true:false;
    }

    *pResult = 0;
}

CWord* CWordListController::GetWordByIndex(size_t index)
{
    if (index < 0 || index >= m_vecIndexList.size())
    {
        return NULL;
    }

    return &m_vecWordListAll[m_vecIndexList[index]];
}

void CWordListController::Sort()
{
    std::sort(m_vecIndexList.begin(), m_vecIndexList.end(), CWordIndexCmpPre(m_vecWordListAll));
    RedrawItems(0, (int)m_vecIndexList.size() - 1);
}