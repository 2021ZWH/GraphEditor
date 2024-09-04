#include "GraphItemRectangle.h"

GraphItemRectangle::GraphItemRectangle(PointF beginPos, PointF endPos)
{
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

void GraphItemRectangle::drawShape(HDC hdc,double xoff, double yoff)
{
  RectF rect;
  rect.left = min(m_aptF[0].x, m_aptF[2].x) - xoff;
  rect.right = max(m_aptF[0].x, m_aptF[2].x) - xoff;
  rect.top = min(m_aptF[0].y, m_aptF[2].y) - yoff;
  rect.bottom = max(m_aptF[0].y, m_aptF[2].y) - yoff;
  
  HBRUSH hbru;
  if(m_fTransparent) hbru = (HBRUSH)GetStockObject(NULL_BRUSH);
  else hbru = CreateSolidBrush(m_fillColor);

  HPEN hpen = CreatePen(PS_SOLID, m_lineWidth, m_lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);
  HBRUSH oldBru = (HBRUSH)SelectObject(hdc, hbru);

  Rectangle(hdc,rect.left, rect.top, rect.right, rect.bottom);
  
  SelectObject(hdc, oldBru);
  SelectObject(hdc, hpen);

  if(!m_fTransparent) DeleteObject(hbru);
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
  
  if(fabs(rect.left - x) < 2 || fabs(rect.right - x) < 2)
  {
    return y <= rect.bottom && y >= rect.top;
  }

  if(fabs(rect.bottom - y) < 2 || fabs(rect.top - y) < 2)
  {
    return x <= rect.right && x >= rect.left;
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

bool GraphItemRectangle::shapeResize(double dx,double dy, ControlHandler* handler)
{
  if(handler->getOwnerShape() != this) return false;
  int id = handler->getId();
  switch(id)
  {
  case 0:
    m_aptF[0].x += dx;
    m_aptF[0].y += dy;
    m_aptF[1].x += dx;
    m_aptF[3].y += dy;
    break;
  case 1:
    m_aptF[0].x += dx;
    m_aptF[1].x += dx;
    break;
  case 2:
    m_aptF[1].x += dx;
    m_aptF[1].y += dy;
    m_aptF[0].x += dx;
    m_aptF[2].y += dy;
    break;
  case 3:
    m_aptF[1].y += dy;
    m_aptF[2].y += dy;
    break;
  case 4:
    m_aptF[2].x += dx;
    m_aptF[2].y += dy;
    m_aptF[1].y += dy;
    m_aptF[3].x += dx;
    break;
  case 5:
    m_aptF[2].x += dx;
    m_aptF[3].x += dx;
    break;
  case 6:
    m_aptF[3].x += dx;
    m_aptF[3].y += dy;
    m_aptF[2].x += dx;
    m_aptF[0].y += dy;
    break;
  case 7:
    m_aptF[0].y += dy;
    m_aptF[3].y += dy;
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
