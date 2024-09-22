#ifndef _OVAL_H
#define _OVAL_H
#include"comvis.h"


void On_Vis_Oval(HWND hwnd,HDC hdc);

void On_Vis_Oval(HWND hwnd,HDC hdc)
{
     RECT rc,rco;
     GetClientRect(hwnd,&rc);
     GetClientRect(hwnd,&rc);
     for(int i=0;i<10;i++)
     {
     HPEN hPen=CreatePen(PS_SOLID,1,clr[i]);
     HBRUSH hBrush=CreateSolidBrush(clr[i]);
     HGDIOBJ hOldPen=SelectObject(hdc,hPen);
     HGDIOBJ hOldBrush=SelectObject(hdc,hBrush);
     rc.left+=(rc.right-rc.left);
     rc.top+=(rc.bottom-rc.top)/20;
     rc.right-=(rc.right-rc.left)/40;
     rc.bottom-=(rc.bottom-rc.top)/60;
     Ellipse(hdc,rc.left,rc.top-10,rc.right-rc.left,rc.bottom-rc.top-100);
     SelectObject(hdc,hOldBrush);
     SelectObject(hdc,hOldPen);
     DeleteObject(hOldBrush);
     DeleteObject(hOldPen);
     DeleteObject(hBrush);
     DeleteObject(hPen);
     }
     rc.left=rco.left;
     rc.top=rco.top;
     rc.right=rco.right;
     rc.bottom=rco.bottom;
     clr[9]=clr[8];
     clr[8]=clr[7];
     clr[7]=clr[6];
     clr[6]=clr[5];
     clr[5]=clr[4];
     clr[4]=clr[3];
     clr[3]=clr[2];
     clr[2]=clr[1];
     clr[1]=clr[0];
     clr[0]=RGB(rand()%255,rand()%255,rand()%255);
     ReleaseDC(hwnd,hdc);
}


#endif
