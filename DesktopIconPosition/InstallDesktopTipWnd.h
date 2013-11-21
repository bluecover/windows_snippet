#pragma once

#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

const int WND_X = 332;
const int WND_Y = 61;

class CInstallDesktopTipWnd : public CWnd
{
public:
    static HBITMAP CreateDefaultDIBSection(int width, int height);
    static void StretchBltX(HDC hdcDest, int xDest, int yDest, int wDest, int hDest,
                            HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, const CRect& dim);


    CInstallDesktopTipWnd();
    ~CInstallDesktopTipWnd();

protected:
    DECLARE_DYNAMIC(CInstallDesktopTipWnd)
    DECLARE_MESSAGE_MAP()

private:
    bool LoadBkgImage();

    static Gdiplus::GdiplusStartupInput	ms_GdiStartupInput;
    static ULONG_PTR ms_GdiToken;

    Gdiplus::Image*	m_Image;
    HBITMAP         m_ImageMemBitmap;
    HDC				m_ImageMemDC;
    HBITMAP         m_BufferMemBitmap;
    HDC				m_BufferMemDC;
    int				m_ImageWidth;
    int				m_ImageHeight; 

    afx_msg LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

};