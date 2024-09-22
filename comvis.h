#ifndef _COMVIS_H
#define _COMVIS_H


#define VIS_TIME_ID 9001

int Find_Vis=0;

int clr[9]; 

void Vis_Initialization();

void Vis_Initialization()
{
     for(int i=0;i<10;i++)
     clr[i]=RGB(rand()%255,rand()%255,rand()%255);
}



#endif
