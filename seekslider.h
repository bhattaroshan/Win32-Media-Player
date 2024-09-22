#ifndef SEEKSLIDER_H
#define SEEKSLIDER_H

#include<windows.h>
#include"sliders.h"
#include"Time.h"


void On_Click_SeekSlider();
void On_Auto_SeekSlider();
int Slider_Length=0,Slider_Start=0,Slider_End=0;

int Slider_Control=0;
int singleposition=0;

BOOL Once_It_Is_Played=FALSE;

HWND hSeekSlider,hThumb,hStatic_Thumb;
HWND SeekSlider(HWND hwnd,int x,int y);

LRESULT CALLBACK SeekSlider_Proc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ThumbProc(HWND,UINT,WPARAM,LPARAM);

HWND SeekSlider(HWND hwnd,int x,int y,int cx,int cy=50)
{
     WNDCLASS wnd;
     wnd.style=0;
     wnd.lpfnWndProc=SeekSlider_Proc;
     wnd.cbClsExtra=0;
     wnd.cbWndExtra=0;
     wnd.hCursor=LoadCursor(NULL,IDC_ARROW);
     wnd.hbrBackground=CreateSolidBrush(RGB(0,0,0));
     wnd.lpszClassName="SeekSlider_Cls";
     
     RegisterClass(&wnd);
     
     hSeekSlider=CreateWindowEx(0,"SeekSlider_Cls",NULL,WS_CHILD|WS_VISIBLE,x,y,cx,cy,
                                 hwnd,NULL,NULL,NULL);

return hSeekSlider;
};


LRESULT CALLBACK SeekSlider_Proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
        SetTimer(hwnd,0,10,NULL);
        switch(msg)
        {
                   case WM_CREATE:
                        {
                        WNDCLASS wnd;
                        wnd.style=0;
                        wnd.lpfnWndProc=ThumbProc;
                        wnd.cbClsExtra=0;
                        wnd.cbWndExtra=0;
                        wnd.hCursor=LoadCursor(0,IDC_HAND);
                        wnd.hbrBackground=(HBRUSH)(COLOR_3DFACE+1);
                        wnd.lpszClassName="Thumb_Procedure";
                        
                        RegisterClass(&wnd);
                        
                        hThumb=CreateWindowEx(0,
                                   "Thumb_Procedure",
                                   NULL,
                                   WS_CHILD|WS_VISIBLE,
                                   0,
                                   15,
                                   22,
                                   22,
                                   hwnd,
                                   NULL,
                                   NULL,
                                   NULL);
                        
             
                        }
                   break;
                   case WM_PAINT:
                        {
                         PAINTSTRUCT ps;
                         RECT rc;
                         HDC hdc=GetDC(hwnd);
                         HPEN hPen=CreatePen(PS_SOLID,1,RGB(0,255,0));
                         HPEN hPenRed=CreatePen(PS_SOLID,1,RGB(255,0,0));
                         GetWindowRect(hwnd,&rc);
                         BeginPaint(hwnd,&ps);
                         HGDIOBJ oldPen=SelectObject(hdc,hPen);
                         MoveToEx(hdc,2,(rc.bottom-rc.top)/2,NULL);
                         LineTo(hdc,rc.right,(rc.bottom-rc.top)/2);
                         SelectObject(hdc,oldPen);
                         DeleteObject(oldPen);
                         DeleteObject(hPen);
                         
                         HGDIOBJ oldPenRed=SelectObject(hdc,hPenRed);
                         MoveToEx(hdc,2,(rc.bottom-rc.top)/2,NULL);
                         LineTo(hdc,singleposition+1,(rc.bottom-rc.top)/2);
                         SelectObject(hdc,oldPenRed);
                         DeleteObject(oldPenRed);
                         DeleteObject(hPenRed);
                         
                         ReleaseDC(hwnd,hdc);
                         EndPaint(hwnd,&ps);
                        };
                   break;
                   case WM_MOUSEMOVE:
                   case WM_LBUTTONDOWN:
                   {
                    RECT rc;
                    GetClientRect(hwnd,&rc);
                   if(wParam==MK_LBUTTON)
                   {
                   if(LOWORD(lParam)<=rc.right-8 && LOWORD(lParam)>=rc.left+10)
                   SetWindowPos(hThumb,NULL,LOWORD(lParam)-12,15,0,0,SWP_NOSIZE|SWP_NOZORDER);            
                   InvalidateRect(hwnd,NULL,TRUE);
                   On_Click_SeekSlider();
                   }
                        }
                   break;
                        
                  case WM_TIMER:
                       {
                       On_Auto_SeekSlider();
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


LRESULT CALLBACK ThumbProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{

   switch(msg)
   {
              case WM_CREATE:
                   {
                  RECT rc;
                  GetWindowRect(hwnd,&rc); 
                  HRGN hRgn_Thumb=CreateRoundRectRgn(2,2,rc.right-rc.left,rc.bottom-rc.top,22,22);
                  SetWindowRgn(hwnd,hRgn_Thumb,TRUE);
                  hStatic_Thumb=CreateWindowEx(0,"static",NULL,
                                            WS_CHILD|WS_VISIBLE|SS_BITMAP,
                                            0,0,0,0,hwnd,NULL,NULL,NULL);
                        
                   SendMessage(hStatic_Thumb,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                                   (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LSLIDER)));
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


void On_Click_SeekSlider()
{
 if(BASS_ChannelIsActive((DWORD)SongHandle)==1 || BASS_ChannelIsActive((DWORD)SongHandle)==3)
   {
      POINT pt;
      GetCursorPos(&pt);
      float trk=(float)AudioGetLength(SongHandle);
      float cnt=((pt.x-Slider_Start)*100)/(Slider_End-Slider_Start);
      if(cnt>40) cnt+=1;
      if(cnt>60) cnt+=1;
      if(cnt>80) cnt+=1;
      AudioSetPosition(SongHandle,(float)(cnt*trk)/100);
    }
};

void On_Auto_SeekSlider()
{
  if(BASS_ChannelIsActive((DWORD)SongHandle)==0)
  {
   SetWindowPos(hThumb,NULL,0,15,0,0,SWP_NOSIZE|SWP_NOZORDER);
   singleposition=0;
   if(Slider_Control==0)
   {
    InvalidateRect(hSeekSlider,NULL,FALSE);
    SetWindowText(hSngPos,"00:00:00 \\ 00:00:00");
    if(Once_It_Is_Played==TRUE) Play_After_PlayBack(hWnd);
    if(GetNumberSetting("play","repeat")==1) BASS_ChannelPlay(SongHandle,TRUE);
    if(GetNumberSetting("play","status")==0) BASS_ChannelStop(SongHandle);
    Slider_Control=1;
    Once_It_Is_Played=FALSE;
   }
   }
   
   if(BASS_ChannelIsActive((DWORD)SongHandle)==1)
   {
                        RECT rc;
                        GetWindowRect(hSeekSlider,&rc);
                        Slider_Start=rc.left;
                        Slider_End=rc.right;
                        Slider_Length=Slider_End-Slider_Start;
     int songpercent=((AudioGetPosition(SongHandle)*100)/AudioGetLength(SongHandle));
     singleposition=(songpercent*(Slider_End-Slider_Start-22))/100;
     SetWindowPos(hThumb,NULL,singleposition,15,0,0,SWP_NOSIZE|SWP_NOZORDER);
     InvalidateRect(hSeekSlider,NULL,FALSE);
     Slider_Control=0;
     Once_It_Is_Played=TRUE;
    }
};

#endif
