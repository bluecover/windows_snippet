
#include <windows.h>
#include <WinInet.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, int nCmdShow)
{
    DWORD dwSize = 0;
    BOOL bRet = InternetGetCookieW(L"http://www.sogou.com", NULL, NULL, &dwSize);
    TCHAR* pCookie = new TCHAR[dwSize];
    bRet = InternetGetCookieW(L"http://www.sogou.com", NULL, pCookie, &dwSize);

    return 0;
}