#include "GraphItemRectangle.h"

GraphItemRectangle::GraphItemRectangle(const RECT& rect)
  :m_rect(rect)
{

}

GraphItemRectangle::GraphItemRectangle(const POINT& pos, int w, int h)
{
  m_rect.left = pos.x;
  m_rect.right = pos.x + w;
  m_rect.top = pos.y;
  m_rect.bottom = pos.y + h;

}

GraphItemRectangle::GraphItemRectangle(const POINT& startPos, const POINT& endPos)
{
  m_rect.left = startPos.x;
  m_rect.right = endPos.x;
  m_rect.top = startPos.y;
  m_rect.bottom = endPos.y;

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
  
  HBRUSH hbru = (HBRUSH)GetStockObject(NULL_BRUSH);
  HBRUSH hOldBru = (HBRUSH)SelectObject(hdc, hbru);
  Rectangle(hdc,left, top, right, bottom);
  SelectObject(hdc, hOldBru);
}

void GraphItemRectangle::move(int dx, int dy)
{
  m_rect.left += dx;
  m_rect.right += dx;
  m_rect.top += dy;
  m_rect.bottom += dy;
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