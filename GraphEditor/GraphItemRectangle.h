#ifndef GRAPH_ITEM_RECTANGLE_H
#define GRAPH_ITEM_RECTANGLE_H

#include "GraphItemShape.h"

class GraphItemRectangle : public GraphItemShape
{
public: 
  GraphItemRectangle(const RECT &rect);
  GraphItemRectangle(const POINT& pos, int w, int h);
  GraphItemRectangle(const POINT& startPos, const POINT& endPos);
  ~GraphItemRectangle();
  void draw(HDC hdc,int xoff, int yoff) override;
  void move(int dx,int dy) override;
  
  bool isPointUpShape(const POINT& pos) override;
  bool isRectCrossShape(const RECT& rect) override;

private:
  RECT m_rect;
  int lineW = 1;
};

#endif// GRAPH_ITEM_RECTANGLE_H
