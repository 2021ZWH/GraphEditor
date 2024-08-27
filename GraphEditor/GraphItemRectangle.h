#ifndef GRAPH_ITEM_RECTANGLE_H
#define GRAPH_ITEM_RECTANGLE_H

#include "GraphItemShape.h"
#include "GraphEditor_def.h"

class GraphItemRectangle : public GraphItemShape
{
public: 
  GraphItemRectangle(PointF beginPos, PointF endPos);
  ~GraphItemRectangle();
  void drawShape(HDC hdc, double xoff, double yoff) override;
  void move(double dx, double dy) override;
  
  bool isPointUpShape(const PointF& pos) override;
  bool isRectCrossShape(const RectF& rectf) override;
  bool shapeResize(double dx,double dy, ControlHandler* handler) override;
private:
  void updateCtrHandler();
private:
  RectF m_rectf;
  int lineW = 1;
};

#endif// GRAPH_ITEM_RECTANGLE_H
