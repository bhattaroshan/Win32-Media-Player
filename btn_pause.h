#ifndef BTN_PAUSE_H
#define BTN_PAUSE_H

#include<windows.h>
#include"buttons.h"
#include"bass.h"

void On_Click_Pause();


HWND hStatic_Pause,hBtn_Pause;
HWND Pause_Button(HWND hwnd,int x,int y);

LRESULT CALLBACK Pause_ButtonProc(HWND,UINT,WPARAM,LPARAM);


HWND Pause_Button(HWND hwnd,int x,int y)
{
    WNDCLASS wnd;
    wnd.style=CS_VREDRAW|CS_HREDRAW;
    wnd.lpfnWndProc=Pause_ButtonProc;
    wnd.cbClsExtra=0;
    wnd.cbWndExtra=0;
    wnd.hCursor=LoadCursor(NULL,IDC_HAND);
    wnd.hbrBackground=(HBRUSH)(COLOR_3DFACE);
    wnd.lpszClassName="Pause_Cls";
    
    RegisterClass(&wnd);
    
    hBtn_Pause=CreateWindowEx(0,"Pause_Cls",NULL,WS_CHILD|WS_VISIBLE,x,y,35,35,
                             hwnd,NULL,NULL,NULL);

return hBtn_Pause;
     
};


LRESULT CALLBACK Pause_ButtonProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
       
        switch(msg)
        {
        case WM_CREATE:
             {
             
             RECT rc;
             GetWindowRect(hwnd,&rc);
             HRGN hRgn_Pause=CreateRoundRectRgn(3,3,rc.right-rc.left,rc.bottom-rc.top,35,35);
             SetWindowRgn(hwnd,hRgn_Pause,TRUE);
             hStatic_Pause=CreateWindowEx(0,"static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP,0,0,0,0,
                                         hwnd,NULL,NULL,NULL);
             SendMessage(hStatic_Pause,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_PAUSE)));
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
            SendMessage(hStatic_Pause,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_PAUSE)));   
            
            }
        break;
      case WM_MOUSELEAVE:
           {
            SendMessage(hStatic_Pause,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_PAUSE)));    
            }
        break;
        case WM_LBUTTONDOWN:
             {
             SendMessage(hStatic_Pause,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_CLICK_PAUSE))); 
              Sleep(150); 
              }
              
              
        break;
        case WM_LBUTTONUP:
             {
             SendMessage(hStatic_Pause,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_PAUSE))); 
             On_Click_Pause();
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

void On_Click_Pause()
{
     if(BASS_ChannelIsActive((DWORD)SongHandle)==1) 
     {
     BASS_ChannelPause(SongHandle);
     SetNumberSetting("play","status",2);
     }
};

#endif
