#pragma once

typedef void (WINAPI *LPFN_PGNSI)(LPSYSTEM_INFO);

typedef struct tagLVITEM64A
{
    UINT mask;
    int iItem;
    int iSubItem;
    UINT state;
    UINT stateMask;
    INT64 pszText;
    int cchTextMax;
    int iImage;
    LPARAM lParam;
#if (_WIN32_IE >= 0x0300)
    int iIndent;
#endif
#if (_WIN32_WINNT >= 0x501)
    int iGroupId;
    UINT cColumns; // tile view columns
    PUINT puColumns;
#endif
} LVITEM64A, *LPLVITEM64A;


class CDesktopIconTracker
{
public: 
    static BOOL GetIconRect(const CString& strIconName, LPRECT lpRect, HWND &hDeskListView);

private:
    static BOOL GetIconRect32(HWND hDeskWnd, const CString& strIconName, LPRECT lpRect);
    static BOOL GetIconRect64(HWND hDeskWnd, const CString& strIconName, LPRECT lpRect);
    static BOOL Is64BitOS();
};