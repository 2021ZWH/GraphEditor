#include "ToolManager.h"

ToolManager::ToolManager()
{

}

ToolManager::~ToolManager()
{
  
}

void ToolManager::setToolType(ToolType newType)
{
  m_nowType = newType;
}

ToolType ToolManager::getToolType() const
{
  return m_nowType;
}