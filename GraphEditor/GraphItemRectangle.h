#ifndef GRAPH_ITEM_RECTANGLE_H
#define GRAPH_ITEM_RECTANGLE_H

#include "GraphItemShape.h"
#include "GraphEditor_def.h"

class GraphItemRectangle : 
    public GraphItemShape
{
public: 
  GraphItemRectangle(PointF beginPos, PointF endPos);
  ~GraphItemRectangle();
  Vector<TCHAR> toText() override;
  void drawShape(HDC hdc, double xoff, double yoff) override;
  void move(double dx, double dy) override;
  
  bool isPointUpShape(const PointF& pos) override;
  bool isRectCrossShape(const RectF& rectf) override;
  bool shapeResizeTo(const PointF &newPos, ControlHandler* handler) override;
private:
  void updateCtrHandler();
private:
  Vector<PointF> m_aptF;
};

#endif // GRAPH_ITEM_RECTANGLE_H
