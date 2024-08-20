#include "GraphManager.h"

GraphManager::GraphManager(HWND hwnd)
  :m_hWnd(hwnd)
{

}

GraphManager::~GraphManager()
{

}

UINT GraphManager::getWidth() const
{
  return m_width;
}

UINT GraphManager::getHeight() const
{
  return m_height;
}

void GraphManager::paint(HDC hdc, const RECT &rect)
{   
  // 在00处画一个举行
  int sx = 0 - rect.left;
  int sy = 0 - rect.top;
  Rectangle(hdc, sx, sy,sx+800 ,  sy+800);//画图

  int ex = rect.left;

}