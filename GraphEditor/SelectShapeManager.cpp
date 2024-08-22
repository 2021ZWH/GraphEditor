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

Vector<GraphItemShape*>& SelectShapeManager::getSelect()
{
  return this->m_selectShape;
}