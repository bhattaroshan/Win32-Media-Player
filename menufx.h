
#ifndef _MENUFX_H
#define _MENUFX_H

#include"record.h"



void Menu_Initialization(HWND);
void UnCheck_Menu(HWND);

void File_Exit(HWND);

void File_Open_File(HWND);

void View_On_Top(HWND);
void View_Transparency(HWND,int);
void Check_Transparency(HWND,int);

void Play_Play(HWND);
void Play_Pause(HWND);
void Play_Stop(HWND);
void Play_Repeat(HWND);


void Settings_Record(HWND);


void Menu_Initialization(HWND hwnd)
{
     HMENU View_Menu=GetSubMenu(GetMenu(hwnd),1);
     HMENU Play_Menu=GetSubMenu(GetMenu(hwnd),2);
     HMENU Trans=GetSubMenu(View_Menu,1);
     HMENU Playback=GetSubMenu(Play_Menu,6);
     if(GetNumberSetting("view","top")==1) 
     {
     CheckMenuItem(View_Menu,IDD_VIEW_ONTOP,MF_BYCOMMAND|MF_CHECKED);
     SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
     }
     
     if(GetNumberSetting("play","repeat")==0)
     CheckMenuItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_REPEAT,MF_BYCOMMAND|MF_UNCHECKED);
     else
     CheckMenuItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_REPEAT,MF_BYCOMMAND|MF_CHECKED);
     CheckMenuRadioItem(Trans,0,9,GetNumberSetting("view","trans"),MF_BYPOSITION);
     if(GetNumberSetting("view","trans")!=0) View_Transparency(hwnd,GetNumberSetting("view","trans")*10);
     
     if(GetNumberSetting("play","status")==0) CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_STOP,MF_BYCOMMAND);
     if(GetNumberSetting("play","status")==1) CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_PLAY,MF_BYCOMMAND);
     
     if(GetNumberSetting("play","playback")==0) CheckMenuRadioItem(Playback,0,5,0,MF_BYPOSITION);
     if(GetNumberSetting("play","playback")==1) CheckMenuRadioItem(Playback,0,5,2,MF_BYPOSITION);
     if(GetNumberSetting("play","playback")==2) CheckMenuRadioItem(Playback,0,5,3,MF_BYPOSITION);
     if(GetNumberSetting("play","playback")==3) CheckMenuRadioItem(Playback,0,5,4,MF_BYPOSITION);
     if(GetNumberSetting("play","playback")==4) CheckMenuRadioItem(Playback,0,5,5,MF_BYPOSITION);
}


void Check_Transparency(HWND hwnd,int cnt)
{
      HMENU View_Menu=GetSubMenu(GetMenu(hwnd),1);
      HMENU Trans=GetSubMenu(View_Menu,1);
      CheckMenuRadioItem(Trans,0,9,cnt,MF_BYPOSITION);
  
}

void File_Exit(HWND hwnd)
{
     DestroyWindow(hwnd);
}


void View_On_Top(HWND hwnd)
{
     HMENU View_Menu=GetSubMenu(GetMenu(hwnd),1);
     
     if(GetNumberSetting("view","top")==0)
     {
     SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
     CheckMenuItem(View_Menu,IDD_VIEW_ONTOP,MF_BYCOMMAND|MF_CHECKED);
     }
     if(GetNumberSetting("view","top")==1)
     {
     CheckMenuItem(View_Menu,IDD_VIEW_ONTOP,MF_BYCOMMAND|MF_UNCHECKED);
     SetWindowPos(hwnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
     }
     
     if(GetNumberSetting("view","top")==0) SetNumberSetting("view","top",1);
     else SetNumberSetting("view","top",0);
}

void Settings_Record(HWND hwnd)
{
     DialogBox(NULL,MAKEINTRESOURCE(IDD_DIALOG_RECORD),hwnd,(DLGPROC)Dialog_Record);
}

void View_Transparency(HWND hwnd,int per)
{  
       typedef BOOL(__stdcall *SLWA)(HWND,COLORREF,BYTE,DWORD);
     HMODULE hMod=LoadLibrary("user32.dll");
     SLWA WinSetTrans=SLWA(GetProcAddress(hMod,"SetLayeredWindowAttributes"));
     LONG style=GetWindowLong(hwnd,GWL_EXSTYLE);
     
     if(per!=100){
     SetWindowLong(hwnd,GWL_EXSTYLE,style|0x00080000);
     WinSetTrans(hwnd,0,(int)(255-(per*255/100)),0x00000002);
     }
     if(per==100) 
     {
     SetWindowLong(hwnd,GWL_EXSTYLE,style|0x00080000);
     WinSetTrans(hwnd,0,(int)255,0x00000002);
     }

    
     FreeLibrary(hMod);
}


void Play_PPS(HWND hwnd)
{
    
}


void Play_Repeat(HWND hwnd)
{
    if(GetNumberSetting("play","repeat")==0) 
    {
    CheckMenuItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_REPEAT,MF_BYCOMMAND|MF_CHECKED);
    }
    if(GetNumberSetting("play","repeat")==1) 
    {
     CheckMenuItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_REPEAT,MF_BYCOMMAND|MF_UNCHECKED);
    }
    if(GetNumberSetting("play","repeat")==0) 
    SetNumberSetting("play","repeat",1);
    else
    SetNumberSetting("play","repeat",0);
}

void Play_After_PlayBack(HWND hwnd)
{
     HANDLE hToken;
     TOKEN_PRIVILEGES tkp;
     OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);
     LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
     tkp.PrivilegeCount=1;
     tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
     AdjustTokenPrivileges(hToken,FALSE,&tkp,0,NULL,0);
     
     if(GetNumberSetting("play","playback")==1) PostQuitMessage(0);
     if(GetNumberSetting("play","playback")==2) ExitWindowsEx(EWX_LOGOFF|EWX_FORCE,0);
     if(GetNumberSetting("play","playback")==3) ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);
     if(GetNumberSetting("play","playback")==4) ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE,0);
     
}

void File_Open_File(HWND hwnd)
{
     WIN32_FIND_DATA wfd;
     char FilePath[65534]="\0";
     OPENFILENAME ofn;
     ZeroMemory(&ofn,sizeof(ofn));
     ofn.lStructSize=sizeof(ofn);
     ofn.lpstrTitle="Choose a file to play....";
     ofn.hwndOwner=hwnd;
     ofn.lpstrFile=FilePath;
     ofn.nMaxFile=65534;
     ofn.lpstrFilter="\
All Files(*.*)\0*.*\0\
aac files(*.aac)\0*.aac\0\
aiff files(*.aiff)\0*.aiff\0\
alac files(*.alac)\0*.alac\0\
ape files(*.ape)\0*.ape\0\
cda files(*.cda)\0*.cda\0\
flac files(*.flac)\0*.flac\0\
MIDI files(*.mid,*.midi,*.rmi)\0*.mid;*.midi;*.rmi\0\
mp1\\mp2\\mp3 files(*.mp1,*.mp2,*.mp3)\0*.mp1;*.mp2;*.mp3\0\
mpc files(*.mpc)\0*.mpc\0\
m3u files(*.m3u)\0*.m3u\0\
m4a files(*.m4a)\0*.m4a\0\
ogg vorbis files(*.ogg)\0*.ogg\0\
spif files(*.spif)\0*.spif\0\
spx files(*.spx)\0*.spx\0\
tta files(*.tta)\0*.tta\0\
wav audio files(*.wav)\0*.wav\0\
windows audio files(*.wm,*.wma,*.asf)\0*.wm;*.wma;*.asf\0";










     GetOpenFileName(&ofn);
     HANDLE hFile=FindFirstFile(FilePath,&wfd);
     if(hFile!=INVALID_HANDLE_VALUE)
     SetCharacterSetting("songid","path",FilePath);
}

#endif
