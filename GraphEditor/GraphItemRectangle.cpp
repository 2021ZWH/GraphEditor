#include "GraphItemRectangle.h"

GraphItemRectangle::GraphItemRectangle()
{

}
GraphItemRectangle::~GraphItemRectangle()
{

}

void GraphItemRectangle::draw(HDC hdc,int xoff, int yoff)
{
  int left = m_rect.left - xoff;
  int right = m_rect.right - xoff;
  int top = m_rect.top - yoff;
  int bottom = m_rect.bottom - yoff;
  
  Rectangle(hdc,left, top, right, bottom);
}

bool GraphItemRectangle::isPointUpShape(const POINT& pos)
{
  int x = pos.x;
  int y = pos.y;

  if(x == m_rect.left || x == m_rect.right)
  {
    return y <= m_rect.bottom && y >= m_rect.top;
  }

  if(y == m_rect.top || y == m_rect.bottom)
  {
    return x <= m_rect.right && x >= m_rect.left;
  }

  return false;
}

bool GraphItemRectangle::isRectCrossShape(const RECT& rect)
{
  int w1 = rect.right - m_rect.left;
  int h1 = m_rect.bottom - m_rect.top;
  int w2 = rect.right - rect.left;
  int h2 = rect.bottom - rect.top;
  int w = abs((m_rect.left + m_rect.right) / 2 - (rect.left + rect.right) / 2);
  int h = abs((m_rect.top + m_rect.bottom) / 2 - (rect.top + rect.bottom) / 2);

  if(w < (w1 + w2) / 2 && h < (h1 + h2) / 2)
    return true;
  else
    return false;
}