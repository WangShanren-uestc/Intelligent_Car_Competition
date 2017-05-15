#include  "common.h"
#include  "darw.h"
#include "DEFINEimg.h"
extern double CarAngle;

void draw_point_anti(uint8 pData[ROW][COL],uint8 row,uint8 col){
  pData[row][col]=~pData[row][col];
}

void draw_num(uint8 pData[ROW][COL],int num,uint8 row,uint8 col){
  if(num<0){
    num=-num;
    
    draw_point_anti(pData,row + 2,col - 2);
    draw_point_anti(pData,row + 2,col - 3);
  }
  
  switch(num){
  case 0:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 1:
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 2:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 3:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 4:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 5:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 6:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 7:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 8:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 9:
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 10://A
    draw_point_anti(pData,row + 0,col + 1);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 11://B
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    
    draw_point_anti(pData,row + 3,col + 0);
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    break;
  case 12://C
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    
    draw_point_anti(pData,row + 2,col + 0);
    
    draw_point_anti(pData,row + 3,col + 0);
    
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 13://D
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    
    draw_point_anti(pData,row + 1,col + 0);
    draw_point_anti(pData,row + 1,col + 2);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    draw_point_anti(pData,row + 3,col + 2);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    break;
  case 14://E
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    
    draw_point_anti(pData,row + 4,col + 0);
    draw_point_anti(pData,row + 4,col + 1);
    draw_point_anti(pData,row + 4,col + 2);
    break;
  case 15://F
    draw_point_anti(pData,row + 0,col + 0);
    draw_point_anti(pData,row + 0,col + 1);
    draw_point_anti(pData,row + 0,col + 2);
    
    draw_point_anti(pData,row + 1,col + 0);
    
    draw_point_anti(pData,row + 2,col + 0);
    draw_point_anti(pData,row + 2,col + 1);
    draw_point_anti(pData,row + 2,col + 2);
    
    draw_point_anti(pData,row + 3,col + 0);
    
    draw_point_anti(pData,row + 4,col + 0);
    break;
  }
}

void draw_num1(uint8 pData[ROW][COL],int num,uint8 row,uint8 col){
  if(num<0)num=-num;
  
  draw_num(pData,num,row,col);
  
}

void draw_hat(uint8 pData[ROW][COL],uint8 row,uint8 col){
  
  draw_point_anti(pData,row - 2,col - 2);
  draw_point_anti(pData,row - 2,col - 1);
  draw_point_anti(pData,row - 2,col + 0);
  draw_point_anti(pData,row - 2,col + 1);
  draw_point_anti(pData,row - 2,col + 2);
  draw_point_anti(pData,row - 2,col + 3);
  draw_point_anti(pData,row - 2,col + 4);
  
  draw_point_anti(pData,row - 1,col - 2);
  draw_point_anti(pData,row - 1,col + 4);
  
  draw_point_anti(pData,row + 0,col - 2);
  draw_point_anti(pData,row + 0,col + 4);
  
}

void draw_ren(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL);
  draw_point_anti(pData,REN_ROW,REN_COL+1);
  
  draw_point_anti(pData,REN_ROW+1,REN_COL);
  draw_point_anti(pData,REN_ROW+1,REN_COL+2);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL);
  draw_point_anti(pData,REN_ROW+2,REN_COL+1);
  
  draw_point_anti(pData,REN_ROW+3,REN_COL);
  draw_point_anti(pData,REN_ROW+3,REN_COL+2);
}

void draw_c(uint8 pData[ROW][COL]){
  draw_point_anti(pData,C_ROW,C_COL+1);
  draw_point_anti(pData,C_ROW,C_COL+2);
  
  draw_point_anti(pData,C_ROW+1,C_COL);
  
  draw_point_anti(pData,C_ROW+2,C_COL);
  
  
  draw_point_anti(pData,C_ROW+3,C_COL+1);
  draw_point_anti(pData,C_ROW+3,C_COL+2);
  
  
}

void draw_speed(uint8 pData[ROW][COL]){
  draw_num(pData,(int)NowSpeed*10,SPEED_ROW,SPEED_COL);
}

void draw_speed_set(uint8 pData[ROW][COL]){
  draw_num(pData,(int)uSet*10,SPEED_ROW,SPEED_COL+6);
}

void draw_ren_hat(uint8 pData[ROW][COL]){
  draw_hat(pData,REN_ROW,REN_COL);
}

void draw_left(uint8 pData[ROW][COL]){
  draw_num(pData,(int)g_nLeftVoltageSigma,LEFT_ROW,LEFT_COL);
}

void draw_right(uint8 pData[ROW][COL]){
  draw_num(pData,(int)g_nRightVoltageSigma,RIGHT_ROW,RIGHT_COL);
}

void draw_angle(uint8 pData[ROW][COL]){
  draw_num(pData,(int)CarAngle/10,ANGEL_ROW,ANGEL_COL);
  draw_num1(pData,(int)CarAngle%10,ANGEL_ROW,ANGEL_COL+6);
}

void draw_width(uint8 pData[ROW][COL]){
  extern int line1_width[];
  draw_num(pData,(int)(line1_width[1]/100)%10,ANGEL_ROW,ANGEL_COL-32);
  draw_num1(pData,(int)(line1_width[1]/10)%10,ANGEL_ROW,ANGEL_COL-26);
  draw_num1(pData,(int)line1_width[1]%10,ANGEL_ROW,ANGEL_COL-20);
}

void draw_ctrl(uint8 pData[ROW][COL]){
  if(A_Ctrlflag>0){
    draw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 0);
    draw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 1);
    draw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 2);
    draw_point_anti(pData,CTRL_ROW + 0,CTRL_COL + 3);
    
    draw_point_anti(pData,CTRL_ROW + 1,CTRL_COL + 0);
    draw_point_anti(pData,CTRL_ROW + 1,CTRL_COL + 3);
  }
  if(S_Ctrlflag>0){
    draw_point_anti(pData,CTRL_ROW + 2,CTRL_COL + 0);
    
    draw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 0);
    draw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 1);
  }
  if(D_Ctrlflag>0){
    draw_point_anti(pData,CTRL_ROW + 2,CTRL_COL + 3);
    
    draw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 2);
    draw_point_anti(pData,CTRL_ROW + 3,CTRL_COL + 3);
  }
}

void draw_s(uint8 pData[ROW][COL]){
    
    draw_point_anti(pData,S_ROW + 0,S_COL + 1);
    draw_point_anti(pData,S_ROW + 0,S_COL + 2);
                         
    draw_point_anti(pData,S_ROW + 1,S_COL + 0);
  
    draw_point_anti(pData,S_ROW + 2,S_COL + 1);
                       
    draw_point_anti(pData,S_ROW + 3,S_COL + 2);
                          
    draw_point_anti(pData,S_ROW + 4,S_COL + 0);
    draw_point_anti(pData,S_ROW + 4,S_COL + 1);
  
}

void draw_zhidao(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL);
  draw_point_anti(pData,REN_ROW,REN_COL+2);
  
  draw_point_anti(pData,REN_ROW+1,REN_COL);
  draw_point_anti(pData,REN_ROW+1,REN_COL+2);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL);
  draw_point_anti(pData,REN_ROW+2,REN_COL+2);
  
  draw_point_anti(pData,REN_ROW+3,REN_COL);
  draw_point_anti(pData,REN_ROW+3,REN_COL+2);
}
void draw_zhangaiwu(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL);
  draw_point_anti(pData,REN_ROW,REN_COL+1);
  
  draw_point_anti(pData,REN_ROW+1,REN_COL);
  draw_point_anti(pData,REN_ROW+1,REN_COL+1);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL);
  draw_point_anti(pData,REN_ROW+2,REN_COL+1);  
  
}
void draw_xiaos(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL);
  draw_point_anti(pData,REN_ROW,REN_COL+3);
  
  draw_point_anti(pData,REN_ROW+1,REN_COL+1);
  draw_point_anti(pData,REN_ROW+1,REN_COL+4);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL);
  draw_point_anti(pData,REN_ROW+2,REN_COL+3);
  
  draw_point_anti(pData,REN_ROW+3,REN_COL+1);
  draw_point_anti(pData,REN_ROW+3,REN_COL+4);
}
void draw_wandao(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL+1);  
  
  draw_point_anti(pData,REN_ROW+1,REN_COL);  
  
  draw_point_anti(pData,REN_ROW+2,REN_COL);  
 
  draw_point_anti(pData,REN_ROW+3,REN_COL+1);
}
void draw_renzi(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW-1,REN_COL+2);  
  draw_point_anti(pData,REN_ROW,REN_COL+2);  
  
  draw_point_anti(pData,REN_ROW+1,REN_COL+1);
  draw_point_anti(pData,REN_ROW+1,REN_COL+2);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL);
  draw_point_anti(pData,REN_ROW+2,REN_COL+3);
  
  draw_point_anti(pData,REN_ROW+3,REN_COL-1); 
    draw_point_anti(pData,REN_ROW+3,REN_COL+4);  
  
}
void draw_shizi(uint8 pData[ROW][COL]){  
  draw_point_anti(pData,REN_ROW,REN_COL+1);
  
  draw_point_anti(pData,REN_ROW+1,REN_COL);
  draw_point_anti(pData,REN_ROW+1,REN_COL+1);
  draw_point_anti(pData,REN_ROW+1,REN_COL+2);  
 
  draw_point_anti(pData,REN_ROW+2,REN_COL+1);  
}
void draw_jiwan(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL+2);  
  
  draw_point_anti(pData,REN_ROW+1,REN_COL+1);
  draw_point_anti(pData,REN_ROW+1,REN_COL+3);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL); 
   draw_point_anti(pData,REN_ROW+2,REN_COL+4); 
  
}
void draw_podao(uint8 pData[ROW][COL]){
  draw_point_anti(pData,REN_ROW,REN_COL+1);
  draw_point_anti(pData,REN_ROW,REN_COL+2);
  draw_point_anti(pData,REN_ROW,REN_COL+3);
  draw_point_anti(pData,REN_ROW,REN_COL+4);
  draw_point_anti(pData,REN_ROW,REN_COL+5);
  
  draw_point_anti(pData,REN_ROW+1,REN_COL+3);
  
  draw_point_anti(pData,REN_ROW+2,REN_COL+3);
  
  draw_point_anti(pData,REN_ROW+3,REN_COL+3);
}



