#include "Window.h"

class EditBox
  :public Window
{
public:
  EditBox(HINSTANCE hIns, HWND hParent);
  ~EditBox();
  TCHAR* getStr();
  int getStrLen() const;
private:
  static INT_PTR CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
  INT_PTR CALLBACK runProc(UINT message, WPARAM wParam, LPARAM lParam);
  void onCommand(WPARAM wParam, LPARAM lParam);

private:
  TCHAR* m_Text = nullptr;
  int m_textLen;
};

