#include "GraphView.h"
#include "windowsx.h"
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
    WS_VISIBLE|WS_CHILD,
    0, 29
    , 1184, 784,
    m_hParent,
    NULL,
    m_hIns,
    this);

  ShowWindow(m_hWnd, SW_SHOW);
}
void GraphView::destroy()
{
  if (m_hWnd)
  {
    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, 0);
    DestroyWindow(m_hWnd);
    m_hWnd = nullptr;
  }
}
LRESULT CALLBACK GraphView::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch(uMsg)
  {
    case WM_NCCREATE:
    {
      GraphView* GE = static_cast<GraphView*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);
      GE->m_hWnd = hwnd;
      if (!GE->m_pGhMger) GE->m_pGhMger = new GraphManager(hwnd);

      SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(GE));
      break;
    }
    default:
      GraphView* GE = reinterpret_cast<GraphView*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
      if (GE) return GE->runProc(uMsg, wParam, lParam);
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK GraphView::runProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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
  }
  return DefWindowProc(m_hWnd,uMsg, wParam, lParam);
}
void GraphView::onPaint()
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hWnd, &ps);
  
  int boardWidth  = getWidth() * m_scale;
  int boardHeight = getHeight() * m_scale;

  RECT updateRec;
  updateRec.left  = m_viewPoint.x;
  updateRec.top   = m_viewPoint.y;
  updateRec.right = m_viewPoint.x + boardWidth;
  updateRec.bottom = m_viewPoint.y + boardHeight;

  HDC hdcMem = CreateCompatibleDC(hdc);
  HBITMAP hbmMem = CreateCompatibleBitmap(hdcMem, boardWidth, boardHeight);
  SelectObject(hdcMem, hbmMem);
  RECT rec = { 0,0,boardWidth,boardHeight };
  HBRUSH hBrush =(HBRUSH)GetStockObject(WHITE_BRUSH);
  FillRect(hdcMem, &rec,hBrush);

  m_pGhMger->paint(hdcMem, updateRec);

  StretchBlt(hdc, 0, 0, getWidth(), getHeight(),
            hdcMem, 0, 0, boardWidth, boardHeight, SRCCOPY);

  DeleteObject(hbmMem);
  DeleteDC(hdcMem);
  EndPaint(m_hWnd, &ps);
}
void GraphView::onMouseLButtonDown(WPARAM wParam, LPARAM lParam)
{
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);

	HDC hdc = GetDC(m_hWnd);
	SetBkColor(hdc, RGB(0, 0, 0));// 设置当前背景颜
	Rectangle(hdc, x, y, x + 40, y + 40);//画图

	ReleaseDC(m_hWnd, hdc);
}
void GraphView::onMouseWheel(WPARAM wParam, LPARAM lParam)
{
  int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
  m_scale *=  1+(double)( - zDelta / 120)/10;
  InvalidateRect(m_hWnd, NULL, false);
}