#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include <Windows.h>

enum ToolType{
  EDIT_MOUSE,
  DRAW_LINE,
  DRAW_CURVE,
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
private:
  ToolType m_nowType = EDIT_MOUSE;

};

#endif // TOOL_MANAGER_H

