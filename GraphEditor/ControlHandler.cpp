#include "ControlHandler.h"

ControlHandler::ControlHandler(GraphItemShape *owner,HandlerType type,int id)
  :m_ownerShape(owner),m_type(type),m_id(id)
{
  switch(type)
  {
  case HT_WEST:
    m_hCursor = LoadCursor(NULL, IDC_SIZEWE);
    break;
  case HT_NW:
    m_hCursor = LoadCursor(NULL, IDC_SIZENWSE);
    break;
  case HT_NORTH:
    m_hCursor = LoadCursor(NULL, IDC_SIZENS);
    break;
  case HT_NE:
    m_hCursor = LoadCursor(NULL, IDC_SIZENESW);
    break;
  case HT_EAST:
    m_hCursor = LoadCursor(NULL, IDC_SIZEWE);
    break;
  case HT_SE:
    m_hCursor = LoadCursor(NULL, IDC_SIZENWSE);
    break;
  case HT_SOUTH:
    m_hCursor = LoadCursor(NULL, IDC_SIZENS);
    break;
  case HT_SW:
    m_hCursor = LoadCursor(NULL, IDC_SIZENESW);
    break;
  case HT_ALL:
    m_hCursor = LoadCursor(NULL, IDC_SIZEALL);
    break;
  }
}

void ControlHandler::draw(HDC hdc,double xoff,double yoff,double w)
{
  double x = m_ctrPos.x - xoff;
  double y = m_ctrPos.y - yoff;
  HBRUSH hbru = (HBRUSH)GetStockObject(BLACK_BRUSH);
  HBRUSH hOldBru = (HBRUSH)SelectObject(hdc, hbru);
  HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
  HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
  
  Rectangle(hdc, x - w / 2, y - w / 2, x + w / 2, y + w / 2);

  SelectObject(hdc, hOldBru);
  SelectObject(hdc, hOldPen);
}

void ControlHandler::move(double dx, double dy)
{
  m_ctrPos.x += dx;
  m_ctrPos.y += dy;
}

bool ControlHandler::isPointInHandler(const PointF& pos)
{
  if(pos.x > m_ctrPos.x + m_width / 2 || pos.x < m_ctrPos.x - m_width / 2)
    return false;

  if(pos.y > m_ctrPos.y + m_width / 2 || pos.y < m_ctrPos.y - m_width / 2)
    return false;

  return true;
}

void ControlHandler::setPos(const PointF& pos)
{
  m_ctrPos = pos;
}

int ControlHandler::getId() const
{
  return this->m_id;
}

void ControlHandler::SetSelect(bool fSelect)
{
  m_fSelect = fSelect;
}

bool ControlHandler::isSelect() const
{
  return m_fSelect;
}

HCURSOR ControlHandler::getCursor()
{
  return m_hCursor;
}

HandlerType ControlHandler::getHandlerType()const
{
  return this->getHandlerType();
}

GraphItemShape* ControlHandler::getOwnerShape()
{
  return m_ownerShape;
}

