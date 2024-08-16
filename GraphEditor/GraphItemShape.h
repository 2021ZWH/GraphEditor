#ifndef GRAPH_ITEM_SHAPE_H
#define GRAPH_ITEM_SHAPE_H

#include <Windows.h>

class GraphItemShape
{
public:
  GraphItemShape() = default;
  virtual ~GraphItemShape() = default;

  virtual void draw(HDC hdc,int xoff, int yoff) = 0;
  virtual bool isPointUpShape(const POINT& pos) = 0;
  virtual bool isRectCrossShape(const RECT& rect) = 0;

protected:

};

#endif

