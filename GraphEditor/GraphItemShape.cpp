#include "GraphItemShape.h"

GraphItemShape::~GraphItemShape()
{
  clearCtrHandler();
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