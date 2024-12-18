#ifndef GRAPH_ITEM_CIRCLE_H
#define GRAPH_ITEM_CIRCLE_H

#include "GraphItemShape.h"
class GraphItemCircle :
    public GraphItemShape
{
public:
  GraphItemCircle(const PointF &beginPos,const PointF &endPos);
  ~GraphItemCircle();
  Vector<TCHAR> toText() override;
  void drawShape(HDC hdc) override;
  void move(double dx, double dy) override;
  bool isPointUpShape(const PointF& pos) override;
  bool isRectCrossShape(const RectF& rectf) override;
  bool shapeResizeTo(const PointF &newPos, ControlHandler* handler) override;
private:
  void updateHandlers();
private:
  Vector<PointF>m_aptF;

};

#endif // GRAPH_ITEM_CIRCLE_H

