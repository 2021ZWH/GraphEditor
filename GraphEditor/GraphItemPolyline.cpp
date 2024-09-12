#include "GraphItemPolyline.h"
#include <stdio.h>
#include <wchar.h>

GraphItemPolyline::GraphItemPolyline(const PointF &startPos)
{
  m_shapeType = SHAPE_POLYLINE;
  addPos(startPos);
}

GraphItemPolyline::~GraphItemPolyline()
{
  clearCtrHandler();
}

Vector<TCHAR> GraphItemPolyline::toText()
{
  Vector<TCHAR> vec = GraphItemShape::toText();

  TCHAR buffer[10000];
  _itow_s(m_linePos.size(), buffer, 10);
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  for(int i = 0; i < m_linePos.size(); i++)
  {
    swprintf(buffer, 10000, L"%f %f", m_linePos[i].x, m_linePos[i].y);
    for(int i = 0; i < lstrlen(buffer); i++)
      vec.push_back(buffer[i]);
    vec.push_back(' ');
  }

  return vec;
}

void GraphItemPolyline::drawShape(HDC hdc, double xoff, double yoff)
{
  HPEN hpen;
  if(m_shapeProper.lineWidth == 0) hpen = (HPEN)GetStockObject(NULL_PEN);
  else hpen = CreatePen(PS_SOLID, m_shapeProper.lineWidth, m_shapeProper.lineColor);
  HPEN oldPen = (HPEN)SelectObject(hdc, hpen);

  for(int i = 0; i < m_linePos.size() - 1; i++)
  {
    PointF startPos = m_linePos[i];
    PointF endPos = m_linePos[i + 1];
    startPos.x -= xoff;
    startPos.y -= yoff;
    endPos.x -= xoff;
    endPos.y -= yoff;
    drawSingleLine(hdc, startPos, endPos);
  }

  SelectObject(hdc, oldPen);
  if(m_shapeProper.lineWidth)
    DeleteObject(hpen);
}

void GraphItemPolyline::move(double dx, double dy)
{
  for(int i = 0; i < m_linePos.size(); i++)
  {
    m_linePos[i].x += dx;
    m_linePos[i].y += dy;
  }

  updateCtrHandler();
}

bool GraphItemPolyline::isPointUpShape(const PointF& pos)
{
  SegmentF seg;
  for(int i = 0; i < m_linePos.size() - 1; i++)
  {
    seg.posA = m_linePos[i];
    seg.posB = m_linePos[i + 1];
    if(seg.isPointIn(pos, 1000)) return true;
  }

  return false;
}

bool GraphItemPolyline::isRectCrossShape(const RectF& rectf)
{
  SegmentF seg;
  for(int i = 0; i < m_linePos.size() - 1; i++)
  {
    seg.posA = m_linePos[i];
    seg.posB = m_linePos[i + 1];
    if(rectf.isSegmentIntersect(seg)) return true;
  }
  return false;
}

bool GraphItemPolyline::shapeResizeTo(const PointF &newPos, ControlHandler* handler)
{
  if(handler->getOwnerShape() != this) return false;
  
  int id = handler->getId();
  m_linePos[id] = newPos;
  m_ctrHandlers[id]->setPos(m_linePos[id]);
  return true;
}

void GraphItemPolyline::updateCtrHandler()
{
  for(int i = 0; i < m_linePos.size(); i++)
  {
    m_ctrHandlers[i]->setPos(m_linePos[i]);
  }
}

void GraphItemPolyline::drawSingleLine(HDC hdc, PointF startPos, PointF endPos)
{
  POINT pos;
  MoveToEx(hdc, startPos.x, startPos.y, &pos);
  LineTo(hdc, endPos.x, endPos.y);
  MoveToEx(hdc, pos.x, pos.y, NULL);
}

void GraphItemPolyline::addPos(const PointF& pos)
{
  m_linePos.push_back(pos);
  int newId = m_ctrHandlers.size();
  ControlHandler* handler = new ControlHandler(this, HT_ALL, newId);
  handler->setPos(pos);
  m_ctrHandlers.push_back(handler);
}
