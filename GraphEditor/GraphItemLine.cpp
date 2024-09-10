#include "GraphItemLine.h"
#include <stdio.h>
#include <wchar.h>

GraphItemLine::GraphItemLine(PointF posA, PointF posB)
  :m_posA(posA),m_posB(posB)
{
  m_shapeType = SHAPE_LINE;
  m_ctrHandlers.resize(2);
  m_ctrHandlers[0] = new ControlHandler(this, HT_ALL, 0);
  m_ctrHandlers[1] = new ControlHandler(this, HT_ALL, 1);

  updateCtrHandler();
}

GraphItemLine::~GraphItemLine()
{
  clearCtrHandler();
}

Vector<TCHAR> GraphItemLine::toText()
{
  Vector<TCHAR> vec = GraphItemShape::toText();
  vec.push_back('2');
  vec.push_back(' ');
  
  TCHAR buffer[100];
  swprintf(buffer, 100, L"%f %f %f %f", m_posA.x, m_posA.y, m_posB.x, m_posB.y);
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');
  return vec;
}

void GraphItemLine::drawShape(HDC hdc, double xoff, double yoff)
{
  POINT pos;
  double sx = m_posA.x - xoff;
  double sy = m_posA.y - yoff;
  double ex = m_posB.x - xoff;
  double ey = m_posB.y - yoff;

  HPEN hpen = CreatePen(PS_SOLID, m_lineWidth, m_lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);
  
  MoveToEx(hdc, sx, sy, &pos);
  LineTo(hdc, ex, ey);

  MoveToEx(hdc, pos.x, pos.y,NULL);
  SelectObject(hdc, oldPen);
  DeleteObject(hpen);
}

void GraphItemLine::move(double dx, double dy)
{
  m_posA.x += dx;
  m_posA.y += dy;
  m_posB.x += dx;
  m_posB.y += dy;
  updateCtrHandler();
}

bool GraphItemLine::isPointUpShape(const PointF& pos)
{
  if(pos.x > max(m_posA.x, m_posB.x) || pos.x < min(m_posA.x, m_posB.x))
    return false;
  if(pos.y > max(m_posA.y, m_posB.y) || pos.y < min(m_posA.y, m_posB.y))
    return false;

  double left = (pos.x - m_posA.x) * (m_posB.y - m_posA.y);
  double right = (m_posB.x - m_posA.x) * (pos.y - m_posA.y);

  if(fabs(left - right) <= 1000)
    return true;
  return false;
}

bool GraphItemLine::isRectCrossShape(const RectF& rectf)
{
  SegmentF seg = { m_posA,m_posB };
  return rectf.isSegmentIntersect(seg);
}

bool GraphItemLine::shapeResizeTo(const PointF &pos, ControlHandler* handler)
{
  if(handler->getOwnerShape() != this) return false;

  int id = handler->getId();

  switch(id)
  {
    case 0:
    {
      m_posA = pos;
      break;
    }
    case 1:
    {
      m_posB = pos;
      break;
    }
  }
  updateCtrHandler();

  return true;
}

void GraphItemLine::updateCtrHandler()
{
  m_ctrHandlers[0]->setPos(m_posA);
  m_ctrHandlers[1]->setPos(m_posB);
}