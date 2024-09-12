#ifndef GRAPH_MANAGER_H
#define GRAPH_MANAGER_H

#include <Windows.h>
#include "GraphEditor_def.h"
#include "GraphItemShape.h"
#include "GraphItemRectangle.h"
#include "GraphItemLine.h"
#include "GraphItemPolyline.h"
#include "GraphItemPolyBezier.h"
#include "GraphItemCircle.h"
#include "GraphItemElliptic.h"
#include "Vector.h"
#include "SelectShapeManager.h"
#include "GraphFile.h"
#include "GraphCommandManager.h"

class GraphManager 
{
public:
  GraphManager(HWND m_hWnd);
  ~GraphManager();
  void clear();
  UINT getWidth() const;
  UINT getHeight() const;
  HCURSOR getCursor(const PointF &scenePos);

  void paint(HDC hdc, const RectF& rectf, double scale);
  bool save(const TCHAR* szFilename);
  bool open(const TCHAR* szFIlename);
  bool copy();
  bool cut();
  bool paste();
  bool undo();
  bool redo();
  bool setShapeProper(const ShapeProperty& property);

  bool isSelect() const;
  void addShape(GraphItemShape* shape);
  bool delSelectShape();
  void setSelectShape(const PointF& pos);
  void setSelectShape(const RectF& rectf);

  void onMouseLButtonDown(const PointF& scenePos);
  void onMouseMove(bool fLButtonDown, const PointF& scenePos);
  void onMouseLButtonUp(const PointF& scenePos);
private:
  void freshView();
  bool setSelectShapeByPos(const PointF& pos);
  bool setSelectShapeByRect(const RectF& rectf);
private:
  HWND m_hWnd;
  UINT m_width  = MAX_SCENE_WIDTH;
  UINT m_height = MAX_SCENE_HEIGHT;

  SelectShapeManager m_selectMger;
  Vector<GraphItemShape*> m_shapeVec;

  GraphCommandManager* m_pCmdMger = nullptr;
  PointF m_mouseBeginPos;
  PointF m_mouseEndPos;
  PointF m_handlerBeginPos;

};

#endif// ! GRAPH_MANAGER_H


