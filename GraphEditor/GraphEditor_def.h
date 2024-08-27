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
};

#endif// GRAPH_EDITOR_DEF_H