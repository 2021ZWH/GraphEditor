#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <Windows.h>
#include "Window.h"
#include "GraphManager.h"
#include "ScrollBarManager.h"
#include "ToolManager.h"

class GraphView : public Window
{
public:
  GraphView(HINSTANCE hIns, HWND hParent);
  ~GraphView();
  void init();
  void destroy();
  void resize(int w, int h);
  void setMode(ToolType toolType);
  POINT mapToScene(const POINT &viewPos);
  POINT mapToView(const POINT &scenePos);
private:
  static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK runProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onCreate();
  void onPaint();
  void onSetCursor();
  void onMouseLButtonDown(WPARAM wParam, LPARAM lParam);
  void onMouseLButtonUp(WPARAM wParam, LPARAM lParam);
  void onMouseMove(WPARAM wParam, LPARAM lParam);
  void onMouseWheel(WPARAM wParam, LPARAM lParam);
private:
  double    m_scale = 1.0;
  HBRUSH    m_hBgdBru;

  GraphManager      *m_pGhMger = nullptr;
  ScrollBarManager  *m_pSbMger = nullptr;
  ToolManager       *m_pToolMger = nullptr;

  POINT m_startPos;
  POINT m_endPos;

};

#endif// GRAPH_VIEW_H