#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <Windows.h>
#include "Window.h"
#include "GraphEditor_def.h"
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
  bool save(const TCHAR* szFilename);
  bool open(const TCHAR* szFilename);
  bool copy();
  bool cut();
  bool paste();
  bool undo();
  bool redo();
  bool setShapeProperty(const ShapeProperty &property);
  void setTempText(TCHAR* pText, int len);
  PointF mapToScene(const POINT &viewPos);
  POINT mapToView(const PointF &scenePos);
private:
  static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK runProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onCreate();
  void onPaint();
  void onSetCursor(LPARAM lParam);
  void onKeyDown(WPARAM wParam, LPARAM lParam);
  void onMouseLButtonDown(WPARAM wParam, LPARAM lParam);
  void onMouseLButtonUp(WPARAM wParam, LPARAM lParam);
  void onMouseRButtonDown(WPARAM wParam, LPARAM lParam);
  void onMouseMove(WPARAM wParam, LPARAM lParam);
  void onMouseWheel(WPARAM wParam, LPARAM lParam);

  void startDraw(const POINT& pos);
  void drawNext(const POINT& pos);
  void onDraw(bool fLButtonDown,const POINT& pos);
  void endDraw(const POINT& pos);
private:
  double    m_scale = 1.0;
  HBRUSH    m_hBgdBru;

  GraphManager      *m_pGhMger = nullptr;
  ScrollBarManager  *m_pSbMger = nullptr;
  ToolManager       *m_pToolMger = nullptr;

  PointF m_startPos;
  PointF m_endPos;
  PointF m_aptF[5];
  ShapeProperty m_shapeProperty;
  bool isDrawing = false;

  Vector<TCHAR> m_tempStr;

};

#endif // GRAPH_VIEW_H