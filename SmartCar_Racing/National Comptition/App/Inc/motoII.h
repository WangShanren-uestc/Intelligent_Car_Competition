#ifndef __MOTOII_H__
#define __MOTOII_H__

#include  "common.h"
#include "DEFINEmoto.h"
#include "DEFINEADC.h"
#include "DEFINECTRL.h"
#include  "MKL_TPM.h"
#include "MKL_adc.h"
#include  "MKL_uart.h"
#include  "MKL_gpio.h"
#include "FIRE_LED.H"
#include "define.h"

//陀螺仪比例因子(3.291V/4096)/(0.67mV/deg.s * 5)//16bitADC(3.291V/65536)/(0.67mV/deg.s * 5)
#define GYRO_RATIO 		0.015
#define Tw				15.0	   //Tw为对陀螺仪静态电压进行低通滤波的时间常数

#define DG_FIX 0.0040

#define ACCZ_OFFSET 26600
#define ACCX_OFFSET 31200
#define ACCZ_ANGLE_RATIO  90.0 / 15318
#define TIME_Z		   4.0  

#define ANGLE_SPEED_CONTROL_MAX		7.0 //5.6 //角度和速度控制电压最大值
#define ANGLE_SPEED_CONTROL_MIN		-7.0 //角度和速度控制电压最小值

//电机控制参量
#define MOTOR_OUT_MAX_II	7.6 //电机最大值
#define MOTOR_OUT_MIN_II	-7.6  //电机最小值

#define PWM_MAX 100
#define PWM_MIN -100

//其他参量
#define PI		3.1415926
#define dt  	0.003

//速度控制
#define DECODER_NUM_LEN	26//52	//用于存放最近的编码器脉冲数的数组长度
#define SPEED_DATALEN	12//25	//用于计算速度的编码器数据个数
#define SPEED_RATIO		(1.0/(5400 * (SPEED_DATALEN * dt)*2.0))


#define ERROR_MAX 60
#define ERROR_D_MAX 20
#define DIRECTION_ERRORS_NUMS   20//50 //求方向控制D的数组长度

#define AD_AVERAGE 20

extern uint16 OutData[4];
extern float g_fDIR;
extern int NRF_on;

#endif  
