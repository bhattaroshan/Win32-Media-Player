


#ifndef _BASSCB_H
#define _BASSCB_H

#include<windows.h>

void InitRecord(int FKhz,int BKhz,char Channel[2],int Bitrate,char Path[65534]);
void RecordStop();
char *GetAudioDeviceName();


typedef DWORD (__stdcall *STARTRECORDING)(DWORD,int,DWORD);
typedef DWORD (__stdcall *STARTMP3)(LPSTR,DWORD);
typedef DWORD (__stdcall *STOPENCODE)();
typedef DWORD (__stdcall *STOPRECORDING)();
typedef LPSTR (__stdcall *GETDEVICEDESC)(DWORD);
typedef DWORD (__stdcall *CLOSEBASS)();

HMODULE BASSCD=LoadLibrary("basscb.dll");

STARTRECORDING StartRecording=STARTRECORDING(GetProcAddress(BASSCD,"StartRecording"));
STARTMP3 StartMP3=STARTMP3(GetProcAddress(BASSCD,"StartMP3"));
STOPENCODE StopEncode=STOPENCODE(GetProcAddress(BASSCD,"StopEncode"));
STOPRECORDING StopRecording=STOPRECORDING(GetProcAddress(BASSCD,"StopRecording"));
GETDEVICEDESC GetDeviceDesc=GETDEVICEDESC(GetProcAddress(BASSCD,"GetDeviceDesc"));
CLOSEBASS CloseBass=CLOSEBASS(GetProcAddress(BASSCD,"CloseBass"));




void InitRecord(int FKhz,int BKhz,char Channel[2],int Bitrate,char *Path)
{
 char Temp[65534]="\0";
 StartRecording(0,0,44100);
 wsprintf(Temp,"lame -r -x -s %d.%d -m %hs -b %d -h - ""%hs""",FKhz,BKhz,Channel,Bitrate,Path);
 StartMP3(Temp,0);
};


void RecordStop()
{
     StopEncode();
     StopRecording();
};


char *GetAudioDeviceName()
{
  return GetDeviceDesc(0);
};







#endif
