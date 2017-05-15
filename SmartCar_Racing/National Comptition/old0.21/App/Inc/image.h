#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "DEFINEimg.h"
#include "common.h"
#include  "MKL_uart.h"          //´®¿Ú
#include "MKL_PIT.h"

#define DARW_1 1

int threshold_1 = 130;

int kittlercount = 0;

         int Leftline[60];
	 int Rightline[60];
	 int Centreline[60];
	 int Forwardleftline[60];
	 int Forwardrightline[60];
	 int Forwardcentreline[60];
	 
         int SuperForwardleftline[60];
	 int SuperForwardrightline[60];
	 int SuperForwardcentreline[60];
         
         
         
	 int Turnleft=0;
	 int Turnright=0;
	 int CrosssroadFLAG=0;
	 
	 int Qipaoflag = 0;

	 int ForwardLeftLost=0;
	 int ForwardRightLost=0;
	 int StartLeftLost[60];
	 int StartRightLost[60];
          
         int SuperForwardLeftLost=0;
	 int SuperForwardRightLost=0;
         
         int borderjump = 0;
         int forwardture = 0;
         
         
         int Superborderjump = 0;
         
        int RenRoadFLAG =0;
         
         int renflag = 0;
         float renoffset = 0;
         
         int dirdir = 0;
         
         int ture_point = 0;
         
         
         
extern int comm;
extern float g_fDIR;
extern uint8 processcomplete;

int CrossRecognize(void);
void crossroadrecognize(uint8 pData[ROW][COL]);
void RenRoadRecognize(uint8 pData[ROW][COL]);

int widthmesure(int dirr,uint8 pData[ROW][COL]);

void renpro(int dirr,uint8 pData[ROW][COL]);
         
#endif