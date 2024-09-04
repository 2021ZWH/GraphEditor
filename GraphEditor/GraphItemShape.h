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

  virtual void setLineWidth(UINT width);
  virtual void setLineColor(COLORREF color);
  virtual void setFillColor(COLORREF color);
  virtual UINT getLineWidth() const;
  virtual COLORREF getLineColor() const;
  virtual COLORREF getFillColor() const;
protected:
  virtual void clearCtrHandler();
protected:
  Vector<ControlHandler*> m_ctrHandlers;
  ControlHandler* m_selectHandler = nullptr;
  UINT m_lineWidth = 1;
  COLORREF m_lineColor = BGR_BLACK;
  COLORREF m_fillColor = BGR_WHITE;
  bool m_fTransparent = true;
  
};

#endif // GRAPH_ITEM_SHAPE_H

