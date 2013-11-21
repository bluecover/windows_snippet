// CMyList.cpp : implementation file
//

#include "stdafx.h"
#include "MFCWnd.h"
#include "MyList.h"
#include "ColumnStyle.h"

// CMyList

IMPLEMENT_DYNAMIC(CMyList, CListCtrl)

BEGIN_MESSAGE_MAP(CMyList, CListCtrl)
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CMyList::OnSelectionChange)
END_MESSAGE_MAP()

const DWORD CMyList::ms_dwListStyle   = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_OWNERDATA;
const DWORD CMyList::ms_dwListStyleEx = LVS_EX_SUBITEMIMAGES| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_DOUBLEBUFFER;

CMyList::CMyList()
{
}

CMyList::~CMyList()
{
    for (int i = 0; i < (int)m_columnDrawers.size(); ++i)
    {
        delete m_columnDrawers[i];
    }
    m_columnDrawers.clear();
}

BOOL CMyList::Create(CWnd* pParent, UINT nID)
{
    if (!CListCtrl::Create(ms_dwListStyle, CRect(0,0,0,0), pParent, nID))
    {
        return FALSE;
    }
    return TRUE;
}

void CMyList::AddColumn(ColumnType type, int index, const CString& str, int format, int width)
{
    InsertColumn(index, str, format, width);
    
    switch (type)
    {
    case COLUMN_TYPE_CHECKBOX:
        m_columnDrawers.push_back(new CColumnStyle_CheckBox);
        break;
    case COLUMN_TYPE_TEXT:
        m_columnDrawers.push_back(new CColumnStyle_Text);
        break;
    case COLUMN_TYPE_PROGRESS:
        m_columnDrawers.push_back(new CColumnStyle_Progress);
        break;
    default:
        break;
    }
}

void CMyList::SetColumnFont( int index, int nPointSize, LPCTSTR lpszFaceName )
{
    if (index < 0 || index >= (int)m_columnDrawers.size())
    {
        return;
    }

    m_columnDrawers[index]->SetFont(nPointSize, lpszFaceName);
}

INT CMyList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    ListView_SetExtendedListViewStyle(m_hWnd, ms_dwListStyleEx);
    ModifyStyle(NULL, LVS_SHOWSELALWAYS);


    m_imgList.Create(2, 18, ILC_COLOR16|ILC_MASK, 18, 1);
    SetImageList(&m_imgList, LVSIL_SMALL);
    
    return 0;
}

VOID CMyList::OnSelectionChange(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pnmlv = (LPNMLISTVIEW)pNMHDR;
    if (pnmlv->uChanged & LVIF_STATE)
    {
        BOOL bSel = GetItemState(pnmlv->iItem, LVIS_SELECTED) == LVIS_SELECTED;
        SetCheck(pnmlv->iItem, bSel);
    }
    *pResult = 0;
}

void CMyList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    int nItem = lpDrawItemStruct->itemID;
    COLORREF crBkgnd = GetSysColor(COLOR_WINDOW);
    if (GetItemState(nItem, LVIS_SELECTED))
    {
        crBkgnd = GetSysColor(COLOR_HIGHLIGHT); // Ñ¡ÖÐ¸ßÁÁ

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

    for (size_t i = 0; i < m_columnDrawers.size(); ++i)
    {
        CRect rcLable;
        GetSubItemRect(nItem, (int)i, LVIR_LABEL, rcLable);
        CRect rcBound;
        GetSubItemRect(nItem, (int)i, LVIR_BOUNDS, rcBound);

        m_columnDrawers[i]->DrawItem(this, nItem, (int)i, rcBound, rcLable, pDC);
    }
}


