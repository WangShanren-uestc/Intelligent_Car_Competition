#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "DEFINEimg.h"
#include "common.h"
#include  "MKL_uart.h"          //´®¿Ú
#include "MKL_PIT.h"
#include "FIRE_LED.H"

#define draw_1 1
#define MID COL/2
#define MaxNum 200
#define PHS  15 
#define MaxAngle  35 
#define MID COL/2
#define limit_up  15
#define limit_down  ROW/2-9

    void DIR_fifo(void);
    void draw_renzi(uint8 *pData);
    void draw_shizi(uint8 *pData);
    void draw_width(uint8 *pData);
    void gpio_set (PTXn_e ptxn, uint8 data);
    void draw_point_anti(uint8 *pData,uint8 row,uint8 col);
    void draw_angle(uint8 *pData);


    extern double CarAngle;
    extern int stop_flag;
    extern double uSet,uSet_pre;
    extern float nErrors[];      
    extern double NowSpeed;
    extern float g_fDIR;
    extern uint8 processcomplete;
    extern uint16 OutData[4];
    extern int sendimgflag;
    extern int DD_Ratio;
      
      
        float  OffsetQ = 0.8;
        float  OffsetQ_line3 = 0.8; 
        int ren_startturn = 40;
        int ren_offset = 15;
        int zhang_offset = 13;
        int zhang_holdtime = 45;
        int R_ren = 1;
        int R_xiaos = 1;
        int R_qipao = 1;
        int R_shizi = 1;
        int R_zhang = 1;
    
	int fixedrow1 = ROW/2-5;
        int fixedrow2 = ROW/2-3;
        int fixedrow3 = ROW/2-10;
        int centreline1[2] = {COL/2,COL/2};
        int centreline2[2] = {COL/2,COL/2};
        int centreline3[2] = {COL/2,COL/2};
        
        int control_row[3];
        int line1_width[2];
        int line2_width[2];
        int line3_width[2];
        
        int left1lost_flag = 0;
        int right1lost_flag = 0;
        int left2lost_flag = 0;
        int right2lost_flag = 0;
        int left3lost_flag = 0;
        int right3lost_flag = 0;
        
        int line1lost_memo[2];
        int line2lost_memo[2];
        int line3lost_memo[2];
        
        
        int leftlinerow[ MaxNum];        
        int leftlinecol[ MaxNum];
        int rightlinerow[ MaxNum];
        int rightlinecol[ MaxNum];
        int leftdirection[ MaxNum];
        int rightdirection[ MaxNum];  
        int AV_leftcol = 0;
        int AV_rightcol = 0;
        
        int lefthighestpoint[3];
        int righthighestpoint[3]; 
        int leftcolmaxpoint[3];
        int rightcolminpoint[3];
        int leftpointnumber=0;
        int rightpointnumber=0;  
        int centrepointnumber = 0;     
       
        int straightaway_flag=0;
        int block_flag=0;
        int s_bend_flag=0;
        int ramp_flag=0;
        int crossroad_flag=0;        
        int herringbone_flag=0;
        int startingline_flag = 0;
        int sharp_turn_flag = 0;      
        int turn_flag = 0;
        int move_flag = 0;
       
        int  hold_flag = 0;
        int  Ren_Clean_Flag = 0;
        int  double_flag = 0;
        int  ren_turn_limit = 0;
        
         
        int typememo[2];  
        
        int leftline[60];
        int rightline[60];
        int centreline[60];
        int leftline1 = 0;
        int rightline1 = COL-1;
        int leftline2 = 0;
        int rightline2 = COL-1; 
        int leftline3 = 0;
        int rightline3 = COL-1;
        
        float offset_line3 = 0;
        float line3_fifo[10];
        
        int view_limit = 0;
        int control_limit = 0;
        int line_move = 0;
        int linewidth = 0;
        
        int conntrol_array[56] = { 20,19,19,18,17,17,16,16,15,14,     //£¨-20£¬-11£©
                                   13,13,12,11,11,10, 9 ,9, 8, 7,     //£¨-10£¬-1£©
                                    7, 6, 5, 4, 4, 3, 3, 2, 2, 1,     //£¨0£¬9£©
                                    0, 0,-1,-1,-2,-2,-3,-3,-4,-4,     //£¨10£¬19£©
                                   -5,-5,-6,-7,-7,-8,-8,-9,-10,-10    //£¨20£¬29£©
                                   -11,-12,-12,-13,-13,-14 };         //£¨30£¬35£©
        
        int ren_array[56] = { 49,48,47,46,45,44,43,42,41,40,     //£¨-20£¬-11£©
                              39,38,37,37,36,36,35,34,34,33,     //£¨-10£¬-1£©
                              32,32,31,31,30,30,29,29,28,28,     //£¨0£¬9£©
                              28,27,27,26,26,25,25,24,24,23,     //£¨10£¬19£©
                              23,23,23,22,22,21,21,20,20,20,     //£¨20£¬29£©
                              19,19,18,18,17,17};                //£¨30£¬35£©
        
        int ramp_array[56] = { 0,0,0,0,0,0,0,0,0,0,                  //£¨-20£¬-11£©
                               0,0,0,0,0,56,58,60,62,62,             //£¨-10£¬-1£©
                               64,66,66,69,72,72,74,74,78,78,        //£¨0£¬9£©                           
                               78,80,80,82,84,86,88,90,90,94,        //£¨10£¬19£©
                               94,98,98,100,100,100,100,100,100,100  //£¨20£¬29£©                               
                              };                                   
                                                                 
        typedef struct                                          
        {                                                         
            int row;
      	    int col;
      	    int pointnumber;  
      	    int angle;
        }angledef;

        angledef     leftposmaxangle;
        angledef     leftnegmaxangle;
        angledef     leftfoldangle;
        
        angledef     rightposmaxangle;
        angledef     rightnegmaxangle;
        angledef     rightfoldangle;
        
        angledef     leftsixtyone;
        angledef     leftsixtytwo;
        angledef     leftsixtythree;
        
        angledef     rightsixtyone;
        angledef     rightsixtytwo;
        angledef     rightsixtythree;
       
#endif