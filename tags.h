
#ifndef _TAGS_H
#define _TAGS_H

#include<windows.h>

char *GetSong_Title(HWND nFile);
char *GetSong_Album(HWND nFile);
char *GetSong_Artist(HWND nFile);
char *GetSong_Year(HWND nFile);
char *GetSong_Genre(HWND nFile);
char *GetSong_Track(HWND nFile);
char *GetSong_Comment(HWND nFile);
char *GetSong_CopyWrite(HWND nFile);
char *GetSong_Composer(HWND nFile);


typedef LPSTR (__stdcall *TAGS_READ)(HWND,LPSTR);


HMODULE TAGS=LoadLibrary("tags.dll");


TAGS_READ TAGS_Read=TAGS_READ(GetProcAddress(TAGS,"TAGS_Read"));





char *GetSong_Title(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%TITL,%ICAP(%TITL),No Title)");
};

char *GetSong_Album(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%ALBM,%ICAP(%ALBM),No Album)");
};

char *GetSong_Artist(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%ARTI,%ICAP(%ARTI),No Artist)");
};

char *GetSong_Year(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%YEAR,%YEAR,--)");
};

char *GetSong_Genre(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%GNRE,%GNRE,--)");
};

char *GetSong_Track(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%TRCK,%TRCK,--)");
};

char *GetSong_Comment(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%CMNT,%CMNT,--)");
};

char *GetSong_CopyWrite(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%COPY,%COPY,--)");
};

char *GetSong_Composer(HWND nFile)
{
    return TAGS_Read(nFile,"%IFV2(%COMP,%COMP,--)");
};


#endif
