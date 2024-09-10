#include "GraphItemElliptic.h"
#include <stdio.h>
#include <wchar.h>

GraphItemElliptic::GraphItemElliptic(const PointF &beginPos, const PointF &endPos)
{
  m_shapeType = SHAPE_ELLIPTIC;

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

Vector<TCHAR> GraphItemElliptic::toText()
{
  Vector<TCHAR> vec = GraphItemShape::toText();

  TCHAR buffer[100];
  _itow_s(m_aptF.size(), buffer, 10);
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  for(int i = 0; i < m_aptF.size(); i++)
  {
    swprintf(buffer, 100, L"%f %f", m_aptF[i].x, m_aptF[i].y);
    for(int i = 0; i < lstrlen(buffer); i++)
      vec.push_back(buffer[i]);
    vec.push_back(' ');
  }

  return vec;
}

void GraphItemElliptic::drawShape(HDC hdc, double xoff, double yoff)
{
  int left = min(m_aptF[0].x, m_aptF[2].x) - xoff;
  int right = max(m_aptF[0].x, m_aptF[2].x) - xoff;
  int top = min(m_aptF[0].y, m_aptF[2].y) - yoff;
  int bottom = max(m_aptF[0].y, m_aptF[2].y) - yoff;

  HBRUSH hbru;
  if(m_fTransparent) hbru = (HBRUSH)GetStockObject(NULL_BRUSH);
  else hbru = CreateSolidBrush(m_fillColor);

  HPEN hpen = CreatePen(PS_SOLID, m_lineWidth, m_lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);
  HBRUSH oldBru = (HBRUSH)SelectObject(hdc, hbru);

  Ellipse(hdc, left, top, right, bottom);

  SelectObject(hdc, oldBru);
  SelectObject(hdc, hpen);

  if(!m_fTransparent) DeleteObject(hbru);
  DeleteObject(hpen);
}

void GraphItemElliptic::move(double dx, double dy)
{
  for(int i = 0; i < m_aptF.size(); i++)
    m_aptF[i].x += dx, m_aptF[i].y += dy;

  updateHandlers();
}

bool GraphItemElliptic::isPointUpShape(const PointF& pos)
{
  double width = max(m_aptF[0].x, m_aptF[2].x) - min(m_aptF[0].x, m_aptF[2].x);
  double height = max(m_aptF[0].y, m_aptF[2].y) - min(m_aptF[0].y, m_aptF[2].y);
  double a = width / 2; // 长轴长
  double b = height / 2; // 短轴长
  PointF p0;  // 中心点
  p0.x = (m_aptF[0].x + m_aptF[2].x) / 2;
  p0.y = (m_aptF[0].y + m_aptF[2].y) / 2;

  double val = pow(pos.x - p0.x, 2) / pow(a, 2) + pow(pos.y - p0.y,2) / pow(b, 2);
  if(fabs(val - 1) <= 0.05) return true;

  return false;
}

bool GraphItemElliptic::isRectCrossShape(const RectF& rectf)
{
  RectF rect;
  rect.left = min(m_aptF[0].x, m_aptF[2].x);
  rect.right = max(m_aptF[0].x, m_aptF[2].x);
  rect.top = min(m_aptF[0].y, m_aptF[2].y);
  rect.bottom = max(m_aptF[0].y, m_aptF[2].y);

  if(!rect.isRectIntersect(rectf)) return false; // 判断包围盒相不相交

  return true;
}

bool GraphItemElliptic::shapeResizeTo(const PointF &newPos, ControlHandler* handler)
{
  if(handler->getOwnerShape() != this) return false;
  int id = handler->getId();
  switch(id)
  {
  case 0:
    m_aptF[0] = newPos;
    m_aptF[1].x = m_aptF[0].x;
    m_aptF[3].y = m_aptF[0].y;
    break;
  case 1:
    m_aptF[0].x = newPos.x;
    m_aptF[1].x = newPos.x;
    break;
  case 2:
    m_aptF[1] = newPos;
    m_aptF[0].x = m_aptF[1].x;
    m_aptF[2].y = m_aptF[1].y;
    break;
  case 3:
    m_aptF[1].y = newPos.y;
    m_aptF[2].y = newPos.y;
    break;
  case 4:
    m_aptF[2] = newPos;
    m_aptF[3].x = m_aptF[2].x;
    m_aptF[1].y = m_aptF[2].y;
    break;
  case 5:
    m_aptF[2].x = newPos.x;
    m_aptF[3].x = newPos.x;
    break;
  case 6:
    m_aptF[3] = newPos;
    m_aptF[2].x = m_aptF[3].x;
    m_aptF[0].y = m_aptF[3].y;
    break;
  case 7:
    m_aptF[3].y = newPos.y;
    m_aptF[0].y = newPos.y;
    break;
  }
  
  updateHandlers();
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