#include  "common.h"
#include  "darw.h"
#include "DEFINEimg.h"

void darw_point_anti(uint8 pData[ROW][COL],uint8 row,uint8 col){
  pData[row][col]=~pData[row][col];
}

void darw_num(uint8 pData[ROW][COL],int num,uint8 row,uint8 col){
  if(num<0){
    num=-num;
    
    darw_point_anti(pData,row + 2,col - 2);
    darw_point_anti(pData,row + 2,col - 3);
  }
  
  switch(num){
  case 0:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 1:
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 2:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 3:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 4:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 5:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 6:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 7:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 8:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 9:
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 10://A
    darw_point_anti(pData,row + 0,col + 1);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 11://B
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    
    darw_point_anti(pData,row + 3,col + 0);
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    break;
  case 12://C
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    
    darw_point_anti(pData,row + 2,col + 0);
    
    darw_point_anti(pData,row + 3,col + 0);
    
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 13://D
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    
    darw_point_anti(pData,row + 1,col + 0);
    darw_point_anti(pData,row + 1,col + 2);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    darw_point_anti(pData,row + 3,col + 2);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    break;
  case 14://E
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    
    darw_point_anti(pData,row + 4,col + 0);
    darw_point_anti(pData,row + 4,col + 1);
    darw_point_anti(pData,row + 4,col + 2);
    break;
  case 15://F
    darw_point_anti(pData,row + 0,col + 0);
    darw_point_anti(pData,row + 0,col + 1);
    darw_point_anti(pData,row + 0,col + 2);
    
    darw_point_anti(pData,row + 1,col + 0);
    
    darw_point_anti(pData,row + 2,col + 0);
    darw_point_anti(pData,row + 2,col + 1);
    darw_point_anti(pData,row + 2,col + 2);
    
    darw_point_anti(pData,row + 3,col + 0);
    
    darw_point_anti(pData,row + 4,col + 0);
    break;
  }
}

void darw_num1(uint8 pData[ROW][COL],int num,uint8 row,uint8 col){
  if(num<0)num=-num;
  
  darw_num(pData,num,row,col);
  
}

void darw_hat(uint8 pData[ROW][COL],uint8 row,uint8 col){
  
  darw_point_anti(pData,row - 2,col - 2);
  darw_point_anti(pData,row - 2,col - 1);
  darw_point_anti(pData,row - 2,col + 0);
  darw_point_anti(pData,row - 2,col + 1);
  darw_point_anti(pData,row - 2,col + 2);
  darw_point_anti(pData,row - 2,col + 3);
  darw_point_anti(pData,row - 2,col + 4);
  
  darw_point_anti(pData,row - 1,col - 2);
  darw_point_anti(pData,row - 1,col + 4);
  
  darw_point_anti(pData,row + 0,col - 2);
  darw_point_anti(pData,row + 0,col + 4);
  
}

void darw_ren(uint8 pData[ROW][COL]){
  darw_point_anti(pData,REN_ROW,REN_COL);
  darw_point_anti(pData,REN_ROW,REN_COL+1);
  
  darw_point_anti(pData,REN_ROW+1,REN_COL);
  darw_point_anti(pData,REN_ROW+1,REN_COL+2);
  
  darw_point_anti(pData,REN_ROW+2,REN_COL);
  darw_point_anti(pData,REN_ROW+2,REN_COL+1);
  
  darw_point_anti(pData,REN_ROW+3,REN_COL);
  darw_point_anti(pData,REN_ROW+3,REN_COL+2);
}

void darw_c(uint8 pData[ROW][COL]){
  darw_point_anti(pData,C_ROW,C_ROW+1);
  darw_point_anti(pData,C_ROW,C_ROW+2);
  
  darw_point_anti(pData,C_ROW+1,C_ROW);
  
  darw_point_anti(pData,C_ROW+2,C_ROW);
  
  
  darw_point_anti(pData,C_ROW+3,C_ROW+1);
  darw_point_anti(pData,C_ROW+3,C_ROW+2);
  
  
}

void darw_speed(uint8 pData[ROW][COL]){
  darw_num(pData,(int)g_fCarSpeed,SPEED_ROW,SPEED_COL);
}

void darw_speed_set(uint8 pData[ROW][COL]){
  darw_num(pData,(int)CAR_SPEED_SETfDelta,SPEED_ROW,SPEED_COL+6);
}

void darw_ren_hat(uint8 pData[ROW][COL]){
  darw_hat(pData,REN_ROW,REN_COL);
}

void darw_left(uint8 pData[ROW][COL]){
  darw_num(pData,(int)g_nLeftVoltageSigma,LEFT_ROW,LEFT_COL);
}

void darw_right(uint8 pData[ROW][COL]){
  darw_num(pData,(int)g_nRightVoltageSigma,RIGHT_ROW,RIGHT_COL);
}

void darw_angle(uint8 pData[ROW][COL]){
  darw_num(pData,(int)g_fCarAngle/10,ANGEL_ROW,ANGEL_COL);
  darw_num1(pData,(int)g_fCarAngle%10,ANGEL_ROW,ANGEL_COL+6);
}

void darw_ctrl(uint8 pData[ROW][COL]){
  if(A_Ctrlflag>0){
    darw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 0);
    darw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 1);
    darw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 2);
    darw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 3);
    
    darw_point_anti(pData,CTRL_ROW + 1,CTRL_COL + 0);
    darw_point_anti(pData,CTRL_ROW + 1,CTRL_COL + 3);
  }
  if(S_Ctrlflag>0){
    darw_point_anti(pData,CTRL_ROW + 2,CTRL_COL + 0);
    
    darw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 0);
    darw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 1);
  }
  if(D_Ctrlflag>0){
    darw_point_anti(pData,CTRL_ROW + 2,CTRL_COL + 3);
    
    darw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 2);
    darw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 3);
  }
}

