#ifndef  GRAPH_MANAGER_H
#define GRAPH_MANAGER_H

#include <Windows.h>

class GraphManager 
{
public:
  GraphManager(HWND m_hWnd);
  ~GraphManager();
  void paint(HDC hdc, const RECT &rect);
private:
  

private:
  HWND m_hWnd;



};


#endif // ! GRAPH_MANAGER_H


