#pragma once

class CMyList;
class CWordListController;

class CColumnStyle
{
public:
    CColumnStyle() : m_bUseDefaultFont(true) {}
    void SetFont(int nPointSize, LPCTSTR lpszFaceName);
    virtual void DrawItem(CWordListController& listController, int nItemIndex, int colIndex, CRect rcBound, CRect rcLabel, CDC* pDC) = 0;
protected:
    void DrawString(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat);
    CFont m_fontItem;
    bool  m_bUseDefaultFont;
};

class CColumnStyle_CheckBox : public CColumnStyle
{
public:
    virtual void DrawItem(CWordListController& listController, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC);
};

class CColumnStyle_Text : public CColumnStyle
{
public:
    virtual void DrawItem(CWordListController& listController, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC);
};

class CColumnStyle_Progress : public CColumnStyle
{
public:
    virtual void DrawItem(CWordListController& listController, int nItemIndex, int nColIndex, CRect rcBound, CRect rcLabel, CDC* pDC);
};
