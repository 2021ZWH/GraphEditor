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

POINT GraphView::mapToScene(const POINT &viewPos)
{
  POINT centerPos = { getWidth() / 2,getHeight() / 2 };
  POINT viewRawPos;  // 解缩放
  viewRawPos.x = (viewPos.x - centerPos.x)/m_scale + centerPos.x;
  viewRawPos.y = (viewPos.y - centerPos.y)/m_scale + centerPos.y;

  int xPos = m_pSbMger->getHBarPos();
  int yPos = m_pSbMger->getVBarPos();

  int xoff = xPos * m_pSbMger->getUnitW() - m_pGhMger->getWidth() / 2;
  int yoff = yPos * m_pSbMger->getUnitH() - m_pGhMger->getHeight() / 2;

  POINT retPos;
  retPos.x = viewRawPos.x + xoff;
  retPos.y = viewRawPos.y + yoff;

  return retPos;
}

POINT GraphView::mapToView(const POINT& scenePos)
{
  int xPos = m_pSbMger->getHBarPos();
  int yPos = m_pSbMger->getVBarPos();

  int xoff = xPos * m_pSbMger->getUnitW() - m_pGhMger->getWidth() / 2;
  int yoff = yPos * m_pSbMger->getUnitH() - m_pGhMger->getHeight() / 2;

  POINT viewRawPos;
  viewRawPos.x = scenePos.x - xoff;
  viewRawPos.y = scenePos.y - xoff;

  POINT centerPos = { getWidth() / 2,getHeight() / 2 };
  POINT retPos; // 缩放
  retPos.x = m_scale * (viewRawPos.x - centerPos.x) + centerPos.x;
  retPos.y = m_scale * (viewRawPos.y - centerPos.y) + centerPos.y;
  return retPos;
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
    onSetCursor();
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

  POINT beginPos = mapToScene({ 0,0 });
  POINT endPos = mapToScene({ xClient,yClient });

  RECT updateRec;
  updateRec.left = beginPos.x;
  updateRec.top = beginPos.y;
  updateRec.right = endPos.x;
  updateRec.bottom = endPos.y;

  FillRect(hdcMem, &rec, m_hBgdBru);
  m_pGhMger->paint(hdcMem, updateRec);
  
  StretchBlt(hdc, 0, 0, xClient, yClient,
    hdcMem, 0, 0, mapW, mapH, SRCCOPY);
  //BitBlt(hdc, x * boardW, y * boardH, min(xClient, (x + 1) * boardW), min(yClient, (y + 1) * boardH), hdcMem, 0, 0, SRCCOPY);

  DeleteObject(hbmMem);
  DeleteDC(hdcMem);
  EndPaint(m_hWnd, &ps);
}

void GraphView::onSetCursor()
{
  if(m_pToolMger->getToolType() == ToolType::EDIT_MOUSE)
    SetCursor(LoadCursor(NULL,IDC_ARROW));
  else SetCursor(LoadCursor(NULL, IDC_CROSS));
}
  
void GraphView::onMouseLButtonDown(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);
  
  m_startPos = m_endPos = { x,y };

  m_pGhMger->onMouseLButtonDown(mapToScene({ x,y }));
}

void GraphView::onMouseLButtonUp(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);

  HDC hdc = GetDC(m_hWnd);
  m_pToolMger->drawRubberBand(hdc, m_startPos, m_endPos); 

  m_endPos = { x,y };

  GraphItemShape* pItemShape = nullptr;
  switch(m_pToolMger->getToolType())
  {
    case ToolType::DRAW_RECTANGLE:
      pItemShape = new GraphItemRectangle(mapToScene(m_startPos), mapToScene(m_endPos));
      break;
  }
  
  if(pItemShape)
  {
    m_pGhMger->addShape(pItemShape);
    InvalidateRect(m_hWnd, NULL, false);
  }
  
  ReleaseDC(m_hWnd, hdc);
}

void GraphView::onMouseMove(WPARAM wParam, LPARAM lParam)
{
  if(wParam != MK_LBUTTON) return;

  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);

  HDC hdc = GetDC(m_hWnd);

  m_pToolMger->drawRubberBand(hdc, m_startPos, m_endPos);
  m_endPos = { x,y };
  m_pToolMger->drawRubberBand(hdc, m_startPos, m_endPos);
  
  ReleaseDC(m_hWnd, hdc);

  m_pGhMger->onMouseMove(1, mapToScene({ x,y }));
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