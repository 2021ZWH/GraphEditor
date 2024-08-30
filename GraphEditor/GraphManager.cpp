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

HCURSOR GraphManager::getCursor(const PointF& scenePos)
{
  Vector<GraphItemShape*> vec = m_selectMger.getShape();

  if(m_selectMger.getHandler())
  {
    return m_selectMger.getHandler()->getCursor();
  }

  for(int i = 0; i < vec.size(); i++)
  {
    ControlHandler* handler = vec[i]->getHandlerByPos(scenePos);
    if(handler != nullptr)
      return handler->getCursor();
  }

  return LoadCursor(NULL, IDC_ARROW);
}

void GraphManager::paint(HDC hdc, const RectF &rectf,double scale)
{   
  // ��00����һ������
  double sx = 0 - rectf.left;
  double sy = 0 - rectf.top;
  Rectangle(hdc, sx, sy, sx + 800, sy + 800);//��ͼ

  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    if(m_shapeVec[i]->isRectCrossShape(rectf))
    {
      m_shapeVec[i]->drawShape(hdc, rectf.left, rectf.top);
    }
  }

  if(isSelect())
  {
    Vector<GraphItemShape*> vec = m_selectMger.getShape();

    for(int i = 0; i < vec.size();i++)
    {
      vec[i]->drawHandler(hdc, rectf.left, rectf.top, 1.0/scale);
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
  m_selectMger.addShape(shape);
}

void GraphManager::onMouseLButtonDown(const PointF& scenePos,bool canSelect)
{
  bool freshWnd = false;

  if(!canSelect)
  {
    m_selectMger.setHandler(nullptr);
    m_selectMger.clearSelect();
    InvalidateRect(m_hWnd, NULL, false);
    return;
  }

  m_selectMger.setHandler(nullptr); // �ж��Ƿ�ѡ�п��Ƶ�
  Vector<GraphItemShape*> vec = m_selectMger.getShape();
  for(int i = 0; i < vec.size(); i++)
  {
    ControlHandler* handler = vec[i]->getHandlerByPos(scenePos);
    if(handler != nullptr)
    {
      m_selectMger.setHandler(handler);
      handler->getOwnerShape()->SetSelectHandler(handler);
      break;
    }
  }

  if(m_selectMger.getHandler() == nullptr)  // ��ûѡ�п��Ƶ�
  {
    m_selectMger.clearSelect();  // ���ѡ��
    freshWnd = true;

    for(int i = 0; i < m_shapeVec.size(); i++)  // ��ѡ�о��Σ����
    {
      if(m_shapeVec[i]->isPointUpShape(scenePos))
      {
        m_selectMger.addShape(m_shapeVec[i]);
        break;
      }
    }
  }

  m_mouseBeginPos = scenePos;
 
  if(freshWnd) InvalidateRect(m_hWnd, NULL, false);
}

void GraphManager::onMouseMove(bool fLButtonDown, const PointF& scenePos)
{
  if(!fLButtonDown) return;

  double xoff = scenePos.x - m_mouseBeginPos.x;
  double yoff = scenePos.y - m_mouseBeginPos.y;
  m_mouseBeginPos = scenePos;
  bool freshWnd = false;
  Vector<GraphItemShape*> vec = m_selectMger.getShape();

  if(m_selectMger.getHandler() != nullptr) // ������갴�µ�����Ƶ㣬�����ƶ�����
  {
    // �ƶ����Ƶ�
    GraphItemShape* shape = m_selectMger.getHandler()->getOwnerShape();
    shape->shapeResize(xoff, yoff, m_selectMger.getHandler());
    freshWnd = true;
  }
  else
  {
    if(isSelect()) // ���ж��Ƿ��ƶ�
    {
      for(int i = 0; i < vec.size(); i++)
      {
        vec[i]->move(xoff, yoff);
      }
      freshWnd = true;
    }
  }

  if(freshWnd) InvalidateRect(m_hWnd, NULL, false);
}

void GraphManager::onMouseLButtonUp(const PointF& scenePos)
{
  m_selectMger.setHandler(nullptr); // ���Ƶ��������
}