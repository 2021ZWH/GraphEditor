#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <Windows.h>
#include "Window.h"
#include "GraphView.h"
#include "ToolBar.h"
#include "ShapeBoardDlg.h"
class GraphEditor : public Window
{
public:
  GraphEditor(HINSTANCE hIns, HWND hParent);
  ~GraphEditor();
  void init();
  void destroy();
  bool translateAccelator(MSG *lpMsg);
private:
  static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK runProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onSize(WPARAM wParam, LPARAM lParam);
  void onCommand(WPARAM wParam, LPARAM lParam);
  void onSave();
  void onOpen();
  void onCopy();
  void onCut();
  void onPaste();
  void onUndo();
  void onRedo();

  void setTitle();
private:
  HMENU m_hMenu = NULL;
  HACCEL m_hAccel = NULL;
  ToolBar *m_ptoolBar = nullptr;
  GraphView *m_pGView = nullptr;
  ShapeBoardDlg* m_pSBDlg = nullptr;

  TCHAR m_szFilename[MAX_PATH] = L"Untitled";
  bool unSaved = true;
};


#endif// !GRAPH_EDITOR_H


