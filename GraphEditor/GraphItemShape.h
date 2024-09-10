 #ifndef GRAPH_ITEM_SHAPE_H
#define GRAPH_ITEM_SHAPE_H

#include <Windows.h>
#include "GraphEditor_def.h"
#include "ControlHandler.h"
#include "Vector.h"

enum ShapeType
{
  SHAPE_UNKNOWN,
  SHAPE_LINE,
  SHAPE_POLYLINE,
  SHAPE_POLYBEZIER,
  SHAPE_CIRCLE,
  SHAPE_ELLIPTIC,
  SHAPE_RECTANGLE
};

class GraphItemShape
{
public:
  GraphItemShape() = default;
  virtual ~GraphItemShape();
  virtual Vector<TCHAR> toText();
  virtual void drawShape(HDC hdc,double xoff, double yoff) = 0;
  virtual void drawHandler(HDC hdc, double xoff, double yoff, double scale);
  virtual ControlHandler* getHandlerByPos(const PointF& pos);
  virtual void move(double dx, double dy) = 0;
  virtual bool isPointUpShape(const PointF& pos) = 0;
  virtual bool isRectCrossShape(const RectF& rectf) = 0;
  virtual bool shapeResizeTo(const PointF &newPos, ControlHandler* handler) = 0;
  virtual void addPos(const PointF& pos);
  virtual void SetSelectHandler(ControlHandler* handler);
  virtual void resetSelect();

  virtual void setLineWidth(UINT width);
  virtual void setLineColor(COLORREF color);
  virtual void setFillColor(COLORREF color);
  virtual void setTransParent(bool flag);
  virtual UINT getLineWidth() const;
  virtual COLORREF getLineColor() const;
  virtual COLORREF getFillColor() const;

  virtual bool isVisible() const;
  virtual void setVisible(bool flag);
protected:
  virtual void clearCtrHandler();
protected:
  Vector<ControlHandler*> m_ctrHandlers;
  ControlHandler* m_selectHandler = nullptr;

  ShapeType m_shapeType = SHAPE_UNKNOWN;
  UINT m_lineWidth = 1;
  COLORREF m_lineColor = BGR_BLACK;
  COLORREF m_fillColor = BGR_WHITE;
  bool m_fTransparent = true;

  bool m_fVisible = true;
  
  
};

#endif // GRAPH_ITEM_SHAPE_H

