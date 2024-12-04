#include "GraphItemRectangle.h"
#include <stdio.h>
#include <wchar.h>

GraphItemRectangle::GraphItemRectangle(PointF beginPos, PointF endPos)
  :GraphItemShape::GraphItemShape()
{
  m_shapeType = SHAPE_RECTANGLE;
  m_aptF.resize(4);
  m_aptF[0] = { beginPos.x,endPos.y };
  m_aptF[1] = beginPos;
  m_aptF[2] = { endPos.x,beginPos.y };
  m_aptF[3] = endPos;

  m_ctrHandlers.resize(8);
  m_ctrHandlers[0] = new ControlHandler(this,HandlerType::HT_SW, 0);
  m_ctrHandlers[1] = new ControlHandler(this,HandlerType::HT_WEST,1);
  m_ctrHandlers[2] = new ControlHandler(this,HandlerType::HT_NW, 2);
  m_ctrHandlers[3] = new ControlHandler(this,HandlerType::HT_NORTH, 3);
  m_ctrHandlers[4] = new ControlHandler(this,HandlerType::HT_NE, 4);
  m_ctrHandlers[5] = new ControlHandler(this,HandlerType::HT_EAST, 5);
  m_ctrHandlers[6] = new ControlHandler(this,HandlerType::HT_SE, 6);
  m_ctrHandlers[7] = new ControlHandler(this,HandlerType::HT_SOUTH,7);

  updateCtrHandler();
}

GraphItemRectangle::~GraphItemRectangle()
{
  GraphItemShape::clearCtrHandler();
}

Vector<TCHAR> GraphItemRectangle::toText()
{
  Vector<TCHAR> vec = GraphItemShape::toText();

  TCHAR buffer[100];
  _itow_s(m_aptF.size(), buffer, 10);
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  for(int i = 0; i < m_aptF.size(); i++)
  {
    swprintf(buffer, 100, L"%f %f", m_aptF[i].x, m_aptF[i].y);
    for(int i = 0; i < lstrlen(buffer); i++)
      vec.push_back(buffer[i]);
    vec.push_back(' ');
  }

  return vec;
}

void GraphItemRectangle::drawShape(HDC hdc,double xoff, double yoff)
{
  RectF rect;
  rect.left = min(m_aptF[0].x, m_aptF[2].x) - xoff;
  rect.right = max(m_aptF[0].x, m_aptF[2].x) - xoff;
  rect.top = min(m_aptF[0].y, m_aptF[2].y) - yoff;
  rect.bottom = max(m_aptF[0].y, m_aptF[2].y) - yoff;
  
  HBRUSH hbru;
  if(m_shapeProper.fTransparent) hbru = (HBRUSH)GetStockObject(NULL_BRUSH);
  else hbru = CreateSolidBrush(m_shapeProper.fillColor);
  HBRUSH oldBru = (HBRUSH)SelectObject(hdc, hbru);

  HPEN hpen;
  if(m_shapeProper.lineWidth == 0) hpen = (HPEN)GetStockObject(NULL_PEN);
  else hpen = CreatePen(PS_SOLID, m_shapeProper.lineWidth, m_shapeProper.lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);
  
  Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

  SelectObject(hdc, oldBru);
  SelectObject(hdc, hpen);

  if(!m_shapeProper.fTransparent) 
    DeleteObject(hbru);
  if(m_shapeProper.lineWidth)
    DeleteObject(hpen);
}

void GraphItemRectangle::move(double dx, double dy)
{
 
  for(int i = 0; i < m_aptF.size(); i++)
  {
    m_aptF[i].x += dx;
    m_aptF[i].y += dy;
  }

  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    m_ctrHandlers[i]->move(dx, dy);
  }
}

bool GraphItemRectangle::isPointUpShape(const PointF& pos)
{
  double x = pos.x;
  double y = pos.y;

  RectF rect;
  rect.left = min(m_aptF[0].x, m_aptF[2].x);
  rect.right = max(m_aptF[0].x, m_aptF[2].x);
  rect.top = min(m_aptF[0].y, m_aptF[2].y);
  rect.bottom = max(m_aptF[0].y, m_aptF[2].y);
  
  if(m_shapeProper.fTransparent)
  {
    if(fabs(rect.left - x) < 2 || fabs(rect.right - x) < 2)
    {
      return y <= rect.bottom && y >= rect.top;
    }

    if(fabs(rect.bottom - y) < 2 || fabs(rect.top - y) < 2)
    {
      return x <= rect.right && x >= rect.left;
    }
  }
  else
  {
    return x >= rect.left && x <= rect.right
      && y >= rect.top && y <= rect.bottom;
  }
  

  return false;
}

bool GraphItemRectangle::isRectCrossShape(const RectF& rectf)
{
  RectF rect;
  rect.left = min(m_aptF[0].x, m_aptF[2].x);
  rect.right = max(m_aptF[0].x, m_aptF[2].x);
  rect.top = min(m_aptF[0].y, m_aptF[2].y);
  rect.bottom = max(m_aptF[0].y, m_aptF[2].y);
  bool ret = rectf.isRectIntersect(rect);

  return ret;
}

bool GraphItemRectangle::shapeResizeTo(const PointF &newPos, ControlHandler* handler)
{
  if(handler->getOwnerShape() != this) return false;
  int id = handler->getId();
  switch(id)
  {
  case 0:
    m_aptF[0] = newPos;
    m_aptF[1].x = m_aptF[0].x;
    m_aptF[3].y = m_aptF[0].y;
    break;
  case 1:
    m_aptF[0].x = newPos.x;
    m_aptF[1].x = newPos.x;
    break;
  case 2:
    m_aptF[1] = newPos;
    m_aptF[0].x = m_aptF[1].x;
    m_aptF[2].y = m_aptF[1].y;
    break;
  case 3:
    m_aptF[1].y = newPos.y;
    m_aptF[2].y = newPos.y;
    break;
  case 4:
    m_aptF[2] = newPos;
    m_aptF[3].x = m_aptF[2].x;
    m_aptF[1].y = m_aptF[2].y;
    break;
  case 5:
    m_aptF[2].x = newPos.x;
    m_aptF[3].x = newPos.x;
    break;
  case 6:
    m_aptF[3] = newPos;
    m_aptF[2].x = m_aptF[3].x;
    m_aptF[0].y = m_aptF[3].y;
    break;
  case 7:
    m_aptF[3].y = newPos.y;
    m_aptF[0].y = newPos.y;
    break;
  }

  updateCtrHandler();
  return true;
 }

void GraphItemRectangle::updateCtrHandler()
{
  for(int i = 0; i < 8; i++)
  {
    if(i % 2 == 0) m_ctrHandlers[i]->setPos(m_aptF[i / 2]);
    else
    {
      PointF posA = m_aptF[i / 2];
      PointF posB = m_aptF[(i / 2 + 1) % 4];
      m_ctrHandlers[i]->setPos({ (posA.x + posB.x) / 2,(posA.y + posB.y) / 2 });
    }
  }
}
