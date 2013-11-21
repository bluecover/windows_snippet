// Wow6432Node.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <Shlwapi.h>

int _tmain(int argc, _TCHAR* argv[])
{
    DWORD result = SHDeleteKeyW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ÓÐµÀ´Êµä");
    
    if (result != ERROR_SUCCESS)
    {
        DWORD error = GetLastError();

    }

    return 0;
}

