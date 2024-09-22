#ifndef VOLSLIDER_H
#define VOLSLIDER_H

#include<windows.h>
#include"sliders.h"

void On_Click_VolSlider();
void On_Auto_Click_VolSlider();


int VSlider_Length=0,VSlider_Start=0,VSlider_End=0;

HWND hVolSlider,hThumbVol,hStatic_ThumbVol;
HWND VolSlider(HWND hwnd,int x,int y);

LRESULT CALLBACK VolSlider_Proc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ThumbVolProc(HWND,UINT,WPARAM,LPARAM);

HWND VolSlider(HWND hwnd,int x,int y,int cx,int cy=50)
{
     WNDCLASS wnd;
     wnd.style=0;
     wnd.lpfnWndProc=VolSlider_Proc;
     wnd.cbClsExtra=0;
     wnd.cbWndExtra=0;
     wnd.hCursor=LoadCursor(NULL,IDC_ARROW);
     wnd.hbrBackground=CreateSolidBrush(RGB(0,0,0));
     wnd.lpszClassName="VolSlider_Cls";
     
     RegisterClass(&wnd);
     
     hVolSlider=CreateWindowEx(0,"VolSlider_Cls",NULL,WS_CHILD|WS_VISIBLE,x,y,cx,cy,
                                 hwnd,NULL,NULL,NULL);

return hVolSlider;
};


LRESULT CALLBACK VolSlider_Proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
        
        switch(msg)
        {
                   case WM_CREATE:
                        {
                        
                       
                        WNDCLASS wnd;
                        wnd.style=0;
                        wnd.lpfnWndProc=ThumbVolProc;
                        wnd.cbClsExtra=0;
                        wnd.cbWndExtra=0;
                        wnd.hCursor=LoadCursor(0,IDC_HAND);
                        wnd.hbrBackground=(HBRUSH)(COLOR_3DFACE+1);
                        wnd.lpszClassName="Thumb_Procedure";
                        
                        RegisterClass(&wnd);
                        
                        hThumbVol=CreateWindowEx(0,
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
                      SetWindowPos(hThumbVol,NULL,GetNumberSetting("volume","vol"),15,0,0,SWP_NOSIZE|SWP_NOZORDER);
                      BASS_SetVolume(GetNumberSetting("volume","vol"));
                        }
                   break;
                   case WM_PAINT:
                        {
                         PAINTSTRUCT ps;
                         RECT rc;
                         HPEN hPen=CreatePen(PS_SOLID,1,RGB(0,255,0));
                         GetWindowRect(hwnd,&rc);
                         BeginPaint(hwnd,&ps);
                         HGDIOBJ oldPen=SelectObject(ps.hdc,hPen);
                         MoveToEx(ps.hdc,2,(rc.bottom-rc.top)/2,NULL);
                         LineTo(ps.hdc,rc.right,(rc.bottom-rc.top)/2);
                         SelectObject(ps.hdc,oldPen);
                         DeleteObject(oldPen);
                         DeleteObject(hPen); 
                         ReleaseDC(hwnd,ps.hdc);
                         EndPaint(hwnd,&ps);
                        };
                   break;
                   case WM_MOUSEMOVE:
                   case WM_LBUTTONDOWN:
                        {
                    POINT pt;
                    RECT rc;
                    GetClientRect(hwnd,&rc);
                    GetCursorPos(&pt);
                    ScreenToClient(hwnd,&pt);
                   if(wParam==MK_LBUTTON)
                   {
                   On_Click_VolSlider();
                   if(pt.x<rc.right-5 && pt.x>rc.left+5)
                   SetWindowPos(hThumbVol,NULL,LOWORD(lParam)-12,15,0,0,SWP_NOSIZE|SWP_NOZORDER);
               
                   if(LOWORD(lParam)-12<0)
                   {
                   SetWindowPos(hThumbVol,NULL,0,15,0,0,SWP_NOSIZE|SWP_NOZORDER);
                   BASS_SetVolume(0);
                   SetNumberSetting("volume","vol",0);
                   }
                   
                   if(LOWORD(lParam)-12>100) 
                   SetWindowPos(hThumbVol,NULL,100,15,0,0,SWP_NOSIZE|SWP_NOZORDER);
                   
                   InvalidateRect(hwnd,NULL,TRUE);
                   }
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


LRESULT CALLBACK ThumbVolProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
   switch(msg)
   {
              case WM_CREATE:
                   {
                  RECT rc;
                  GetWindowRect(hwnd,&rc); 
                  HRGN hRgn_ThumbVol=CreateRoundRectRgn(2,2,rc.right-rc.left,rc.bottom-rc.top,22,22);
                  SetWindowRgn(hwnd,hRgn_ThumbVol,TRUE);
                  hStatic_ThumbVol=CreateWindowEx(0,"static",NULL,
                                            WS_CHILD|WS_VISIBLE|SS_BITMAP,
                                            0,0,0,0,hwnd,NULL,NULL,NULL);
                        
                   SendMessage(hStatic_ThumbVol,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
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


void On_Click_VolSlider()
{
      POINT pt;
      RECT rc;
      GetWindowRect(hVolSlider,&rc);
      GetCursorPos(&pt);
      VSlider_Start=rc.left;
      VSlider_End=rc.right;
      VSlider_Length=VSlider_End-VSlider_Start;
      int cnt=((pt.x-VSlider_Start)*100)/(VSlider_End-VSlider_Start);
      BASS_SetVolume(cnt);
      SetNumberSetting("volume","vol",cnt);
};



#endif
