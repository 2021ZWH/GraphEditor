#include "GraphItemElliptic.h"

GraphItemElliptic::GraphItemElliptic(const PointF &beginPos, const PointF &endPos)
{
  m_aptF.resize(4);
  m_aptF[0] = { beginPos.x,endPos.y };
  m_aptF[1] = beginPos;
  m_aptF[2] = { endPos.x, beginPos.y };
  m_aptF[3] = endPos;

  m_ctrHandlers.resize(8);
  m_ctrHandlers[0] = new ControlHandler(this, HandlerType::HT_SW, 0);
  m_ctrHandlers[1] = new ControlHandler(this, HandlerType::HT_WEST, 1);
  m_ctrHandlers[2] = new ControlHandler(this, HandlerType::HT_NW, 2);
  m_ctrHandlers[3] = new ControlHandler(this, HandlerType::HT_NORTH, 3);
  m_ctrHandlers[4] = new ControlHandler(this, HandlerType::HT_NE, 4);
  m_ctrHandlers[5] = new ControlHandler(this, HandlerType::HT_EAST, 5);
  m_ctrHandlers[6] = new ControlHandler(this, HandlerType::HT_SE, 6);
  m_ctrHandlers[7] = new ControlHandler(this, HandlerType::HT_SOUTH, 7);

  updateHandlers();
}

GraphItemElliptic::~GraphItemElliptic()
{
  GraphItemShape::clearCtrHandler();
}

void GraphItemElliptic::drawShape(HDC hdc, double xoff, double yoff)
{
  int left = m_aptF[0].x - xoff;
  int right = m_aptF[3].x - xoff;
  int top = m_aptF[1].y - yoff;
  int bottom = m_aptF[3].y - yoff;

  HBRUSH hbru;
  if(m_fTransparent) hbru = (HBRUSH)GetStockObject(NULL_BRUSH);
  else hbru = CreateSolidBrush(m_fillColor);

  HPEN hpen = CreatePen(PS_SOLID, m_lineWidth, m_lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);
  HBRUSH oldBru = (HBRUSH)SelectObject(hdc, hbru);

  Ellipse(hdc, left, top, right, bottom);

  SelectObject(hdc, oldBru);
  SelectObject(hdc, hpen);

  if(!m_fTransparent) DeleteObject(hbru);
  DeleteObject(hpen);
}

void GraphItemElliptic::move(double dx, double dy)
{
  for(int i = 0; i < m_aptF.size(); i++)
    m_aptF[i].x += dx, m_aptF[i].y += dy;

  updateHandlers();
}

bool GraphItemElliptic::isPointUpShape(const PointF& pos)
{
  double a = fabs((m_aptF[3].x - m_aptF[0].x) / 2); // 长轴长
  double b = fabs((m_aptF[1].y - m_aptF[0].y) / 2); // 短轴长
  PointF p0;  // 中心点
  p0.x = (m_aptF[0].x + m_aptF[3].x) / 2;
  p0.y = (m_aptF[1].y + m_aptF[0].y) / 2;

  double val = pow(pos.x - p0.x, 2) / pow(a, 2) + pow(pos.y - p0.y,2) / pow(b, 2);
  if(fabs(val - 1) <= 0.05) return true;

  return false;
}

bool GraphItemElliptic::isRectCrossShape(const RectF& rectf)
{
  RectF rect = { m_aptF[1].x,m_aptF[1].y,m_aptF[3].x,m_aptF[3].y };

  if(!rect.isRectIntersect(rectf)) return false; // 判断包围盒相不相交

  return true;
}

bool GraphItemElliptic::shapeResize(double dx, double dy, ControlHandler* handler)
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
  
  updateHandlers();
  return true;
}

void GraphItemElliptic::updateHandlers()
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