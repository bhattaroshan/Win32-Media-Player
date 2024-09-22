
#ifndef STRING_MANIP_H
#define STRING_MANIP_H

char* GetPathFromCommandLine(char path[65534]);
char* GetFileNameFromCommandLine(char path[65534]);
char *GetExtension(char FileName[65534]);
char *CutLastPath(char path[65534]);
char *GetFileName(char path[65534]);

char* GetPathFromCommandLine(char path[65534])
{
      char temp[65534]="\0";
      static char Result[65534]="\0";
      strncpy(temp,path,strlen(path)-1);
      strrev(temp);
      strncpy(Result,temp,strlen(temp)-1);
      strrev(Result);
      return Result;
      
};

char* GetFileNameFromCommandLine(char path[65534])
{
      int cnt=0;
      char temp[65534]="\0";
      static char Result[65534]="\0";
      strcpy(temp,path);
      strrev(temp);
      for(int i=0;i<strlen(temp);i++)
      {
              if(temp[i]=='\\') 
              {
              cnt=i;
              break;
              }
      }
      strncpy(Result,temp,cnt);
      strrev(Result);
      return Result;
};

char *GetExtension(char FileName[65534])
{
     static char temp1[65534]="\0";
     static char temp[65534]="\0";
     int count=0;
     strrev(strcpy(temp1,FileName));
     for(int i=0;i<strlen(temp1);i++)
     {
             if(temp1[i]=='.')
                           {
                            count=i;
                            break;
                            }
                              
     }
     return strrev(strncpy(temp,temp1,count));
};

char *CutLastPath(char path[65534])
{
  int a;
  static char Result[65534]="\0";
  strrev(path);
  for(int i=0;i<strlen(path);i++)
  {
  if(path[i]=='\\') 
  {
    a=i;
    break;
  }
}
  strrev(path);
  strncat(Result,path,strlen(path)-a);

return Result;
}

char *GetFileName(char path[65534])
{
     int a=0;
     static char Result[65534]="\0";
     char temp[65534]="\0";
     strcpy(temp,path);
     strrev(temp);
     strcpy(Result,"");
     for(int i=0;i<strlen(temp);i++)
     {
             if(temp[i]=='\\')
             {
              a=i;
              break;
             }
     }
     strncat(Result,temp,a);
     strrev(Result);

return Result;     
};
#endif










