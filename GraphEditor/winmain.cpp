#include <Windows.h>
#include "GraphEditor.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
  AllocConsole();
#endif// _DEBUG

  GraphEditor GE(hInstance,nullptr);
  GE.init();
  MSG msg = { 0 };
  while (GetMessage(&msg, NULL, 0, 0))
  {
    if(!GE.translateAccelator(&msg))
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
}