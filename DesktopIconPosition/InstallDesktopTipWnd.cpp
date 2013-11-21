#include "stdafx.h"
#include "Resource.h"
#include "InstallDesktopTipWnd.h"

using namespace Gdiplus;

Gdiplus::GdiplusStartupInput CInstallDesktopTipWnd::ms_GdiStartupInput;
ULONG_PTR CInstallDesktopTipWnd::ms_GdiToken;

IMPLEMENT_DYNAMIC(CInstallDesktopTipWnd, CWnd)

BEGIN_MESSAGE_MAP(CInstallDesktopTipWnd, CWnd)
    ON_MESSAGE(WM_NCCALCSIZE, OnNcCalcSize)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CInstallDesktopTipWnd::CInstallDesktopTipWnd()
{

}

CInstallDesktopTipWnd::~CInstallDesktopTipWnd()
{

}

LRESULT CInstallDesktopTipWnd::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void CInstallDesktopTipWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
}

int CInstallDesktopTipWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  Add your specialized creation code here

    Status status = GdiplusStartup(&ms_GdiToken, &ms_GdiStartupInput, NULL);
    ATLASSERT(status == Ok);    

    LoadBkgImage();

    // 把图片拉伸到窗口大小
    m_BufferMemBitmap = CreateDefaultDIBSection(WND_X, WND_Y);
    m_BufferMemDC = ::CreateCompatibleDC(NULL);
    ::SelectObject(m_BufferMemDC, m_BufferMemBitmap);

    StretchBltX(m_BufferMemDC, 0, 0, WND_X, WND_Y, 
        m_ImageMemDC, 0, 0, m_ImageWidth, m_ImageHeight, CRect(0, 0, 0, 0));


    FontFamily* fontFamily = new FontFamily(L"微软雅黑");
    Font* font = new Gdiplus::Font(fontFamily, 18.0f, FontStyleRegular, UnitPixel);

    LPCTSTR lpszString = L"欢迎您使用有道词典！";

    CRect rc;
    GetClientRect(&rc);
    Gdiplus::RectF rectF((REAL)rc.left, (REAL)rc.top, (REAL)rc.Width(), (REAL)rc.Height());
    StringFormat stringFormat;
    stringFormat.SetAlignment(StringAlignmentCenter);
    stringFormat.SetLineAlignment(StringAlignmentCenter);
    Gdiplus::Color strColor(254, 0, 0, 0);
    SolidBrush  solidBrush(strColor);

    Graphics graphics(m_BufferMemDC);
    graphics.DrawString(lpszString, -1, font, rectF, &stringFormat, &solidBrush);

    return 0;
}

void CInstallDesktopTipWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: Add your message handler code here
    // Do not call CWnd::OnPaint() for painting messages

    DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
    {
        ::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED);
    }

    CRect screenRect;
    GetWindowRect(&screenRect);
    int cx = screenRect.Width();
    int cy = screenRect.Height();
    CPoint dstPos(screenRect.left, screenRect.top);
    CSize  size(cx, cy);
    CPoint srcPos(0, 0);

    BLENDFUNCTION blendFunction = {0};
    blendFunction.BlendOp = AC_SRC_OVER;  
    blendFunction.BlendFlags = 0;
    blendFunction.AlphaFormat = AC_SRC_ALPHA;
    blendFunction.SourceConstantAlpha = 255;
    ::UpdateLayeredWindow(m_hWnd, 0, &dstPos, &size, m_BufferMemDC, &srcPos, 0, &blendFunction, ULW_ALPHA);
}

HBITMAP CInstallDesktopTipWnd::CreateDefaultDIBSection(int width, int height)
{  
    BITMAPINFOHEADER	bmih;   
    ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));   

    bmih.biSize				= sizeof(BITMAPINFOHEADER) ;   
    bmih.biWidth			= width;   
    bmih.biHeight			= height;   
    bmih.biPlanes			= 1;   
    bmih.biBitCount			= 32;
    bmih.biCompression		= BI_RGB;   
    bmih.biSizeImage		= 0;   
    bmih.biXPelsPerMeter	= 0;   
    bmih.biYPelsPerMeter	= 0;   
    bmih.biClrUsed			= 0;   
    bmih.biClrImportant		= 0;   

    BYTE*	pBits = NULL;   
    HBITMAP hBitMap = CreateDIBSection(NULL, (BITMAPINFO*) &bmih, 0, (VOID**)&pBits, NULL, 0) ;  

    return hBitMap;  
} 

void CInstallDesktopTipWnd::StretchBltX(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, const CRect& dim)
{
    // fix left
    if (hdcDest != hdcSrc)
    {
        BitBlt(hdcDest, xDest, yDest, dim.left, hSrc, hdcSrc, xSrc, ySrc, SRCCOPY);
    }

    // fix right
    BitBlt(hdcDest, xDest + wDest - dim.right, yDest, dim.right, hSrc, hdcSrc, xSrc + wSrc - dim.right, ySrc, SRCCOPY);

    // stretch mid
    StretchBlt(hdcDest, xDest + dim.left, yDest, wDest - dim.left - dim.right, hSrc, hdcSrc, xSrc + dim.left, ySrc, wSrc - dim.left - dim.right, hSrc, SRCCOPY);
}

bool CInstallDesktopTipWnd::LoadBkgImage()
{
    HRSRC hRes = FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_PNG_NEW), _T("png"));
    if(hRes == NULL)
    {
        return false;
    }
    DWORD dwResSize = SizeofResource(AfxGetInstanceHandle(), hRes);
    if(dwResSize <= 0)
    {
        return false;
    }
    HGLOBAL hResData = LoadResource(AfxGetInstanceHandle(), hRes);
    if(hResData == NULL)
    {
        return false;
    }
    LPVOID lpResourceData = LockResource(hResData);
    HGLOBAL hResourceBuffer = GlobalAlloc(GMEM_MOVEABLE, dwResSize);
    LPVOID lpResourceBuffer = GlobalLock(hResourceBuffer); 
    CopyMemory(lpResourceBuffer, lpResourceData, dwResSize);
    IStream* piStream = NULL; 
    if(CreateStreamOnHGlobal(hResourceBuffer, FALSE, &piStream) == S_OK)
    {
        m_Image = Image::FromStream(piStream);
        piStream->Release();
    }
    GlobalUnlock(hResourceBuffer);
    GlobalFree(hResourceBuffer);
    FreeResource(hResData);

    ATLASSERT(m_Image);
    m_ImageWidth = m_Image->GetWidth();
    m_ImageHeight = m_Image->GetHeight();

    m_ImageMemBitmap = CreateDefaultDIBSection(m_ImageWidth, m_ImageHeight);
    m_ImageMemDC = ::CreateCompatibleDC(NULL);
    ::SelectObject(m_ImageMemDC, m_ImageMemBitmap);

    Gdiplus::Graphics memGraphics(m_ImageMemDC);
    memGraphics.SetCompositingMode(CompositingModeSourceOver);
    memGraphics.SetCompositingQuality(CompositingQualityHighSpeed);
    BitBlt(m_ImageMemDC, 0, 0, m_ImageWidth, m_ImageHeight, NULL, 0, 0, BLACKNESS);
    Gdiplus::ImageAttributes imAtt; 	
    imAtt.SetWrapMode(Gdiplus::WrapModeTileFlipXY);
    memGraphics.DrawImage(m_Image, Gdiplus::Rect(0, 0, m_ImageWidth, m_ImageHeight),
        0, 0, m_ImageWidth, m_ImageHeight, Gdiplus::UnitPixel, &imAtt, NULL, NULL);

    return true;
}

void CInstallDesktopTipWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    DestroyWindow();
    PostQuitMessage(0);
}