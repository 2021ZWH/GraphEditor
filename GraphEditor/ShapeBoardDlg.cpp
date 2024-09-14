#include "ShapeBoardDlg.h"
#include "resource.h"
#include "ConSoleDebug.h"

ShapeBoardDlg::ShapeBoardDlg(HINSTANCE hIns, HWND hParent)
{
  Window::init(hIns, hParent);
}

ShapeBoardDlg::~ShapeBoardDlg()
{
  ImageList_Destroy(m_imageList);
  for(int i = 0; i < m_bitmapVec.size(); i++)
    DeleteObject(m_bitmapVec[i]);
  destroy();
}

void ShapeBoardDlg::init()
{
  m_hWnd = CreateDialogParam(m_hIns,
    MAKEINTRESOURCE(IDD_SHAPEBOARD),
    m_hParent,
    DlgProc,
    reinterpret_cast<LPARAM>(this));

  m_imageList = ImageList_Create(80, 20, ILC_COLOR24 | ILC_MASK, 3, 20);

  WORD icoID[] = { IDI_LINEWIDTH0,
                   IDI_LINEWIDTH1,
                   IDI_LINEWIDTH2,
                   IDI_BLACK,
                   IDI_WHITE,
                   IDI_RED,
                   IDI_YELLOW,
                   IDI_BLUE,
                   IDI_GRENE,
                   IDI_TRANSPARENT
  };
  
  for(int i = 0; i < sizeof icoID / sizeof icoID[0]; i++)
  {
    HICON hIcon = LoadIcon(m_hIns, MAKEINTRESOURCE(icoID[i]));
    m_bitmapVec.push_back(hIcon);
    ImageList_AddIcon(m_imageList, hIcon);
  }

  // 初始化线宽组合框
  HWND hwnd = GetDlgItem(m_hWnd, IDC_COMBOEX_LINEWIDTH);
  SendMessage(hwnd, CBEM_SETIMAGELIST, 0, (LPARAM)m_imageList);

  for(int i = 0; i < 3; i++)
  {
    COMBOBOXEXITEM cbi;
    cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
      CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

    cbi.iItem = i;
    cbi.pszText = (LPWSTR)L"";
    cbi.cchTextMax = 0;
    cbi.iImage = i;
    cbi.iSelectedImage = i;
    cbi.iOverlay = i;
    cbi.iIndent = 0;

    SendMessage(hwnd, CBEM_INSERTITEM, 0, (LPARAM)&cbi);
  }
 
  // 初始化线色组合框
  hwnd = GetDlgItem(m_hWnd, IDC_COMBOEX_LINECOLOR);
  SendMessage(hwnd, CBEM_SETIMAGELIST, 0, (LPARAM)m_imageList);

  for(int i = 0; i < 6; i++)
  {
    COMBOBOXEXITEM cbi;
    cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
      CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

    cbi.iItem = i;
    cbi.pszText = (LPWSTR)L"";
    cbi.cchTextMax = 0;
    cbi.iImage = i + 3;
    cbi.iSelectedImage = i + 3;
    cbi.iOverlay = i + 3;
    cbi.iIndent = 0;

    SendMessage(hwnd, CBEM_INSERTITEM, 0, (LPARAM)&cbi);
  }

  // 初始化填充色组合框
  hwnd = GetDlgItem(m_hWnd, IDC_COMBOEX_FILLCOLOR);
  SendMessage(hwnd, CBEM_SETIMAGELIST, 0, (LPARAM)m_imageList);

  for(int i = 0; i < 7; i++)
  {
    COMBOBOXEXITEM cbi;
    cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
      CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

    cbi.iItem = i;
    cbi.pszText = (LPWSTR)L"";
    cbi.cchTextMax = 0;
    cbi.iImage = i + 3;
    cbi.iSelectedImage = i + 3;
    cbi.iOverlay = i + 3;
    cbi.iIndent = 0;

    SendMessage(hwnd, CBEM_INSERTITEM, 0, (LPARAM)&cbi);
  }
  
  syncBoard();
}

void ShapeBoardDlg::destroy()
{
  if(m_hWnd != NULL)
  {
    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, NULL);
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;
  }
}

void ShapeBoardDlg::showDialog(bool flag)
{
  syncBoard();
  ShowWindow(m_hWnd, flag ? SW_SHOW : SW_HIDE);
}

void ShapeBoardDlg::setShapeProperty(const ShapeProperty& property)
{
  m_shapeProperty = property;
}

ShapeProperty ShapeBoardDlg::getShapeProperty() const
{
  return m_shapeProperty;
}

INT_PTR CALLBACK ShapeBoardDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message)
  {
    case WM_INITDIALOG:
    {
      ShapeBoardDlg* pSBDlg = reinterpret_cast<ShapeBoardDlg*>(lParam);
      pSBDlg->m_hWnd = hwnd;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, static_cast<LONG_PTR>(lParam));
      break;
    }

    default:
    {
      ShapeBoardDlg* pSBDlg = reinterpret_cast<ShapeBoardDlg*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
      if(pSBDlg)
        return pSBDlg->runProc(message, wParam, lParam);
    }
  }

  return 0;
}

INT_PTR CALLBACK ShapeBoardDlg::runProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  /*ConsoleDebugMessage(message);
  ConsoleDebug(L"\n", 1);*/
  switch(message)
  {
  case WM_COMMAND:
    onCommad(wParam, lParam);
    return 1;
  }
  return false;
}

void ShapeBoardDlg::onCommad(WPARAM wParam, LPARAM lParam)
{
  /*ConsoleDebug(wParam);
  ConsoleDebug(L"\n", 1);*/
  switch(wParam)
  {
  case IDC_MYICON:
    SendMessage(m_hParent,GE_SB_HIDE, 0, 0);
    break;
  case IDC_BUTTON_APPLY:
    syncData();
    SendMessage(m_hParent, GE_SB_DATACHANGE, 0, 0);
    break;
  }
}

bool ShapeBoardDlg::syncData()
{
  bool dataChanged = false;
  // 线宽
  HWND hCombo = GetDlgItem(m_hWnd, IDC_COMBOEX_LINEWIDTH);
  int selIdx = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
  if(selIdx != CB_ERR && selIdx != m_shapeProperty.lineWidth)
  {
    m_shapeProperty.lineWidth = selIdx;
    dataChanged = true;
  }

  // 线色
  hCombo = GetDlgItem(m_hWnd, IDC_COMBOEX_LINECOLOR);
  selIdx = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
  if(selIdx != CB_ERR && selIdx != getIdbyColor(m_shapeProperty.lineColor))
  {
    m_shapeProperty.lineColor = getColorBySelId(selIdx);
    dataChanged = true;
  }

  // 填充色
  hCombo = GetDlgItem(m_hWnd, IDC_COMBOEX_FILLCOLOR);
  selIdx = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
  if(selIdx == 6)
  {
    if(!m_shapeProperty.fTransparent)
    {
      m_shapeProperty.fTransparent = true;
      dataChanged = true;
    }
  }
  else
  {
    if((selIdx != CB_ERR && selIdx != getIdbyColor(m_shapeProperty.fillColor))
      || m_shapeProperty.fTransparent == true)
    {
      m_shapeProperty.fTransparent = false;
      m_shapeProperty.fillColor = getColorBySelId(selIdx);
      dataChanged = true;
    }
  }
 
  return dataChanged;
}

bool ShapeBoardDlg::syncBoard()
{
  bool boardChanged = false;

  HWND hCombo = GetDlgItem(m_hWnd, IDC_COMBOEX_LINEWIDTH);
  int selIdx = SendMessageW(hCombo, CB_GETCURSEL, 0, 0);
  if(selIdx != m_shapeProperty.lineWidth || selIdx == CB_ERR)
  {
    SendMessage(hCombo, CB_SETCURSEL, m_shapeProperty.lineWidth, 0);
    boardChanged = true;
  }

  hCombo = GetDlgItem(m_hWnd, IDC_COMBOEX_LINECOLOR);
  selIdx = SendMessageW(hCombo, CB_GETCURSEL, 0, 0);
  if(selIdx != getIdbyColor(m_shapeProperty.lineColor) || selIdx == CB_ERR)
  {
    SendMessage(hCombo, CB_SETCURSEL, getIdbyColor(m_shapeProperty.lineColor), 0);
    boardChanged = true;
  }

  hCombo = GetDlgItem(m_hWnd, IDC_COMBOEX_FILLCOLOR);
  selIdx = SendMessageW(hCombo, CB_GETCURSEL, 0, 0);
  int curIdx = getIdbyColor(m_shapeProperty.fillColor);
  if(m_shapeProperty.fTransparent)
  {
    if(selIdx != 6)
    {
      SendMessage(hCombo, CB_SETCURSEL, 6, 0);
      boardChanged = true;
    }
  }
  else
  {
    if(selIdx != curIdx || selIdx == CB_ERR)
    {
      SendMessage(hCombo, CB_SETCURSEL, curIdx, 0);
      boardChanged = true;
    }
  }
  return boardChanged;
}

COLORREF ShapeBoardDlg::getColorBySelId(int id)
{
  if(id < 0) return 0xff000000;

  switch(id)
  {
  case 0:
    return BGR_BLACK;
  case 1:
    return BGR_WHITE;
  case 2:
    return BGR_RED;
  case 3:
    return BGR_YELLOW;
  case 4:
    return BGR_BLUE;
  case 5:
    return BGR_GREEN;
  }

  return 0xff000000;
}

int ShapeBoardDlg::getIdbyColor(COLORREF color)
{
  if(color > 0xffffff) return -1;

  switch(color)
  {
  case BGR_BLACK:
    return 0;
  case BGR_WHITE:
    return 1;
  case BGR_RED:
    return 2;
  case BGR_YELLOW:
    return 3;
  case BGR_BLUE:
    return 4;
  case BGR_GREEN:
    return 5;
  }

  return -1;
}