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
  destroy();
}

void GraphView::init()
{

  WNDCLASS WC = { 0 };
  WC.cbClsExtra = 0;
  WC.cbWndExtra = 0;
  WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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

  m_viewPoint = { 1184 / 2,714 / 2 };
 
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
  m_viewPoint = { w / 2,h / 2 };
  if(m_pSbMger && m_pGhMger)
  {
    m_pSbMger->setHBar(w, m_pGhMger->getWidth());
    m_pSbMger->setVBar(h, m_pGhMger->getHeight());
  }
}

POINT GraphView::mapToScene(const POINT &viewPos)
{
  int xPos = m_pSbMger->getHBarPos();
  int yPos = m_pSbMger->getVBarPos();

  int xoff = xPos * m_pSbMger->getUnitW() - m_pGhMger->getWidth() / 2;
  int yoff = yPos * m_pSbMger->getUnitH() - m_pGhMger->getHeight() / 2;

  POINT retPos;
  retPos.x = viewPos.x + xoff;
  retPos.y = viewPos.y + yoff;

  return retPos;
}
POINT GraphView::mapToView(const POINT& scenePos)
{
  int xPos = m_pSbMger->getHBarPos();
  int yPos = m_pSbMger->getVBarPos();

  int xoff = xPos * m_pSbMger->getUnitW() - m_pGhMger->getWidth() / 2;
  int yoff = yPos * m_pSbMger->getUnitH() - m_pGhMger->getHeight() / 2;

  POINT retPos;
  retPos.x = scenePos.x - xoff;
  retPos.y = scenePos.y - xoff;
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
  case WM_MOUSEWHEEL:
    onMouseWheel(wParam, lParam);
    break;
	case WM_PAINT:
		onPaint();
		break;
  case WM_CREATE:
    onCreate();
    break;
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

  int boardW = 1000;
  int boardH = 1000;

  HDC hdcMem = CreateCompatibleDC(hdc);
  HBITMAP hbmMem = CreateCompatibleBitmap(hdcMem, boardW, boardH);
  SelectObject(hdcMem, hbmMem);
  RECT rec = { 0,0,boardW,boardH };
  HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

  int xClient = getWidth();
  int yClient = getHeight();

  // 这里要分块去重绘，减少花屏
  for(int x = 0; x * boardW < xClient; x++)
  {
    for(int y = 0; y* boardH < yClient; y++)
    {
      POINT beginPos = mapToScene({ x* boardW,y* boardH });
      POINT endPos = mapToScene({ min(xClient,(x + 1) * boardW),min(yClient,(y + 1) * boardH) });

      RECT updateRec;
      updateRec.left = beginPos.x;
      updateRec.top = beginPos.y;
      updateRec.right = endPos.x;
      updateRec.bottom = endPos.y;

      FillRect(hdcMem, &rec, hBrush);
      m_pGhMger->paint(hdcMem, updateRec);
                     
      BitBlt(hdc, x * boardW, y * boardH, min(xClient, (x + 1) * boardW), min(yClient, (y + 1) * boardH), hdcMem, 0, 0, SRCCOPY);
    }
  }

  DeleteObject(hbmMem);
  DeleteDC(hdcMem);
  EndPaint(m_hWnd, &ps);
}

void GraphView::onMouseLButtonDown(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);
  ConsoleDebug(x);
  ConsoleDebug(L" ", 1);
  ConsoleDebug(y);
  ConsoleDebug(L"\n", 1);
	HDC hdc = GetDC(m_hWnd);
  HBRUSH hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
  HBRUSH oldHbr = (HBRUSH)SelectObject(hdc, hbr);
	Rectangle(hdc, x, y, x + 40, y + 40);//画图
  SelectObject(hdc,oldHbr);
	ReleaseDC(m_hWnd, hdc);
}

void GraphView::onMouseWheel(WPARAM wParam, LPARAM lParam)
{
 /* int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
  m_scale *=  1+(double)( - zDelta / 120)/10;
  InvalidateRect(m_hWnd, NULL, false);*/
}