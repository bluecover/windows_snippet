// CreateFileTwice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <ShlObj.h>
#include <shlwapi.h>
#include <string>

#pragma comment(lib, "shlwapi.lib")

int _tmain(int argc, _TCHAR* argv[])
{
  HANDLE hvolume1 = CreateFileW(
    L"C:\\Users\\Jim\\AppData\\Roaming\\WandoujiaUsbDriver\\33F9DF8D2000F3A6E56C83E479B48E53_13028264933821.zip",
    GENERIC_READ,
    0,
    NULL,
    OPEN_EXISTING,
    0,
    NULL);

  HANDLE hvolume2 = CreateFileW(
    L"C:\\Users\\Jim\\AppData\\Roaming\\WandoujiaUsbDriver\\002_dfe690df0.zip.wdj",
    GENERIC_READ,
    0,
    NULL,
    OPEN_EXISTING,
    0,
    NULL);

  HANDLE hvolume3 = CreateFileW(
    L"C:\\Users\\Jim\\AppData\\Roaming\\WandoujiaUsbDriver\\33F9DF8D2000F3A6E56C83E479B48E53_13028264933821\\android_winusb.inf",
    GENERIC_READ,
    0,
    NULL,
    OPEN_EXISTING,
    0,
    NULL);

  const char* device_path = "\\\\?\\usb#vid_12d1&pid_1038&mi_01#7&389a7fb&0&0001#{f72fe0d4-cbcb-407d-8814-9ed673d0dd6b}";

  bool success = false;
  HANDLE usb_handle = CreateFileA(device_path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
  if (usb_handle != INVALID_HANDLE_VALUE) {
    char buf[512 + 1] = { 0 };
    DWORD temp = 0;
    if (DeviceIoControl(usb_handle, CTL_CODE(FILE_DEVICE_UNKNOWN, 16, METHOD_BUFFERED, FILE_READ_ACCESS), NULL, NULL, &buf, 512, &temp, NULL)) {
      buf[temp] = '\0';
      success = true;
    }
    CloseHandle(usb_handle);
  }
	return 0;
}

