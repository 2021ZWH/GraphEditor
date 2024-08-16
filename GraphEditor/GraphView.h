#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <Windows.h>
#include "Window.h"
#include "GraphManager.h"

class GraphView : public Window
{
public:
  GraphView(HINSTANCE hIns, HWND hParent);
  ~GraphView();
  void init();
  void destroy();
private:
  static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK runProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onPaint();
  void onMouseLButtonDown(WPARAM wParam, LPARAM lParam);
  void onMouseWheel(WPARAM wParam, LPARAM lParam);
private:

  double    m_scale = 1.0;
  POINT     m_viewPoint = { 0,0 };

  GraphManager* m_pGhMger = nullptr;

};

#endif // GRAPH_VIEW_H