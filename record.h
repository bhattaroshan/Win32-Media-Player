
#ifndef _RECORD_H
#define _RECORD_H

#include<windows.h>
#include<shlobj.h>
#include"basscb.h"
#include"tooltips.h"
//  USE 5001 FOR MENUS
//  USE 5101 FOR DIALOGS
//  USE 5201 FOR BUTTONS
//  USE 5401 FOR STATIC
//  USE 5601 FOR TRACKBAR
//  USE 5701 FOR EDIT
//  USE 5801 FOR COMBO

//USE   6001 FOR BITMAP


//         CONSTANTS                    //
char Record_Output_Directory[65534]="\0";





//           RECORD DIALOG              //

#define IDD_DIALOG_RECORD 5101
#define IDD_DIALOG_ABOUT  5102
#define IDD_ACCELERATOR   5103

#define IDD_RECORD_STATIC_OUTPUT 5401
#define IDD_RECORD_STATIC_FREQUENCY 5402
#define IDD_RECORD_STATIC_BITRATE 5403
#define IDD_RECORD_STATIC_CHANNEL 5404


#define IDD_RECORD_MP3 5201
#define IDD_RECORD_WAV 5202
#define IDD_RECORD_BROWSE 5203
#define IDD_RECORD_GROUPBOX 5204
#define IDD_RECORD_OK 5205
#define IDD_RECORD_CANCEL 5206

#define IDD_HELP_OK 5207
#define IDD_HELP_INFO 5208

#define IDD_RECORD_OUTPUT 5701

#define IDD_RECORD_FREQUENCY 5801
#define IDD_RECORD_BITRATE   5802
#define IDD_RECORD_CHANNEL   5803

#define IDD_BITMAP_ROSHAN 5904
#define IDD_ICON_PLAYER 5905
#define IDD_ICON_DEFAULT 5906
#define IDD_FILE_VERSION 5907
/*          BITRATES
      32
      40
      48
      56
      64
      80
      96
      112
      128
      160
      192
      224
      256
      320
  
               KHZ
     44.1
     32
     48
              
              CHANNEL
     STEREO s
     JOINT  j
*/



void RecordStart();

char *GetDirectory();
char *Get_Current_Time();
char *Get_Current_Date();
char *GetHomeDrive();
int GetNumberSetting(char nSection[20],char nKey[20]);
char *GetCharacterSetting(char nSection[20],char nKey[20]);
void SetNumberSetting(char nSection[20],char nKey[20],int Result);
void SetCharacterSetting(char nSection[40],char nKey[40],char Result[65534]);


LRESULT CALLBACK Dialog_Record(HWND,UINT,WPARAM,LPARAM);

LRESULT CALLBACK Dialog_Record(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
        switch(msg)
        {
                   case WM_INITDIALOG:
                        {
                        HFONT hFont_GroupBox=CreateFont(15,8,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,0);
                        HFONT hFont_ComboBox=CreateFont(15,6,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,0);
                        HFONT hFont_Static=CreateFont(15,8,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,0);
                        HFONT hFont_RadioButton=CreateFont(15,5,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,0);
                        
                        //           GROUPBOX             //
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_GROUPBOX),WM_SETFONT,(WPARAM)hFont_GroupBox,0);
                        
                      
                        //          RadioButton           //
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_MP3),WM_SETFONT,(WPARAM)hFont_RadioButton,0);
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_WAV),WM_SETFONT,(WPARAM)hFont_RadioButton,0);
                        
                        
                        //        STATIC           //
                        
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_STATIC_OUTPUT),WM_SETFONT,(WPARAM)hFont_Static,0);
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_STATIC_FREQUENCY),WM_SETFONT,(WPARAM)hFont_Static,0);
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_STATIC_BITRATE),WM_SETFONT,(WPARAM)hFont_Static,0);
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_STATIC_CHANNEL),WM_SETFONT,(WPARAM)hFont_Static,0);
                        
                        
                        
                        //       FREQUENCY            //
                        
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_FREQUENCY),CB_ADDSTRING,0,(LPARAM)"32");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_FREQUENCY),CB_ADDSTRING,0,(LPARAM)"44.1");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_FREQUENCY),CB_ADDSTRING,0,(LPARAM)"48");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_FREQUENCY),WM_SETFONT,(WPARAM)hFont_ComboBox,0);
                        
                        
                        
                        //     BITRATE               //
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"32");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"40");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"48");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"56");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"64");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"80");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"96");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"112");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"128");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"160");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"192");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"224");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"256");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_ADDSTRING,0,(LPARAM)"320");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),WM_SETFONT,(WPARAM)hFont_ComboBox,0);
                        
                        //    CHANNEL               //
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_CHANNEL),CB_ADDSTRING,0,(LPARAM)"Joint");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_CHANNEL),CB_ADDSTRING,0,(LPARAM)"Stereo");
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_CHANNEL),WM_SETFONT,(WPARAM)hFont_ComboBox,0);
                        
                        //    CHECKING  RADIO CONTROLS       //
                        if(GetNumberSetting("record","format")==1)
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_MP3),BM_SETCHECK,(WPARAM)BST_CHECKED,0);
                        else
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_WAV),BM_SETCHECK,(WPARAM)BST_CHECKED,0);
                        
                        //    CHECKING  FREQUENCY CONTROL       //
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_FREQUENCY),CB_SETCURSEL,GetNumberSetting("record","frequency")-1,0);
                        
                        //    CHECKING  BITRATE CONTROL       //
                         SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_SETCURSEL,GetNumberSetting("record","bitrate")-1,0);
                        
                        //    CHECKING  CHANNEL CONTROL       //
                        SendMessage(GetDlgItem(hwnd,IDD_RECORD_CHANNEL),CB_SETCURSEL,GetNumberSetting("record","channel")-1,0);
                        
                        //    CHECKING  EDIT   CONTROL        //
                         if(strcmp(GetCharacterSetting("record","output"),"%homedrive%")==0)
                         {
                         strcpy(Record_Output_Directory,GetCharacterSetting("record","%homedrive%"));
                         SetWindowText(GetDlgItem(hwnd,IDD_RECORD_OUTPUT),GetHomeDrive());
                         }
                         else
                         {
                         strcpy(Record_Output_Directory,GetCharacterSetting("record","output"));
                         SetWindowText(GetDlgItem(hwnd,IDD_RECORD_OUTPUT),GetCharacterSetting("record","output"));
                         }
                         SendMessage(GetDlgItem(hwnd,IDD_RECORD_OUTPUT),WM_SETFONT,(WPARAM)hFont_Static,0);
                        
                        
                        
                        
                        
                        }
                   break;
                   case WM_COMMAND:
                        {
                         switch(LOWORD(wParam))
                         {
                           case IDD_RECORD_OK:
                                {
                                int Format=SendMessage(GetDlgItem(hwnd,IDD_RECORD_MP3),BM_GETCHECK,0,0);
                                int Frequency=SendMessage(GetDlgItem(hwnd,IDD_RECORD_FREQUENCY),CB_GETCURSEL,0,0);
                                int Bitrate=SendMessage(GetDlgItem(hwnd,IDD_RECORD_BITRATE),CB_GETCURSEL,0,0);
                                int Channel=SendMessage(GetDlgItem(hwnd,IDD_RECORD_CHANNEL),CB_GETCURSEL,0,0);
                               
                                
                                if(Format==BST_CHECKED)
                                SetNumberSetting("record","format",1);
                                else
                                SetNumberSetting("record","format",2);
                                
                                SetNumberSetting("record","frequency",Frequency+1);
                                SetNumberSetting("record","bitrate",Bitrate+1);
                                SetNumberSetting("record","channel",Channel+1);
                                SetCharacterSetting("record","output",Record_Output_Directory);
                                EndDialog(hwnd,TRUE);
                                }
                           break;
                           
                           case IDD_RECORD_CANCEL:
                                {
                                 EndDialog(hwnd,TRUE);
                                }
                           break;
                           
                           case IDD_RECORD_BROWSE:
                                {
                                SetErrorMode(SEM_FAILCRITICALERRORS);
                                WIN32_FIND_DATA wfd;
                                char Result[65534]="\0";
                                LPITEMIDLIST hPath;
                                BROWSEINFO bi;
                                ZeroMemory(&bi,sizeof(bi));
                                bi.hwndOwner=hwnd;
                                bi.lpszTitle="Select the destination path...";
                                hPath=SHBrowseForFolder(&bi);
                                SHGetPathFromIDList(hPath,Result);
                                HANDLE nFile=FindFirstFile(Result,&wfd);
                                UINT Drive=GetDriveType(Result);
                                if(wfd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY ||
                                   Drive==DRIVE_FIXED)
                                {
                                SetWindowText(GetDlgItem(hwnd,IDD_RECORD_OUTPUT),Result);
                                strcpy(Record_Output_Directory,Result);
                                }
                                else if(Drive==DRIVE_REMOVABLE ||
                                       Drive==DRIVE_CDROM)
                                {
                                GetDiskFreeSpace(Result,0,0,0,0);
                                UINT Error=GetLastError();
                                if(Error==ERROR_SUCCESS)
                                {
                                SetWindowText(GetDlgItem(hwnd,IDD_RECORD_OUTPUT),Result);
                                strcpy(Record_Output_Directory,Result);
                                }
                                else
                                MessageBox(hwnd,"Drive not ready.","Error!",MB_ICONERROR|MB_OK);
                                }
                                else if(strcmp(Result,"")==0) {}
                                else
                                MessageBox(hwnd,"This is not directory","Error!",MB_ICONERROR|MB_OK);
                                }
                           break;
                         }
                        }
                   break;
                   case WM_CTLCOLORSTATIC:
                        {
                         HDC hdc=(HDC)wParam;
                         SetTextColor(hdc,RGB(255,0,100));
                         SetBkMode(hdc,TRANSPARENT);
                         return (LONG)(HBRUSH)(COLOR_3DFACE+1);
                        }
                   break;
                   case WM_CLOSE:
                        EndDialog(hwnd,TRUE);
                   break;
        }
return FALSE;
};


int GetNumberSetting(char nSection[20],char nKey[20])
{
    char temp[500]="\0";
    char Result[500]="\0",vResult[500]="\0";
    strcpy(temp,GetDirectory());
    strcat(temp,"settings.ini");
    GetPrivateProfileString(nSection,nKey,vResult,Result,sizeof(Result),temp);
    return atoi(Result);
};

char *GetCharacterSetting(char nSection[20],char nKey[20])
{
    char temp[500]="\0";
    static char Result[500]="\0",vResult[500]="\0";
    strcpy(temp,GetDirectory());
    strcat(temp,"settings.ini");
    GetPrivateProfileString(nSection,nKey,vResult,Result,sizeof(Result),temp);
    return Result;
};

void SetNumberSetting(char nSection[20],char nKey[20],int Result)
{
    char temp[500]="\0";
    char vResult[500]="\0";
    itoa(Result,vResult,10);
    strcpy(temp,GetDirectory());
    strcat(temp,"settings.ini");
    WritePrivateProfileString(nSection,nKey,vResult,temp);
};

void SetCharacterSetting(char nSection[40],char nKey[40],char Result[500])
{
    char temp[500]="\0";
    strcpy(temp,GetDirectory());
    strcat(temp,"settings.ini");
    WritePrivateProfileString(nSection,nKey,Result,temp);
};


char *GetHomeDrive()
{
     static char Result[500]="\0";
     ExpandEnvironmentStrings("%HOMEDRIVE%",Result,sizeof(Result));
     return Result;
};

void RecordStart()
{
    int FKhz=0,BKhz=0;
    int Bitrate=0;
    char Channel[20]="\0";
    char Format[20]="\0";
    char Path_Res[500]="\0";
    char Path[500]="\0";
    int Format_Res=GetNumberSetting("record","format");
    int Freq_Res=GetNumberSetting("record","frequency");
    int Bitrate_Res=GetNumberSetting("record","bitrate");
    int Channel_Res=GetNumberSetting("record","channel");
    
    if(Format_Res==1) strcpy(Format,"mp3");
    if(Format_Res==2) strcpy(Format,"wav");
    
    if(Freq_Res==1) 
    {
    FKhz=32;
    BKhz=0;
    }
    if(Freq_Res==2) 
    {
    FKhz=44;
    BKhz=1;
    }
    if(Freq_Res==3) 
    {
    FKhz=48;
    BKhz=0;
    }
    
    if(Bitrate_Res==1) Bitrate=32;
    if(Bitrate_Res==2) Bitrate=40;
    if(Bitrate_Res==3) Bitrate=48;
    if(Bitrate_Res==4) Bitrate=56;
    if(Bitrate_Res==5) Bitrate=64;
    if(Bitrate_Res==6) Bitrate=80;
    if(Bitrate_Res==7) Bitrate=96;
    if(Bitrate_Res==8) Bitrate=112;
    if(Bitrate_Res==9) Bitrate=128;
    if(Bitrate_Res==10) Bitrate=160;
    if(Bitrate_Res==11) Bitrate=192;
    if(Bitrate_Res==12) Bitrate=224;
    if(Bitrate_Res==13) Bitrate=256;
    if(Bitrate_Res==14) Bitrate=320;
    
    if(Channel_Res==1) strcpy(Channel,"j");
    if(Channel_Res==2) strcpy(Channel,"s");
    
    if(strcmp(GetCharacterSetting("record","output"),"%homedrive%")==0)
    strcpy(Path_Res,GetHomeDrive());
    else
    strcpy(Path_Res,GetCharacterSetting("record","output"));
    
    wsprintf(Path,"%hs\\%hs_%hs.%hs",Path_Res,Get_Current_Date(),
                                    Get_Current_Time(),Format);
    
    InitRecord(FKhz,BKhz,Channel,Bitrate,Path);
};




char *Get_Current_Time()
{
  static char Time[30]="\0";
  SYSTEMTIME st;
  GetSystemTime(&st);
  GetTimeFormat(LOCALE_SYSTEM_DEFAULT,TIME_FORCE24HOURFORMAT,&st,"hh'_'mm'_'ss",Time,sizeof(Time));
  return Time;
};

char *Get_Current_Date()
{
      static char Date[30]="\0";
      SYSTEMTIME st;
      GetSystemTime(&st);
      GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,"dddd'_'dd'_'MMMM'_'yyyy",Date,sizeof(Date));
      return Date;
};
 

char *GetDirectory()
{
     int a=0;
     char temp[500]="\0";
     static char Result[500]="\0";
     GetModuleFileName(NULL,temp,sizeof(temp));
     strrev(temp);
     
     for(int i=0;i<strlen(temp);i++)
     {
       if(temp[i]=='\\')
       {
        a=i;
        break;
       }
     };
     strrev(temp);
     strncpy(Result,temp,(strlen(temp)-a));
     return Result;
};


#endif
