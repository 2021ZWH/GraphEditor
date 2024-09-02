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
  for(int i = 0; i + 3 < m_aptf.size(); i += 3)
  {
    if(isPointInLine(pos, i)) return true;
  }
  return false;
}

bool GraphItemPolyBezier::isRectCrossShape(const RectF& rectf)
{
  for(int i = 0; i < m_aptf.size(); i+=3)
  {
    if(rectf.isPointIn(m_aptf[i]))
      return true;
  }

  for(int i = 0; i+3 < m_aptf.size(); i += 3)
  {
    if(isRectInLine(rectf,i))
      return true;
  }

  return  false;
}

bool GraphItemPolyBezier::shapeResize(double dx, double dy, ControlHandler* handler)
{
  int id = handler->getId();
  if(handler->getOwnerShape() != this) return false;

  if(id % 3 == 0) // 说明移动的是端点
  {
    m_aptf[id].x += dx;
    m_aptf[id].y += dy;
    m_ctrHandlers[id]->setPos(m_aptf[id]);
    if(id - 1 >= 0)
    {
      m_aptf[id - 1].x += dx;
      m_aptf[id - 1].y += dy;
      m_ctrHandlers[id - 1]->setPos(m_aptf[id - 1]);
    }
    if(id + 1 < m_aptf.size())
    {
      m_aptf[id + 1].x += dx;
      m_aptf[id + 1].y += dy;
      m_ctrHandlers[id + 1]->setPos(m_aptf[id + 1]);
    }
  }
  else // 移动控制点
  {
    m_aptf[id].x += dx;
    m_aptf[id].y += dy;
    m_ctrHandlers[id]->setPos(m_aptf[id]);
  }
  return true;
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

    HPEN blueDashPen = CreatePen(PS_DASH, 1, RGB(0, 0, 255));
    HPEN oldPen = (HPEN)SelectObject(hdc, blueDashPen);

    if(id - 1 >= 0)
    {
      m_ctrHandlers[id - 1]->draw(hdc, xoff, yoff, 12 * scale);
      PointF posA = m_aptf[id - 1];
      PointF posB = m_aptf[id];
      posA.x -= xoff, posA.y -= yoff;
      posB.x -= xoff, posB.y -= yoff;
      
      MoveToEx(hdc, posA.x, posA.y, NULL);
      LineTo(hdc, posB.x, posB.y);
    }

    if(id + 1 < m_ctrHandlers.size())
    {
      m_ctrHandlers[id + 1]->draw(hdc, xoff, yoff, 12 * scale);
      PointF posA = m_aptf[id + 1];
      PointF posB = m_aptf[id];
      posA.x -= xoff, posA.y -= yoff;
      posB.x -= xoff, posB.y -= yoff;

      MoveToEx(hdc, posA.x, posA.y, NULL);
      LineTo(hdc, posB.x, posB.y);
    }

    SelectObject(hdc, oldPen);
    DeleteObject(blueDashPen);
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

bool GraphItemPolyBezier::isPointInLine(const PointF &pos,int id)
{
  PointF p0 = m_aptf[id];
  PointF p1 = m_aptf[id + 1];
  PointF p2 = m_aptf[id + 2];
  PointF p3 = m_aptf[id + 3];

  PointF b;

  for(int i = 0; i <= 100; i++) // 将每段曲线分成100个点，判断点是否在附近
  {
    double t = 1.0 / 100 * i;
    b.x = pow(1 - t, 3.0) * p0.x + 3 * t * pow(1 - t, 2.0) * p1.x + 3 * pow(t, 2) * (1 - t) * p2.x + pow(t, 3) * p3.x;
    b.y = pow(1 - t, 3.0) * p0.y + 3 * t * pow(1 - t, 2.0) * p1.y + 3 * pow(t, 2) * (1 - t) * p2.y + pow(t, 3) * p3.y;
    
    if(pow(pos.x - b.x,2) + pow(pos.y - b.y, 2) < 4) return true;
  }

  return false;
}

bool GraphItemPolyBezier::isRectInLine(const RectF& rect, int id)
{
  PointF p0 = m_aptf[id];
  PointF p1 = m_aptf[id + 1];
  PointF p2 = m_aptf[id + 2];
  PointF p3 = m_aptf[id + 3];

  PointF b;
  bool status[4][2];
  memset(status, 0, sizeof status);
  for(int i = 0; i <= 100; i++) // 将每段曲线分成100个点，判断点是否在附近
  {
    double t = 1.0 / 100 * i;
    b.x = pow(1 - t, 3.0) * p0.x + 3 * t * pow(1 - t, 2.0) * p1.x + 3 * pow(t, 2) * (1 - t) * p2.x + pow(t, 3) * p3.x;
    b.y = pow(1 - t, 3.0) * p0.y + 3 * t * pow(1 - t, 2.0) * p1.y + 3 * pow(t, 2) * (1 - t) * p2.y + pow(t, 3) * p3.y;
    
    if(b.x < rect.left) status[0][0] = true;
    else if(b.x > rect.left) status[0][1] = true;

    if(b.y < rect.top) status[1][0] = true;
    else if(b.y > rect.top) status[1][1] = true;

    if(b.x < rect.right) status[2][0] = true;
    else if(b.x > rect.right) status[2][1] = true;

    if(b.y < rect.bottom) status[3][0] = true;
    else if(b.y > rect.bottom) status[3][1] = true;
    
    for(int i = 0; i < 4; i++)
      if(status[i][0] && status[i][1]) return true;
  }
  return false;
}