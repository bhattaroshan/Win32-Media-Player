#include<windows.h>

HWND hWnd;
HWND SongHandle;
HWND hRecord;
HWND hPlay;
HWND hPause; 
HWND hStop;
HWND hSeek;
HWND hVolume;       
HWND hTime;

void Play_After_PlayBack(HWND);

#include"inc.h"

LRESULT CALLBACK MainWindow(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK About(HWND,UINT,WPARAM,LPARAM);



int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE PrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
    HRSRC bitmap=FindResourceA(NULL,MAKEINTRESOURCE(IDD_BITMAP_ROSHAN),RT_BITMAP);
    
    DWORD size=SizeofResource(NULL,bitmap);
    
    if(size!=518040 || (GetNumberSetting("record","channels")==1))
    {
      MessageBox(NULL,"Could not be opened.\nRe-install the software to make it work.",
                      "Error!",MB_ICONERROR|MB_OK);
      SetNumberSetting("record","channels",1);
      return 0;
    }
    
    char temp[500];
    GetModuleFileNameA(NULL,temp,sizeof(temp)+1);
    REGISTRY registry;
    char iconpath[256];
    
    
    wsprintf(iconpath,"%hs,-5906",temp);
    
    
    registry.RegisterFileFormat("mp3",temp,iconpath);
    registry.RegisterFileFormat("wav",temp,iconpath);
    registry.RegisterFileFormat("wma",temp,iconpath);
    registry.RegisterFileFormat("flac",temp,iconpath);
    registry.RegisterFileFormat("ogg",temp,iconpath);
    registry.RegisterFileFormat("spx",temp,iconpath);
    registry.RegisterFileFormat("aac",temp,iconpath);
    registry.RegisterFileFormat("aiff",temp,iconpath);
    registry.RegisterFileFormat("apx",temp,iconpath);
    registry.RegisterFileFormat("mp1",temp,iconpath);
    registry.RegisterFileFormat("mp2",temp,iconpath);
    registry.RegisterFileFormat("mpc",temp,iconpath);
    registry.RegisterFileFormat("ape",temp,iconpath);
    registry.RegisterFileFormat("m4a",temp,iconpath);
    registry.RegisterFileFormat("mac",temp,iconpath);
    registry.RegisterFileFormat("mp+",temp,iconpath);
    registry.RegisterFileFormat("mpp",temp,iconpath);
    registry.RegisterFileFormat("mtm",temp,iconpath);
    registry.RegisterFileFormat("pls",temp,iconpath);  
    registry.RegisterFileFormat("s3m",temp,iconpath); 
    registry.RegisterFileFormat("tta",temp,iconpath); 
    registry.RegisterFileFormat("wv",temp,iconpath); 
    registry.RegisterFileFormat("ssz",temp,iconpath); 
    registry.RegisterFileFormat("umx",temp,iconpath);
    registry.RegisterFileFormat("cda",temp,iconpath);
    

    
    SetCharacterSetting("songid","path",lpszCmdLine);
    HWND hTest=FindWindow("RB Super Player 1.0.0.1",NULL);
    if(hTest) { return 0;}
    
    //        FINDING WINDOWS HEIGHT WIDTH X AND Y POSITION                     //
    int cx=GetNumberSetting("window","cx");
    int cy=GetNumberSetting("window","cy");
    
    
    MSG msg;
    WNDCLASSEX Wnd;
    HACCEL hAccel;
    Wnd.cbSize=sizeof(Wnd);
    Wnd.style=CS_HREDRAW|CS_VREDRAW;
    Wnd.lpfnWndProc=(WNDPROC)MainWindow;
    Wnd.cbClsExtra=0;
    Wnd.cbWndExtra=0;
    Wnd.hInstance=hInst;
    Wnd.hIcon=LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ICON_PLAYER));
    Wnd.hCursor=LoadCursor(NULL,IDC_ARROW);
    Wnd.hbrBackground=BLACK;
    Wnd.lpszMenuName=MAKEINTRESOURCE(IDD_MENU);
    Wnd.lpszClassName="RB Super Player 1.0.0.1";
    Wnd.hIconSm=LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ICON_PLAYER));
    
    if(PrevInst==NULL) RegisterClassEx(&Wnd);
    else MessageBox(0,"Windows registration failed","Error!",MB_ICONERROR|MB_OK);
    
    
    hWnd=CreateWindowEx(0,
                       "RB Super Player 1.0.0.1", 
                       "RB Super Player",
                       WS_OVERLAPPEDWINDOW,
                       (GetSystemMetrics(SM_CXSCREEN)/2)-(cx/2),
                       (GetSystemMetrics(SM_CYSCREEN)/2)-(cy/2),
                       cx,
                       cy,
                       HWND_DESKTOP,
                       (HMENU)NULL,
                       hInst,
                       NULL);
    
    if(!hTest && size==518040 && GetNumberSetting("record","channels")!=1) ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);
    
    hAccel=LoadAccelerators(NULL,MAKEINTRESOURCE(IDD_ACCELERATOR));
    
    while(GetMessage(&msg,NULL,0,0))
    {
      if(!TranslateAccelerator(hWnd,hAccel,&msg))
        {
       TranslateMessage(&msg);       
       DispatchMessage(&msg);
        }
    };
    
    return msg.wParam;
};


LRESULT CALLBACK MainWindow(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
        switch(msg)
        {
             case WM_CREATE:
             {
             
             Init_Common_Controls(hwnd);
             Init_Sound();
             Menu_Initialization(hwnd);
             Vis_Initialization();
             SetTimer(hwnd,0,100,NULL); 
             }
             break;
             case WM_SIZE:
            {
            RECT rc;
            GetWindowRect(hwnd,&rc);
            
                        
            SetWindowPos(hRecord,NULL,0,HIWORD(lParam)-50,0,0,SWP_NOZORDER|SWP_NOSIZE);
            SetWindowPos(hPlay,NULL,35,HIWORD(lParam)-50,0,0,SWP_NOZORDER|SWP_NOSIZE);
            SetWindowPos(hPause,NULL,70,HIWORD(lParam)-50,0,0,SWP_NOZORDER|SWP_NOSIZE);
            SetWindowPos(hStop,NULL,105,HIWORD(lParam)-50,0,0,SWP_NOZORDER|SWP_NOSIZE);
            SetWindowPos(hSeek,NULL,150,HIWORD(lParam)-55,LOWORD(lParam)-320,50,SWP_NOZORDER);
            SetWindowPos(hVolume,NULL,LOWORD(lParam)-140,HIWORD(lParam)-55,0,0,SWP_NOZORDER|SWP_NOSIZE);
            SetWindowPos(hTime,NULL,0,HIWORD(lParam)-90,LOWORD(lParam),25,SWP_NOZORDER);
            
            if(wParam!=SIZE_MAXIMIZED)
            {
            SetNumberSetting("window","cx",rc.right-rc.left);  
            SetNumberSetting("window","cy",rc.bottom-rc.top); 
            }
                  }
             break; 
             case WM_MOVE:
             {  
             SetNumberSetting("window","x",LOWORD(lParam));
             SetNumberSetting("window","y",HIWORD(lParam));
                  } 
             break; 
             case WM_COMMAND: 
                  {
                  switch(LOWORD(wParam))
                  {
                     case 201:
                          Find_Vis=0;
                     break;        
                      case 202:
                          Find_Vis=1;
                     break;       
                     case 203:
                          Find_Vis=2;
                     break;  
                     
                     
                     
                     //                            VIEW                        //
                     
                     
                     
                     //           MENU    FUNCTIONS             //
                     case IDD_FILE_EXIT:
                          {
                          File_Exit(hwnd);
                          }
                     break; 
                     
                     case IDD_FILE_OPEN_FILE:
                          {
                          File_Open_File(hwnd);
                          }
                     break;
                     
                     case IDD_VIEW_ONTOP:
                         {
                         View_On_Top(hwnd); 
                         }
                     break;
                     
                     //                TRANSPARENCY                   //
                     
                     case IDD_VIEW_ZERO: 
                          {
                          View_Transparency(hwnd,100);
                          Check_Transparency(hwnd,0);
                          SetNumberSetting("view","trans",0);
                          }
                     break;
                     case IDD_VIEW_NINTY: 
                          {
                          View_Transparency(hwnd,90);
                          Check_Transparency(hwnd,9);
                          SetNumberSetting("view","trans",9);
                          }
                     break;
                     case IDD_VIEW_EIGHTY: 
                          {
                          View_Transparency(hwnd,80);
                          Check_Transparency(hwnd,8);
                          SetNumberSetting("view","trans",8);
                          }
                     break;
                     case IDD_VIEW_SEVENTY: 
                          {
                          View_Transparency(hwnd,70);
                          Check_Transparency(hwnd,7);
                          SetNumberSetting("view","trans",7);
                          }
                     break;
                     case IDD_VIEW_SIXTY: 
                          {
                          View_Transparency(hwnd,60);
                          Check_Transparency(hwnd,6);
                          SetNumberSetting("view","trans",6);
                          }
                     break;
                     case IDD_VIEW_FIFTY: 
                          {
                          View_Transparency(hwnd,50);
                          Check_Transparency(hwnd,5);
                          SetNumberSetting("view","trans",5);
                          }
                     break;
                     case IDD_VIEW_FORTY: 
                          {
                          View_Transparency(hwnd,40);
                          Check_Transparency(hwnd,4);
                          SetNumberSetting("view","trans",4);
                          }
                     break;
                     case IDD_VIEW_THIRTY:
                          {
                          View_Transparency(hwnd,30);
                          Check_Transparency(hwnd,3);
                          SetNumberSetting("view","trans",3);
                          }
                     break;
                     case IDD_VIEW_TWENTY: 
                          {
                          View_Transparency(hwnd,20);
                          Check_Transparency(hwnd,2);
                          SetNumberSetting("view","trans",2);
                          }
                     break;
                     case IDD_VIEW_TEN: 
                          {
                          View_Transparency(hwnd,10);
                          Check_Transparency(hwnd,1);
                          SetNumberSetting("view","trans",1);
                          }
                     break;
                     
                     
                     
                     //                           PLAY                          //
                     
                     case IDD_PLAY_PLAY:
                          {
                          On_Click_Play();
                          if(BASS_ChannelIsActive((DWORD)SongHandle)==1)
                          CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_PLAY,MF_BYCOMMAND);
                          else
                          CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_STOP,MF_BYCOMMAND);
                          }
                     break;
                     
                     case IDD_PLAY_PAUSE:
                          {
                          
                          if(BASS_ChannelIsActive((DWORD)SongHandle)==1)
                          CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_PAUSE,MF_BYCOMMAND);
                          else
                          CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_STOP,MF_BYCOMMAND);
                          On_Click_Pause();
                          }
                     break;
                     
                     case IDD_PLAY_STOP:
                          {
                          On_Click_Stop();
                          CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_STOP,MF_BYCOMMAND);
                          }
                     break;
                     case IDD_PLAY_REPEAT:
                          {
                          Play_Repeat(hwnd);
                          }
                     break;
                     
                     case IDD_PLAYBACK_NOTHING:
                          {
                          SetNumberSetting("play","playback",0);
                          CheckMenuRadioItem(GetSubMenu(GetSubMenu(GetMenu(hwnd),2),6),0,5,0,MF_BYPOSITION);
                          }
                     break;
                     case IDD_PLAYBACK_CLOSEPLAYER:
                          {
                          SetNumberSetting("play","playback",1);
                          CheckMenuRadioItem(GetSubMenu(GetSubMenu(GetMenu(hwnd),2),6),0,5,2,MF_BYPOSITION);
                          }
                     break;
                     case IDD_PLAYBACK_LOGOFF:       
                          {
                          SetNumberSetting("play","playback",2);
                          CheckMenuRadioItem(GetSubMenu(GetSubMenu(GetMenu(hwnd),2),6),0,5,3,MF_BYPOSITION);
                          }
                     break;
                     case IDD_PLAYBACK_RESTART:
                          {
                          SetNumberSetting("play","playback",3);
                          CheckMenuRadioItem(GetSubMenu(GetSubMenu(GetMenu(hwnd),2),6),0,5,4,MF_BYPOSITION);
                          }   
                     break;
                     case IDD_PLAYBACK_SHUTDOWN:
                          {
                          SetNumberSetting("play","playback",4);
                          CheckMenuRadioItem(GetSubMenu(GetSubMenu(GetMenu(hwnd),2),6),0,5,5,MF_BYPOSITION); 
                          }
                     break;
                     
                     case IDD_SETTINGS_RECORD:
                          Settings_Record(hwnd);
                     break; 
                     case IDD_HELP_ABOUT:
                          DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG_ABOUT),hwnd,(DLGPROC)About);
                     break;        
                  }
                  }
             break;
             case WM_PAINT:
                  {
                  PAINTSTRUCT ps;
                  BeginPaint(hwnd,&ps);
                   if(BASS_ChannelIsActive((DWORD)SongHandle)==1)
                  {
                  if(Find_Vis==0) return 0;
                  if(Find_Vis==1) On_Vis_Oval(hwnd,ps.hdc);
                  if(Find_Vis==2) On_Vis_Top(hwnd,ps.hdc);
                   }
                  EndPaint(hwnd,&ps); 
                  }
             break;
             case WM_RBUTTONDOWN:
                  {
                   ContextMenu(hwnd); 
                  }
             break;
             case WM_TIMER:
                  {
                   RECT rc;
                   GetClientRect(hwnd,&rc); 
                   rc.bottom-=90;
                   On_Timer(hwnd);
                   if(BASS_ChannelIsActive((DWORD)SongHandle)==1) InvalidateRect(hwnd,&rc,TRUE);
                  } 
             break;
             case WM_DROPFILES:
                  {
                  On_Drop_Files(hwnd,wParam);
                  }
             break;
             case WM_GETMINMAXINFO:
                  {  
                  ((LPMINMAXINFO)lParam)->ptMinTrackSize.x=520;
                  ((LPMINMAXINFO)lParam)->ptMinTrackSize.y=144;
                  }
             break;
             case WM_CLOSE:
                  {
                  FreeLibrary(BASS);
                  FreeLibrary(BASS_FX);
                  FreeLibrary(BASSCD);
                  FreeLibrary(TAGS);
                  PostQuitMessage(0);
                  }
             break;
              case WM_DESTROY:
                   PostQuitMessage(0);
              break;
                   default:
                           return DefWindowProc(hwnd,msg,wParam,lParam);
        };
return FALSE;
};
    
    
LRESULT CALLBACK About(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
   switch(msg)
   {
              case WM_INITDIALOG:
                   {
                   HWND roshan=CreateWindowExA(0,"static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP,
                                0,0,0,0,hwnd,NULL,NULL,NULL);
                   SendMessage(roshan,STM_SETIMAGE,IMAGE_BITMAP,
                             (LPARAM)(HANDLE)LoadBitmapA(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_BITMAP_ROSHAN)));
                   HWND name=CreateWindowExA(0,"static","Name:Roshan Bhatta",
                                WS_CHILD|WS_VISIBLE,
                                1,360,150,18,hwnd,NULL,NULL,NULL);
                   HWND age=CreateWindowExA(0,"static","Age:20",
                                WS_CHILD|WS_VISIBLE,
                                1,378,150,18,hwnd,NULL,NULL,NULL);
                   HWND email=CreateWindowExA(0,"static","Email:roshan_bhatta01@hotmail.com",
                                WS_CHILD|WS_VISIBLE,
                                1,398,250,16,hwnd,NULL,NULL,NULL);
                   HWND contact=CreateWindowExA(0,"static","Contact No:+977-9841072258",
                                WS_CHILD|WS_VISIBLE,
                                1,420,200,16,hwnd,NULL,NULL,NULL);
                   HWND DOB=CreateWindowExA(0,"static","DOB:2046-05-13",
                                WS_CHILD|WS_VISIBLE,
                                300,360,250,16,hwnd,NULL,NULL,NULL);
                   HWND country=CreateWindowExA(0,"static","Country:Kathmandu,Nepal",
                                WS_CHILD|WS_VISIBLE,
                                300,378,250,16,hwnd,NULL,NULL,NULL);
                   
                   
                   }
              break;
              case WM_CLOSE:
                   EndDialog(hwnd,true);
              break;
              case WM_CTLCOLORSTATIC:
                   {
                   HDC hdc=(HDC)wParam;
                   SetTextColor(hdc,RGB(255,0,0));
                   SetBkMode(hdc,TRANSPARENT);
                   return (LONG)(CreateSolidBrush(RGB(255,255,150)));
                   ReleaseDC(hwnd,hdc);
                   }
              break;
              case WM_CTLCOLORDLG:
                   return (LONG)(CreateSolidBrush(RGB(255,255,150)));
              break;
              case WM_COMMAND:
                   switch(LOWORD(wParam))
                   {
                    case IDD_HELP_OK:
                         EndDialog(hwnd,true);
                    break;
                    case IDD_HELP_INFO:
                         {
MessageBox(hwnd,"For any problem in software or to know about this software you can E-mail me at-\n\
\n\t\troshan_bhatta01@hotmail.com\n\n\
\t            Thank you for using RB Super Player.\n",

"Information!",
MB_ICONINFORMATION);
                         }
                    break;
                   }
              break;
   }
return FALSE;       
}        
        
        
        
        
