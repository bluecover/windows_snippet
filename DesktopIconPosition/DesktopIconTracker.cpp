#include "stdafx.h"
#include "DesktopIconTracker.h"

BOOL CDesktopIconTracker::GetIconRect(const CString& strIconName, LPRECT lpRect, HWND &hDeskListView)
{
    HWND hDeskWnd = NULL; //桌面上SysListView32的窗口句柄
    HWND hWnd  = ::FindWindow(_T("WorkerW"), NULL); //先当WIN7系统查找
    while (hWnd)
    {
        HWND hShellView = ::FindWindowEx(hWnd, NULL, _T("SHELLDLL_DefView"), NULL);
        if (hShellView)
        {
            hDeskWnd = ::FindWindowEx(hShellView, NULL, _T("SysListView32"), NULL);
            break;
        }
        hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
    }

    if (!hDeskWnd)
    {
        //如果没找到，再按XP方式查找
        hWnd = ::FindWindow(_T("Progman"), _T("Program Manager"));
        if (hWnd)
        {
            hWnd = ::FindWindowEx(hWnd, NULL, _T("SHELLDLL_DefView"), NULL);
            hDeskWnd = ::FindWindowEx(hWnd, NULL, _T("SysListView32"), NULL);
        }
    }

    if(!hDeskWnd)
    {
        return FALSE;
    }

    hDeskListView = hDeskWnd;
    BOOL bRet = FALSE;
    if (Is64BitOS())
    {
        bRet = GetIconRect64(hDeskWnd, strIconName, lpRect);
    }
    else
    {
        bRet = GetIconRect32(hDeskWnd, strIconName, lpRect);
    }
    if (bRet)
    {
        CPoint pt(lpRect->left, lpRect->top);
        ::ClientToScreen(hDeskWnd, &pt);
        OffsetRect(lpRect, pt.x-lpRect->left, pt.y-lpRect->top);
    }
    return bRet;
}

BOOL CDesktopIconTracker::GetIconRect32(HWND hDeskWnd, const CString& strIconName, LPRECT lpRect)
{
    BOOL bRet = FALSE;
    DWORD PID = 0;
    GetWindowThreadProcessId(hDeskWnd,&PID);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
    if (!hProcess)
    {
        return FALSE;
    }
    else
    {
        LVITEMA* pLVITEM = (LVITEMA*)VirtualAllocEx(hProcess, NULL, sizeof(LVITEM), MEM_COMMIT, PAGE_READWRITE);
        char* pszText = (char*)VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT, PAGE_READWRITE);
        RECT* pItemRc = (RECT*)VirtualAllocEx(hProcess, NULL, sizeof(RECT), MEM_COMMIT, PAGE_READWRITE);
        RECT rc;
        if (!pItemRc || !pLVITEM)
        {
            return FALSE;
        }
        else
        {
            LVITEMA LVITEM;
            LVITEM.mask = LVIF_TEXT;
            LVITEM.cchTextMax = 512;
            LVITEM.pszText = pszText;
            char ItemBuf[512];
            int nCount = (int)::SendMessage(hDeskWnd, LVM_GETITEMCOUNT, 0, 0);
            for (int iItem = 0; iItem < nCount; iItem++)
            {
                LVITEM.iItem = iItem;
                LVITEM.iSubItem = 0; 
                // 将设置好的结构插入目标进程
                WriteProcessMemory(hProcess, pLVITEM, &LVITEM, sizeof(LVITEM), NULL);
                // 发送LVM_GETITEM消息
                BOOL r = (BOOL)::SendMessage(hDeskWnd, LVM_GETITEMTEXTA, iItem, (LPARAM)pLVITEM);
                // 获取pszText
                ReadProcessMemory(hProcess, pszText, ItemBuf, 512, NULL);
                CString str = CString(ItemBuf);
                if (str == strIconName)
                {				
                    ::SendMessage(hDeskWnd, LVM_GETITEMRECT, iItem, (LPARAM)pItemRc);
                    ReadProcessMemory(hProcess, pItemRc, &rc, sizeof(RECT), NULL);
                    memcpy(lpRect, &rc, sizeof(RECT));
                    bRet = TRUE;
                    break;
                }
            }

            VirtualFreeEx(hProcess, pLVITEM, 0, MEM_RELEASE);
            VirtualFreeEx(hProcess, pszText, 0, MEM_RELEASE);
            VirtualFreeEx(hProcess, pItemRc, 0, MEM_RELEASE);
        }
        CloseHandle(hProcess);
    }

    return bRet;
}

BOOL CDesktopIconTracker::GetIconRect64(HWND hDeskWnd, const CString& strIconName, LPRECT lpRect)
{
    BOOL bRet = FALSE;
    DWORD PID = 0;
    GetWindowThreadProcessId(hDeskWnd, &PID);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
    if (!hProcess)
    {
        return FALSE;
    }
    else
    {
        LVITEM64A* pLVITEM = (LVITEM64A*)VirtualAllocEx(hProcess, NULL, sizeof(LVITEM64A), MEM_COMMIT, PAGE_READWRITE);
        char* pszText = (char*)VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT, PAGE_READWRITE);
        RECT* pItemRc = (RECT*)VirtualAllocEx(hProcess, NULL, sizeof(RECT), MEM_COMMIT, PAGE_READWRITE);
        RECT rc;
        if(!pItemRc || !pLVITEM)
        {
            return FALSE;
        }
        else
        {
            LVITEM64A LVITEM;
            LVITEM.mask = LVIF_TEXT;
            LVITEM.cchTextMax = 512;
            LVITEM.pszText = (INT64)pszText;
            char ItemBuf[512];
            int nCount = (int)::SendMessage(hDeskWnd, LVM_GETITEMCOUNT, 0, 0);
            for (int iItem = 0; iItem < nCount; iItem++)
            {
                LVITEM.iItem = iItem;
                LVITEM.iSubItem = 0;
                //将设置好的结构插入目标进程
                WriteProcessMemory(hProcess, pLVITEM, &LVITEM, sizeof(LVITEM), NULL);
                //发送LVM_GETITEM消息
                BOOL r = (BOOL)::SendMessage(hDeskWnd, LVM_GETITEMTEXTA, iItem, (LPARAM)pLVITEM);
                //获取pszText
                ReadProcessMemory(hProcess, pszText, ItemBuf, 512, NULL);
                CString str = CString(ItemBuf);
                if(str == strIconName)
                {				
                    ::SendMessage(hDeskWnd, LVM_GETITEMRECT, iItem, (LPARAM)pItemRc);
                    ReadProcessMemory(hProcess, pItemRc, &rc, sizeof(RECT), NULL);
                    memcpy(lpRect, &rc, sizeof(RECT));
                    bRet = TRUE;
                    break;
                }

            }

            VirtualFreeEx(hProcess, pLVITEM, 0, MEM_RELEASE);
            VirtualFreeEx(hProcess, pszText, 0, MEM_RELEASE);
            VirtualFreeEx(hProcess, pItemRc, 0, MEM_RELEASE);
        }
        CloseHandle(hProcess);
    }

    return bRet;
}

BOOL CDesktopIconTracker::Is64BitOS()
{
    SYSTEM_INFO si = { 0 };
    LPFN_PGNSI pGNSI = (LPFN_PGNSI)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetNativeSystemInfo");
    if (pGNSI == NULL)
    {
        return FALSE;
    }
    pGNSI(&si);
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || 
        si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}