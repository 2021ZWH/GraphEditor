#ifndef GRAPH_ITEM_ELLIPTIC_H
#define GRAPH_ITEM_ELLIPTIC_H

#include "GraphItemShape.h"

class GraphItemElliptic :
    public GraphItemShape
{
public:
  GraphItemElliptic(const PointF &beginPos, const PointF &endPos);
  ~GraphItemElliptic();
  Vector<TCHAR> toText() override;
  void drawShape(HDC hdc) override;
  void move(double dx, double dy) override;
  bool isPointUpShape(const PointF& pos) override;
  bool isRectCrossShape(const RectF& rectf) override;
  bool shapeResizeTo(const PointF &newPos, ControlHandler* handler) override;
private:
  void updateHandlers();
private:
  Vector<PointF> m_aptF;

};

#endif // GRAPH_ITEM_ELLIPTIC_H
