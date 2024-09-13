#include "ScrollBarManager.h"

ScrollBarManager::ScrollBarManager(HWND hwnd)
  :m_hWnd(hwnd)
{

}

void ScrollBarManager::init(int unitH, int unitW)
{
  m_unitH = unitH;
  m_unitW = unitW;
}

void ScrollBarManager::setHBar(int xClient, int mxWidth)
{
  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_ALL;

  GetScrollInfo(m_hWnd, SB_HORZ, &si);
  si.nMin = 0;
  si.nMax = max(1, mxWidth / m_unitW);
  si.nPage = xClient / m_unitW;
  SetScrollInfo(m_hWnd, SB_HORZ, &si, true);
}

void ScrollBarManager::setVBar(int yClient, int mxHeight)
{
  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_RANGE | SIF_PAGE;

  GetScrollInfo(m_hWnd, SB_VERT, &si);
  si.nMin = 0;
  si.nMax = max(1, mxHeight / m_unitH);
  si.nPage = yClient / m_unitH;
  SetScrollInfo(m_hWnd, SB_VERT, &si, true);
}

int ScrollBarManager::setHPos(int hPos)
{
  if(hPos == getHBarPos()) return 0;

  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_RANGE | SIF_POS;
  GetScrollInfo(m_hWnd, SB_HORZ, &si);
  int xpos = si.nPos;
  si.fMask = SIF_POS;
  si.nPos = hPos;
  SetScrollInfo(m_hWnd, SB_HORZ, &si, true);

  GetScrollInfo(m_hWnd, SB_HORZ, &si);
  return si.nPos - xpos;
}

int ScrollBarManager::setVPos(int vPos)
{
  if(vPos == getVBarPos()) return 0;

  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_RANGE | SIF_POS;
  GetScrollInfo(m_hWnd, SB_VERT, &si);
  int ypos = si.nPos;
  si.fMask = SIF_POS;
  si.nPos = vPos;
  SetScrollInfo(m_hWnd, SB_VERT, &si, true);

  GetScrollInfo(m_hWnd, SB_VERT, &si);
  return si.nPos - ypos;
}

int ScrollBarManager::getHBarPos()
{
  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_POS;
  GetScrollInfo(m_hWnd, SB_HORZ, &si);
  return si.nPos;
}

int ScrollBarManager::getVBarPos()
{
  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_POS;
  GetScrollInfo(m_hWnd, SB_VERT, &si);
  return si.nPos;
}

int ScrollBarManager::getUnitW() const
{
  return m_unitW;
}

int ScrollBarManager::getUnitH() const
{
  return m_unitH;
}

void ScrollBarManager::scroll(int dx, int dy)
{
  if(dx == 0 && dy == 0) return;
  int preHPos = getHBarPos();
  int preVPos = getVBarPos();
  int hPos = preHPos + dx;
  int vPos = preVPos + dy;

  if(hPos < 0) hPos = 0;
  if(vPos < 0) vPos = 0;
  int xoff = setHPos(hPos) * m_unitW;
  int yoff = setVPos(vPos) * m_unitH;
  if(xoff == 0 && yoff == 0) return;
  /*ScrollWindow(m_hWnd, -xoff, -yoff, NULL, NULL);
  UpdateWindow(m_hWnd);*/
  InvalidateRect(m_hWnd, NULL, false);
}

void ScrollBarManager::scrollToPos(const POINT& pos)
{
  RECT clientRect;
  GetClientRect(m_hWnd, &clientRect);
  POINT nowCenterPos = { clientRect.right / 2,clientRect.bottom / 2 };

  int dx = (pos.x-nowCenterPos.x) / m_unitW;
  int dy = (pos.y-nowCenterPos.y) / m_unitH;
  scroll(dx, dy);
 
}

void ScrollBarManager::onWMHScroll(WPARAM wParam, LPARAM lParam)
{
  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_ALL;
  GetScrollInfo(m_hWnd, SB_HORZ, &si);
  int xPos = si.nPos;
  switch(LOWORD(wParam))
  {
  case SB_LEFT: //
    si.nPos = 0;
    break;
  case SB_RIGHT:
    si.nPos = si.nMax;
    break;
  case SB_LINELEFT: // 用户点击左箭头
    si.nPos--;
    break;
  case SB_LINERIGHT:// 用户点击右键头
    si.nPos++;
    break;
  case SB_THUMBTRACK:// 用户拖拽
    si.nPos = si.nTrackPos;
    break;
  }
  si.fMask = SIF_POS;
  SetScrollInfo(m_hWnd, SB_HORZ, &si, TRUE);
  GetScrollInfo(m_hWnd, SB_HORZ, &si);
  if(xPos != si.nPos)// 说明发生了变化
  {
    // 
    InvalidateRect(m_hWnd,NULL, false);
   /* ScrollWindow(m_hWnd, (xPos - si.nPos) * m_unitW, 0, NULL, NULL);
    UpdateWindow(m_hWnd);*/
  }
}

void ScrollBarManager::onWMVScroll(WPARAM wParam, LPARAM lParam)
{
  SCROLLINFO si;
  si.cbSize = sizeof si;
  si.fMask = SIF_ALL;
  GetScrollInfo(m_hWnd, SB_VERT, &si);
  int yPos = si.nPos;
  switch(LOWORD(wParam))
  {
  case SB_TOP:
    si.nPos = 0;
    break;
  case SB_BOTTOM:
    si.nPos = si.nMax;
    break;
  case SB_LINEUP:// 上箭头
    si.nPos--;
    break;
  case SB_LINEDOWN:// 下箭头
    si.nPos++;
    break;
  case SB_THUMBTRACK:// 拖拽
    si.nPos = si.nTrackPos;
    break;
  }
  si.fMask = SIF_POS;
  SetScrollInfo(m_hWnd, SB_VERT, &si, TRUE);
  GetScrollInfo(m_hWnd, SB_VERT, &si);
  if(yPos != si.nPos)// 说明发生了变化
  {
    InvalidateRect(m_hWnd, NULL, false);
   /* ScrollWindow(m_hWnd, 0, (yPos - si.nPos) * m_unitH, NULL, NULL);
    UpdateWindow(m_hWnd);*/
  }
}








