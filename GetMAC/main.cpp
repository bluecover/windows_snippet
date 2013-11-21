
#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Iphlpapi.lib")

int main()
{
    ULONG uBufLen = sizeof(IP_ADAPTER_INFO);
    PIP_ADAPTER_INFO pAdapterInfo = (PIP_ADAPTER_INFO)operator new(uBufLen);
    DWORD dwRet = GetAdaptersInfo(pAdapterInfo, &uBufLen);
    if (dwRet == ERROR_BUFFER_OVERFLOW)
    {
        delete pAdapterInfo;
        pAdapterInfo = (PIP_ADAPTER_INFO)operator new(uBufLen);
    }

    char szMac[255] = {0};
    dwRet = GetAdaptersInfo(pAdapterInfo, &uBufLen);
    if (dwRet == ERROR_SUCCESS)
    {
        for (PIP_ADAPTER_INFO pInfo = pAdapterInfo; pInfo; pInfo = pInfo->Next)
        {   
            if (pInfo->Type == MIB_IF_TYPE_ETHERNET)
            {
                sprintf_s(szMac, 255, "%02x-%02x-%02x-%02x-%02x-%02x\n",
                        pInfo->Address[0], pInfo->Address[1],
                        pInfo->Address[2], pInfo->Address[3],
                        pInfo->Address[4], pInfo->Address[5]
                        );
            }
        }
    }
    delete pAdapterInfo;

    return 0;
}