#ifndef GRAPH_MANAGER_H
#define GRAPH_MANAGER_H

#include <Windows.h>
#include "GraphEditor_def.h"
#include "GraphItemShape.h"
#include "GraphItemRectangle.h"
#include "GraphItemLine.h"
#include "GraphItemPolyline.h"
#include "Vector.h"
#include "SelectShapeManager.h"

class GraphManager 
{
public:
  GraphManager(HWND m_hWnd);
  ~GraphManager();
 
  UINT getWidth() const;
  UINT getHeight() const;
  HCURSOR getCursor(const PointF &scenePos );
  void paint(HDC hdc, const RectF& rectf,double scale);

  bool isSelect() const;

  void addShape(GraphItemShape* shape);

  void onMouseLButtonDown(const PointF& scenePos,bool canSelect);
  void onMouseMove(bool fLButtonDown, const PointF& scenePos);
  void onMouseLButtonUp(const PointF& scenePos);
private:
 
private:
  HWND m_hWnd;
  UINT m_width  = MAX_SCENE_WIDTH;
  UINT m_height = MAX_SCENE_HEIGHT;

  SelectShapeManager m_selectMger;

  Vector<GraphItemShape*> m_shapeVec;

  PointF m_mouseBeginPos;

};

#endif// ! GRAPH_MANAGER_H


