#ifndef GRAPH_CODER_H
#define GRAPH_CODER_H

#include <Windows.h>
#include "Vector.h"
#include "GraphItemShape.h"

class GraphCoder
{
public:
  int code(Vector<GraphItemShape*>& shapeVec,TCHAR **szData);
  int decode(TCHAR *szData, Vector<GraphItemShape*>& shapeVec);
private:
  int parseLine(TCHAR* szData, int begin, GraphItemShape** shape);
  int strToFloat(TCHAR* szData, int begin, double* val);
  int strToInt(TCHAR* szData, int begin, int* val);
};

#endif // !GRAPH_CODER_H
