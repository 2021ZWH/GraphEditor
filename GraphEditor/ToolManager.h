#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include <Windows.h>
#include "GraphItemShape.h"

enum ToolType{
  EDIT_MOUSE,
  DRAW_LINE,
  DRAW_POLYLINE,
  DRAW_BEZIER,
  DRAW_CIRCLE,
  DRAW_ELLIPTIC,
  DRAW_RECTANGLE,
};

class ToolManager
{
public:
  ToolManager();
  ~ToolManager();
  void setToolType(ToolType newType);
  ToolType getToolType() const;
  void drawRubberBand(HDC hdc, const POINT& pos1, const POINT& pos2, const POINT& pos3={0,0}, const POINT& pos4={0,0});
  bool isValidShape() const;
  bool updateShape(const PointF& pos1, const PointF& pos2 = { 0,0 }, const PointF &pos3 = { 0,0 });
  void setShape(GraphItemShape *shape);
  void clearShape();
private:
  ToolType m_nowType = EDIT_MOUSE;
  GraphItemShape* m_drawShape = nullptr;

};

#endif // TOOL_MANAGER_H

