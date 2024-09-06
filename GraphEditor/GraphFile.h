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
  int readFile(TCHAR **szData);
  int writeFile(TCHAR *szData);
  bool isOpen() const;
private:
  HANDLE    m_hFile;
  FileMode  m_fileMode;

};

#endif // GRAPH_FILE_H

