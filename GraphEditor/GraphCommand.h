#ifndef GRAPH_COMMAND_H
#define GRAPH_COMMAND_H

#include "GraphItemShape.h"
#include "SelectShapeManager.h"

class GraphCommand
{
public:
  GraphCommand() = default;
  virtual ~GraphCommand() = default;
  virtual void undo() = 0;
  virtual void redo() = 0;
private:

};

class GraphAddCommand
  : public GraphCommand
{
public:
  GraphAddCommand(GraphItemShape* shape,SelectShapeManager *selectMger); 
  GraphAddCommand(const Vector<GraphItemShape*> &shapeVec, SelectShapeManager* selectMger);
  ~GraphAddCommand();
  void undo()override;
  void redo()override;
private:
  Vector<GraphItemShape*> m_shapeVec;
  SelectShapeManager* m_pSelectMger = nullptr;
};

class GraphDelCommand
  : public GraphCommand
{
public:
  GraphDelCommand(GraphItemShape* shape, SelectShapeManager* selectMger);
  GraphDelCommand(const Vector<GraphItemShape*> &shapeVec, SelectShapeManager* selectMger);
  ~GraphDelCommand();
  void undo()override;
  void redo()override;
private:
  Vector<GraphItemShape*> m_shapeVec;
  SelectShapeManager* m_pSelectMger = nullptr;
};

class GraphMoveCommand
  : public GraphCommand
{
public:
  GraphMoveCommand(const Vector<GraphItemShape*> &shapeVec, SelectShapeManager* selectMger,double xoff,double yoff);
  ~GraphMoveCommand();
  void undo()override;
  void redo()override;
private:
  Vector<GraphItemShape*> m_shapeVec;
  SelectShapeManager* m_pSelectMger = nullptr;
  double m_moveXoff;
  double m_moveYoff;
};

class GraphHandlerCommand
  : public GraphCommand
{
public:
  GraphHandlerCommand(ControlHandler *pHandler, SelectShapeManager* selectMger,PointF beginPos,PointF endPos);
  ~GraphHandlerCommand();
  void undo()override;
  void redo()override;
private:
  ControlHandler* m_pHandler = nullptr;
  SelectShapeManager* m_pSelectMger = nullptr;
  PointF m_beginPos;
  PointF m_endPos;

};

class GraphChangePropertyCommand
  :public GraphCommand
{
public:
  GraphChangePropertyCommand(const Vector<GraphItemShape*>& shapeVec, 
                            const Vector<ShapeProperty> &properVec);
  ~GraphChangePropertyCommand();
  void undo()override;
  void redo()override;
private:
  Vector<GraphItemShape*> m_shapeVec;
  ShapeProperty m_newShapeProperty;
  Vector<ShapeProperty> m_oldPropertyVec;
  
};
#endif // GRAPH_COMMAND_H

