#include "GraphItemElliptic.h"

GraphItemElliptic::GraphItemElliptic(const PointF beginPos, const PointF endPos)
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
  Ellipse(hdc, left, top, right, bottom);
}

void GraphItemElliptic::move(double dx, double dy)
{
  for(int i = 0; i < m_aptF.size(); i++)
    m_aptF[i].x += dx, m_aptF[i].y += dy;

  updateHandlers();
}

bool GraphItemElliptic::isPointUpShape(const PointF& pos)
{
  return true;
}

bool GraphItemElliptic::isRectCrossShape(const RectF& rectf)
{
  return true;
}

bool GraphItemElliptic::shapeResize(double dx, double dy, ControlHandler* handler)
{

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