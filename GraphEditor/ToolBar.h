#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include <Windows.h>
#include <CommCtrl.h>
#include "Window.h"
#include "Vector.h"

#pragma comment(lib ,"Comctl32.lib")

enum IDM_TBBUTTON {
  BT_EDITMODE =0,
  BT_LINE ,
  BT_POLYLINE,
  BT_BEZIER,
  BT_CIRCLE,
  BT_ELLIPTIC,
  BT_RECTANGLE,
  BT_TEXTSHAPE,
  BT_DASHBOARD 
};

class ToolBar : public Window
{
public:
  ToolBar(HINSTANCE hIns,HWND hParent);
  ~ToolBar();
  void init();
  void destroy();
  void resize();
  void checkButton(IDM_TBBUTTON idx);
private:
  HIMAGELIST m_imgList = nullptr;
  Vector<HICON> m_iconVec;

};
#endif// TOOL_BAR_H

