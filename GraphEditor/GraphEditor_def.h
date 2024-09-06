#ifndef GRAPH_EDITOR_DEF_H
#define GRAPH_EDITOR_DEF_H

#define BGR_BLUE       0x00FF0000  // 颜色的一些宏
#define BGR_RED        0x000000FF
#define BGR_GREEN      0x0000FF00
#define BGR_BLUE       0x00FF0000
#define BGR_BLACK      0x00000000
#define BGR_WHITE      0x00FFFFFF
#define BGR_LIGHTBLUE  0x00D2923F

#define BGDCOLOR          (0x00c8c8c8)
#define MAX_SCENE_WIDTH   20000
#define MAX_SCENE_HEIGHT  20000


#include <math.h>

struct PointF
{
  double x;
  double y;

  POINT toPoint() const
  {
    int intX = (int)(x + 0.5);
    int intY = (int)(y + 0.5);
    return { intX,intY };
  }

};

struct SegmentF
{
  PointF posA;
  PointF posB;

  bool isPointIn(const PointF pos, double err = 0) const
  {
    if(pos.x > max(posA.x, posB.x) || pos.x < min(posA.x, posB.x))
      return false;
    if(pos.y > max(posA.y, posB.y) || pos.y < min(posA.y, posB.y))
      return false;

    double left = (pos.x - posA.x) * (posB.y - posA.y);
    double right = (posB.x - posA.x) * (pos.y - posA.y);

    if(fabs(left - right) <= err)
      return true;
    return false;
  }

  bool isSegmentIntersect(const SegmentF& other) const
  {
    PointF Q1 = other.posA;
    PointF Q2 = other.posB;

    if(max(Q1.x, Q2.x) < min(posA.x, posB.x) ||  
      max(posA.x, posB.x) < min(Q1.x, Q2.x) ||
      max(Q1.y, Q2.y) < min(posA.y, posB.y) ||
      max(posA.y, posB.y) < min(Q1.y, Q2.y)) // 快速跨立实验
      return false;

    if(((Q1.x - posA.x) * (Q1.y - Q2.y) - (Q1.y - posA.y) * (Q1.x - Q2.x)) *
       ((Q1.x - posB.x) * (Q1.y - Q2.y) - (Q1.y - posB.y) * (Q1.x - Q2.x)) < 0)
      return true;

    if(((posA.x - Q1.x) * (posA.y - posB.y) - (posA.y - Q1.y) * (posA.x - posB.x)) * 
       ((posA.x - Q2.x) * (posA.y - posB.y) - (posA.y - Q2.y) * (posA.x - posB.x)) < 0)
      return true;

    return false;
  }

};

struct RectF
{
  double left;
  double top;
  double right;
  double bottom;

  RECT toRect() const
  {
    int intL = (int)(left + 0.5);
    int intT = (int)(top + 0.5);
    int intR = (int)(right + 0.5);
    int intB = (int)(bottom + 0.5);
    return { intL,intT,intR,intB };
  }

  bool isPointIn(const PointF& pos) const
  {
    if(pos.x < left || pos.x > right) return false;
    if(pos.y < top || pos.y > bottom) return false;
    return true;
  }

  bool isSegmentIntersect(const SegmentF& seg) const
  {
    // 判断线段两点是否在矩形
    if(isPointIn(seg.posA)) return true;
    if(isPointIn(seg.posB)) return true;

    //判断线段与矩形对角线是否相交
    SegmentF segA = { {left,top},{right,bottom} };
    SegmentF segB = { {right,top},{left,bottom} };
    if(segA.isSegmentIntersect(seg)) return true;
    if(segB.isSegmentIntersect(seg)) return true;

    return false;
  }

  bool isRectIntersect(const RectF& other) const
  {
    // 判断两矩形的相交矩形是否合法
    double minFx = max(left, other.left);
    double maxFx = min(right, other.right);
    if(maxFx < minFx) return false;

    double minFy = max(top, other.top);
    double maxFy = min(bottom, other.bottom);
    if(maxFy < minFy) return false;

    return true;
  }

};

#endif // GRAPH_EDITOR_DEF_H