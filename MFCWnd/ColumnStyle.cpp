#include "stdafx.h"
#include "ColumnStyle.h"
#include "WordListController.h"

void CColumnStyle::SetFont(int nPointSize, LPCTSTR lpszFaceName)
{
    if (m_fontItem.CreatePointFont(nPointSize, lpszFaceName))
    {
        m_bUseDefaultFont = true;
    }
}

void CColumnStyle::DrawString(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat)
{
    CFont* pOldFont = NULL;
    if (m_bUseDefaultFont)
    {
        pOldFont = pDC->SelectObject(&m_fontItem);
    }

    pDC->DrawText(lpszString, lstrlen(lpszString), &rect, nFormat);

    if (m_bUseDefaultFont)
    {
        pDC->SelectObject(pOldFont);
    }
}

void CColumnStyle_CheckBox::DrawItem(CWordListController& listController, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC)
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

    CWord* word = listController.GetWordByIndex(nItemIndex);
    if (word && word->m_bIsChecked)
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
    CString szText = listController.GetItemText(nItemIndex, nColIndex);
    DrawString(pDC, szText, lstrlen(szText), rcLabel, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
}

void CColumnStyle_Text::DrawItem(CWordListController& listController, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC)
{
    rcLabel.left += 4;
    rcLabel.right -= 2;
    CString szText = listController.GetItemText(nItemIndex, nColIndex);
    DrawString(pDC, szText, lstrlen(szText), rcLabel, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
}

void CColumnStyle_Progress::DrawItem(CWordListController& listController, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC)
{
    
}