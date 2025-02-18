#include "EditBox.h"
#include "resource.h"

EditBox::EditBox(HINSTANCE hIns, HWND hParent)
{
  Window::init(hIns, hParent);

   DialogBoxParam(m_hIns,
    MAKEINTRESOURCE(IDD_TEXTINPUT),
    m_hParent,
    DlgProc,
    reinterpret_cast<LPARAM>(this));
}

EditBox::~EditBox()
{
  if(m_Text)
    delete m_Text;
}

INT_PTR CALLBACK EditBox::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message)
  {
    case WM_INITDIALOG:
    {
      EditBox* pEditBox = reinterpret_cast<EditBox*>(lParam);
      pEditBox->m_hWnd = hwnd;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, static_cast<LONG_PTR>(lParam));
      break;
    }

    default:
    {
      EditBox* pEditBox = reinterpret_cast<EditBox*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
      if(pEditBox)
        return pEditBox->runProc(message, wParam, lParam);
    }
  }
}

INT_PTR CALLBACK EditBox::runProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message)
  {
  case WM_COMMAND:
    onCommand(wParam, lParam);
    return true;
  default:
    break;
  }

  return false;
}

void EditBox::onCommand(WPARAM wParam, LPARAM lParam)
{
  switch(wParam)
  {
    case IDOK:
    {
      HWND editHwnd = GetDlgItem(m_hWnd, IDC_EDIT);

      m_textLen = GetWindowTextLength(editHwnd);

      if(m_textLen)
        m_Text = new TCHAR[m_textLen + 1];

      if(m_Text)
        GetWindowText(editHwnd, m_Text, m_textLen + 1);

      EndDialog(m_hWnd, TRUE);
      break;
    }
    case IDCANCEL1:
    {
      EndDialog(m_hWnd, FALSE);
      break;
    }
  }
}

TCHAR* EditBox::getStr()
{
  return m_Text;
}

int EditBox::getStrLen() const
{
  return m_textLen;
}