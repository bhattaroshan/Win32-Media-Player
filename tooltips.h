#ifndef TOOLTIPS_H
#define TOOLTIPS_H

#include<windows.h>



void AddToolTips(HWND hwnd,HWND nID,char szText[255])
{
     TOOLINFO ti;
     HWND hToolTip=CreateWindowEx(WS_EX_TOPMOST,"tooltips_class32",NULL,
                                  WS_CHILD|WS_VISIBLE|WS_POPUP|TTS_ALWAYSTIP|TTS_NOPREFIX,
                                  0,0,0,0,hwnd,NULL,NULL,NULL);
     
     ti.cbSize=sizeof(ti);
     ti.uFlags=TTF_SUBCLASS|TTF_IDISHWND;
     ti.hwnd=hwnd;
     ti.lpszText=szText;
     ti.uId=(UINT)nID;
     
     SendMessage(hToolTip,TTM_ADDTOOL,0,(LPARAM)&ti);
};


#endif
