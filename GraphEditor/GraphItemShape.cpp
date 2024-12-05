#include "GraphItemShape.h"

GraphItemShape::GraphItemShape()
  :m_xForm({ 1,0,0,1,0,0 }),m_shapeType(SHAPE_UNKNOWN)
{

}

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
  
  _itow_s(m_shapeProper.lineWidth, buffer, 10); // 线宽
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  _itow_s(m_shapeProper.lineColor, buffer, 10); // 线色
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  _itow_s(m_shapeProper.fillColor, buffer, 10); // 填充色
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  _itow_s(m_shapeProper.fTransparent, buffer, 10); // 是否透明
  for(int i = 0; i < lstrlen(buffer); i++)
    vec.push_back(buffer[i]);
  vec.push_back(' ');

  return vec;
}

void GraphItemShape::drawHandler(HDC hdc)
{
  XFORM oldXform;
  GetWorldTransform(hdc, &oldXform);
  ModifyWorldTransform(hdc, &m_xForm, MWT_RIGHTMULTIPLY);
  for(int i = 0; i < m_ctrHandlers.size(); i++)
  {
    m_ctrHandlers[i]->draw(hdc);
  }

  SetWorldTransform(hdc,&oldXform);
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

void GraphItemShape::setProperty(const ShapeProperty& property)
{
  m_shapeProper = property;
}

ShapeProperty GraphItemShape::getProperty() const
{
  return m_shapeProper;
}

bool GraphItemShape::isVisible() const
{
  return m_fVisible;
}

void GraphItemShape::setVisible(bool flag)
{
  m_fVisible = flag;
}