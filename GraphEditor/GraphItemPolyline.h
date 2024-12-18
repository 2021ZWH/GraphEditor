#ifndef GRAPH_ITEM_POLYLINE_H
#define GRAPH_ITEM_POLYLINE_H

#include "GraphItemShape.h"
#include "Vector.h"

class GraphItemPolyline : public GraphItemShape
{
public:
  GraphItemPolyline(const PointF& startPos);
  ~GraphItemPolyline();
  Vector<TCHAR> toText() override;
  void drawShape(HDC hdc) override;
  void move(double dx, double dy) override;
  bool isPointUpShape(const PointF& pos) override;
  bool isRectCrossShape(const RectF& rectf) override;
  bool shapeResizeTo(const PointF &newPos, ControlHandler* handler) override;
  void addPos(const PointF& pos) override;
private:
  void updateCtrHandler();
  void drawSingleLine(HDC hdc, PointF startPos, PointF endPos);
private:
  Vector<PointF> m_linePos;

};

#endif

