#ifndef TIME_H
#define TIME_H

#include<windows.h>
#include"bass.h"

HWND hSngTitle;
HWND hSngPos;
BOOL Time_Format=TRUE;
HWND Create_Time_Display(HWND hwnd,int x,int y,int cx,int cy);
LRESULT CALLBACK Time_Proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);



HWND Create_Time_Display(HWND hwnd,int x,int y,int cx,int cy)
{
     WNDCLASS wnd;
     wnd.style=CS_HREDRAW|CS_VREDRAW;
     wnd.lpfnWndProc=Time_Proc;
     wnd.cbClsExtra=0;
     wnd.cbWndExtra=0;
     wnd.hCursor=LoadCursor(NULL,IDC_ARROW);
     wnd.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(0,255,0));
     wnd.lpszClassName="Time_Proc";
     
     RegisterClass(&wnd);
     
     HWND hTime=CreateWindowEx(0,"Time_Proc",NULL,WS_CHILD|WS_VISIBLE,
                               x,y,cx,cy,hwnd,NULL,NULL,NULL);

return hTime;
};

LRESULT CALLBACK Time_Proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
        switch(msg)
        {
                   case WM_CREATE:
                        {
                         hSngTitle=CreateWindowEx(0,"static","",WS_CHILD|WS_VISIBLE,4,5,320,18,
                                    hwnd,NULL,NULL,NULL);
                         if(strlen(GetFileName(GetCharacterSetting("songid","path")))<=35)
                         SetWindowText(hSngTitle,GetFileName(GetCharacterSetting("songid","path")));
                         else
                         {
                          char Title[50]="\0";
                          strncpy(Title,GetFileName(GetCharacterSetting("songid","path")),31);
                          strcat(Title,"....");
                          SetWindowText(hSngTitle,Title);
                         }
                         hSngPos=CreateWindowEx(0,"static","00:00:00 \\ 00:00:00",WS_CHILD|WS_VISIBLE,
                                                380,5,130,18,hwnd,NULL,NULL,NULL);
                         SetTimer(hwnd,0,100,NULL);
                        }
                   break;
                   case WM_TIMER:
                        {
                        if(Time_Format==TRUE) Time_Format_HH_MM_SS(hSngPos,SongHandle);
                       
                        if(Time_Format==FALSE) Time_Format_Millisecond(hSngPos,SongHandle);
                        
                        }
                   break;
                   case WM_LBUTTONDOWN:
                        {
                        POINT pt;
                        pt.x=LOWORD(lParam);
                        pt.y=HIWORD(lParam);
                        HWND ChildWnd=ChildWindowFromPoint(hwnd,pt);
                        if(ChildWnd==hSngPos && Time_Format==TRUE) 
                        {
                         Time_Format=FALSE;
                         break;
                         }
                        if(ChildWnd==hSngPos && Time_Format==FALSE)
                        {
                         Time_Format=TRUE;
                         break;
                         }
                        }
                   break;
                   case WM_SIZE:
                        {
                        SetWindowPos(hSngPos,NULL,LOWORD(lParam)-132,5,0,0,SWP_NOZORDER|SWP_NOSIZE);
                        }
                   break;
                   case WM_CTLCOLORSTATIC:
                        {
                         HDC hdc=(HDC)wParam;
                         COLORREF PrevColor=SetTextColor(hdc,RGB(255,0,0));
                         int mode=SetBkMode(hdc,TRANSPARENT);
                         return (LONG)CreateSolidBrush(RGB(0,255,0));
                         SetBkMode(hdc,mode);
                         SetTextColor(hdc,PrevColor);
                         ReleaseDC(hwnd,hdc);
                        }
                   break;
                   case WM_DESTROY:
                        PostQuitMessage(0);
                   break;
                   default:
                     return DefWindowProc(hwnd,msg,wParam,lParam);
        }
return FALSE;
};













#endif
