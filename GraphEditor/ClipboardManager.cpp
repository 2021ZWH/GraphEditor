#include "ClipBoardManager.h"

ClipboardManager::ClipboardManager(HWND hwnd)
  :m_hWnd(hwnd)
{

}

ClipboardManager::~ClipboardManager()
{

}

TCHAR* ClipboardManager::getText()
{
  /*if(OpenClipboard(m_hWnd))
  {
    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if(hData == NULL)
    {
      CloseClipboard();
      return nullptr;
    }

    LPWSTR pData = (LPWSTR)GlobalLock(hData);
    if(pData == nullptr)
    {
      CloseClipboard();
      return nullptr;
    }

    int size = wcslen(pData) * sizeof(WCHAR);
    TCHAR* szText = new TCHAR[wcslen(pData) + 1];
    memcpy(szText, pData, size);
    szText[wcslen(pData)] = NULL;
    GlobalUnlock(hData);
    CloseClipboard();
    return szText;
  }*/
  if(m_clipData.size())
  {
    TCHAR* szText = new TCHAR[m_clipData.size()+1];
    if(szText == nullptr) return nullptr;
    for(int i = 0; i < m_clipData.size(); i++)
      szText[i] = m_clipData[i];
    szText[m_clipData.size()] = NULL;
    return szText;
  }
  return nullptr;
}

bool ClipboardManager::setText(const TCHAR* szText)
{
  /*if(OpenClipboard(m_hWnd)) {
    EmptyClipboard();
    int szTextLen = lstrlen(szText);
    HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, (szTextLen + 1) * sizeof(TCHAR));
    if(hData == INVALID_HANDLE_VALUE || hData == NULL)
    {
      CloseClipboard();
      return false;
    }

    LPWSTR pData = (LPWSTR)GlobalLock(hData);
    if(pData == nullptr)
    {
      CloseClipboard();
      return false;
    }

    memcpy(pData, szText, szTextLen * sizeof(TCHAR));
    pData[szTextLen + 1] = NULL;
    SetClipboardData(CF_UNICODETEXT, hData);
    GlobalUnlock(hData);
    CloseClipboard();
    return true;
  }*/

  int szTextLen = lstrlen(szText);
  if(!szTextLen) return false;

  m_clipData.resize(szTextLen);
  for(int i = 0; i < szTextLen; i++)
    m_clipData[i] = szText[i];
  return true;
}