#ifndef GRAPH_MANAGER_H
#define GRAPH_MANAGER_H

#include <Windows.h>
#include "GraphEditor_def.h"

class GraphManager 
{
public:
  GraphManager(HWND m_hWnd);
  ~GraphManager();
 
  UINT getWidth() const;
  UINT getHeight() const;
  void paint(HDC hdc, const RECT& rect);
private:
  

private:
  HWND m_hWnd;
  UINT m_width  = MAX_SCENE_WIDTH;
  UINT m_height = MAX_SCENE_HEIGHT;


};

#endif// ! GRAPH_MANAGER_H


