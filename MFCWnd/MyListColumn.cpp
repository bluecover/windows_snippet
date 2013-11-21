#include "stdafx.h"
#include "MyList.h"
#include "MyListColumn.h"

void CColumnDrawer::DrawString(CDC* pDC, CFont* pFont, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat)
{
    CFont* pOldFont = NULL;
    if (pFont)
    {
        pOldFont = pDC->SelectObject(pFont);
    }

    pDC->DrawText(lpszString, lstrlen(lpszString), &rect, nFormat);

    if (pOldFont)
    {
        pDC->SelectObject(pOldFont);
    }
}

void CColumnDrawer_CheckBox::DrawItem(CMyList* pList, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC)
{
    if (rcBound.IsRectEmpty() || rcBound.right < 0)
    {
        return;
    }

    CRect rcCheckBox = rcBound;
    rcCheckBox.top = rcCheckBox.top - rcBound.Height() * nItemIndex;
    rcCheckBox.bottom = rcCheckBox.bottom - rcBound.Height() * nItemIndex;
    rcCheckBox.left += 3;
    rcCheckBox.right = rcCheckBox.left + rcCheckBox.Height();

    rcBound.left += 3;
    rcBound.top += 3;
    rcBound.bottom -= 4;
    rcBound.right = rcBound.left + rcBound.Height();

    CPen * pOldPen;
    pDC->FillSolidRect(&rcBound, GetSysColor(COLOR_WINDOW));
    CBrush brush(RGB(0,0,0));
    pDC->FrameRect(&rcBound, &brush);

    if (pList->GetCheck(nItemIndex))
    {
        CPen * rpOldPen = NULL;
        CPen blackpen(PS_SOLID, 1, RGB(51,153,51));

        pOldPen = pDC->SelectObject(&blackpen);

        // »­¶Ô¹´
        int x = rcBound.left + 10;
        int y = rcBound.top + 4;
        ASSERT(x < rcBound.right && y < rcBound.bottom);
        for (int i = 0; i < 4; ++i, --x, ++y)
        {
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y+3);

        }

        for (int i = 0; i < 3; i++, --x, --y)
        {
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y+3);
        }

        if (pOldPen)
            pDC->SelectObject(pOldPen);
    }

    rcLabel.left += 4;
    rcLabel.right -= 2;
    CString szText = pList->GetItemText(nItemIndex, nColIndex);
    DrawString(pDC, m_pFont, szText, lstrlen(szText), rcLabel, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
}

void CColumnDrawer_Text::DrawItem(CMyList* pList, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC)
{
    rcLabel.left += 4;
    rcLabel.right -= 2;
    CString szText = pList->GetItemText(nItemIndex, nColIndex);
    DrawString(pDC, m_pFont, szText, lstrlen(szText), rcLabel, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
}

void CColumnDrawer_Progress::DrawItem(CMyList* pList, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC)
{
    
}