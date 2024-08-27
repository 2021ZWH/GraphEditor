#include "GraphItemRectangle.h"

GraphItemRectangle::GraphItemRectangle(PointF beginPos, PointF endPos)
{
  m_rectf.left = beginPos.x;
  m_rectf.top = beginPos.y;
  m_rectf.right = endPos.x;
  m_rectf.bottom = endPos.y;
  m_ctrHandlers.resize(8);
  m_ctrHandlers[0] = new ControlHandler(this,HandlerType::HT_WEST, 0);
  m_ctrHandlers[1] = new ControlHandler(this,HandlerType::HT_NW,1);
  m_ctrHandlers[2] = new ControlHandler(this,HandlerType::HT_NORTH, 2);
  m_ctrHandlers[3] = new ControlHandler(this,HandlerType::HT_NE, 3);
  m_ctrHandlers[4] = new ControlHandler(this,HandlerType::HT_EAST, 4);
  m_ctrHandlers[5] = new ControlHandler(this,HandlerType::HT_SE, 5);
  m_ctrHandlers[6] = new ControlHandler(this,HandlerType::HT_SOUTH, 6);
  m_ctrHandlers[7] = new ControlHandler(this,HandlerType::HT_SW ,7);

  updateCtrHandler();

}

GraphItemRectangle::~GraphItemRectangle()
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    delete m_ctrHandlers[i];
    m_ctrHandlers[i] = nullptr;
  }

}

void GraphItemRectangle::drawShape(HDC hdc,double xoff, double yoff)
{
  int left = m_rectf.left - xoff;
  int right = m_rectf.right - xoff;
  int top = m_rectf.top - yoff;
  int bottom = m_rectf.bottom - yoff;
  
  HBRUSH hbru = (HBRUSH)GetStockObject(NULL_BRUSH);
  HBRUSH hOldBru = (HBRUSH)SelectObject(hdc, hbru);
  Rectangle(hdc,left, top, right, bottom);
  SelectObject(hdc, hOldBru);
}

void GraphItemRectangle::move(double dx, double dy)
{
  m_rectf.left += dx;
  m_rectf.right += dx;
  m_rectf.top += dy;
  m_rectf.bottom += dy;

  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    m_ctrHandlers[i]->move(dx, dy);
  }
}

bool GraphItemRectangle::isPointUpShape(const PointF& pos)
{
  double x = pos.x;
  double y = pos.y;

  
  if(fabs(m_rectf.left - x) < 2 || fabs(m_rectf.right - x) < 2)
  {
    return y <= m_rectf.bottom && y >= m_rectf.top;
  }

  if(fabs(m_rectf.bottom - y) < 2 || fabs(m_rectf.top - y) < 2)
  {
    return x <= m_rectf.right && x >= m_rectf.left;
  }

  return false;
}

bool GraphItemRectangle::isRectCrossShape(const RectF& rectf)
{
  double w1 = rectf.right - m_rectf.left;
  double h1 = m_rectf.bottom - m_rectf.top;
  double w2 = rectf.right - rectf.left;
  double h2 = rectf.bottom - rectf.top;
  double w = fabs((m_rectf.left + m_rectf.right) / 2 - (rectf.left + rectf.right) / 2);
  double h = fabs((m_rectf.top + m_rectf.bottom) / 2 - (rectf.top + rectf.bottom) / 2);

  if(w < (w1 + w2) / 2 && h < (h1 + h2) / 2)
    return true;

  return false;
}

bool GraphItemRectangle::shapeResize(double dx,double dy, ControlHandler* handler)
{
  int id = handler->getId();
  if(m_ctrHandlers.size() <= id || id < 0) return false;
  if(m_ctrHandlers[id] != handler) return false;

  switch(id)
  {
    case 0: // 左边
    {
      m_rectf.left += dx;
      break;
    }
    case 1: // 左上角点
    {
      m_rectf.left += dx;
      m_rectf.top += dy;
      break;
    }
    case 2: // 上边
    {
      m_rectf.top += dy;
      break;
    }
    case 3: // 右上角点
    {
      m_rectf.right += dx;
      m_rectf.top += dy;
      break;
    }
    case 4: // 右边
    {
      m_rectf.right += dx;
      break;
    }
    case 5: // 右下角点
    {
      m_rectf.right += dx;
      m_rectf.bottom += dy;
      break;
    }
    case 6: // 下边
    {
      m_rectf.bottom += dy;
      break;
    }
    case 7: // 左下角点
    {
      m_rectf.left += dx;
      m_rectf.bottom += dy;
      break;
    }
  }
  updateCtrHandler();
  return true;
 }

void GraphItemRectangle::updateCtrHandler()
{
  PointF beginPos = { m_rectf.left,m_rectf.top };
  PointF endPos = { m_rectf.right,m_rectf.bottom };

  m_ctrHandlers[0]->setPos({ beginPos.x,(endPos.y + beginPos.y) / 2 });
  m_ctrHandlers[1]->setPos(beginPos);
  m_ctrHandlers[2]->setPos({ (endPos.x + beginPos.x) / 2,beginPos.y });
  m_ctrHandlers[3]->setPos({ endPos.x,beginPos.y });
  m_ctrHandlers[4]->setPos({ endPos.x,(endPos.y + beginPos.y) / 2 });
  m_ctrHandlers[5]->setPos(endPos);
  m_ctrHandlers[6]->setPos({ (endPos.x + beginPos.x) / 2,endPos.y });
  m_ctrHandlers[7]->setPos({ beginPos.x,endPos.y });

}
