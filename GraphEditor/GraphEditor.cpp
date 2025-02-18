#include "GraphEditor.h"
#include "GraphEditor_def.h"
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
  delete m_pSBDlg;
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
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
    100, 50, 1200, 800,
    m_hParent,
    m_hMenu = LoadMenu(m_hIns, MAKEINTRESOURCE(IDC_GRAPHEDITOR)),
    m_hIns,
    this);
 
  m_hAccel = LoadAccelerators(m_hIns, MAKEINTRESOURCE(IDC_GRAPHEDITOR));
  ShowWindow(m_hWnd, SW_SHOW);
  
  m_ptoolBar->init();
  m_pGView->init();
  m_pSBDlg->init();
  setTitle();
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
      GE->m_pSBDlg = new ShapeBoardDlg(GE->m_hIns, hwnd);

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
  case GE_SB_HIDE:
  {
    m_pSBDlg->showDialog(false);
    m_ptoolBar->checkButton(BT_DASHBOARD);
    break;
  }
  case GE_SB_DATACHANGE:
  {
    ShapeProperty shapeProperty = m_pSBDlg->getShapeProperty();
    m_pGView->setShapeProperty(shapeProperty);
    break;
  }
    
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }
  return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

bool GraphEditor::translateAccelator(MSG* lpMsg)
{
  if(m_hMenu == NULL || m_hAccel == NULL)
    return false;
  return TranslateAccelerator(m_hWnd, m_hAccel, lpMsg);
}

void GraphEditor::onSize(WPARAM wParam, LPARAM lParam)
{
  int x = LOWORD(lParam);
  int y = HIWORD(lParam);

  m_ptoolBar->resize();
 
  int toolH = m_ptoolBar->getHeight();
  m_pGView->resize(x, y - toolH);

  InvalidateRect(m_hWnd, NULL, true);
}

void GraphEditor::onCommand(WPARAM wParam, LPARAM lParam)
{
 /* ConsoleDebug((int)(wParam));
  ConsoleDebug(L"\n", 1);*/
  switch(LOWORD(wParam))
  {
  case BT_EDITMODE:
    m_ptoolBar->checkButton(BT_EDITMODE);
    m_pGView->setMode(ToolType::EDIT_MOUSE);
    break;
  case BT_LINE:
    m_ptoolBar->checkButton(BT_LINE);
    m_pGView->setMode(ToolType::DRAW_LINE);
    break;
  case BT_POLYLINE:
    m_ptoolBar->checkButton(BT_POLYLINE);
    m_pGView->setMode(ToolType::DRAW_POLYLINE);
    break;
  case BT_BEZIER:
    m_ptoolBar->checkButton(BT_BEZIER);
    m_pGView->setMode(ToolType::DRAW_BEZIER);
    break;
  case BT_CIRCLE:
    m_ptoolBar->checkButton(BT_CIRCLE);
    m_pGView->setMode(ToolType::DRAW_CIRCLE);
    break;
  case BT_ELLIPTIC:
    m_ptoolBar->checkButton(BT_ELLIPTIC);
    m_pGView->setMode(ToolType::DRAW_ELLIPTIC);
    break;
  case BT_RECTANGLE:
    m_ptoolBar->checkButton(BT_RECTANGLE);
    m_pGView->setMode(ToolType::DRAW_RECTANGLE);
    break;
  case BT_DASHBOARD:
    m_ptoolBar->checkButton(BT_DASHBOARD);
    m_pSBDlg->showDialog(true);
    break;
  case IDM_SAVE:
    onSave();
    break;
  case IDM_OPEN:
    onOpen();
    break;
  case IDM_COPY:
    onCopy();
    break;
  case IDM_CUT:
    onCut();
    break;
  case IDM_PASTE:
    onPaste();
    break;
  case IDM_UNDO:
    onUndo();
    break;
  case IDM_REDO:
    onRedo();
    break;
  }
}

void GraphEditor::onSave()
{
  OPENFILENAME opfn;
  WCHAR strFilename[MAX_PATH] = L"*.ge";//存放文件名

  ZeroMemory(&opfn, sizeof opfn);
  opfn.lStructSize = sizeof opfn;
  opfn.lpstrFilter = L"自定义文件\0*.ge\0";
  opfn.lpstrFile = strFilename;
  opfn.nMaxFile = sizeof(strFilename);
  //设置标志位，检查目录或文件是否存在
  opfn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

  if(GetSaveFileName(&opfn) != 0)
  {
    bool ret = m_pGView->save(strFilename);
    if(ret)
    {
      unSaved = false;
      memcpy(m_szFilename, strFilename, lstrlen(strFilename)*sizeof(TCHAR));
      setTitle();
    }
  }
}

void GraphEditor::onOpen()
{
  OPENFILENAME opfn;
  WCHAR strFilename[MAX_PATH] = L"*.ge";//存放文件名

  ZeroMemory(&opfn, sizeof opfn);
  opfn.lStructSize = sizeof opfn;
  opfn.lpstrFilter = L"自定义文件\0*.ge\0";
  opfn.lpstrFile = strFilename;
  opfn.nMaxFile = sizeof(strFilename);
  //设置标志位，检查目录或文件是否存在
  opfn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

  if(GetOpenFileName(&opfn) != 0)
  {
    bool fSuccess = m_pGView->open(strFilename);
    if(fSuccess)
    {
      unSaved = false;
      memcpy(m_szFilename, strFilename, lstrlen(strFilename) * sizeof(TCHAR));
      setTitle();
    }
 
  }
}

void GraphEditor::onCopy()
{
  m_pGView->copy();
}

void GraphEditor::onCut()
{
  if(m_pGView->cut())
  {
    unSaved = true;
    setTitle();
  }
}

void GraphEditor::onPaste()
{
  if(m_pGView->paste())
  {
    unSaved = true;
    setTitle();
  }
}

void GraphEditor::onUndo()
{
  if(m_pGView->undo())
  {
    unSaved = true;
    setTitle();
  }
}

void GraphEditor::onRedo()
{
  if(m_pGView->redo())
  {
    unSaved = true;
    setTitle();
  }
}

void GraphEditor::setTitle()
{
  Vector<TCHAR> title;
  if(unSaved)
  {
    title.push_back('*');
  }
  for(int i = 0; i < lstrlen(m_szFilename); i++)
  {
    title.push_back(m_szFilename[i]);
  }
  title.push_back(NULL);
  SetWindowText(m_hWnd, title.data());
}