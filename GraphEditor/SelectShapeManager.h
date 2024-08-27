#ifndef SELECT_SHAPE_MANAGER_H
#define SELECT_SHAPE_MANAGER_H

#include "Vector.h"
#include "GraphItemShape.h"

class SelectShapeManager
{
public:
  bool isSelect()const;
  void addShape(GraphItemShape* pItemShape);
  void clearSelect();
  void setHandler(ControlHandler *handler);
  Vector<GraphItemShape*> &getShape();
  ControlHandler* getHandler();
  PointF getBeginPos() const;
private:
  Vector<GraphItemShape*> m_selectShape;
  PointF m_beginPos;
  ControlHandler* m_selectHandler = nullptr;

};

#endif // SELECT_SHAPE_MANAGER_H
