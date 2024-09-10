#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <Windows.h>
#include "Window.h"
#include "GraphView.h"
#include "ToolBar.h"

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
private:
  HMENU m_hMenu = NULL;
  HACCEL m_hAccel = NULL;
  ToolBar *m_ptoolBar = nullptr;
  GraphView *m_pGView = nullptr;

  TCHAR m_szFilename[200];
};


#endif// !GRAPH_EDITOR_H


