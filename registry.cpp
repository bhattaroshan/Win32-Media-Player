
#include"registry.h"


bool REGISTRY::RegisterFileFormat(char *format,char *ProgramPath,char *IconPath)
{
     DWORD dwDisposition;
     HKEY hKey;
     char temp_format[10];
     char temp_file_ext[10];
     char default_icon[20];
     char default_open[30];
     char default_shell[30];
     char default_program[500];
     
     wsprintf(temp_format,".%hs",format);
     wsprintf(temp_file_ext,"%hsfile",format);
     wsprintf(default_icon,"%hs\\DefaultIcon",temp_file_ext);
     wsprintf(default_open,"%hs\\shell\\open\\command",temp_file_ext);
     wsprintf(default_program,"\"%hs\" \"%hs\"",ProgramPath,"%L");
     wsprintf(default_shell,"%hs\\shell",temp_file_ext);
     
     RegCreateKeyExA(HKEY_CLASSES_ROOT,temp_format,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
                     NULL,&hKey,&dwDisposition);
     
     RegSetValueExA(hKey,"",0,REG_SZ,(CONST BYTE*)(char*)temp_file_ext,sizeof temp_file_ext);
     
     RegCloseKey(hKey);
                     
     RegCreateKeyExA(HKEY_CLASSES_ROOT,default_icon,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
                     NULL,&hKey,&dwDisposition);
     
     
     RegSetValueExA(hKey,"",0,REG_SZ,(CONST BYTE*)IconPath,strlen(IconPath));
     
     RegCloseKey(hKey);
     
     RegCreateKeyExA(HKEY_CLASSES_ROOT,default_shell,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
                     NULL,&hKey,&dwDisposition);
     
     RegSetValueExA(hKey,"",0,REG_SZ,(CONST BYTE*)"open",5);
     
     RegCloseKey(hKey);
     
     RegCreateKeyExA(HKEY_CLASSES_ROOT,default_open,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
                     NULL,&hKey,&dwDisposition);
     
     
     RegSetValueExA(hKey,"",0,REG_SZ,(CONST BYTE*)default_program,strlen(default_program));
     
     RegCloseKey(hKey);
}
