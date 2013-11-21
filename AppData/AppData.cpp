// AppData.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <shlobj.h>

int _tmain(int argc, _TCHAR* argv[])
{
    wchar_t appdataPath[MAX_PATH] = {0};
    HRESULT result = SHGetFolderPath(
        0, CSIDL_APPDATA, 0, SHGFP_TYPE_CURRENT, appdataPath
        );

    wchar_t localAppdataPath[MAX_PATH] = {0};
    result = SHGetFolderPath(
        0, CSIDL_LOCAL_APPDATA, 0, SHGFP_TYPE_CURRENT, localAppdataPath
        );

    int startMenuDirCSIDL[] = 
    {
        CSIDL_PROGRAMS, CSIDL_COMMON_PROGRAMS
    };
    wchar_t programPath[MAX_PATH] = {0};
    HRESULT getProgramFolderResult = SHGetFolderPath(
        0, startMenuDirCSIDL[1], 0, SHGFP_TYPE_DEFAULT, programPath
        );
	return 0;
}

