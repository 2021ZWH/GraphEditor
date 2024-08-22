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
  Vector<GraphItemShape*> &getSelect();
private:
  Vector<GraphItemShape*> m_selectShape;

};

#endif // SELECT_SHAPE_MANAGER_H
