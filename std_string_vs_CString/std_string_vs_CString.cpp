// std_string_vs_CString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <atlbase.h>
#include <atlstr.h>
#include "WTL80/atlapp.h"
#include "WTL80/atlmisc.h"

#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
    std::wstring str3(L"Hello");
    std::wstring str4(str3);

    DWORD time2 = timeGetTime();

    for (int i = 0; i < 1000000; ++i)
    {
        std::wstring tempStr = str4;
        int c = str4 > L"hello";
        std::wstring tempStr2 = tempStr;
        tempStr2 += L", World!";
        str3 = tempStr2;
    }

    printf("%d\n", timeGetTime() - time2);

    CStringW str(L"Hello");
    CStringW str2(str);

    DWORD time = timeGetTime();

    for (int i = 0; i < 1000000; ++i)
    {
        CStringW tempStr = str2;
        int c = str2.Compare(L"hello");
        CStringW tempStr2 = tempStr;
        tempStr2 += L", World!";
        str = tempStr2;
    }

    printf("%d\n", timeGetTime() - time);




	return 0;
}

&