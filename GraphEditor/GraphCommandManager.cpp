#include "GraphCommandManager.h"

GraphCommandManager::GraphCommandManager()
{

}

GraphCommandManager::~GraphCommandManager()
{
  clear();
}

void GraphCommandManager::addCommand(GraphCommand *cmd)
{
  clearRedoCmd();
  m_undoCmd.push(cmd);
}

bool GraphCommandManager::canUndo()
{
  return m_undoCmd.size() != 0;
}

bool GraphCommandManager::canRedo()
{
  return m_redoCmd.size() != 0;
}

void GraphCommandManager::undo()
{
  if(!canUndo()) return;
  GraphCommand* cmd = m_undoCmd.top();
  m_undoCmd.pop();
  cmd->undo();
  m_redoCmd.push(cmd);
}

void GraphCommandManager::redo()
{
  if(!canRedo()) return;
  GraphCommand* cmd = m_redoCmd.top();
  m_redoCmd.pop();
  cmd->redo();
  m_undoCmd.push(cmd);

}

void GraphCommandManager::clear()
{
  clearUndoCmd();
  clearRedoCmd();
}

void GraphCommandManager::clearUndoCmd()
{
  while(m_undoCmd.size())
  {
    GraphCommand* cmd = m_undoCmd.top();
    m_undoCmd.pop();
    delete cmd;
  }
}

void GraphCommandManager::clearRedoCmd()
{
  while(m_redoCmd.size())
  {
    GraphCommand* cmd = m_redoCmd.top();
    m_redoCmd.pop();
    delete cmd;
  }
}

