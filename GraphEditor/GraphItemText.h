#ifndef GRAPH_ITEM_TEXT_H
#define GRAPH_ITEM_TEXT_H

#include "GraphItemRectangle.h"

class GraphItemText :public GraphItemRectangle
{
public:
  GraphItemText(PointF beginPos, PointF endPos,TCHAR *str,int strlen);
  ~GraphItemText();
  void drawShape(HDC hdc) override;
  bool shapeResizeTo(const PointF& newPos, ControlHandler* handler) override;
protected:
  Vector<TCHAR> m_VecText;
};

#endif

