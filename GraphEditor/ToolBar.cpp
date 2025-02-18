#include "ToolBar.h"
#include "resource.h"

ToolBar::ToolBar(HINSTANCE hIns, HWND hParent)
{
  Window::init(hIns, hParent);
}

ToolBar::~ToolBar()
{ 
  for(int i = 0; i < m_iconVec.size(); i++)
    DeleteObject(m_iconVec[i]);
  ImageList_Destroy(m_imgList);
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

  m_imgList = ImageList_Create(16, 16, ILC_COLOR24 | ILC_MASK, 8, 0);

  WORD icoId[] = { IDI_CURSOR,
                   IDI_LINE,
                   IDI_POLYLINE,
                   IDI_BEZIER,
                   IDI_CIRCLE,
                   IDI_ELLIPTIC,
                   IDI_RECTANGLE,
                   IDI_TEXTSHAPE,
                   IDI_DASHBOARD };

  int idNum = sizeof icoId / sizeof WORD;

  int* iIcon = new int[idNum];

  for(int i = 0; i < idNum; i++)
  {
    HICON hicon = (HICON)LoadIcon(m_hIns, MAKEINTRESOURCE(icoId[i]));
    m_iconVec.push_back(hicon);
    iIcon[i] = ImageList_AddIcon(m_imgList, hicon);
  }
 
  SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)m_imgList);

  TBBUTTON tbb[] =
  {
    { MAKELONG(iIcon[0], 0), BT_EDITMODE, TBSTATE_ENABLED,  BTNS_BUTTON , {0}, 0, NULL},
    { 0, -1, TBSTATE_ENABLED, TBSTYLE_SEP, {0}, 0, NULL},
    { MAKELONG(iIcon[1], 0), BT_LINE, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[2], 0), BT_POLYLINE, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[3], 0), BT_BEZIER, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[4], 0), BT_CIRCLE, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[5], 0), BT_ELLIPTIC, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[6], 0), BT_RECTANGLE, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { MAKELONG(iIcon[7], 0), BT_TEXTSHAPE, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL},
    { 0, -1, TBSTATE_ENABLED, TBSTYLE_SEP, {0}, 0, NULL },
    { MAKELONG(iIcon[8], 0), BT_DASHBOARD, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, NULL}
  };
  
  SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);   //计算工具栏大小
  SendMessage(m_hWnd, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);

  resize();
}

void ToolBar::resize()
{
  SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}

void ToolBar::checkButton(IDM_TBBUTTON idx)
{
  if(idx == 8)
  {
    bool ret = SendMessage(m_hWnd, TB_ISBUTTONPRESSED, idx, 0);
      SendMessage(m_hWnd, TB_PRESSBUTTON, idx, !ret);
  }
  else
  {
    SendMessage(m_hWnd, TB_PRESSBUTTON, idx, true);
    for(int i = 0; i < 8; i++)
    {
      if(idx == i) continue;

      if(SendMessage(m_hWnd, TB_ISBUTTONPRESSED, i, 0))
        SendMessage(m_hWnd, TB_PRESSBUTTON, i, false);
    }
  }
  
}