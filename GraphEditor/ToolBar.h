#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include <Windows.h>
#include <CommCtrl.h>
#include "Window.h"
#pragma comment(lib ,"Comctl32.lib")
class ToolBar : public Window
{
public:
  ToolBar(HINSTANCE hIns,HWND hParent);
  ~ToolBar();
  void init();
  void destroy();
private:
  HIMAGELIST m_imgList = nullptr;

};
#endif // TOOL_BAR_H

