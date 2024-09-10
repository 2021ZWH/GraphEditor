#include "GraphItemShape.h"

GraphItemShape::~GraphItemShape()
{
  clearCtrHandler();
}

Vector<TCHAR> GraphItemShape::toText()
{
  Vector<TCHAR> vec;
  vec.push_back(m_shapeType + '0'); // 图形类型
  vec.push_back(' ');

  TCHAR buffer[100];
  memset(buffer, 0, sizeof buffer);

  _itow_s(m_lineWidth, buffer, 10); // 线宽
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  _itow_s(m_lineColor, buffer, 10); // 线色
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  _itow_s(m_fillColor, buffer, 10); // 填充色
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  _itow_s(m_fTransparent, buffer, 10); // 是否透明
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  return vec;
}

void GraphItemShape::drawHandler(HDC hdc, double xoff, double yoff, double scale)
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    m_ctrHandlers[i]->draw(hdc, xoff, yoff, 12*scale);
  }
}

ControlHandler* GraphItemShape::getHandlerByPos(const PointF& pos)
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    if(m_ctrHandlers[i]->isPointInHandler(pos))
      return m_ctrHandlers[i];
  }

  return nullptr;
}

void GraphItemShape::clearCtrHandler()
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    delete m_ctrHandlers[i];
    m_ctrHandlers[i] = nullptr;
  }
}

void GraphItemShape::addPos(const PointF& pos)
{

}

void GraphItemShape::SetSelectHandler(ControlHandler *handler)
{
  m_selectHandler = handler;

}

void GraphItemShape::resetSelect()
{
  m_selectHandler = nullptr;
}

void GraphItemShape::setLineWidth(UINT width)
{
  if(width >= 1) m_lineWidth = width;
}

void GraphItemShape::setLineColor(COLORREF color)
{
  m_lineColor = color;
}

void GraphItemShape::setFillColor(COLORREF color)
{
  m_fillColor = color;
}

void GraphItemShape::setTransParent(bool flag)
{
  m_fTransparent = flag;
}

UINT GraphItemShape::getLineWidth() const
{
  return m_lineWidth;
}

COLORREF GraphItemShape::getLineColor() const
{
  return m_lineColor;
}

COLORREF GraphItemShape::getFillColor() const
{
  return m_fillColor;
}

bool GraphItemShape::isVisible() const
{
  return m_fVisible;
}

void GraphItemShape::setVisible(bool flag)
{
  m_fVisible = flag;
}