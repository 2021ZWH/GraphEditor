#include "GraphItemPolyBezier.h"

GraphItemPolyBezier::GraphItemPolyBezier(const PointF& m_startPos)
{
  addPos(m_startPos);
}

GraphItemPolyBezier::~GraphItemPolyBezier()
{
  GraphItemShape::clearCtrHandler();
}

void GraphItemPolyBezier::drawShape(HDC hdc, double xoff, double yoff)
{
  if(m_aptf.size() < 4) return;

  POINT *apt = new POINT[m_aptf.size()];
  if(apt == nullptr) return;

  for(int i = 0; i < m_aptf.size(); i++)
  {
    apt[i].x = (m_aptf[i].x - xoff + 0.5);
    apt[i].y = (m_aptf[i].y - yoff + 0.5);
  }

  PolyBezier(hdc, apt, m_aptf.size());

  delete[] apt;
}

void GraphItemPolyBezier::move(double dx, double dy)
{
  for(int i = 0; i < m_aptf.size(); i++)
  {
    m_aptf[i].x += dx;
    m_aptf[i].y += dy;
    m_ctrHandlers[i]->setPos(m_aptf[i]);
  }
}

bool GraphItemPolyBezier::isPointUpShape(const PointF& pos)
{
  return true;
}

bool GraphItemPolyBezier::isRectCrossShape(const RectF& rectf)
{
  return  true;
}

bool GraphItemPolyBezier::shapeResize(double dx, double dy, ControlHandler* handler)
{
  return false;
}

void GraphItemPolyBezier::addPos(const PointF& pos)
{
  // id 0,3,6,9 ... 为端点.
  int nowId = m_aptf.size();
  m_aptf.push_back(pos);

  ControlHandler* handler = new ControlHandler(this, HT_ALL, nowId);
  handler->setPos(pos);
  m_ctrHandlers.push_back(handler);
}

void GraphItemPolyBezier::drawHandler(HDC hdc, double xoff, double yoff, double scale)
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    if(i % 3 == 0) //端点控制点都要绘制
      m_ctrHandlers[i]->draw(hdc, xoff, yoff, 12 * scale);
  }

  if(m_selectHandler) // 若有选中的控制点
  {
    int id = m_selectHandler->getId();
    if(id % 3 == 1) id--;
    else if(id % 3 == 2) id++; // 转换为端点id

    if(id - 1 >= 0)
    {
      m_ctrHandlers[id - 1]->draw(hdc, xoff, yoff, 12 * scale);
      PointF posA = m_aptf[id - 1];
      PointF posB = m_aptf[id];
      posA.x -= xoff, posA.y -= yoff;
      posB.x -= xoff, posB.y -= yoff;
      HPEN blueDashPen = CreatePen(PS_DASH, 1, BGR_LIGHTBLUE);
      HPEN oldPen = (HPEN)SelectObject(hdc, blueDashPen);
      MoveToEx(hdc, posA.x, posB.y, NULL);
      LineTo(hdc, posB.x, posB.y);
      SelectObject(hdc, oldPen);
      DeleteObject(blueDashPen);

    }
    if(id + 1 < m_ctrHandlers.size())
    {
      m_ctrHandlers[id + 1]->draw(hdc, xoff, yoff, 12 * scale);
      PointF posA = m_aptf[id + 1];
      PointF posB = m_aptf[id];
      posA.x -= xoff, posA.y -= yoff;
      posB.x -= xoff, posB.y -= yoff;
      HPEN blueDashPen = CreatePen(PS_DASH, 1, BGR_LIGHTBLUE);
      HPEN oldPen = (HPEN)SelectObject(hdc, blueDashPen);
      MoveToEx(hdc, posA.x, posB.y, NULL);
      LineTo(hdc, posB.x, posB.y);
      SelectObject(hdc, oldPen);
      DeleteObject(blueDashPen);
    }

  }
}

ControlHandler* GraphItemPolyBezier::getHandlerByPos(const PointF& pos)
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    if(m_ctrHandlers[i]->isPointInHandler(pos)) 
      return m_ctrHandlers[i];
  }

  if(m_selectHandler)
  {
    int id = m_selectHandler->getId();
    if(id % 3 == 1) id--;
    else if(id % 3 == 2) id++; // 转换为端点id
    if(id - 1 >= 0)
    {
      if(m_ctrHandlers[id - 1]->isPointInHandler(pos))
        return m_ctrHandlers[id - 1];
    }
    if(id + 1 < m_ctrHandlers.size())
    {
      if(m_ctrHandlers[id + 1]->isPointInHandler(pos))
        return m_ctrHandlers[id + 1];
    }
  }
  return nullptr;
}