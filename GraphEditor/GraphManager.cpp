#include "GraphManager.h"
#include "GraphCoder.h"

GraphManager::GraphManager(HWND hwnd)
  :m_hWnd(hwnd),
  m_pCmdMger(new GraphCommandManager),
  m_pClipboard(new ClipboardManager(hwnd))
{

}

GraphManager::~GraphManager()
{
  clear();
  delete m_pCmdMger;
  delete m_pClipboard;
  
}

void GraphManager::clear()
{
  m_selectMger.clearSelect();
  m_pCmdMger->clear();
  m_selectMger.setHandler(nullptr);
  for(int i = 0; i < m_shapeVec.size(); i++)
    delete m_shapeVec[i];
  m_shapeVec.clear();

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

void GraphManager::paint(HDC hdc)
{   
  // 在00处画一个矩形
 // Rectangle(hdc, 0, 0, 800, 800);
 
  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    if(!m_shapeVec[i]->isVisible())
      continue;
  
    m_shapeVec[i]->drawShape(hdc);
    
  }

  if(isSelect())
  {
    Vector<GraphItemShape*> vec = m_selectMger.getShape();

    for(int i = 0; i < vec.size();i++)
    {
      vec[i]->drawHandler(hdc);
    }
  }
}

bool GraphManager::save(const TCHAR* szFilename)
{
  TCHAR* szData = nullptr;
  GraphCoder gc;

  if(gc.code(m_shapeVec, &szData))
    return false;

  GraphFile gf(szFilename, FileMode::WRITE);
  if(!gf.isOpen()) 
    return false;

  int ret = gf.writeFile(szData);

  delete[] szData;
  return ret == 0;
}

bool GraphManager::open(const TCHAR* szFilename)
{
  GraphFile gf(szFilename, FileMode::READ);
  if(!gf.isOpen()) 
    return false;

  TCHAR* szData = nullptr;
  if(gf.readFile(&szData))
    return false;

  GraphCoder gc;
  Vector<GraphItemShape*> shapeVec;
  int ret = gc.decode(szData, shapeVec);
  
  if(!ret)
  {
    clear();
    m_shapeVec = shapeVec;
    freshView();
  }

  delete[] szData;
  return ret == 0;
}

bool GraphManager::copy()
{
  if(!isSelect())
    return false;

  Vector<GraphItemShape*> selectShape = m_selectMger.getShape();
  TCHAR* szData = nullptr;

  GraphCoder gc;
  if(gc.code(selectShape, &szData) != 0)
    return false;

  
  bool ret = m_pClipboard->setText(szData);

  delete[] szData;
  return ret;
}

bool GraphManager::cut()
{
  if(copy())
  {
    delSelectShape();
    return true;
  }

  return false;
}

bool GraphManager::paste()
{
  TCHAR* szData = m_pClipboard->getText();

  if(szData == nullptr)
    false;

  GraphCoder gc;
  Vector<GraphItemShape*> shapeVec;
  int ret = gc.decode(szData, shapeVec);

  if(ret == 0)
  {
    addShape(shapeVec);

    freshView();
  }

  delete[] szData;

  return ret == 0;
}

bool GraphManager::undo()
{
  if(!m_pCmdMger->canUndo())
    return false;

  m_pCmdMger->undo();
  freshView();
  return true;
}

bool GraphManager::redo()
{
  if(!m_pCmdMger->canRedo())
    return false;

  m_pCmdMger->redo();
  freshView();
  return true;
}

bool GraphManager::setShapeProper(const ShapeProperty& property)
{
  if(!isSelect())
    return false;

  bool flag = false;
  Vector<GraphItemShape*> shapeVec = m_selectMger.getShape();
  Vector<ShapeProperty> properVec;
  properVec.resize(shapeVec.size());
  for(int i = 0; i < shapeVec.size(); i++)
  {
    properVec[i] = shapeVec[i]->getProperty();
    if(!(properVec[i] == property))
    {
      shapeVec[i]->setProperty(property);
      flag = true;
    }
   
  }
  if(!flag) return false;
  GraphCommand* cmd = new GraphChangePropertyCommand(shapeVec, properVec);
  m_pCmdMger->addCommand(cmd);
  freshView();
  return true;
  
}

bool GraphManager::isSelect() const
{
  return m_selectMger.isSelect();
}

void GraphManager::addShape(GraphItemShape* shape)
{
  m_shapeVec.push_back(shape);
  m_selectMger.clearSelect();
  m_selectMger.addShape(shape);

  GraphCommand *cmd = new GraphAddCommand(shape,&m_selectMger);
  m_pCmdMger->addCommand(cmd);
}

void GraphManager::addShape(const Vector<GraphItemShape*>& shapeVec)
{
  m_selectMger.clearSelect();
  for(int i = 0; i < shapeVec.size(); i++)
  {
    m_shapeVec.push_back(shapeVec[i]);
    m_selectMger.addShape(shapeVec[i]);
  }

  GraphCommand* cmd = new GraphAddCommand(shapeVec, &m_selectMger);
  m_pCmdMger->addCommand(cmd);
}

bool GraphManager::delSelectShape()
{
  if(!isSelect()) 
    return false;

  Vector<GraphItemShape*> vec = m_selectMger.getShape();
  for(int i = 0; i < vec.size(); i++)
  {
    vec[i]->setVisible(false);
  }

  GraphCommand* cmd = new GraphDelCommand(vec, &m_selectMger);
  m_pCmdMger->addCommand(cmd);

  m_selectMger.clearSelect();
  freshView();
  return true;
}

void GraphManager::setSelectShape(const PointF& pos)
{
  if(setSelectShapeByPos(pos))
  {
    freshView();
  }
}

void GraphManager::setSelectShape(const RectF& rectf)
{
  if(setSelectShapeByRect(rectf))
  {
    freshView();
  }
}

void GraphManager::onMouseLButtonDown(const PointF& scenePos)
{
  m_mouseBeginPos = m_mouseEndPos = scenePos;
  if(isSelect())
  {
    Vector<GraphItemShape*> shapeVec = m_selectMger.getShape();

    for(int i = 0; i < shapeVec.size(); i++) // 判断是否选中控制点
    {
      ControlHandler* handler = shapeVec[i]->getHandlerByPos(scenePos);
      if(handler != nullptr)
      {
        shapeVec[i]->SetSelectHandler(handler);
        m_selectMger.setHandler(handler);
        m_handlerBeginPos = handler->getPos();
        freshView();
        return;
      }
    }

    for(int i = 0; i < shapeVec.size(); i++) // 判断是否选中已选中的图形
    {
      if(shapeVec[i]->isPointUpShape(scenePos))
        return;
    }

    m_selectMger.clearSelect();
    freshView();
    
  }

  if(setSelectShapeByPos(scenePos))
    freshView();

}

void GraphManager::onMouseMove(bool fLButtonDown, const PointF& scenePos)
{
  if(!fLButtonDown) return;

  double xoff = scenePos.x - m_mouseEndPos.x;
  double yoff = scenePos.y - m_mouseEndPos.y;
  m_mouseEndPos = scenePos;
  bool freshWnd = false;
  Vector<GraphItemShape*> vec = m_selectMger.getShape();

  if(m_selectMger.getHandler() != nullptr) // 若在鼠标按下点击控制点，忽略移动操作
  {
    // 移动控制点
    GraphItemShape* shape = m_selectMger.getHandler()->getOwnerShape();
    shape->shapeResizeTo(scenePos, m_selectMger.getHandler());
    freshWnd = true;
  }
  else
  {
    if(isSelect()) // 再判断是否移动
    {
      for(int i = 0; i < vec.size(); i++)
      {
        vec[i]->move(xoff, yoff);
      }
      freshWnd = true;
    }
  }

  if(freshWnd)
    freshView();
}

void GraphManager::onMouseLButtonUp(const PointF& scenePos)
{
  m_mouseEndPos = scenePos;
  GraphCommand* cmd = nullptr;
  if(m_selectMger.getHandler() != nullptr) // 移动控制点操作
  {
    ControlHandler* handler = m_selectMger.getHandler();
    cmd = new GraphHandlerCommand(handler, &m_selectMger, m_handlerBeginPos, m_mouseEndPos);
    m_selectMger.setHandler(nullptr);
  }
  else if(isSelect())
  {
    Vector<GraphItemShape*> shapeVec = m_selectMger.getShape();
    cmd = new GraphMoveCommand(shapeVec, &m_selectMger, 
                               m_mouseEndPos.x - m_mouseBeginPos.x, 
                               m_mouseEndPos.y - m_mouseBeginPos.y);
  }

  if(cmd != nullptr)
    m_pCmdMger->addCommand(cmd);

}

void GraphManager::freshView()
{
  InvalidateRect(m_hWnd, NULL, false);
}

bool GraphManager::setSelectShapeByPos(const PointF& pos)
{
  bool ret = false; // 判断选中图形是否发生改变
  if(isSelect()) ret = true;
  m_selectMger.clearSelect();

  for(int i = m_shapeVec.size() - 1; i >= 0; i--)  // 倒序遍历，选中最上层
  {
    if(!m_shapeVec[i]->isVisible()) continue;
    if(m_shapeVec[i]->isPointUpShape(pos))
    {
      m_selectMger.addShape(m_shapeVec[i]);
      ret = true;
      break;
    }
  }

  return ret;
}

bool GraphManager::setSelectShapeByRect(const RectF& rectf)
{
  bool ret = false; // 判断选中图形是否发生改变
  if(isSelect()) ret = true;
  m_selectMger.clearSelect();

  for(int i = 0; i < m_shapeVec.size(); i++)
  {
    if(!m_shapeVec[i]->isVisible()) continue;
    if(m_shapeVec[i]->isRectCrossShape(rectf))
    {
      m_selectMger.addShape(m_shapeVec[i]);
      ret = true;
    }
  }

  return ret;
}