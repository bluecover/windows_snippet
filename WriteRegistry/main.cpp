#include <windows.h>
#include <string>

int main() {
  const std::string UNINSTALL_KEY_32 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
  HKEY key;
  LONG result = RegCreateKeyExA(
    HKEY_LOCAL_MACHINE, 
    "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\1234567890ABCDEFG", 
    0, 
    NULL, 
    REG_OPTION_NON_VOLATILE, 
    KEY_READ | KEY_WRITE, 
    NULL, 
    &key, 
    NULL
    );
  
  if (result == ERROR_SUCCESS) {
    MessageBoxA(NULL, NULL, NULL, 0);
  }

  return 0;
}