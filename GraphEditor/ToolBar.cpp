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
  m_hWnd = CreateWindowEx(0,
    TOOLBARCLASSNAME,
    NULL,
    WS_CHILD | WS_BORDER | WS_VISIBLE,
    0, 0, 16, 16,
    m_hParent,
    NULL,
    m_hIns,
    NULL);

  m_imgList = ImageList_Create(16, 16, ILC_COLOR24 | ILC_MASK, 6, 0);

  WORD icoId[6] = { IDI_CURSOR,IDI_LINE,IDI_POLYLINE,IDI_BEZIER,IDI_RECTANGLE,IDI_ELLIPTIC };
  int iIcon[6];
  for(int i = 0; i < 6; i++)
  {
    HICON hicon = (HICON)LoadIcon(m_hIns, MAKEINTRESOURCE(icoId[i]));
    iIcon[i] = ImageList_AddIcon(m_imgList, hicon);
  }

  SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)m_imgList);

  TBBUTTON tbb[7] =
  {
    { MAKELONG(iIcon[0], 0), BT_EDITMODE, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0, NULL},
    { 0, BT_RECTANGLE, TBSTATE_ENABLED, TBSTYLE_SEP, {0}, 0, NULL},
    { MAKELONG(iIcon[1], 0), BT_LINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[2], 0), BT_POLYLINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[3], 0), BT_BEZIER, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[4], 0), BT_RECTANGLE, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[5], 0), BT_ELLIPTIC, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0, NULL}
  };
  
  SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);   //计算工具栏大小
  SendMessage(m_hWnd, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);

  resize();
}

void ToolBar::resize()
{
  SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}