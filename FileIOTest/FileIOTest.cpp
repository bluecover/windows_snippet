// FileIOTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <windows.h>

//#define USE_STREAM

int _tmain(int argc, _TCHAR* argv[])
{
    DWORD time = timeGetTime();

#ifdef USE_STREAM
    std::wstring finalFilename(L"QQ2011.exe");
    std::ifstream ifile(finalFilename.c_str(), std::ios::binary | std::ios::ate);
    if(ifile.fail())
    {
        return false;
    }

    std::streampos size = ifile.tellg();
    ifile.seekg(0, std::ios::beg);
    unsigned char* buffer = new unsigned char[size];
    ifile.read(reinterpret_cast<char*>(buffer), size);
    ifile.close();
    delete [] buffer;
#else
     HANDLE hFile = ::CreateFileW(L"QQ2011.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
     if (INVALID_HANDLE_VALUE != hFile)
     {
         DWORD dwSize = ::GetFileSize(hFile, NULL);
         if (0 != dwSize)
         {
             unsigned char* buffer = new unsigned char[dwSize];
             DWORD dwRead = 0;
             BOOL bRet = ::ReadFile(hFile, buffer, dwSize, &dwRead, NULL);
             delete [] buffer;
         }
         ::CloseHandle(hFile);
     }
#endif

    DWORD e = timeGetTime() - time;

    printf("%d\n", e);


	return 0;
}

