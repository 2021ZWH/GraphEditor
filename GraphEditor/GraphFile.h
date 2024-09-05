#ifndef GRAPH_FILE_H
#define GRAPH_FILE_H

#include <Windows.h>
#include "Vector.h"
#include "GraphItemShape.h"

enum FileMode
{
  READ,
  WRITE,
  READWRITE
};

class GraphFile
{
public:
  GraphFile(const TCHAR* szFilename, FileMode mode);
  ~GraphFile();
  int readFile(Vector<GraphItemShape*>& shapeVec);
  int writeFile(Vector<GraphItemShape*>& shapeVec);
  bool isOpen() const;
private:
  int parseLine(TCHAR* szData, int begin, GraphItemShape **shape);
  int strToFloat(TCHAR* szData, int begin, double* val);
  int strToInt(TCHAR* szData, int begin, int* val);
private:
  HANDLE    m_hFile;
  FileMode  m_fileMode;

};

#endif // GRAPH_FILE_H

