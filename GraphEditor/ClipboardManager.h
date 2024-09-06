#ifndef CLIPBOARD_MANAGER_H
#define CLIPBOARD_MANAGER_H

#include <Windows.h>

class ClipboardManager
{
public:
  ClipboardManager(HWND hwnd);
  ~ClipboardManager();
  TCHAR* getText();
  bool setText(const TCHAR* szText);
private:
  HWND m_hWnd = NULL;

};

#endif // CLIPBOARD_MANAGER_H

