#include "GraphManager.h"

GraphManager::GraphManager(HWND hwnd)
  :m_hWnd(hwnd)
{

}

GraphManager::~GraphManager()
{
  for(int i = 0; i < m_shapeVec.size(); i++)
    delete m_shapeVec[i];
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

  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    if(m_shapeVec[i]->isRectCrossShape(rect))
    {
      m_shapeVec[i]->draw(hdc, rect.left, rect.top);
    }
  }

}

bool GraphManager::isSelect() const
{
  return m_selectMger.isSelect();
}

void GraphManager::addShape(GraphItemShape* shape)
{
  m_shapeVec.push_back(shape);
}

void GraphManager::onMouseLButtonDown(const POINT& scenePos)
{
  m_selectMger.clearSelect();

  m_mouseBeginPos = scenePos;
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    if(m_shapeVec[i]->isPointUpShape(scenePos))
    {
      m_selectMger.addShape(m_shapeVec[i]);
      break;
    }
  }
}

void GraphManager::onMouseMove(bool fLButtonDown, const POINT& scenePos)
{
  if(!fLButtonDown) return;
  if(isSelect())
  {
    int xoff = scenePos.x - m_mouseBeginPos.x;
    int yoff = scenePos.y - m_mouseBeginPos.y;

    Vector<GraphItemShape*> vec = m_selectMger.getSelect();
    for(int i = 0; i < vec.size(); i++)
    {
      vec[i]->move(xoff, yoff);
    }
    m_mouseBeginPos = scenePos;
    InvalidateRect(m_hWnd, NULL, false);
  }
  
}

void GraphManager::onMouseLButtonUp(const POINT& scenePos)
{

}