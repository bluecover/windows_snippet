#pragma once

class CMyList;

class CColumnDrawer
{
public:
    CColumnDrawer() : m_pFont(NULL) {}
    void SetFont(CFont* pFont) { m_pFont = pFont; }
    virtual void DrawItem(CMyList* list, int nItemIndex, int colIndex, CRect rcBound, CRect rcLabel, CDC* pDC) = 0;
protected:
    void DrawString(CDC* pDC, CFont* pFont, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat);
    CFont* m_pFont;
};

class CColumnDrawer_CheckBox : public CColumnDrawer
{
public:
    virtual void DrawItem(CMyList* pList, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC);
};

class CColumnDrawer_Text : public CColumnDrawer
{
public:
    virtual void DrawItem(CMyList* pList, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC);
};

class CColumnDrawer_Progress : public CColumnDrawer
{
public:
    virtual void DrawItem(CMyList* pList, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC);
};
