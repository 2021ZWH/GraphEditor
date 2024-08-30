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
  for(int i = 0; i < m_selectShape.size(); i++)
    m_selectShape[i]->resetSelect();
  m_selectShape.clear();
}

void SelectShapeManager::setHandler(ControlHandler* handler)
{
  
  if(m_selectHandler)
    m_selectHandler->SetSelect(false);
  m_selectHandler = handler;

  if(handler) 
  m_selectHandler->SetSelect(true);
  
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
