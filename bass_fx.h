

#ifndef _BASS_FX_H
#define _BASS_FX_H

#include<windows.h>

void AudioSetTempo(HWND nFile,float nTempo);
void AudioSetPitch(HWND nFile,float nPitch);



typedef HWND (__stdcall *BASS_FX_TEMPOCREATE)(DWORD,DWORD);
typedef long (__stdcall *BASS_FX_TEMPOSET)(HWND,float,float,float);




   HMODULE BASS_FX=LoadLibrary("bass_fx.dll");
   
   
BASS_FX_TEMPOCREATE BASS_FX_TempoCreate=BASS_FX_TEMPOCREATE(GetProcAddress(BASS_FX,"BASS_FX_TempoCreate"));
   // -95 to 5000
BASS_FX_TEMPOSET BASS_FX_TempoSet=BASS_FX_TEMPOSET(GetProcAddress(BASS_FX,"BASS_FX_TempoSet"));
 



void AudioSetTempo(HWND nFile,float nTempo)
{
     BASS_FX_TempoSet(nFile,nTempo,0,-100);
};

void AudioSetPitch(HWND nFile,float nPitch)
{
     BASS_FX_TempoSet(nFile,nPitch,-100,0);
};



#endif
