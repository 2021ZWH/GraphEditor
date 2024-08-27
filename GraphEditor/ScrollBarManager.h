#ifndef SCROLLBAR_MANAGER_H
#define SCROLLBAR_MANAGER_H

#include<Windows.h>

class ScrollBarManager
{
public:
  ScrollBarManager(HWND hwnd);
  void  init(int lineH, int m_unitW);
  void  setHBar(int xClient, int mxWidth);
  void  setVBar(int yClient, int mxHeight);
  int   setHPos(int hPos);
  int   setVPos(int vPos);
  int   getHBarPos();
  int   getVBarPos();
  int   getUnitW() const;
  int   getUnitH() const;
  // 向右(左）滚 dx（-dx)个单位，向下(上)滚dy(-dy)个单位
  void  scroll(int dx, int dy);
  void  scrollToPos(const POINT& pos);
  void  onWMHScroll(WPARAM wParam, LPARAM lParam);
  void  onWMVScroll(WPARAM wParam, LPARAM lParam);
private:
  HWND  m_hWnd;
  int   m_unitH;
  int   m_unitW;
};

#endif // SCROLLBAR_MANAGER_H

