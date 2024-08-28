#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include <Windows.h>
#include "GraphItemShape.h"

enum ToolType{
  EDIT_MOUSE,
  DRAW_LINE,
  DRAW_POLYLINE,
  DRAW_BEZIER,
  DRAW_RECTANGLE,
  DEAW_ELLIPTIC
};

class ToolManager
{
public:
  ToolManager();
  ~ToolManager();
  void setToolType(ToolType newType);
  ToolType getToolType() const;
  void drawRubberBand(HDC hdc, const POINT& startpos, const POINT& endPos);
  bool isValidShape() const;
  bool updateShape(const PointF& startPos, const PointF& endPos);
  void setShape(GraphItemShape *shape);
  void clearShape();
private:
  ToolType m_nowType = EDIT_MOUSE;
  GraphItemShape* m_drawShape = nullptr;

};

#endif // TOOL_MANAGER_H

