#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <Windows.h>
#include "Window.h"
#include "GraphManager.h"
#include "ScrollBarManager.h"

class GraphView : public Window
{
public:
  GraphView(HINSTANCE hIns, HWND hParent);
  ~GraphView();
  void init();
  void destroy();
  void resize(int w,int h);
  POINT mapToScene(const POINT &viewPos);
  POINT mapToView(const POINT& scenePos);
private:
  static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK runProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onCreate();
  void onPaint();
  void onMouseLButtonDown(WPARAM wParam, LPARAM lParam);
  void onMouseWheel(WPARAM wParam, LPARAM lParam);
private:
  POINT     m_viewPoint = { 0,0 };

  GraphManager      *m_pGhMger = nullptr;
  ScrollBarManager  *m_pSbMger = nullptr;

};

#endif// GRAPH_VIEW_H