#ifndef __MOTO_H__
#define __MOTO_H__

#include  "common.h"
#include "DEFINEmoto.h"
#include "DEFINEADC.h"
#include  "MKL_TPM.h"
#include "MKL_adc.h"
#include  "MKL_uart.h"
#include  "MKL_gpio.h"
#include "FIRE_LED.H"
#include  "MKL_pit.h"           //PIT
#include  "FIRE_NRF24L0.h"      //无线模块NRF24L01+
#include  "FIRE_NRF24L0_MSG.h"  //无线模块消息处理

#define SPEED_METH 1

#define CONTROL_PERIOD 5
#define INPUT_VOLTAGE_AVERAGE 20
#define SPEED_CONTROL_COUNT 20
#define DIRECTION_CONTROL_COUNT1 2


#define GRAVITY_ANGLE_RATIO   90.0 / 15318
#define GRAVITY_ANGLE_RATIO_1   1.0 / 15092
#define ANGLE_RATIO 180.0/3.14159
#define GYROSCOPE_ANGLE_RATIO 0.0160//0.02123//
#define GRAVITY_ADJUST_TIME_CONSTANT 1
#define GYROSCOPE_ANGLE_SIGMA_FREQUENCY (1000 / CONTROL_PERIOD)

#define CAR_ANGLE_SET 0
#define CAR_ANGLE_SPEED_SET 0
#define ANGLE_CONTROL_OUT_MAX MOTOR_OUT_MAX * 10
#define ANGLE_CONTROL_OUT_MIN MOTOR_OUT_MIN * 10
#define MOTOR_OUT_MAX 70.0 
#define MOTOR_OUT_MIN -70.0  

#define MOTOR_OUT_DEAD_VAL 3

#define OPTICAL_ENCODE_CONSTANT 1120 //光电编码盘的刻槽数量
#define SPEED_CONTROL_PERIOD 100 //速度控制周期，ms
#define CAR_SPEED_CONSTANT   1000.0/SPEED_CONTROL_PERIOD/OPTICAL_ENCODE_CONSTANT  // 单位转化比例值
#define DIR_SPEED_CONSTANT   1000.0/DIRECTION_CONTROL_PERIOD/OPTICAL_ENCODE_CONSTANT

#define DIRECTION_CONTROL_COUNT  2
#define DIRECTION_CONTROL_PERIOD (DIRECTION_CONTROL_COUNT * CONTROL_PERIOD) 
#define LEFT_RIGHT_MINIMUM 0

#define DGYRO_ERROR 1

#define DIR_CTRL_1 0

uint8 g_nSpeedControlCount = 0,g_nDirectionControlCount = 0;


float DIRECTION_OFFSET=30650; //水平陀螺仪偏移量
float GYROSCOPE_OFFSET=25710;//33836;
float GRAVITY_OFFSET=38936;

uint8 g_nSpeedControlPeriod=0;
uint8 g_n1MSEventCount=0;

uint16 g_Ang_AD[INPUT_VOLTAGE_AVERAGE],g_Gyro_AD[INPUT_VOLTAGE_AVERAGE],d_Gyro_AD[INPUT_VOLTAGE_AVERAGE];
float VOLTAGE_GRAVITY,VOLTAGE_GYRO,VOLTAGE_dGYRO;

float g_fGravityAngle,g_fGyroscopeAngleSpeed,g_fCarAngle;
float g_fGyroscopeAngleIntegral=0;

float ANGLE_CONTROL_P = 7;
float ANGLE_CONTROL_D = 0.105;

float g_fSpeedControlOut=0;
float g_fDirectionControlOut_left=0;
float g_fDirectionControlOut_right=0;
float g_fDirectionControlOut = 0,g_fDirectionControlOutOld = 0,g_fDirectionControlOutNew = 0;
float g_fAngleControlOut=0;

float g_fLeftMotorOut,g_fRightMotorOut;

uint8 Leftflag=0,Rightflag=0;

int g_nLeftVoltageSigma=0,g_nRightVoltageSigma=0,g_nLeftMotorPulseSigma=0, g_nRightMotorPulseSigma=0;
float g_fCarSpeed=0,g_fSpeedControlIntegral=0,g_fSpeedControlOutOld=0,g_fSpeedControlOutNew=0;
float  CAR_SPEED_SETfDelta = 0; //预想速度             

float SPEED_CONTROL_P = 64;
#if SPEED_METH
float SPEED_CONTROL_I = 4;
#else
float SPEED_CONTROL_I = 0.16;
#endif

float g_fSpeedControlOut;

float g_fLeftspeed,g_fRightspeed;
float g_fDirectionControlOutOld_left=0,g_fDirectionControlOutNew_left=0;
float g_fDirectionControlOutOld_right=0,g_fDirectionControlOutNew_right=0;
int g_nDirectionControlPeriod = 0; 

float DIR_CONTROL_P = 0.5;
float DIR_CONTROL_D = 0.001;

float DIR_CONTROL_D_VALUE = 0; //陀螺仪

float g_fDIR = 0,turn_value = 0.07;


extern int comm,sendimgflag,S_Ctrlflag,A_Ctrlflag,D_Ctrlflag,renflag,RenRoadFLAG,carflag,Qipaoflag;
extern uint8 g_nDirectionControlCount;
extern uint16 OutData[4];
extern uint8 *command;
extern uint8  nrf_rx_buff[DATA_PACKET];
extern double uSet;
extern int stop_flag;

extern int Superborderjump,super_forward_offset,Speed_set,carflag;
#endif  