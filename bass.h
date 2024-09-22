#ifndef _BASS_H
#define _BASS_H

#include<windows.h>
#include<math.h>
int AudioGetLength(HWND nFile);
int AudioGetPosition(HWND nFile);
void AudioSetPosition(HWND nFile,float nPos);

void Time_Format_HH_MM_SS(HWND nStatic,HWND nFile);
void Time_Format_Millisecond(HWND nStatic,HWND nFile);

typedef short (__stdcall *BASS_INIT)(int,long,long,long,long);
typedef HWND  (__stdcall *BASS_PLUGINLOAD)(LPSTR,long);
typedef HWND  (__stdcall *BASS_STREAMCREATEFILE)(long,LPSTR,long,long,long);
typedef short (__stdcall *BASS_CHANNELPLAY)(HWND,long);
typedef short (__stdcall *BASS_CHANNELPAUSE)(HWND);
typedef short (__stdcall *BASS_CHANNELSTOP)(HWND);
typedef DWORD (__stdcall *BASS_CHANNELGETLENGTH)(HWND);
typedef DWORD (__stdcall *BASS_CHANNELGETPOSITION)(HWND);
typedef int   (__stdcall *BASS_CHANNELSETPOSITION)(HWND,__int64);
typedef DWORD (__stdcall *BASS_CHANNELSECONDS2BYTES)(HWND,float);
typedef float (__stdcall *BASS_CHANNELBYTES2SECONDS)(HWND,__int64);
typedef int   (__stdcall *BASS_FREE)();
typedef int   (__stdcall *BASS_CHANNELISACTIVE)(DWORD);
typedef int   (__stdcall *BASS_SETVOLUME)(DWORD);
    
    
    HMODULE BASS=LoadLibrary("bass.dll");
   
   
    BASS_INIT BASS_Init=BASS_INIT(GetProcAddress(BASS,"BASS_Init"));
    BASS_PLUGINLOAD BASS_PluginLoad=BASS_PLUGINLOAD(GetProcAddress(BASS,"BASS_PluginLoad"));
    BASS_STREAMCREATEFILE BASS_StreamCreateFile=BASS_STREAMCREATEFILE(GetProcAddress(BASS,"BASS_StreamCreateFile"));
    BASS_CHANNELPLAY BASS_ChannelPlay=BASS_CHANNELPLAY(GetProcAddress(BASS,"BASS_ChannelPlay"));
    BASS_CHANNELPAUSE BASS_ChannelPause=BASS_CHANNELPAUSE(GetProcAddress(BASS,"BASS_ChannelPause"));
    BASS_CHANNELSTOP BASS_ChannelStop=BASS_CHANNELSTOP(GetProcAddress(BASS,"BASS_ChannelStop"));
    BASS_CHANNELGETLENGTH BASS_ChannelGetLength=BASS_CHANNELGETLENGTH(GetProcAddress(BASS,"BASS_ChannelGetLength"));
    BASS_CHANNELGETPOSITION BASS_ChannelGetPosition=BASS_CHANNELGETPOSITION(GetProcAddress(BASS,"BASS_ChannelGetPosition"));
    BASS_CHANNELSETPOSITION BASS_ChannelSetPosition=BASS_CHANNELSETPOSITION(GetProcAddress(BASS,"BASS_ChannelSetPosition"));
    BASS_CHANNELSECONDS2BYTES BASS_ChannelSeconds2Bytes=BASS_CHANNELSECONDS2BYTES(GetProcAddress(BASS,"BASS_ChannelSeconds2Bytes"));
    BASS_CHANNELBYTES2SECONDS BASS_ChannelBytes2Seconds=BASS_CHANNELBYTES2SECONDS(GetProcAddress(BASS,"BASS_ChannelBytes2Seconds"));
    BASS_FREE BASS_Free=BASS_FREE(GetProcAddress(BASS,"BASS_Free"));
    BASS_CHANNELISACTIVE BASS_ChannelIsActive=BASS_CHANNELISACTIVE(GetProcAddress(BASS,"BASS_ChannelIsActive"));
    BASS_SETVOLUME BASS_SetVolume=BASS_SETVOLUME(GetProcAddress(BASS,"BASS_SetVolume"));
    

//          HH:MM:SS

void Time_Format_HH_MM_SS(HWND nStatic,HWND nFile)
{
     
     char Title[100]="\0";
     char LengthFormat[100]="\0";
     int hrLength=0,minLength=0;
     int hrPosition=0,minPosition=0;
     int secLength=AudioGetLength(nFile);
     int secPosition=AudioGetPosition(nFile);
     
     while(secLength>=60)
     {
      minLength+=1;
      secLength-=60;
      if(minLength>=60)
      {
       hrLength+=1;
       minLength-=60;
      };
     };
     
     while(secPosition>=60)
     {
      minPosition+=1;
      secPosition-=60;
      if(minPosition>60)
      {
       hrPosition+=1;
       minPosition-=60;
      };
     };
     
     wsprintf(LengthFormat,"%.2d:%.2d:%.2d \\ %.2d:%.2d:%.2d",
                             hrPosition,minPosition,secPosition,
                             hrLength,minLength,secLength);
     GetWindowText(nStatic,Title,sizeof(Title));
     if(strcmp(Title,LengthFormat)!=0 && BASS_ChannelIsActive((DWORD)SongHandle)==1)
     SetWindowText(nStatic,LengthFormat);
    
};



//           HH:MM:SS:Ms



void Time_Format_Millisecond(HWND nStatic,HWND nFile)
{
      
      char Title[100]="\0";
      char LengthFormat[100]="\0";
      int secLength=0,minLength=0;
      int secPosition=0,minPosition=0;
      int audiolength=AudioGetLength(nFile);
      float length=BASS_ChannelGetLength(nFile);
      float position=BASS_ChannelGetPosition(nFile);
      float MilliPosition=(position)/176.4;
      float MilliLength=(length)/176.4;     
      
      while(MilliLength>=1000)
      {
       secLength+=1;
       MilliLength-=1000;
       if(secLength>=60)
       {
        minLength+=1;
        secLength-=60;
       }
      };
      
      while(MilliPosition>=1000)
      {
        secPosition+=1;
        MilliPosition-=1000;
        if(secPosition>=60)
        {
         minPosition+=1;
         secPosition-=60;
        }
      };
      
      wsprintf(LengthFormat,"   %.2d:%.2d.%.1d \\ %.2d:%.2d.%.1d",
               minPosition,secPosition,(int)(MilliPosition/100),
               minLength,secLength,(int)(MilliLength/100));
      
     GetWindowText(nStatic,Title,sizeof(Title));
     if(strcmp(Title,LengthFormat)!=0 && BASS_ChannelIsActive((DWORD)SongHandle)==1)
     SetWindowText(nStatic,LengthFormat);
    

};



int AudioGetLength(HWND nFile)
{
    DWORD Length=BASS_ChannelGetLength(nFile);
    return (int)BASS_ChannelBytes2Seconds(nFile,(__int64)Length);
};


int AudioGetPosition(HWND nFile)
{
    DWORD Length=BASS_ChannelGetPosition(nFile);
    return (int)BASS_ChannelBytes2Seconds(nFile,(__int64)Length);
};



void AudioSetPosition(HWND nFile,float nPos)
{
   __int64 nBytes=(__int64)BASS_ChannelSeconds2Bytes(nFile,nPos);
   BASS_ChannelSetPosition(nFile,nBytes);  
};



#endif
