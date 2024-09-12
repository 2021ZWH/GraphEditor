#include "GraphCommand.h"

// GraphAddCommand 
GraphAddCommand::GraphAddCommand(GraphItemShape* shape, SelectShapeManager* selectMger)
  :m_pSelectMger(selectMger)
{
  m_shapeVec.push_back(shape);
}

GraphAddCommand::GraphAddCommand(const Vector<GraphItemShape*>& shapeVec, SelectShapeManager* selectMger)
  :m_pSelectMger(selectMger)
{
  m_shapeVec.resize(shapeVec.size());
  for(int i = 0; i < shapeVec.size(); i++)
  {
    m_shapeVec[i] = shapeVec[i];
  }
}

GraphAddCommand::~GraphAddCommand()
{

}

void GraphAddCommand::undo()
{
  m_pSelectMger->clearSelect();
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    m_shapeVec[i]->setVisible(false);
  }
}

void GraphAddCommand::redo()
{
  m_pSelectMger->clearSelect();
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    m_shapeVec[i]->setVisible(true);
    m_pSelectMger->addShape(m_shapeVec[i]);
  }

}

// GraphDelCommand
GraphDelCommand::GraphDelCommand(GraphItemShape* shape,SelectShapeManager* selectMger)
  :m_pSelectMger(selectMger)
{
  m_shapeVec.push_back(shape);
}

GraphDelCommand::GraphDelCommand(const Vector<GraphItemShape*>& shapeVec, SelectShapeManager* selectMger)
  :m_pSelectMger(selectMger)
{
  m_shapeVec.resize(shapeVec.size());
  for(int i = 0; i < shapeVec.size(); i++)
  {
    m_shapeVec[i] = shapeVec[i];
  }
}

GraphDelCommand::~GraphDelCommand()
{

}

void GraphDelCommand::undo()
{
  m_pSelectMger->clearSelect();
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    m_shapeVec[i]->setVisible(true);
    m_pSelectMger->addShape(m_shapeVec[i]);
  }
}

void GraphDelCommand::redo()
{
  m_pSelectMger->clearSelect();
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    m_shapeVec[i]->setVisible(false);
  }
}

// GraphMoveCommand
GraphMoveCommand::GraphMoveCommand(const Vector<GraphItemShape*>& shapeVec, 
  SelectShapeManager* selectMger,double xoff, double yoff)
  :m_pSelectMger(selectMger),m_moveXoff(xoff), m_moveYoff(yoff)
{
  m_shapeVec.resize(shapeVec.size());
  for(int i = 0; i < shapeVec.size(); i++)
  {
    m_shapeVec[i] = shapeVec[i];
  }
}

GraphMoveCommand::~GraphMoveCommand()
{

}

void GraphMoveCommand::undo()
{
  m_pSelectMger->clearSelect();
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    m_pSelectMger->addShape(m_shapeVec[i]);
    m_shapeVec[i]->move(-m_moveXoff, -m_moveYoff);
  }
}

void GraphMoveCommand::redo()
{
  m_pSelectMger->clearSelect();
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    m_pSelectMger->addShape(m_shapeVec[i]);
    m_shapeVec[i]->move(m_moveXoff, m_moveYoff);
  }
}

// GraphHandlerCommand
GraphHandlerCommand::GraphHandlerCommand(ControlHandler* pHandler, 
   SelectShapeManager* selectMger, PointF beginPos, PointF endPos)
  :m_pSelectMger(selectMger),m_pHandler(pHandler),m_beginPos(beginPos),m_endPos(endPos)
{

}

GraphHandlerCommand::~GraphHandlerCommand()
{

}

void GraphHandlerCommand::undo()
{
  m_pSelectMger->clearSelect();
  
  GraphItemShape* pShape = m_pHandler->getOwnerShape();
  pShape->shapeResizeTo(m_beginPos, m_pHandler);
  
  m_pSelectMger->addShape(pShape);
}

void GraphHandlerCommand::redo()
{
  m_pSelectMger->clearSelect();
  
  GraphItemShape* pShape = m_pHandler->getOwnerShape();
  pShape->shapeResizeTo(m_endPos, m_pHandler);
  
  m_pSelectMger->addShape(pShape);
}

// GraphChangePropertyCommand
GraphChangePropertyCommand::
GraphChangePropertyCommand(const Vector<GraphItemShape*>& shapeVec, 
                          const Vector<ShapeProperty>& properVec)
{
  m_shapeVec.resize(shapeVec.size());
  m_oldPropertyVec.resize(properVec.size());
  for(int i = 0; i < shapeVec.size(); i++)
  {
    m_shapeVec[i] = shapeVec[i];
    m_oldPropertyVec[i] = properVec[i];
  }
  m_newShapeProperty = shapeVec[0]->getProperty();
}

GraphChangePropertyCommand::~GraphChangePropertyCommand()
{

}

void GraphChangePropertyCommand::undo()
{
  for(int i = 0; i < m_shapeVec.size(); i++)
    m_shapeVec[i]->setProperty(m_oldPropertyVec[i]);
}

void GraphChangePropertyCommand::redo()
{
  for(int i = 0; i < m_shapeVec.size(); i++)
    m_shapeVec[i]->setProperty(m_newShapeProperty);
}

