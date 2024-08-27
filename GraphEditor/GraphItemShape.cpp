#include "GraphItemShape.h"

GraphItemShape::~GraphItemShape()
{
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    delete m_ctrHandlers[i];
    m_ctrHandlers[i] = nullptr;
  }
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