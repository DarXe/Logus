#include <iostream>
#include <windows.h>

int main()
{
  system("taskkill /im Logus.exe /f");
  system("bin\\curl --url https://raw.githubusercontent.com/DarXe/Logus/master/Logus.exe --output bin\\Logus.exe");
  system("start Logus.exe");
  return 0;
}