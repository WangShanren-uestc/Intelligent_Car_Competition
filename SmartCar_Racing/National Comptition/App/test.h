
#ifndef _Barrier_

#define _Barrier_ 0

#include "common.h"
#include "MKL_gpio.h"
#include "MKL_port.h"
#define ImageMaxRow 60//图像最远行
#define ImageEdgeL 0//图像最左边
#define ImageEdgeR 159//图像最右边
#define Door_Value 21//像素跳变值  误判增加此值
#define MaxRTRec 20//记录道路类型的最多场数 
#define RoadLengthBarrier 40//有障碍物的时候的控制行道路宽度 (可与角度结合)  转向不足减小此值
unsigned char FindRoadType(int* array,int Length,int roadtype0);
void GetPointTab(int* Row_L,int length_L,int* Row_R,int length_R,int* array_aimnumL,int* array_aimnumR,int* array_aimdataL,int* array_aimdataR,int* Col_L,int* Col_R);
signed char ChargeBarrier(int end_line,int* array_aimnumL,int* array_aimnumR,int* array_aimdataL,int* array_aimdataR);
void  HandleBarrier(int* Row_L,int length_L,int* Row_R,int length_R,int* Col_L,int* Col_R,int end_line,int *centre_pos,int *centre_pos2,const int CtrRow);
#endif