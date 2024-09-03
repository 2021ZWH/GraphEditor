#ifndef GRAPH_ITEM_POLYBEZIER_H
#define GRAPH_ITEM_POLYBEZIER_H

#include "GraphItemShape.h"

class GraphItemPolyBezier :
    public GraphItemShape
{
public:
  GraphItemPolyBezier();
  ~GraphItemPolyBezier();
  void drawShape(HDC hdc, double xoff, double yoff) override;
  void move(double dx, double dy) override;
  bool isPointUpShape(const PointF& pos) override;
  bool isRectCrossShape(const RectF& rectf) override;
  bool shapeResize(double dx, double dy, ControlHandler* handler) override;
  void addPos(const PointF& pos) override;
  virtual void drawHandler(HDC hdc, double xoff, double yoff, double scale);
  virtual ControlHandler* getHandlerByPos(const PointF& pos);
private:
  bool isPointInLine(const PointF &pos,int id);
  bool isRectInLine(const RectF& rect, int id);
private:
  Vector<PointF> m_aptf;



};

#endif // GRAPH_ITEM_POLYBEZIER_H

