#ifndef CONTROL_HANDLER_H
#define CONTROL_HANDLER_H

#include <Windows.h>
#include "GraphEditor_def.h"

class GraphItemShape;

enum HandlerType
{
  HT_WEST, // <-
  HT_NW,   
  HT_NORTH, // ^
  HT_NE,
  HT_EAST,  // ->
  HT_SE,
  HT_SOUTH, // v
  HT_SW,
  HT_ALL,
  HT_INVALID
};

class ControlHandler
{
public:
  ControlHandler(GraphItemShape *owner,HandlerType type, int id);
  void draw(HDC hdc);
  void move(double dx, double dy);
  bool isPointInHandler(const PointF &pos);
  void setPos(const PointF& pos);
  PointF getPos() const;
  void SetSelect(bool fSelect);
  bool isSelect() const;
  int getId() const;
  GraphItemShape* getOwnerShape();
  HCURSOR getCursor();
  HandlerType getHandlerType() const;

private:
  GraphItemShape* m_ownerShape = nullptr;
  HandlerType m_type = HT_INVALID;
  HCURSOR m_hCursor;
  PointF m_ctrPos;
  int m_width = 12;
  int m_id;
  bool m_fSelect = false;
};

#endif // CONTROL_HANDLER_H
