#include "SelectShapeManager.h"


bool SelectShapeManager::isSelect() const
{
  return m_selectShape.size() > 0;
}

void SelectShapeManager::addShape(GraphItemShape* pItemShape)
{
  m_selectShape.push_back(pItemShape);
}

void SelectShapeManager::clearSelect()
{
  m_selectShape.clear();
}

void SelectShapeManager::setHandler(ControlHandler* handler)
{
  m_selectHandler = handler;
}

Vector<GraphItemShape*>& SelectShapeManager::getShape()
{
  return this->m_selectShape;
}

ControlHandler* SelectShapeManager::getHandler()
{
  return m_selectHandler;
}

PointF SelectShapeManager::getBeginPos() const
{
  return m_beginPos;
}
