#include "GraphView.h"
#include "windowsx.h"
#include "ConSoleDebug.h"

GraphView::GraphView(HINSTANCE hIns, HWND hParent)
{
  Window::init(hIns, hParent);
}

GraphView::~GraphView()
{
  delete m_pGhMger;
  delete m_pSbMger;
  delete m_pToolMger;
  DeleteObject(m_hBgdBru);
  destroy();
}

void GraphView::init()
{

  m_hBgdBru =CreateSolidBrush(RGB(255,255,255));
  WNDCLASS WC = { 0 };
  WC.cbClsExtra = 0;
  WC.cbWndExtra = 0;
  WC.hbrBackground = m_hBgdBru;
  WC.hCursor = NULL;
  WC.hIcon = NULL;
  WC.hInstance = m_hIns;
  WC.lpfnWndProc = WinProc;
  WC.lpszClassName = L"GraphView";
  WC.lpszMenuName = NULL;
  WC.style = CS_HREDRAW | CS_VREDRAW;
  RegisterClass(&WC);
  m_hWnd = CreateWindow(TEXT("GraphView"),
    TEXT("GraphView"),
    WS_VISIBLE|WS_CHILD|WS_BORDER|WS_HSCROLL|WS_VSCROLL|WS_CLIPSIBLINGS,
    0, 28,
    1184, 714,
    m_hParent,
    NULL,
    m_hIns,
    this);

  ShowWindow(m_hWnd, SW_SHOW);
}

void GraphView::destroy()
{
  if(m_hWnd)
  {
    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, 0);
    DestroyWindow(m_hWnd);
    m_hWnd = nullptr;
  }
}

void GraphView::resize(int w,int h)
{
  MoveWindow(m_hWnd, 0, 28, w, h, false);
  
  if(m_pSbMger && m_pGhMger)
  {
    m_pSbMger->setHBar(w, m_pGhMger->getWidth());
    m_pSbMger->setVBar(h, m_pGhMger->getHeight());
  }
}

void GraphView::setMode(ToolType toolType)
{
  m_pToolMger->setToolType(toolType);
}

PointF GraphView::mapToScene(const POINT &viewPos)
{
  PointF centerPos = { (double)getWidth() / 2,(double)getHeight() / 2 };
  PointF viewRawPos;  // 解缩放
  viewRawPos.x = (viewPos.x - centerPos.x)/m_scale + centerPos.x;
  viewRawPos.y = (viewPos.y - centerPos.y)/m_scale + centerPos.y;

  int xPos = m_pSbMger->getHBarPos();
  int yPos = m_pSbMger->getVBarPos();

  int xoff = xPos * m_pSbMger->getUnitW() - m_pGhMger->getWidth() / 2;
  int yoff = yPos * m_pSbMger->getUnitH() - m_pGhMger->getHeight() / 2;

  PointF retPos;
  retPos.x = viewRawPos.x + xoff;
  retPos.y = viewRawPos.y + yoff;

  return retPos;
}

POINT GraphView::mapToView(const PointF& scenePos)
{
  int xPos = m_pSbMger->getHBarPos();
  int yPos = m_pSbMger->getVBarPos();

  int xoff = xPos * m_pSbMger->getUnitW() - m_pGhMger->getWidth() / 2;
  int yoff = yPos * m_pSbMger->getUnitH() - m_pGhMger->getHeight() / 2;

  PointF viewRawPos;
  viewRawPos.x = scenePos.x - xoff;
  viewRawPos.y = scenePos.y - yoff;

  PointF centerPos = { (double)getWidth() / 2,(double)getHeight() / 2 };
  PointF retPos; // 缩放
  retPos.x = m_scale * (viewRawPos.x - centerPos.x) + centerPos.x;
  retPos.y = m_scale * (viewRawPos.y - centerPos.y) + centerPos.y;
  return retPos.toPoint();
} 

LRESULT CALLBACK GraphView::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch(uMsg)
  {
    case WM_NCCREATE:
    {
      GraphView* GE = static_cast<GraphView*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);

      GE->m_hWnd = hwnd;
      if(!GE->m_pGhMger) GE->m_pGhMger = new GraphManager(hwnd);
      if(!GE->m_pSbMger) GE->m_pSbMger = new ScrollBarManager(hwnd);
      if(!GE->m_pToolMger) GE->m_pToolMger = new ToolManager();
      GE->m_pSbMger->init(200, 200);

      SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(GE));
      break;
    }
    default:
      GraphView* GE = reinterpret_cast<GraphView*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
      if(GE) return GE->runProc(uMsg, wParam, lParam);
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK GraphView::runProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  ConsoleDebugMessage(uMsg);
  ConsoleDebug(L"\n", 1);
  switch (uMsg)
  {
  case WM_LBUTTONDOWN:
    onMouseLButtonDown(wParam, lParam);
    break;
  case WM_LBUTTONUP:
    onMouseLButtonUp(wParam, lParam);
    break;
  case WM_RBUTTONDOWN:
    onMouseRButtonDown(wParam, lParam);
    break;
  case WM_MOUSEMOVE:
    onMouseMove(wParam, lParam);
    break;
  case WM_MOUSEWHEEL:
    onMouseWheel(wParam, lParam);
    break;
  case WM_PAINT:
    onPaint();
    break;
  case WM_CREATE:
    onCreate();
    break;
  case WM_SETCURSOR:
    onSetCursor(lParam);
    return true;
  case WM_HSCROLL:
    m_pSbMger->onWMHScroll(wParam,lParam);
    break;
  case WM_VSCROLL:
    m_pSbMger->onWMVScroll(wParam,lParam);
    break;
  }
  return DefWindowProc(m_hWnd,uMsg, wParam, lParam);
}

void GraphView::onCreate()
{
  int xClient = getWidth();
  int yClient = getHeight();

  if(m_pSbMger && m_pGhMger)
  {
    m_pSbMger->setHBar(xClient, m_pGhMger->getWidth());
    m_pSbMger->setVBar(yClient, m_pGhMger->getHeight());

    POINT pos = mapToView({ 400,400 });
    m_pSbMger->scrollToPos(pos);
  }
 
}

void GraphView::onPaint()
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hWnd, &ps);

  int xClient = getWidth();
  int yClient = getHeight();

  int mapW = xClient / m_scale;
  int mapH = yClient / m_scale;

  HDC hdcMem = CreateCompatibleDC(hdc);
  HBITMAP hbmMem = CreateCompatibleBitmap(hdcMem, mapW, mapH);
  SelectObject(hdcMem, hbmMem);
  RECT rec = { 0,0,mapW,mapH };

  PointF beginPos = mapToScene({ 0,0 });
  PointF endPos = mapToScene({ xClient,yClient });

  RectF updateRecf;
  updateRecf.left = beginPos.x;
  updateRecf.top = beginPos.y;
  updateRecf.right = endPos.x;
  updateRecf.bottom = endPos.y;

  FillRect(hdcMem, &rec, m_hBgdBru);
  m_pGhMger->paint(hdcMem, updateRecf,m_scale);
  
  StretchBlt(hdc, 0, 0, xClient, yClient,
             hdcMem, 0, 0, mapW, mapH, SRCCOPY);
  //BitBlt(hdc, x * boardW, y * boardH, min(xClient, (x + 1) * boardW), min(yClient, (y + 1) * boardH), hdcMem, 0, 0, SRCCOPY);

  DeleteObject(hbmMem);
  DeleteDC(hdcMem);
  EndPaint(m_hWnd, &ps);
}

void GraphView::onSetCursor(LPARAM lParam)
{
  POINT cursorPos;
  GetCursorPos(&cursorPos);
  ScreenToClient(m_hWnd, &cursorPos);

  if(m_pToolMger->getToolType() == ToolType::EDIT_MOUSE)
  {
    SetCursor(m_pGhMger->getCursor(mapToScene(cursorPos)));
  }
  else
  {
    SetCursor(LoadCursor(NULL, IDC_CROSS));
  }
}
  
void GraphView::onMouseLButtonDown(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);
  m_startPos = mapToScene({ x,y });
  
  if(isDrawing)
  {
    if(m_pToolMger->getToolType() == DRAW_POLYLINE)
      drawNext({ x,y });
  }
  else
  {
    m_pGhMger->onMouseLButtonDown(mapToScene({ x,y }), m_pToolMger->getToolType() == EDIT_MOUSE);

    if(!m_pGhMger->isSelect())
      startDraw({ x,y });
  }

}

void GraphView::onMouseLButtonUp(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);
  ToolType nowType = m_pToolMger->getToolType();
  
  if(isDrawing)
  {
    if(nowType == DRAW_BEZIER)
      drawNext({ x,y });
    else if(nowType != DRAW_POLYLINE)
    {
      endDraw({ x,y });
    }
  }
  else if(m_pGhMger->isSelect())
  {
    m_pGhMger->onMouseLButtonUp(mapToScene({ x,y }));
  }
  m_endPos = mapToScene({ x,y });
}

void GraphView::onMouseRButtonDown(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);

  if(isDrawing)
    endDraw({ x,y });
}

void GraphView::onMouseMove(WPARAM wParam, LPARAM lParam)
{
  bool fLButtonDown = (wParam == MK_LBUTTON);
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);

  if(isDrawing)
    onDraw(fLButtonDown, { x,y });
  else if(m_pGhMger->isSelect())
  {
    m_pGhMger->onMouseMove(fLButtonDown, mapToScene({ x,y }));
  }
  m_endPos = mapToScene({x,y});
}

void GraphView::onMouseWheel(WPARAM wParam, LPARAM lParam)
{
  int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
  int zPos = zDelta / WHEEL_DELTA;

  bool fCtrlDown = (GetKeyState(VK_CONTROL) < 0);
  if(fCtrlDown)
  {
    double preScale = m_scale;

    if(zPos > 0 && m_scale < 8)
    {
      if(m_scale >= 1) m_scale += 1;
      else m_scale *= 2;
    }
    else if(zPos < 0 && m_scale > 0.25)
    {
      
      if(m_scale > 1) m_scale -= 1;
      else m_scale /= 2;
    }

    if(m_scale != preScale)
    {
      m_pSbMger->setHBar(getWidth() * m_scale, m_pGhMger->getWidth());
      m_pSbMger->setVBar(getHeight() * m_scale, m_pGhMger->getHeight());

      InvalidateRect(m_hWnd, NULL, false);
    }
  }
}

void GraphView::startDraw(const POINT& pos)
{
  isDrawing = true;
  switch(m_pToolMger->getToolType())
  {
    case DRAW_POLYLINE:
    {
      if(!m_pToolMger->isValidShape())
      {
        GraphItemShape* pItemShape = new GraphItemPolyline(mapToScene(pos));
        m_pToolMger->setShape(pItemShape);
        m_pGhMger->addShape(pItemShape);
      }
      InvalidateRect(m_hWnd, NULL, false);
      break;
    }

    case DRAW_BEZIER:
    {
      if(!m_pToolMger->isValidShape())
      {
        GraphItemShape* pItemShape = new GraphItemPolyBezier(mapToScene(pos));
        m_pToolMger->setShape(pItemShape);
        m_pGhMger->addShape(pItemShape);
        m_aptF[0] = m_aptF[1] = m_aptF[2] = m_aptF[3] = mapToScene(pos);
      }
      InvalidateRect(m_hWnd, NULL, false);
      break;
    }
  }

  
}

void GraphView::drawNext(const POINT& pos)
{
  switch(m_pToolMger->getToolType())
  {
    case DRAW_POLYLINE:
    {
      if(m_pToolMger->isValidShape())
        m_pToolMger->updateShape(m_endPos);
      
      InvalidateRect(m_hWnd, NULL, false);
      break;
    }
    case DRAW_BEZIER:
    {
      if(m_pToolMger->isValidShape())
        m_pToolMger->updateShape(m_aptF[1], m_aptF[2], m_aptF[3]);
      m_aptF[0] = m_aptF[3];
     /* m_aptF[1].x = m_aptF[3].x * 2 - m_aptF[2].x;
      m_aptF[1].y = m_aptF[3].y * 2 - m_aptF[2].y;*/
      m_aptF[1]=m_aptF[2] = m_aptF[3];
      InvalidateRect(m_hWnd, NULL, false);
      break;
    }
  }
  
  
}

void GraphView::onDraw(bool fLButtonDown,const POINT& pos)
{
  HDC hdc = GetDC(m_hWnd);
  switch(m_pToolMger->getToolType())
  {
    case DRAW_LINE:
    case DRAW_CIRCLE:
    case DRAW_ELLIPTIC:
    case DRAW_RECTANGLE:
    {
      if(fLButtonDown)
      {
        m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
        m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), pos);
      }
      break;
    }

    case EDIT_MOUSE:
    {
      if(fLButtonDown)
      {
        m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
        m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), pos);
      }
      break;
    }

    case DRAW_POLYLINE:
    {
      if(m_pToolMger->isValidShape())
      {
        m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
        m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), pos);
      }
      break;
    }

    case DRAW_BEZIER:
    {
      if(m_pToolMger->isValidShape())
      {
        PointF posF = mapToScene(pos);
        m_pToolMger->drawRubberBand(hdc, mapToView(m_aptF[0]), mapToView(m_aptF[1]), mapToView(m_aptF[2]), mapToView(m_aptF[3]));
        if(fLButtonDown)
        {
          m_aptF[2].x = 2 * m_aptF[3].x - posF.x;
          m_aptF[2].y = 2 * m_aptF[3].y - posF.y;
        }
        else
        {
          m_aptF[3] = posF;
        }
        m_pToolMger->drawRubberBand(hdc, mapToView(m_aptF[0]), mapToView(m_aptF[1]), mapToView(m_aptF[2]), mapToView(m_aptF[3]));
      }
      break;
    }

  }
  ReleaseDC(m_hWnd, hdc);
}

void GraphView::endDraw(const POINT& pos)
{
  HDC hdc = GetDC(m_hWnd);
  m_endPos = mapToScene(pos);
  
  GraphItemShape* pItemShape = nullptr;
  switch(m_pToolMger->getToolType())
  {
  case EDIT_MOUSE:
    m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
    break;

  case DRAW_LINE:
    m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
    pItemShape = new GraphItemLine(m_startPos, m_endPos);
    break;

  case DRAW_ELLIPTIC:
    m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
    pItemShape = new GraphItemElliptic(m_startPos, m_endPos);
    break;

  case DRAW_RECTANGLE:
    m_pToolMger->drawRubberBand(hdc, mapToView(m_startPos), mapToView(m_endPos));
    pItemShape = new GraphItemRectangle(m_startPos, m_endPos);
    break;

  case DRAW_POLYLINE:
    if(m_pToolMger->isValidShape())
    {
      m_pToolMger->updateShape(m_startPos, mapToScene(pos));
      m_pToolMger->setShape(nullptr);
      InvalidateRect(m_hWnd, NULL, false);
    }
    break;
  case DRAW_BEZIER:
    if(m_pToolMger->isValidShape())
    {
      m_aptF[3] = mapToScene(pos);
      m_pToolMger->updateShape(m_aptF[1], m_aptF[2], m_aptF[3]);
      m_pToolMger->setShape(nullptr);
      InvalidateRect(m_hWnd, NULL, false);
    }
    break;
  }

  if(pItemShape)
  {
    m_pGhMger->addShape(pItemShape);
    InvalidateRect(m_hWnd, NULL, false);
  }

  isDrawing = false;
  ReleaseDC(m_hWnd, hdc);
}