#ifndef BTN_STOP_H
#define BTN_STOP_H

#include<windows.h>
#include"buttons.h"
#include"bass.h"

void On_Click_Stop();

HWND hStatic_Stop,hBtn_Stop;
HWND Stop_Button(HWND hwnd,int x,int y);

LRESULT CALLBACK Stop_ButtonProc(HWND,UINT,WPARAM,LPARAM);


HWND Stop_Button(HWND hwnd,int x,int y)
{
    WNDCLASS wnd;
    wnd.style=CS_VREDRAW|CS_HREDRAW;
    wnd.lpfnWndProc=Stop_ButtonProc;
    wnd.cbClsExtra=0;
    wnd.cbWndExtra=0;
    wnd.hCursor=LoadCursor(NULL,IDC_HAND);
    wnd.hbrBackground=(HBRUSH)(COLOR_3DFACE);
    wnd.lpszClassName="Stop_Cls";
    
    RegisterClass(&wnd);
    
    hBtn_Stop=CreateWindowEx(0,"Stop_Cls",NULL,WS_CHILD|WS_VISIBLE,x,y,35,35,
                             hwnd,NULL,NULL,NULL);

return hBtn_Stop;
     
};


LRESULT CALLBACK Stop_ButtonProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
       
        switch(msg)
        {
        case WM_CREATE:
             {
             
             RECT rc;
             GetWindowRect(hwnd,&rc);
             HRGN hRgn_Stop=CreateRoundRectRgn(3,3,rc.right-rc.left,rc.bottom-rc.top,35,35);
             SetWindowRgn(hwnd,hRgn_Stop,TRUE);
             hStatic_Stop=CreateWindowEx(0,"static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP,0,0,0,0,
                                         hwnd,NULL,NULL,NULL);
             SendMessage(hStatic_Stop,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_STOP)));
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
            SendMessage(hStatic_Stop,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_STOP)));   
            }
        break;
      case WM_MOUSELEAVE:
           {
            SendMessage(hStatic_Stop,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_STOP)));    
            }
        break;
        case WM_LBUTTONDOWN:
             {
             SendMessage(hStatic_Stop,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_CLICK_STOP))); 
              Sleep(150); 
              }
              
        break;
        case WM_LBUTTONUP:
             {
             SendMessage(hStatic_Stop,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_STOP))); 
             On_Click_Stop();
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

void On_Click_Stop()
{
  if(BASS_ChannelIsActive((DWORD)SongHandle)==1 || BASS_ChannelIsActive((DWORD)SongHandle)==3 )
  {
  BASS_ChannelStop(SongHandle);
  singleposition=0;
  SetNumberSetting("play","status",0);
  InvalidateRect(hSeekSlider,NULL,TRUE);
  }
};

#endif
