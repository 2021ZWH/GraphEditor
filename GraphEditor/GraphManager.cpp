#include "GraphManager.h"

GraphManager::GraphManager(HWND hwnd)
  :m_hWnd(hwnd)
{

}
GraphManager::~GraphManager()
{

}

void GraphManager::paint(HDC hdc, const RECT &rect)
{   
  // ��00����һ������
  int sx = 0 - rect.left;
  int sy = 0 - rect.top;
  Rectangle(hdc, sx, sy,sx+40 ,  sy+40);//��ͼ

  int ex = rect.left;

}