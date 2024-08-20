#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include <Windows.h>

enum ToolType{
  EDIT_MOUSE,
  DRAW_RECTANGLE,

};
class ToolManager
{
public:
  ToolManager();
  ~ToolManager();
  void setToolType(ToolType newType);
  ToolType getToolType() const;
private:
  ToolType m_nowType = EDIT_MOUSE;

};

#endif// TOOL_MANAGER_H

