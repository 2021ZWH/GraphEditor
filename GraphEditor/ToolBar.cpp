#include "ToolBar.h"
#include "resource.h"

ToolBar::ToolBar(HINSTANCE hIns, HWND hParent)
{
  Window::init(hIns, hParent);
}

ToolBar::~ToolBar()
{
  destroy();
}

void ToolBar::destroy()
{
  if(m_hWnd)
  {
    DestroyWindow(m_hWnd);
    m_hWnd = nullptr;
  }
}

void ToolBar::init()
{
  m_hWnd= CreateWindowEx(0,
    TOOLBARCLASSNAME, 
    NULL,
    WS_CHILD | WS_BORDER | WS_VISIBLE,
    0, 0, 16, 16,
    m_hParent, 
    NULL, 
    m_hIns, 
    NULL);
  
  HICON hIco = (HICON)LoadIcon(m_hIns, MAKEINTRESOURCE(IDI_RECTANGLE));

  m_imgList = ImageList_Create(16, 16, ILC_COLOR24 | ILC_MASK, 1, 0);
  ImageList_AddIcon(m_imgList, hIco);

  SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)m_imgList);

  TBBUTTON tbb[1];
  ZeroMemory(&tbb, sizeof(tbb));
  tbb[0].iBitmap = 0;
  tbb[0].fsState = TBSTATE_ENABLED;
  tbb[0].fsStyle = TBSTYLE_BUTTON;
  tbb[0].idCommand = 2;
  tbb[0].iString = (INT_PTR)L"Create a new file";

  SendMessage(m_hWnd, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);

  SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}

void ToolBar::resize()
{
  SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}