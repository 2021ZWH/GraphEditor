 #ifndef GRAPH_ITEM_SHAPE_H
#define GRAPH_ITEM_SHAPE_H

#include <Windows.h>
#include "GraphEditor_def.h"
#include "ControlHandler.h"
#include "Vector.h"

class GraphItemShape
{
public:
  GraphItemShape() = default;
  virtual ~GraphItemShape();

  virtual void drawShape(HDC hdc,double xoff, double yoff) = 0;
  virtual void drawHandler(HDC hdc, double xoff, double yoff, double scale);
  virtual ControlHandler* getHandlerByPos(const PointF& pos);
  virtual void move(double dx, double dy) = 0;
  virtual bool isPointUpShape(const PointF& pos) = 0;
  virtual bool isRectCrossShape(const RectF& rectf) = 0;
  virtual bool shapeResize(double dx,double dy, ControlHandler* handler) = 0;
  virtual void addPos(const PointF& pos);
  virtual void SetSelectHandler(ControlHandler* handler);
  virtual void resetSelect();
protected:
  virtual void clearCtrHandler();
protected:
  Vector<ControlHandler*> m_ctrHandlers;
  ControlHandler* m_selectHandler = nullptr;

};

#endif // GRAPH_ITEM_SHAPE_H

