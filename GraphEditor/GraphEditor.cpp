#include "GraphEditor.h"
#include "resource.h"
#include "ConSoleDebug.h"

GraphEditor::GraphEditor(HINSTANCE hIns, HWND hParent)
{
  Window::init(hIns, hParent);
}

GraphEditor::~GraphEditor()
{
  delete m_pGView;
  delete m_ptoolBar;
  destroy();
}

void GraphEditor::init()
{
  WNDCLASS WC = { 0 };
  WC.cbClsExtra = 0;
  WC.cbWndExtra = 0;
  WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  WC.hCursor = NULL;
  WC.hIcon = NULL;
  WC.hInstance = m_hIns;
  WC.lpfnWndProc = WinProc;
  WC.lpszClassName = L"GraphEditor";
  WC.lpszMenuName = NULL;
  WC.style = CS_HREDRAW | CS_VREDRAW;
  RegisterClass(&WC);
  m_hWnd = CreateWindow(TEXT("GraphEditor"),
    TEXT("GraphEditor"),
    WS_OVERLAPPEDWINDOW| WS_CLIPCHILDREN| WS_CLIPSIBLINGS,
    100, 50, 1200, 800,
    m_hParent,
    LoadMenu(m_hIns,MAKEINTRESOURCE(IDC_GRAPHEDITOR)),
    m_hIns,
    this);
 

  ShowWindow(m_hWnd, SW_SHOW);
  
  m_ptoolBar->init();
  m_pGView->init();

}

void GraphEditor::destroy()
{
  if(m_hWnd != nullptr)
  {
    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, 0);
    DestroyWindow(m_hWnd);
    m_hWnd = nullptr;
  }
}
 
LRESULT CALLBACK GraphEditor::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_NCCREATE:
    {
      GraphEditor* GE = static_cast<GraphEditor*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);

      GE->m_hWnd = hwnd;
      GE->m_ptoolBar = new ToolBar(GE->m_hIns, hwnd);
      GE->m_pGView = new GraphView(GE->m_hIns, hwnd);

      SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(GE));
      break;
    }
    default:
      GraphEditor* GE = reinterpret_cast<GraphEditor*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
      if(GE) return GE->runProc(uMsg, wParam, lParam);
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK GraphEditor::runProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  ConsoleDebugMessage(uMsg);
  ConsoleDebug(L"\n", 1);
  switch (uMsg)
  {
  case WM_COMMAND:
    onCommand(wParam, lParam);
    break;
  case WM_SIZE:
    onSize(wParam,lParam);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }
  return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void GraphEditor::onSize(WPARAM wParam, LPARAM lParam)
{
  int x = LOWORD(lParam);
  int y = HIWORD(lParam);

  m_ptoolBar->resize();
 
  int toolH = m_ptoolBar->getHeight();
  m_pGView->resize(x, y - toolH);

}

void GraphEditor::onCommand(WPARAM wParam, LPARAM lParam)
{
  ConsoleDebug((int)(wParam));
  ConsoleDebug(L"\n", 1);
  switch(wParam)
  {
  case BT_EDITMODE:
    m_pGView->setMode(ToolType::EDIT_MOUSE);
    break;
  case BT_RECTANGLE:
    m_pGView->setMode(ToolType::DRAW_RECTANGLE);
    break;
  }
}