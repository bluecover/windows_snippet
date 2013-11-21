// Crash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include  <dbghelp.h> 

#pragma comment(lib, "dbghelp.lib")

LONG WINAPI MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
    MessageBox(0,0,0,0);

    TCHAR strDumpFile[MAX_PATH]; 
    swprintf_s(strDumpFile, MAX_PATH, L"%d.dmp", GetTickCount());
    HANDLE hFile = CreateFile(strDumpFile, GENERIC_WRITE, FILE_SHARE_WRITE, 
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) 
    { 
        MINIDUMP_EXCEPTION_INFORMATION ExInfo; 

        ExInfo.ThreadId = ::GetCurrentThreadId(); 
        ExInfo.ExceptionPointers = pExceptionInfo; 
        ExInfo.ClientPointers = NULL; 

        // write the dump 
        BOOL bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), 
            hFile, MiniDumpNormal, &ExInfo, NULL, NULL); 
        CloseHandle(hFile); 
    } 

    return EXCEPTION_EXECUTE_HANDLER;
}

int _tmain(int argc, _TCHAR* argv[])
{
    SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

    int *p  = NULL;
    *p = 1;

	return 0;
}

