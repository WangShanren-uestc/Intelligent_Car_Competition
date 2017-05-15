
#ifndef _Barrier_

#define _Barrier_ 0

#include "common.h"
#include "MKL_gpio.h"
#include "MKL_port.h"
#define ImageMaxRow 60//ͼ����Զ��
#define ImageEdgeL 0//ͼ�������
#define ImageEdgeR 159//ͼ�����ұ�
#define Door_Value 21//��������ֵ  �������Ӵ�ֵ
#define MaxRTRec 20//��¼��·���͵���ೡ�� 
#define RoadLengthBarrier 40//���ϰ����ʱ��Ŀ����е�·��� (����ǶȽ��)  ת�����С��ֵ
unsigned char FindRoadType(int* array,int Length,int roadtype0);
void GetPointTab(int* Row_L,int length_L,int* Row_R,int length_R,int* array_aimnumL,int* array_aimnumR,int* array_aimdataL,int* array_aimdataR,int* Col_L,int* Col_R);
signed char ChargeBarrier(int end_line,int* array_aimnumL,int* array_aimnumR,int* array_aimdataL,int* array_aimdataR);
void  HandleBarrier(int* Row_L,int length_L,int* Row_R,int length_R,int* Col_L,int* Col_R,int end_line,int *centre_pos,int *centre_pos2,const int CtrRow);
#endif