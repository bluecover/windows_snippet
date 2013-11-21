
#include <windows.h>
#include <atlstr.h> 
#include <atlrx.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    CString str;
    GetModuleFileName(NULL, str.GetBuffer(MAX_PATH), MAX_PATH);
    str.ReleaseBuffer();

    int posSlash = str.ReverseFind(_T('\\'));
    str.Delete(posSlash, str.GetLength() - posSlash);

    ATL::CRegKey key;
    key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion"));
    CString strProgramFilePath;
    ULONG nChars = MAX_PATH;
    key.QueryStringValue(_T("ProgramFilesDir"), strProgramFilePath.GetBuffer(nChars), &nChars);
    strProgramFilePath.ReleaseBuffer();


    return 0;
}