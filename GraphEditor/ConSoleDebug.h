#ifndef CONSOLE_DEBUG_H
#define CONSOLE_DEBUG_H
#include <Windows.h>
#include <tchar.h>

static LPCTSTR GetWindowsMsgStringFromMsgID(UINT messageId) {
#ifdef _DEBUG
#define ITERN_WNDDOWSMSGID2STRING( szName , nID ) case (nID):return _T(#szName);break
  switch (messageId) {
    ITERN_WNDDOWSMSGID2STRING(WM_NULL, 0x0000
    ); ITERN_WNDDOWSMSGID2STRING(WM_CREATE, 0x0001
    ); ITERN_WNDDOWSMSGID2STRING(WM_DESTROY, 0x0002
    ); ITERN_WNDDOWSMSGID2STRING(WM_MOVE, 0x0003
    ); ITERN_WNDDOWSMSGID2STRING(WM_SIZE, 0x0005
    ); ITERN_WNDDOWSMSGID2STRING(WM_ACTIVATE, 0x0006
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETFOCUS, 0x0007
    ); ITERN_WNDDOWSMSGID2STRING(WM_KILLFOCUS, 0x0008
    ); ITERN_WNDDOWSMSGID2STRING(WM_ENABLE, 0x000A
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETREDRAW, 0x000B
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETTEXT, 0x000C
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETTEXT, 0x000D
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETTEXTLENGTH, 0x000E
    ); ITERN_WNDDOWSMSGID2STRING(WM_PAINT, 0x000F
    ); ITERN_WNDDOWSMSGID2STRING(WM_CLOSE, 0x0010);
#ifndef _WIN32_WCE
    ITERN_WNDDOWSMSGID2STRING(WM_QUERYENDSESSION, 0x0011
    ); ITERN_WNDDOWSMSGID2STRING(WM_QUERYOPEN, 0x0013
    ); ITERN_WNDDOWSMSGID2STRING(WM_ENDSESSION, 0x0016);
#endif
    ITERN_WNDDOWSMSGID2STRING(WM_QUIT, 0x0012
    ); ITERN_WNDDOWSMSGID2STRING(WM_ERASEBKGND, 0x0014
    ); ITERN_WNDDOWSMSGID2STRING(WM_SYSCOLORCHANGE, 0x0015
    ); ITERN_WNDDOWSMSGID2STRING(WM_SHOWWINDOW, 0x0018
    ); ITERN_WNDDOWSMSGID2STRING(WM_WININICHANGE, 0x001A
    ); ITERN_WNDDOWSMSGID2STRING(WM_DEVMODECHANGE, 0x001B
    ); ITERN_WNDDOWSMSGID2STRING(WM_ACTIVATEAPP, 0x001C
    ); ITERN_WNDDOWSMSGID2STRING(WM_FONTCHANGE, 0x001D
    ); ITERN_WNDDOWSMSGID2STRING(WM_TIMECHANGE, 0x001E
    ); ITERN_WNDDOWSMSGID2STRING(WM_CANCELMODE, 0x001F
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETCURSOR, 0x0020
    ); ITERN_WNDDOWSMSGID2STRING(WM_MOUSEACTIVATE, 0x0021
    ); ITERN_WNDDOWSMSGID2STRING(WM_CHILDACTIVATE, 0x0022
    ); ITERN_WNDDOWSMSGID2STRING(WM_QUEUESYNC, 0x0023
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETMINMAXINFO, 0x0024
    ); ITERN_WNDDOWSMSGID2STRING(WM_PAINTICON, 0x0026
    ); ITERN_WNDDOWSMSGID2STRING(WM_ICONERASEBKGND, 0x0027
    ); ITERN_WNDDOWSMSGID2STRING(WM_NEXTDLGCTL, 0x0028
    ); ITERN_WNDDOWSMSGID2STRING(WM_SPOOLERSTATUS, 0x002A
    ); ITERN_WNDDOWSMSGID2STRING(WM_DRAWITEM, 0x002B
    ); ITERN_WNDDOWSMSGID2STRING(WM_MEASUREITEM, 0x002C
    ); ITERN_WNDDOWSMSGID2STRING(WM_DELETEITEM, 0x002D
    ); ITERN_WNDDOWSMSGID2STRING(WM_VKEYTOITEM, 0x002E
    ); ITERN_WNDDOWSMSGID2STRING(WM_CHARTOITEM, 0x002F
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETFONT, 0x0030
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETFONT, 0x0031
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETHOTKEY, 0x0032
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETHOTKEY, 0x0033
    ); ITERN_WNDDOWSMSGID2STRING(WM_QUERYDRAGICON, 0x0037
    ); ITERN_WNDDOWSMSGID2STRING(WM_COMPAREITEM, 0x0039);
#if(WINVER >=  0x0500)
#ifndef _WIN32_WCE
    ITERN_WNDDOWSMSGID2STRING(WM_GETOBJECT, 0x003D);
#endif
#endif
    ITERN_WNDDOWSMSGID2STRING(WM_COMPACTING, 0x0041
    ); ITERN_WNDDOWSMSGID2STRING(WM_COMMNOTIFY, 0x0044
    ); ITERN_WNDDOWSMSGID2STRING(WM_WINDOWPOSCHANGING, 0x0046
    ); ITERN_WNDDOWSMSGID2STRING(WM_WINDOWPOSCHANGED, 0x0047
    ); ITERN_WNDDOWSMSGID2STRING(WM_POWER, 0x0048
    ); ITERN_WNDDOWSMSGID2STRING(WM_COPYDATA, 0x004A
    ); ITERN_WNDDOWSMSGID2STRING(WM_CANCELJOURNAL, 0x004B);
#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_NOTIFY, 0x004E
    ); ITERN_WNDDOWSMSGID2STRING(WM_INPUTLANGCHANGEREQUEST, 0x0050
    ); ITERN_WNDDOWSMSGID2STRING(WM_INPUTLANGCHANGE, 0x0051
    ); ITERN_WNDDOWSMSGID2STRING(WM_TCARD, 0x0052
    ); ITERN_WNDDOWSMSGID2STRING(WM_HELP, 0x0053
    ); ITERN_WNDDOWSMSGID2STRING(WM_USERCHANGED, 0x0054
    ); ITERN_WNDDOWSMSGID2STRING(WM_NOTIFYFORMAT, 0x0055
    ); ITERN_WNDDOWSMSGID2STRING(WM_CONTEXTMENU, 0x007B
    ); ITERN_WNDDOWSMSGID2STRING(WM_STYLECHANGING, 0x007C
    ); ITERN_WNDDOWSMSGID2STRING(WM_STYLECHANGED, 0x007D
    ); ITERN_WNDDOWSMSGID2STRING(WM_DISPLAYCHANGE, 0x007E
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETICON, 0x007F
    ); ITERN_WNDDOWSMSGID2STRING(WM_SETICON, 0x0080);
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_NCCREATE, 0x0081
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCDESTROY, 0x0082
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCCALCSIZE, 0x0083
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCHITTEST, 0x0084
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCPAINT, 0x0085
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCACTIVATE, 0x0086
    ); ITERN_WNDDOWSMSGID2STRING(WM_GETDLGCODE, 0x0087);
#ifndef _WIN32_WCE
    ITERN_WNDDOWSMSGID2STRING(WM_SYNCPAINT, 0x0088);
#endif
    ITERN_WNDDOWSMSGID2STRING(WM_NCMOUSEMOVE, 0x00A0
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCLBUTTONDOWN, 0x00A1
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCLBUTTONUP, 0x00A2
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCLBUTTONDBLCLK, 0x00A3
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCRBUTTONDOWN, 0x00A4
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCRBUTTONUP, 0x00A5
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCRBUTTONDBLCLK, 0x00A6
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCMBUTTONDOWN, 0x00A7
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCMBUTTONUP, 0x00A8
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCMBUTTONDBLCLK, 0x00A9);
#if(_WIN32_WINNT >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_NCXBUTTONDOWN, 0x00AB
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCXBUTTONUP, 0x00AC
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCXBUTTONDBLCLK, 0x00AD);
#endif


#if(_WIN32_WINNT >=  0x0501)
    ITERN_WNDDOWSMSGID2STRING(WM_INPUT_DEVICE_CHANGE, 0x00FE);
#endif

#if(_WIN32_WINNT >=  0x0501)
    ITERN_WNDDOWSMSGID2STRING(WM_INPUT, 0x00FF);
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_KEYFIRST / WM_KEYDOWN, 0x0100
    ); ITERN_WNDDOWSMSGID2STRING(WM_KEYUP, 0x0101
    ); ITERN_WNDDOWSMSGID2STRING(WM_CHAR, 0x0102
    ); ITERN_WNDDOWSMSGID2STRING(WM_DEADCHAR, 0x0103
    ); ITERN_WNDDOWSMSGID2STRING(WM_SYSKEYDOWN, 0x0104
    ); ITERN_WNDDOWSMSGID2STRING(WM_SYSKEYUP, 0x0105
    ); ITERN_WNDDOWSMSGID2STRING(WM_SYSCHAR, 0x0106
    ); ITERN_WNDDOWSMSGID2STRING(WM_SYSDEADCHAR, 0x0107);
#if(_WIN32_WINNT >=  0x0501)
    ITERN_WNDDOWSMSGID2STRING(WM_UNICHAR / WM_KEYLAST, 0x0109);
#else
    ITERN_WNDDOWSMSGID2STRING(WM_KEYLAST, 0x0108
    );
#endif

#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_IME_STARTCOMPOSITION, 0x010D
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_ENDCOMPOSITION, 0x010E
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_COMPOSITION / WM_IME_KEYLAST, 0x010F
    );
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_INITDIALOG, 0x0110
    ); ITERN_WNDDOWSMSGID2STRING(WM_COMMAND, 0x0111
    ); ITERN_WNDDOWSMSGID2STRING(WM_SYSCOMMAND, 0x0112
    ); ITERN_WNDDOWSMSGID2STRING(WM_TIMER, 0x0113
    ); ITERN_WNDDOWSMSGID2STRING(WM_HSCROLL, 0x0114
    ); ITERN_WNDDOWSMSGID2STRING(WM_VSCROLL, 0x0115
    ); ITERN_WNDDOWSMSGID2STRING(WM_INITMENU, 0x0116
    ); ITERN_WNDDOWSMSGID2STRING(WM_INITMENUPOPUP, 0x0117
    );
#if(WINVER >=  0x0601)
    ITERN_WNDDOWSMSGID2STRING(WM_GESTURE, 0x0119
    ); ITERN_WNDDOWSMSGID2STRING(WM_GESTURENOTIFY, 0x011A
    );
#endif
    ITERN_WNDDOWSMSGID2STRING(WM_MENUSELECT, 0x011F
    ); ITERN_WNDDOWSMSGID2STRING(WM_MENUCHAR, 0x0120
    ); ITERN_WNDDOWSMSGID2STRING(WM_ENTERIDLE, 0x0121
    );
#if(WINVER >=  0x0500)
#ifndef _WIN32_WCE
    ITERN_WNDDOWSMSGID2STRING(WM_MENURBUTTONUP, 0x0122
    ); ITERN_WNDDOWSMSGID2STRING(WM_MENUDRAG, 0x0123
    ); ITERN_WNDDOWSMSGID2STRING(WM_MENUGETOBJECT, 0x0124
    ); ITERN_WNDDOWSMSGID2STRING(WM_UNINITMENUPOPUP, 0x0125
    ); ITERN_WNDDOWSMSGID2STRING(WM_MENUCOMMAND, 0x0126);

#ifndef _WIN32_WCE
#if(_WIN32_WINNT >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_CHANGEUISTATE, 0x0127
    ); ITERN_WNDDOWSMSGID2STRING(WM_UPDATEUISTATE, 0x0128
    ); ITERN_WNDDOWSMSGID2STRING(WM_QUERYUISTATE, 0x0129
    );
#endif
#endif

#endif
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLORMSGBOX, 0x0132
    ); ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLOREDIT, 0x0133
    ); ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLORLISTBOX, 0x0134
    ); ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLORBTN, 0x0135
    ); ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLORDLG, 0x0136
    ); ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLORSCROLLBAR, 0x0137
    ); ITERN_WNDDOWSMSGID2STRING(WM_CTLCOLORSTATIC, 0x0138
    ); ITERN_WNDDOWSMSGID2STRING(WM_MOUSEFIRST / WM_MOUSEMOVE, 0x0200
    ); ITERN_WNDDOWSMSGID2STRING(WM_LBUTTONDOWN, 0x0201
    ); ITERN_WNDDOWSMSGID2STRING(WM_LBUTTONUP, 0x0202
    ); ITERN_WNDDOWSMSGID2STRING(WM_LBUTTONDBLCLK, 0x0203
    ); ITERN_WNDDOWSMSGID2STRING(WM_RBUTTONDOWN, 0x0204
    ); ITERN_WNDDOWSMSGID2STRING(WM_RBUTTONUP, 0x0205
    ); ITERN_WNDDOWSMSGID2STRING(WM_RBUTTONDBLCLK, 0x0206
    ); ITERN_WNDDOWSMSGID2STRING(WM_MBUTTONDOWN, 0x0207
    ); ITERN_WNDDOWSMSGID2STRING(WM_MBUTTONUP, 0x0208
    ); ITERN_WNDDOWSMSGID2STRING(WM_MBUTTONDBLCLK, 0x0209);
#if(_WIN32_WINNT >=  0x0400) || (_WIN32_WINDOWS >  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_MOUSEWHEEL, 0x020A);
#endif
#if(_WIN32_WINNT >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_XBUTTONDOWN, 0x020B
    ); ITERN_WNDDOWSMSGID2STRING(WM_XBUTTONUP, 0x020C
    ); ITERN_WNDDOWSMSGID2STRING(WM_XBUTTONDBLCLK, 0x020D);
#endif
#if(_WIN32_WINNT >=  0x0600)
    ITERN_WNDDOWSMSGID2STRING(WM_MOUSEHWHEEL / WM_MOUSELAST, 0x020E);
#endif

#if(_WIN32_WINNT >=  0x0600) 
#elif(_WIN32_WINNT >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_MOUSELAST, 0x020D);
#elif(_WIN32_WINNT >=  0x0400) || (_WIN32_WINDOWS >  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_MOUSELAST, 0x020A);
#else
    ITERN_WNDDOWSMSGID2STRING(WM_MOUSELAST, 0x0209);
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_PARENTNOTIFY, 0x0210
    ); ITERN_WNDDOWSMSGID2STRING(WM_ENTERMENULOOP, 0x0211
    ); ITERN_WNDDOWSMSGID2STRING(WM_EXITMENULOOP, 0x0212
    );
#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_NEXTMENU, 0x0213
    ); ITERN_WNDDOWSMSGID2STRING(WM_SIZING, 0x0214
    ); ITERN_WNDDOWSMSGID2STRING(WM_CAPTURECHANGED, 0x0215
    ); ITERN_WNDDOWSMSGID2STRING(WM_MOVING, 0x0216
    );
#endif

#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_POWERBROADCAST, 0x0218
    );
#endif

#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_DEVICECHANGE, 0x0219
    );
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_MDICREATE, 0x0220
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIDESTROY, 0x0221
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIACTIVATE, 0x0222
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIRESTORE, 0x0223
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDINEXT, 0x0224
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIMAXIMIZE, 0x0225
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDITILE, 0x0226
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDICASCADE, 0x0227
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIICONARRANGE, 0x0228
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIGETACTIVE, 0x0229
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDISETMENU, 0x0230
    ); ITERN_WNDDOWSMSGID2STRING(WM_ENTERSIZEMOVE, 0x0231
    ); ITERN_WNDDOWSMSGID2STRING(WM_EXITSIZEMOVE, 0x0232
    ); ITERN_WNDDOWSMSGID2STRING(WM_DROPFILES, 0x0233
    ); ITERN_WNDDOWSMSGID2STRING(WM_MDIREFRESHMENU, 0x0234
    );
#if(WINVER >=  0x0601)
    ITERN_WNDDOWSMSGID2STRING(WM_TOUCH, 0x0240
    );
#endif

#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_IME_SETCONTEXT, 0x0281
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_NOTIFY, 0x0282
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_CONTROL, 0x0283
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_COMPOSITIONFULL, 0x0284
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_SELECT, 0x0285
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_CHAR, 0x0286
    );
#endif
#if(WINVER >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_IME_REQUEST, 0x0288
    );
#endif
#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_IME_KEYDOWN, 0x0290
    ); ITERN_WNDDOWSMSGID2STRING(WM_IME_KEYUP, 0x0291
    );
#endif

#if((_WIN32_WINNT >=  0x0400) || (WINVER >=  0x0500))
    ITERN_WNDDOWSMSGID2STRING(WM_MOUSEHOVER, 0x02A1
    ); ITERN_WNDDOWSMSGID2STRING(WM_MOUSELEAVE, 0x02A3);
#endif
#if(WINVER >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_NCMOUSEHOVER, 0x02A0
    ); ITERN_WNDDOWSMSGID2STRING(WM_NCMOUSELEAVE, 0x02A2
    );
#endif

#if(_WIN32_WINNT >=  0x0501)
    ITERN_WNDDOWSMSGID2STRING(WM_WTSSESSION_CHANGE, 0x02B1

    ); ITERN_WNDDOWSMSGID2STRING(WM_TABLET_FIRST, 0x02c0
    ); ITERN_WNDDOWSMSGID2STRING(WM_TABLET_LAST, 0x02df
    );
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_CUT, 0x0300
    ); ITERN_WNDDOWSMSGID2STRING(WM_COPY, 0x0301
    ); ITERN_WNDDOWSMSGID2STRING(WM_PASTE, 0x0302
    ); ITERN_WNDDOWSMSGID2STRING(WM_CLEAR, 0x0303
    ); ITERN_WNDDOWSMSGID2STRING(WM_UNDO, 0x0304
    ); ITERN_WNDDOWSMSGID2STRING(WM_RENDERFORMAT, 0x0305
    ); ITERN_WNDDOWSMSGID2STRING(WM_RENDERALLFORMATS, 0x0306
    ); ITERN_WNDDOWSMSGID2STRING(WM_DESTROYCLIPBOARD, 0x0307
    ); ITERN_WNDDOWSMSGID2STRING(WM_DRAWCLIPBOARD, 0x0308
    ); ITERN_WNDDOWSMSGID2STRING(WM_PAINTCLIPBOARD, 0x0309
    ); ITERN_WNDDOWSMSGID2STRING(WM_VSCROLLCLIPBOARD, 0x030A
    ); ITERN_WNDDOWSMSGID2STRING(WM_SIZECLIPBOARD, 0x030B
    ); ITERN_WNDDOWSMSGID2STRING(WM_ASKCBFORMATNAME, 0x030C
    ); ITERN_WNDDOWSMSGID2STRING(WM_CHANGECBCHAIN, 0x030D
    ); ITERN_WNDDOWSMSGID2STRING(WM_HSCROLLCLIPBOARD, 0x030E
    ); ITERN_WNDDOWSMSGID2STRING(WM_QUERYNEWPALETTE, 0x030F
    ); ITERN_WNDDOWSMSGID2STRING(WM_PALETTEISCHANGING, 0x0310
    ); ITERN_WNDDOWSMSGID2STRING(WM_PALETTECHANGED, 0x0311
    ); ITERN_WNDDOWSMSGID2STRING(WM_HOTKEY, 0x0312
    );
#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_PRINT, 0x0317
    ); ITERN_WNDDOWSMSGID2STRING(WM_PRINTCLIENT, 0x0318
    );
#endif

#if(_WIN32_WINNT >=  0x0500)
    ITERN_WNDDOWSMSGID2STRING(WM_APPCOMMAND, 0x0319
    );
#endif

#if(_WIN32_WINNT >=  0x0501)
    ITERN_WNDDOWSMSGID2STRING(WM_THEMECHANGED, 0x031A
    );
#endif


#if(_WIN32_WINNT >=  0x0501)
    ITERN_WNDDOWSMSGID2STRING(WM_CLIPBOARDUPDATE, 0x031D
    );
#endif

#if(_WIN32_WINNT >=  0x0600)
    ITERN_WNDDOWSMSGID2STRING(WM_DWMCOMPOSITIONCHANGED, 0x031E
    ); ITERN_WNDDOWSMSGID2STRING(WM_DWMNCRENDERINGCHANGED, 0x031F
    ); ITERN_WNDDOWSMSGID2STRING(WM_DWMCOLORIZATIONCOLORCHANGED, 0x0320
    ); ITERN_WNDDOWSMSGID2STRING(WM_DWMWINDOWMAXIMIZEDCHANGE, 0x0321
    );
#endif

#if(_WIN32_WINNT >=  0x0601)
    ITERN_WNDDOWSMSGID2STRING(WM_DWMSENDICONICTHUMBNAIL, 0x0323
    ); ITERN_WNDDOWSMSGID2STRING(WM_DWMSENDICONICLIVEPREVIEWBITMAP, 0x0326
    );
#endif


#if(WINVER >=  0x0600)
    ITERN_WNDDOWSMSGID2STRING(WM_GETTITLEBARINFOEX, 0x033F
    );
#endif

#if(WINVER >=  0x0400)

    ITERN_WNDDOWSMSGID2STRING(WM_HANDHELDFIRST, 0x0358
    ); ITERN_WNDDOWSMSGID2STRING(WM_HANDHELDLAST, 0x035F

    ); ITERN_WNDDOWSMSGID2STRING(WM_AFXFIRST, 0x0360
    ); ITERN_WNDDOWSMSGID2STRING(WM_AFXLAST, 0x037F
    );
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_PENWINFIRST, 0x0380
    ); ITERN_WNDDOWSMSGID2STRING(WM_PENWINLAST, 0x038F);

#if(WINVER >=  0x0400)
    ITERN_WNDDOWSMSGID2STRING(WM_APP, 0x8000);
#endif

    ITERN_WNDDOWSMSGID2STRING(WM_USER, 0x0400);

  default:
    return _T("自定义消息");
  };
#else
  return _T("The method is unused in undebug!");//非调试模式下返回值
#endif// _DEBUG
}
static void ConsoleDebug(const TCHAR* pTchar, int size)
{

#ifdef _DEBUG
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteConsole(hd, pTchar, size, NULL, NULL);
#endif// DEBUG
}
static void ConsoleDebugMessage(UINT message)
{
  ConsoleDebug(GetWindowsMsgStringFromMsgID(message), lstrlen(GetWindowsMsgStringFromMsgID(message)));
}
static void ConsoleDebug(int num)
{
  TCHAR pTchar[100];
  int cnt = 0;
  bool flag = false;
  for (int i = 1e9; i > 0; i /= 10)
  {
    if(num / i)
    {
      pTchar[cnt++] = (num / i + '0');
      num %= i;
      flag = true;
    }
    else if(flag)
    {
      pTchar[cnt++] = '0';

    }
  }
  ConsoleDebug(pTchar, cnt);
}
#endif