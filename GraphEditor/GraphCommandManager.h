#ifndef GRAPH_COMMAND_MANAGER_H
#define GRAPH_COMMAND_MANAGER_H

#include "GraphCommand.h"
#include "Stack.h"

class GraphCommandManager
{
public:
  GraphCommandManager();
  ~GraphCommandManager();
  void addCommand(GraphCommand *cmd);
  bool canUndo();
  bool canRedo();
  void undo();
  void redo();
  void clear();
private:
  void clearUndoCmd();
  void clearRedoCmd();
private:
  Stack<GraphCommand*> m_undoCmd;
  Stack<GraphCommand*> m_redoCmd;
};

#endif // GRAPH_COMMAND_MANAGER_H

