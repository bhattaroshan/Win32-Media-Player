#ifndef BTN_PLAY_H
#define BTN_PLAY_H

#include<windows.h>
#include"buttons.h"
#include"bass.h"
#include"bass_fx.h"


HWND hStatic_Play,hBtn_Play;

HWND Play_Button(HWND hwnd,int x,int y);
void On_Click_Play();
LRESULT CALLBACK Play_ButtonProc(HWND,UINT,WPARAM,LPARAM);


HWND Play_Button(HWND hwnd,int x,int y)
{
    WNDCLASS wnd;
    wnd.style=CS_VREDRAW|CS_HREDRAW;
    wnd.lpfnWndProc=Play_ButtonProc;
    wnd.cbClsExtra=0;
    wnd.cbWndExtra=0;
    wnd.hCursor=LoadCursor(NULL,IDC_HAND);
    wnd.hbrBackground=(HBRUSH)(COLOR_3DFACE);
    wnd.lpszClassName="Play_Cls";
    
    RegisterClass(&wnd);
    
    hBtn_Play=CreateWindowEx(0,"Play_Cls",NULL,WS_CHILD|WS_VISIBLE,x,y,35,35,
                             hwnd,NULL,NULL,NULL);

return hBtn_Play;
     
};


LRESULT CALLBACK Play_ButtonProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
       
        switch(msg)
        {
        case WM_CREATE:
             {
             RECT rc;
             GetWindowRect(hwnd,&rc);
             HRGN hRgn_Play=CreateRoundRectRgn(3,3,rc.right-rc.left,rc.bottom-rc.top,35,35);
             SetWindowRgn(hwnd,hRgn_Play,TRUE);
             hStatic_Play=CreateWindowEx(0,"static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP,0,0,0,0,
                                         hwnd,NULL,NULL,NULL);
             SendMessage(hStatic_Play,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_PLAY)));
             }
        break;
        case WM_MOUSEMOVE:
             {
             TRACKMOUSEEVENT tme;
             tme.cbSize=sizeof(tme);
             tme.dwFlags=TME_LEAVE|TME_HOVER;
             tme.hwndTrack=hwnd;
             tme.dwHoverTime=1;    
             TrackMouseEvent(&tme); 
             }
        break;
        case WM_MOUSEHOVER:
             {
            SendMessage(hStatic_Play,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_PLAY)));   
            }
        break;
      case WM_MOUSELEAVE:
           {
            SendMessage(hStatic_Play,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_PLAY)));    
            }
        break;
        case WM_LBUTTONDOWN:
             {
             SendMessage(hStatic_Play,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_CLICK_PLAY))); 
              Sleep(150); 
              }
              
        break;
        case WM_LBUTTONUP:
             {
             SendMessage(hStatic_Play,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_PLAY))); 
             On_Click_Play();
             }
        break;
        case WM_DESTROY:
             PostQuitMessage(0);
        break;
        default:
          return DefWindowProc(hwnd,msg,wParam,lParam);
        }
return FALSE;
}

void On_Click_Play()
{
  if(BASS_ChannelIsActive((DWORD)SongHandle)==3) 
  {
  BASS_ChannelPlay(SongHandle,FALSE);
  SetNumberSetting("play","status",1);
  }
 
  if(BASS_ChannelIsActive((DWORD)SongHandle)==0) 
  {
  BASS_ChannelPlay(SongHandle,TRUE);
  SetNumberSetting("play","status",1);
  }
};

#endif
