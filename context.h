
#ifndef _CONTEXT_H
#define _CONTEXT_H

void ContextMenu(HWND);

void ContextMenu(HWND hwnd)
{
     POINT pt;
     GetCursorPos(&pt);
     HMENU hMenu=CreatePopupMenu();
     HMENU hSubMenu=CreatePopupMenu();
     AppendMenu(hMenu,MF_STRING|MF_POPUP,(UINT)hSubMenu,"&Visualization");
     AppendMenu(hSubMenu,MF_STRING,(UINT)201,"None");
     AppendMenu(hSubMenu,MF_SEPARATOR,0,NULL);
     AppendMenu(hSubMenu,MF_STRING,(UINT)202,"Oval");
     AppendMenu(hSubMenu,MF_STRING,(UINT)203,"Top");
     TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_TOPALIGN,pt.x,pt.y,0,hwnd,NULL);
}

#endif
