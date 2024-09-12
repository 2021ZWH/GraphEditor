#ifndef SHAPE_BOARD_DIALOG_H
#define SHAPE_BOARD_DIALOG_H

#include "Window.h"
#include <CommCtrl.h>
#include "Vector.h"
#include "GraphEditor_def.h"

class ShapeBoardDlg
  :public Window
{
public:
  ShapeBoardDlg(HINSTANCE hIns, HWND hParent);
  ~ShapeBoardDlg();
  void init();
  void showDialog(bool flag);
  void setShapeProperty(const ShapeProperty &property);
  ShapeProperty getShapeProperty() const;
private:
  static INT_PTR CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
  INT_PTR CALLBACK runProc(UINT message, WPARAM wParam, LPARAM lParam);
  void onCommad(WPARAM wParam, LPARAM lParam);
  bool syncData();
  bool syncBoard();
  COLORREF getColorBySelId(int id);
  int getIdbyColor(COLORREF color);
private:
  HIMAGELIST m_imageList = NULL;
  Vector<HICON> m_bitmapVec;

  ShapeProperty m_shapeProperty;
};

#endif // !SHAPE_BOARD_DIALOG_H



