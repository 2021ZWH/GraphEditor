#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

class Window
{
public:
  Window() = default;
  virtual ~Window() = default;

  virtual void init(HINSTANCE hIns,HWND hParent)
  {
    m_hParent = hParent;
    m_hIns = hIns;
  }

  virtual int getWidth() const
  {
    RECT rect;
    GetClientRect(m_hWnd, &rect);
    return rect.right;
  }

  virtual int getHeight() const
  {
    RECT rect;
    GetClientRect(m_hWnd, &rect);
    return rect.bottom;
  }

  HWND getHWnd() const
  {
    return m_hWnd;
  }

  HWND getHParent() const
  {
    return m_hParent;
  }

  HINSTANCE getHInst() const
  {
    return m_hIns;
  }

protected:
  HWND m_hParent = nullptr;
  HWND m_hWnd = nullptr;
  HINSTANCE m_hIns = nullptr;

};
#endif// WINDOW_H