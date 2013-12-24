#include <windows.h>

int main() {
  const wchar_t* name = L"%ProgramFiles%\\HwAndInstall\\hw_android_usb_driver";
  wchar_t buf[MAX_PATH] = {L'\0'};
  DWORD count = ::ExpandEnvironmentStrings(name, buf, MAX_PATH);

  return 0;
}