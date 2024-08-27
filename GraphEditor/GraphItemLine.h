#ifndef GRAPH_ITEM_LINE_H
#define GRAPH_ITEM_LINE_H

#include <Windows.h>
#include "GraphEditor_def.h"
#include "GraphItemShape.h"
#include "ControlHandler.h"

class GraphItemLine : public GraphItemShape
{
public:
  GraphItemLine(PointF posA,PointF posB);
  ~GraphItemLine();
  
  void drawShape(HDC hdc, double xoff, double yoff);
  void move(double dx, double dy);
  bool isPointUpShape(const PointF& pos);
  bool isRectCrossShape(const RectF& rectf);
  bool shapeResize(double dx, double dy, ControlHandler* handler);
private:
  void updateCtrHandler();
private:
  PointF m_posA;
  PointF m_posB;
};

#endif // GRAPH_ITEM_LINE_H

