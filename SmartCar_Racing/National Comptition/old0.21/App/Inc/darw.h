#ifndef __DARW_H__
#define __DARW_H__

#define DARW_ROW ROW-8

#define REN_ROW DARW_ROW
#define REN_COL COL/2-6

#define C_ROW DARW_ROW
#define C_COL COL/2

#define SPEED_ROW DARW_ROW
#define SPEED_COL COL/2+6

#define LEFT_ROW DARW_ROW
#define LEFT_COL COL/2-18

#define RIGHT_ROW DARW_ROW
#define RIGHT_COL COL/2-12

#define ANGEL_ROW DARW_ROW
#define ANGEL_COL COL/2+19

#define CTRL_ROW 1
#define CTRL_COL 1

extern float g_fCarSpeed,g_fCarAngle,CAR_SPEED_SETfDelta,g_fLeftspeed,g_fRightspeed,g_fLeftMotorOut,g_fRightMotorOut;
extern float g_fDirectionControlOut_left,g_fDirectionControlOut_right,g_nLeftVoltageSigma,g_nRightVoltageSigma,S_Ctrlflag,A_Ctrlflag,D_Ctrlflag;

#endif  