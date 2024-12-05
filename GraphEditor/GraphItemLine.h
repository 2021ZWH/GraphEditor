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
  Vector<TCHAR> toText() override;
  void drawShape(HDC hdc);
  void move(double dx, double dy);
  bool isPointUpShape(const PointF& pos);
  bool isRectCrossShape(const RectF& rectf);
  bool shapeResizeTo(const PointF &newPos, ControlHandler* handler);
private:
  void updateCtrHandler();
private:
  PointF m_posA;
  PointF m_posB;
};

#endif // GRAPH_ITEM_LINE_H

