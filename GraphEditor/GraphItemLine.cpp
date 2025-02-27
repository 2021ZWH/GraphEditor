#include "GraphItemLine.h"
#include <stdio.h>
#include <wchar.h>

GraphItemLine::GraphItemLine(PointF posA, PointF posB)
  :GraphItemShape::GraphItemShape(),m_posA(posA),m_posB(posB)
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

void GraphItemLine::drawShape(HDC hdc)
{
  POINT pos;
  double sx = m_posA.x;
  double sy = m_posA.y;
  double ex = m_posB.x;
  double ey = m_posB.y;

  HPEN hpen;
  if(m_shapeProper.lineWidth == 0) hpen = (HPEN)GetStockObject(NULL_PEN);
  else hpen = CreatePen(PS_SOLID, m_shapeProper.lineWidth, m_shapeProper.lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);

  XFORM oldXForm;
  GetWorldTransform(hdc, &oldXForm);
  ModifyWorldTransform(hdc, &m_xForm, MWT_RIGHTMULTIPLY);
  
  MoveToEx(hdc, sx, sy, &pos);
  LineTo(hdc, ex, ey);

  MoveToEx(hdc, pos.x, pos.y,NULL);

  SetWorldTransform(hdc, &oldXForm);
  SelectObject(hdc, oldPen);

  if(m_shapeProper.lineWidth)
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