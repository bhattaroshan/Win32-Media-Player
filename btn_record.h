#ifndef BTN_RECORD_H
#define BTN_RECORD_H

#include<windows.h>
#include"buttons.h"
#include"record.h"

BOOL Record_Pressed=FALSE;


void On_Click_Record();
void On_Click_Unrecord();

HWND hStatic_Record,hBtn_Record;
HWND Record_Button(HWND hwnd,int x,int y);

LRESULT CALLBACK Record_ButtonProc(HWND,UINT,WPARAM,LPARAM);


HWND Record_Button(HWND hwnd,int x,int y)
{
    WNDCLASS wnd;
    wnd.style=CS_VREDRAW|CS_HREDRAW;
    wnd.lpfnWndProc=Record_ButtonProc;
    wnd.cbClsExtra=0;
    wnd.cbWndExtra=0;
    wnd.hCursor=LoadCursor(NULL,IDC_HAND);
    wnd.hbrBackground=(HBRUSH)(COLOR_3DFACE);
    wnd.lpszClassName="Record_Cls";
    
    RegisterClass(&wnd);
    
    hBtn_Record=CreateWindowEx(0,"Record_Cls",NULL,WS_CHILD|WS_VISIBLE,x,y,35,35,
                             hwnd,NULL,NULL,NULL);

return hBtn_Record;
     
};


LRESULT CALLBACK Record_ButtonProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
        switch(msg)
        {
        case WM_CREATE:
             {
             
             RECT rc;
             GetWindowRect(hwnd,&rc);
             HRGN hRgn_Record=CreateRoundRectRgn(3,3,rc.right-rc.left,rc.bottom-rc.top,35,35);
             SetWindowRgn(hwnd,hRgn_Record,TRUE);
             hStatic_Record=CreateWindowEx(0,"static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP,0,0,0,0,
                                         hwnd,NULL,NULL,NULL);
             SendMessage(hStatic_Record,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_RECORD)));
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
             if(Record_Pressed==FALSE)
             {
            SendMessage(hStatic_Record,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_HOVER_RECORD))); 
               }
            if(Record_Pressed==TRUE)
             { 
              SendMessage(hStatic_Record,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_CLICK_RECORD))); 
              }
              }
        break;
      case WM_MOUSELEAVE:
           {
           if(Record_Pressed==FALSE)
            SendMessage(hStatic_Record,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_LEAVE_RECORD)));    
           if(Record_Pressed==TRUE)
            SendMessage(hStatic_Record,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,
                         (LPARAM)LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDD_BMP_CLICK_RECORD)));    
            }
        break;
        case WM_LBUTTONDOWN:
             {
        if(Record_Pressed==FALSE) 
        {
        Record_Pressed=TRUE;
        Sleep(150);
        On_Click_Record();
        break;
        }
        if(Record_Pressed==TRUE) 
        {
        Record_Pressed=FALSE;
        Sleep(150);
        On_Click_Unrecord();
        break;
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
}

void On_Click_Record()
{
     RecordStart();
};

void On_Click_Unrecord()
{
     RecordStop();
     char temp[65534]="\0";
     strcpy(temp,"Your recorded file is in directory ");
     if(strcmp(GetCharacterSetting("record","output"),"%homedrive%")==0)
     strcat(temp,GetHomeDrive());
     else
     strcat(temp,GetCharacterSetting("record","output"));
     MessageBox(hWnd,temp,"Information",MB_ICONINFORMATION|MB_OK);
};
#endif
