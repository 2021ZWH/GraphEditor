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

void ToolManager::drawRubberBand(HDC hdc, const POINT& pos1, const POINT& pos2, const POINT& pos3, const POINT& pos4)
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
      Rectangle(hdc, pos1.x, pos1.y, pos2.x, pos2.y);
      break;
    case DRAW_LINE:
    {
      POINT pos;
      MoveToEx(hdc, pos1.x, pos1.y, &pos);
      LineTo(hdc, pos2.x, pos2.y);
      MoveToEx(hdc, pos.x, pos.y, NULL);
      break;
    }
    case DRAW_POLYLINE:
    {
      POINT pos;
      MoveToEx(hdc, pos1.x, pos1.y, &pos);
      LineTo(hdc, pos2.x, pos2.y);
      MoveToEx(hdc, pos.x, pos.y, NULL);
      break;
    }
    case DRAW_BEZIER:
    {
      POINT* apt = new POINT[4];
      if(apt == nullptr) break;

      apt[0] = pos1, apt[1] = pos2, apt[2] = pos3, apt[3] = pos4;
      PolyBezier(hdc, apt, 4);

      HPEN blueDashPen = CreatePen(PS_DASH, 1, BGR_LIGHTBLUE);
      SelectObject(hdc, blueDashPen);
      POINT pos;
      MoveToEx(hdc, apt[2].x, apt[2].y, &pos);
      LineTo(hdc, apt[3].x, apt[3].y);
      MoveToEx(hdc, pos.x, pos.y, NULL);

      DeleteObject(blueDashPen);
      delete[] apt;
      break;
    }
    case DRAW_CIRCLE:
    {
      int w = max(pos2.x - pos1.x, pos2.y - pos1.y);
      Ellipse(hdc, pos1.x, pos1.y, pos1.x + w, pos1.y + w);
      break;
    }
    case DRAW_ELLIPTIC:
    {
      Ellipse(hdc, pos1.x, pos1.y, pos2.x, pos2.y);
      break;
    }
    case DRAW_RECTANGLE:
      Rectangle(hdc, pos1.x, pos1.y, pos2.x, pos2.y);
      break;
  }

  SelectObject(hdc,oldHBru);
  SelectObject(hdc,oldHPen);
  DeleteObject(hPen);
}

bool ToolManager::isValidShape() const
{
  return m_drawShape != nullptr;
}

bool ToolManager::updateShape(const PointF& pos1, const PointF& pos2 , const PointF& pos3)
{
  if(!isValidShape()) return false;

  switch(m_nowType)
  {
  case DRAW_POLYLINE:
    m_drawShape->addPos(pos1);
    break;
  case DRAW_BEZIER:
    m_drawShape->addPos(pos1);
    m_drawShape->addPos(pos2);
    m_drawShape->addPos(pos3);
    break;
  }

  return true;
}

void ToolManager::setShape(GraphItemShape *shape)
{
  m_drawShape = shape;
}

void ToolManager::clearShape()
{
  m_drawShape = nullptr;
}


