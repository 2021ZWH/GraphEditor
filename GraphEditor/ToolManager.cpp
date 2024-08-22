#include "ToolManager.h"
#include "GraphEditor_def.h"

ToolManager::ToolManager()
{

}

ToolManager::~ToolManager()
{
  
}

void ToolManager::setToolType(ToolType newType)
{
  m_nowType = newType;
}

ToolType ToolManager::getToolType() const
{
  return m_nowType;
}

void ToolManager::drawRubberBand(HDC hdc, const POINT& startPos, const POINT& endPos)
{
  HBRUSH hBru = (HBRUSH)GetStockObject(NULL_BRUSH); // ±³¾°Í¸Ã÷µÄ»­Ë¢

  HPEN hPen;
  if(m_nowType == EDIT_MOUSE)
    hPen = CreatePen(PS_DASH, 1, BGR_LIGHTBLUE);
  else hPen = CreatePen(PS_SOLID, 1, BGR_BLACK);

  HBRUSH oldHBru = (HBRUSH)SelectObject(hdc, hBru);
  HPEN oldHPen = (HPEN)SelectObject(hdc, hPen);

  SetROP2(hdc, R2_NOTXORPEN);

  switch(m_nowType)
  {
  case EDIT_MOUSE:
    Rectangle(hdc, startPos.x, startPos.y, endPos.x, endPos.y);
    break;
  case DRAW_RECTANGLE:
    Rectangle(hdc, startPos.x, startPos.y, endPos.x, endPos.y);
    break;
  }

  SelectObject(hdc,oldHBru);
  SelectObject(hdc,oldHPen);
  DeleteObject(hPen);
}
