#ifndef MAINFROM_H
#define MAINFORM_H

#include"bass.h"
#include"bass_fx.h"

#define BLACK CreateSolidBrush(RGB(0,0,0))
#define NORMAL (HBRUSH)(COLOR_3DFACE+1)

#define IDD_MENU      5001
#define IDD_FILE_OPEN_FILE 5002
#define IDD_FILE_EXIT 5003
#define IDD_VIEW_ONTOP 5004
#define IDD_FILE_PLAYLIST 5005
#define IDD_SETTINGS_RECORD 5006
#define IDD_FILE_OPEN_DIRECTORY 5007
#define IDD_VIEW_OPTIONS 5008
#define IDD_VIEW_PLAYLIST 5009
#define IDD_VIEW_ZERO 5010
#define IDD_VIEW_TEN 5011
#define IDD_VIEW_TWENTY 5012
#define IDD_VIEW_THIRTY 5013
#define IDD_VIEW_FORTY 5014
#define IDD_VIEW_FIFTY 5015
#define IDD_VIEW_SIXTY 5016
#define IDD_VIEW_SEVENTY 5017
#define IDD_VIEW_EIGHTY 5018
#define IDD_VIEW_NINTY 5019
#define IDD_PLAY_PLAY 5020
#define IDD_PLAY_PAUSE 5021
#define IDD_PLAY_STOP 5022
#define IDD_PLAY_SEEK 5023
#define IDD_PLAY_REPEAT 5024
#define IDD_PLAYBACK_NOTHING 5025
#define IDD_PLAYBACK_LOGOFF 5026
#define IDD_PLAYBACK_RESTART 5027
#define IDD_PLAYBACK_SHUTDOWN 5028
#define IDD_PLAYBACK_CLOSEPLAYER 5029
#define IDD_HELP_ABOUT 5030

char SongID[65534]="\0";




void Init_Sound();
void Init_Common_Controls(HWND hwnd);
void On_Timer(HWND hwnd);
void On_Drop_Files(HWND hwnd,WPARAM wParam);




BOOL On_Drop_Error=FALSE;

void Init_Sound()
{
      WIN32_FIND_DATA wfd;
      
     char path[500]="\0";
     char plugin[500]="\0";
     
     strcpy(path,GetDirectory());
     strcat(path,"\\plugins\\*.dll");
     
     HANDLE hFile=FindFirstFile(path,&wfd);
     
     BASS_Init(-1,44100,0,0,0);
     
     while(hFile!=INVALID_HANDLE_VALUE)
     {
      strcpy(plugin,GetDirectory());
      strcat(plugin,"\\plugins\\");
      strcat(plugin,wfd.cFileName);
      BASS_PluginLoad(plugin,0);
      
      if(!FindNextFile(hFile,&wfd)) break;
     }
     FindClose(hFile);
     
     strcpy(SongID,GetCharacterSetting("songid","path"));
     SongHandle=BASS_StreamCreateFile(0,SongID,0,0,0x200000|128);
     SongHandle=BASS_FX_TempoCreate((DWORD)SongHandle,0x10000);
     BASS_ChannelPlay(SongHandle,FALSE);
     BASS_SetVolume(GetNumberSetting("volume","vol"));
     if(BASS_ChannelIsActive((DWORD)SongHandle)==0) 
     {
     BASS_Free();
     SetNumberSetting("play","status",0);
     }
     else SetNumberSetting("play","status",1);
};


void Init_Common_Controls(HWND hwnd)
{
             DragAcceptFiles(hwnd,TRUE);
             hRecord=Record_Button(hwnd,-3,50);
             hPlay=Play_Button(hwnd,37,50);
             hPause=Pause_Button(hwnd,77,50); 
             hStop=Stop_Button(hwnd,117,50);
             hSeek=SeekSlider(hwnd,170,65,300);
             hVolume=VolSlider(hwnd,500,65,120);
             hTime=Create_Time_Display(hwnd,2,100,540,25);
};


void On_Timer(HWND hwnd)
{  
     if(strcmp(GetCharacterSetting("songid","path"),SongID)!=0 && strcmp(GetCharacterSetting("songid","path"),"")!=0)
                  {
                   SetForegroundWindow(hwnd);
                   BASS_Free();
                   Init_Sound();
      if(BASS_ChannelIsActive((DWORD)SongHandle)==0)
      {
      MessageBox(hwnd,"RB Super Player cannot play this file","Error!",MB_ICONERROR|MB_OK);
      SetNumberSetting("play","status",0);
      CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_STOP,MF_BYCOMMAND);
      SetCharacterSetting("songid","path",GetCharacterSetting("songid","previous"));
      return;
      }
      
      if(strlen(GetFileName(GetCharacterSetting("songid","path")))<=35)
      SetWindowText(hSngTitle,GetFileName(GetCharacterSetting("songid","path")));
      else
                         {
                          char Title[50]="\0";
                          strncpy(Title,GetFileName(GetCharacterSetting("songid","path")),31);
                          strcat(Title,"....");
                          SetWindowText(hSngTitle,Title);
                         }
      
       if(BASS_ChannelIsActive((DWORD)SongHandle)==1)
      {
      SetNumberSetting("play","status",1);
      CheckMenuRadioItem(GetSubMenu(GetMenu(hwnd),2),IDD_PLAY_PLAY,IDD_PLAY_STOP,IDD_PLAY_PLAY,MF_BYCOMMAND);
      BASS_ChannelPlay(SongHandle,TRUE);
      return;
      }
      }
};


void On_Drop_Files(HWND hwnd,WPARAM wParam)
{
     char nFile[500]="\0";
     WIN32_FIND_DATA wfd;
     UINT count=DragQueryFile((HDROP)wParam,0xFFFFFFFF,0,0);
     if(count==1)
     {
      HANDLE FileCheck=FindFirstFile(nFile,&wfd);
     if(wfd.dwFileAttributes!=FILE_ATTRIBUTE_DIRECTORY)
     {
      DragQueryFile((HDROP)wParam,0,nFile,sizeof(nFile));
      SetCharacterSetting("songid","previous",GetCharacterSetting("songid","path"));
      SetCharacterSetting("songid","path",nFile);
      On_Timer(hwnd);
     }
     }
     
}


#endif
