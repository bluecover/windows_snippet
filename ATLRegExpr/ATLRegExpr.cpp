// ATLRegExpr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <atlstr.h> 
#include <atlrx.h>


int _tmain(int argc, _TCHAR* argv[])
{
    CAtlRegExp<> reUrl; 
    // five match groups: scheme, authority, path, query, fragment 
    REParseError status = reUrl.Parse( 
        L"http://www\\.sogou\\.com/web\\?query=[%a-zA-Z0-9]+&clickid={\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h\\h}"); 
    if (REPARSE_ERROR_OK != status) 
    { 
        // Unexpected error. 
        return 0; 
    } 
    const CAtlREMatchContext<>::RECHAR* szEnd = 0; 
    CAtlREMatchContext<> mcUrl; 
    wchar_t* url = L"http://www.sogou.com/web?query=1234&clickid=12345678abcdefff12345678abcdefff";
    if (!reUrl.Match(url, &mcUrl, &szEnd)) 
    { 
        // Unexpected error.
        return 0; 
    } 
    for (UINT nGroupIndex = 0; nGroupIndex < mcUrl.m_uNumGroups; 
        ++nGroupIndex) 
    { 
        const CAtlREMatchContext<>::RECHAR* szStart = 0; 
        const CAtlREMatchContext<>::RECHAR* szEnd = 0; 
        mcUrl.GetMatch(nGroupIndex, &szStart, &szEnd); 
        ptrdiff_t nLength = szEnd - szStart; 
        wprintf(L"%d: \"%.*s\"\n", nGroupIndex, nLength, szStart); 
    } 

	return 0;
}

