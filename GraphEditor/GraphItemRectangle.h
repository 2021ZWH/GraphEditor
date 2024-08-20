#ifndef GRAPH_ITEM_RECTANGLE_H
#define GRAPH_ITEM_RECTANGLE_H

#include "GraphItemShape.h"

class GraphItemRectangle : public GraphItemShape
{
public: 
  GraphItemRectangle();
  ~GraphItemRectangle();
  void draw(HDC hdc,int xoff, int yoff) override;
  bool isPointUpShape(const POINT& pos) override;
  bool isRectCrossShape(const RECT& rect) override;

private:
  RECT m_rect;
  int lineW = 1;
};

#endif// GRAPH_ITEM_RECTANGLE_H
