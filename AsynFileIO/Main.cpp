
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPWSTR lpCmdLine, int nCmdShow)
{
    BOOL ret = PostThreadMessage(GetCurrentThreadId(), 8999, 222, 333);
    MSG msg;
    GetMessage(&msg, NULL, 0, 0);

    HANDLE hFile = CreateFile(L"F:\\vs2005\\VS80sp1-KB971090-X86-INTL.exe", GENERIC_READ | GENERIC_READ,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

    OVERLAPPED o = {0};
    o.Offset = 0;
    BYTE buf[1024];
    BOOL fRet = ReadFile(hFile, buf, 1024, NULL, &o);
    DWORD dwError = GetLastError();
    if (!fRet || dwError == ERROR_IO_PENDING)
    {
        WaitForSingleObject(hFile, INFINITE);

    }

    return 0;
}