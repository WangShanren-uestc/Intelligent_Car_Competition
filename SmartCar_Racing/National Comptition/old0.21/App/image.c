#include "image.h"


void drawstartline(uint8 pData[ROW][COL])
{
	 int i=0,j=0;	 
         
     
	 memset(Leftline,0,sizeof(int)*60);
	 memset(Rightline,0,sizeof(int)*60);
	 memset(Centreline,0,sizeof(int)*60);
         memset(StartLeftLost,0,sizeof(int)*60);
         memset(StartRightLost,0,sizeof(int)*60);
         
	 
	 
	  Rightline[Startline]=COL-1;
	  Leftline[Startline]=0;
//	  Centreline[Startline]=COL/2;
    /***寻找起始线,起始线不存在则补线***/
          
          
	i=Startline;
          
        for(j=COL/2;j<=COL-2;j++)
	{   
	      if((uint8)pData[i][j-1]>=threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]<threshold_1)
		  {
			  Rightline[i]=j;break;
		  }
	}
	for(j=COL/2;j>=1;j--)
	{
	      if((uint8)pData[i][j-1]<threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]>=threshold_1)
		  {
			  Leftline[i]=j;break;
		  }
	}
        Centreline[i]=(Rightline[i]+Leftline[i])/2;
          
          
	for(i=Startline-3;i>Endline;i-=3)
	    {  
              
            
                for(j=Centreline[i+3];j<=COL-2;j++)
                {   
                        
                      if((uint8)pData[i][j-1]>=threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]<threshold_1)
                          {
                                  Rightline[i]=j; StartRightLost[i]=1;break;
                          }
                }
                for(j=Centreline[i+3];j>=1;j--)
                {
                    
                      if((uint8)pData[i][j-1]<threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]>=threshold_1)
                          {
                                  Leftline[i]=j;StartLeftLost[i]=1;break;
                          }				
                }
                if((StartLeftLost[i]&&StartRightLost[i]))
                {
                  Centreline[i]=(Rightline[i]+Leftline[i])/2;
                }
                else if(StartLeftLost[i]==0&&StartRightLost[i]==1)
                {
                  Centreline[i]=Centreline[i+3]+Rightline[i]-Rightline[i+3];
                  Leftline[i]=0;
                  if(Centreline[i]<0) Centreline[i]=0;
                }
                else if(StartLeftLost[i]==1&&StartRightLost[i]==0)
                {
                  Centreline[i]=Centreline[i+3]+Leftline[i]-Leftline[i+3];
                  Rightline[i]=COL-1;
                 if(Centreline[i]>COL) Centreline[i]=COL;  
                }	
                else{
                  Centreline[i]=COL/2;
                  Leftline[i]=0;
                  Rightline[i]=COL-1;
                }
                
#if DARW_1 
		  pData[i][Rightline[i]-2]=0;
		  pData[i][Leftline[i]+2]=0;
                  pData[i][Centreline[i]]=0;
#endif
	   }
        
              
              
                  /******十字路识别后从上往下补线*****/
        
}

void drawforwardline(uint8 pData[ROW][COL])//前瞻约60cm
{
     int j=0,i=0;	 
     


	 ForwardLeftLost=1;
	 ForwardRightLost=1;
         borderjump = 0;
         forwardture = 0;
         
         Turnright=0;
         Turnleft=0;
         
         

	   for(j=Centreline[32];j<=COL-5;j++)
	     { 
		    
                        if((uint8)pData[Forward][j-1]>=threshold_1 && (uint8)pData[Forward][j]<threshold_1 && (uint8)pData[Forward][j+1]<threshold_1)
                              {
					  Forwardrightline[Forward]=j; 
					   ForwardRightLost=0;break;
			      }
	     }	 
	   for(j=Centreline[32];j>=4;j--)
	     {
		   
	         if((uint8)pData[Forward][j-1]<threshold_1 && (uint8)pData[Forward][j]<threshold_1 && (uint8)pData[Forward][j+1]>=threshold_1)
				  {
					   Forwardleftline[Forward]=j; 
					   ForwardLeftLost=0;break;
			      }
	     }	
           
           
           
           
           
           
           if(ForwardRightLost==0 && ForwardLeftLost==0){
             Forwardcentreline[Forward] = (Forwardrightline[Forward] + Forwardleftline[Forward])/2;
             
             for(i=Forward+1;i<Endline;i++){
               
               if((uint8)pData[i][Forwardcentreline[Forward]]<threshold_1){
                 borderjump = 1;//跳界
                 break;
               }
             }
             if(borderjump==0)forwardture = 1;
             
           }
	   else if(ForwardRightLost==1 && ForwardLeftLost==0)
	   {
             Forwardcentreline[Forward] = (COL-1 + Forwardleftline[Forward])/2;
             
             for(i=Forward+1;i<Endline;i++){
               
               if((uint8)pData[i][Forwardcentreline[Forward]]<threshold_1){
                 borderjump = 1;//跳界
                 break;
               }
             }
             
             
             if(borderjump == 0){
               forwardture = 1;
                     Turnright=1;//前瞻丢右线表明右转
                      
//                  if(RenRoadFLAG==0){
//                    dirdir = 1;
//                    RenRoadRecognize(pData);
//                  }
             }
             
	    
            
            

	   }
	   else if(ForwardRightLost==0 && ForwardLeftLost==1)
	   {
	    
             Forwardcentreline[Forward] = Forwardrightline[Forward]/2;
             
             for(i=Forward+1;i<Endline;i++){
               
               if((uint8)pData[i][Forwardcentreline[Forward]]<threshold_1){
                 borderjump = 1;//跳界
                 break;
               }
             }
             
             
             if(borderjump == 0){
               forwardture = 1;
                   Turnleft=1;//前瞻丢左线表明左转	

//                if(RenRoadFLAG==0){
//                  dirdir = 0;
//                  RenRoadRecognize(pData);
//                }
             }
             

	   }
	   else  {
             
             forwardture = 0;
             
             for(i=Forward+1;i<Endline;i++){
               
               if((uint8)pData[i][Forwardcentreline[Forward]]<threshold_1){
                 borderjump = 1;//跳界
                 break;
               }
             }
             
             
             if(borderjump==0){
                  crossroadrecognize(pData);
             }
             
           }  /**两条线都丢**/
           
           if(CrosssroadFLAG==1)
                crossroadrecognize(pData);
#if DARW_1            
	   pData[Forward][Forwardcentreline[Forward]]=0;   
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Qipaoxian(uint8 pData[ROW][COL]){
  int i = 0,j = 0;
  int blackpointcount = 0;
  
  for(i=Startline;i>Startline-20;i--){
    if(pData[i][Centreline[Startline]-7]<threshold_1&&pData[i][Centreline[Startline]+7]<threshold_1&&StartRightLost[23]==1&&StartLeftLost[23]==1){
      for(j=Leftline[23]+1;j<Rightline[23]-1;j++){
        if(pData[i][j]<threshold_1)
          blackpointcount++;
      }
    }
  }
  if(blackpointcount>6){
    
    
      if(Qipaoflag==0){
        pit_init_ms(PIT0,2000);
        enable_irq (PIT_IRQn);
//        uart_putchar (UART0, 'Q');
      }
      else{
        pit_init_ms(PIT0,200);
        enable_irq (PIT_IRQn);
      }
    
  }
}


void crossroadrecognize(uint8 pData[ROW][COL])
{
  int leftwidth=0;
  int rightwidth=0;
  
    
      leftwidth=widthmesure(0,pData);
      rightwidth=widthmesure(1,pData);
      
      if(leftwidth>=15&&rightwidth>=15){
        CrosssroadFLAG=1;
//        uart_putchar (UART0, '+');
      }
      else if(CrosssroadFLAG==1&&(leftwidth<5||rightwidth<5)){
                  CrosssroadFLAG=0; 
//                  uart_putchar (UART0, '-');
//                  uart_putchar (UART0, '\n');
      }
              
}


float crossroadpro(uint8 pData[ROW][COL]){
  
  int i = 0,j = 0;
  float crossoffset = 0;
  
  for(i=Startline+3;i<=59;i+=3)
    {  
        for(j=Centreline[i-3];j<=COL-2;j++)
        {   
              if((uint8)pData[i][j-1]>=threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]<threshold_1)
                  {
                          Rightline[i]=j; StartRightLost[i]=1;break;
                  }
        }
        for(j=Centreline[i-3];j>=1;j--)
        {
              if((uint8)pData[i][j-1]<threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]>=threshold_1)
                  {
                          Leftline[i]=j;StartLeftLost[i]=1;break;
                  }				
        }
        if((StartLeftLost[i]&&StartRightLost[i]))
        {
          crossoffset+=(Rightline[i]+Leftline[i])/2-MID;
        }
    }
  
  for(i=29;i>10;i-=3)
    {  
        for(j=Centreline[i+3];j<=COL-2;j++)
        {   
              if((uint8)pData[i][j-1]>=threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]<threshold_1)
                  {
                          Rightline[i]=j; StartRightLost[i]=1;break;
                  }
        }
        for(j=Centreline[i+3];j>=1;j--)
        {
              if((uint8)pData[i][j-1]<threshold_1 && (uint8)pData[i][j]<threshold_1 && (uint8)pData[i][j+1]>=threshold_1)
                  {
                          Leftline[i]=j;StartLeftLost[i]=1;break;
                  }				
        }
        if((StartLeftLost[i]&&StartRightLost[i]))
        {
          crossoffset+=(float)((Rightline[i]+Leftline[i])/2-MID)*i/ROW;
        }
    }
  return crossoffset;
  
}


int lengthmeasure(uint8 pData[ROW][COL],int point_x,int point_y)
  {
	    
	  int i=0;int length=0;

	for(i=point_x;i>1;i--)
	{
			
			 if((uint8)pData[i][point_y]>=threshold_1)
			   {
				   length++;
				   if(pData[i-1][point_y]<threshold_1)
				    {
						return length;
				    }
			   }
			 else if((uint8)pData[i][point_y]<threshold_1)
			   {
				   length++;
				   if((uint8)pData[i-1][point_y]>=threshold_1)
				     {
						 return length;
				     }
			   }  
			 else return 0;
         }
        return 0;
}




//void RenRoadRecognize(uint8 pData[ROW][COL])
//{
//	
//	 int i=0;
//	 int midp = 1,leftp = 0,rightp = 0;
//         
//	 int length=0;
//	 int j=Forwardrightline[Forward]*Turnleft+Forwardleftline[Forward]*Turnright;
//	 
//         int whitelinecount = 0,blacklinecount = 0;
//         
//         
//         if(Centreline[23]<9||Centreline[23]>COL-10)return;
//         
//           for(i=23;i>3;i--){
//             if(pData[i][Centreline[23]]>=threshold_1&&pData[i-1][Centreline[23]]<threshold_1&&pData[i-2][Centreline[23]]<threshold_1){
//               midp = i;
//               break;
//             }
//           }
//           for(i=23;i>3;i--){
//             if(pData[i][Centreline[23]-8]>=threshold_1&&pData[i-1][Centreline[23]-8]<threshold_1&&pData[i-2][Centreline[23]-8]<threshold_1){
//               leftp = i;
//               break;
//             }
//           }
//           for(i=23;i>3;i--){
//             if(pData[i][Centreline[23]+8]>=threshold_1&&pData[i-1][Centreline[23]+8]<threshold_1&&pData[i-2][Centreline[23]+8]<threshold_1){
//               rightp = i;
//               break;
//             }
//           }
//         if(leftp<midp||rightp<midp)return;
//         
//        
//         
//         
//	for(i=Forward-1;i>3;i--)
//	{
//            if((uint8)pData[i][j]>=threshold_1)
//             {
//                 length=lengthmeasure(pData,i,j);
//                   if(length==0)
//                   {
//                       break;
//                   }
//                   if(length>=2&&length<=5)
//                   {
//                       whitelinecount++;
//                       i-=(length-1);
//                   }
//             }
//            else if((uint8)pData[i][j]<threshold_1)
//             {
//                    length=lengthmeasure(pData,i,j);
//                     if(length==0)
//                             {
//                                 break;
//                             }
//                     if(length>=2&&length<=5)
//                     {
//                         blacklinecount++;
//                         i-=(length-1);
//                     }
//             }
//	}
//	if(blacklinecount+whitelinecount>=4)
//         {
//                  
//           if((dirdir==1)&&g_fDIR>0)
//             RenRoadFLAG=1;
//           else if((dirdir==0)&&g_fDIR<0)
//             RenRoadFLAG=1;
//               
//         }
//}


int widthmesure(int dirr,uint8 pData[ROW][COL]){
  
  int up = 0,down = 0,i=0;
  
  
  if(dirr==1){ //Right
    for(i=ROW-1;i>1;i--)
    {
          
    
          if(pData[i-1][COL-2]<threshold_1 && (uint8)pData[i][COL-2]>=threshold_1 && (uint8)pData[i+1][COL-2]>=threshold_1)
            {
              up=i;break;		 
            }	
    
    }
    if(up==0){
      return 0;
    }
     for(i=ROW-1;i>1;i--)
    {
          if(pData[i-1][COL-2]>=threshold_1 && (uint8)pData[i][COL-2]>=threshold_1 && (uint8)pData[i+1][COL-2]<threshold_1)
              {
                  down=i;break;
              }
    }
    
    
    if(down==0||(down<up))down=ROW-1;
    
    return(down-up);
    
  }
  else{
    for(i=ROW-1;i>1;i--)
    {
          
    
          if(pData[i-1][2]<threshold_1 && (uint8)pData[i][2]>=threshold_1 && (uint8)pData[i+1][2]>=threshold_1)
            {
              up=i;break;		 
            }	
          
    
    }
    if(up==0){
      return 0;
    }
     for(i=ROW-1;i>1;i--)
    {
          if(pData[i-1][2]>=threshold_1 && (uint8)pData[i][2]>=threshold_1 && (uint8)pData[i+1][2]<threshold_1)
              {
                  down=i;break;
              }
    }
    
    if(down==0||(down<up))down=ROW-1;
    
    return(down-up);

  }
  
}


//float fivepoint(int direction,uint8 pData[ROW][COL])
//{             
//      int i=0;    
//      int P1_col=0;
//      int P2_col=0;
//      int P3_col=0;
//      int P4_col=0; 
//      int P5_col=0;	 
//      int P1_row=0;
//      int P2_row=0;
//      int P3_row=0;
//      int P4_row=0; 
//      int P5_row=0;	
//      float k=0;
//	 /*****人字右转*****/
//	 if(direction==1)
//	 {
//		          /****求出顶点****/
//	              for(i=ROW-1;i>1;i--)
//	              {  
//		         if(pData[i-1][COL-1]<threshold_1 && (uint8)pData[i][COL-1]>=threshold_1 && (uint8)pData[i+1][COL-1]>=threshold_1)
//		         {
//		           P5_row=i;
//		           break;		 
//		         }			      
//	              }
//	
//		         /*****求出各点*****/
//		   if(P5_row!=0)
//		   {
//		        P1_col=Centreline[Startline];
//		        P2_col=P1_col+(COL-1-Centreline[Startline])/4;
//		        P3_col=P2_col+(COL-1-Centreline[Startline])/4;
//		        P4_col=P3_col+(COL-1-Centreline[Startline])/4;
//			P5_col=COL-1;
//
//		        P1_row=Startline;
//	                P2_row= P1_row-(Startline-P5_row)/4;
//                        P3_row= P2_row-(Startline-P5_row)/4;
//	                P4_row= P3_row-(Startline-P5_row)/4;
//			P5_row=P5_row;
//		   }
//              
//          k = (float)(P1_row*(P1_col - MID) + P2_row*(P2_col - MID) + P3_row*(P3_col - MID) + P4_row*(P4_col - MID) +P5_row*(P5_col - MID))/4/ROW;     
//          
//          }   
//  
//	  /*****人字左转*****/
//	else  
//	{
//	               /****求出顶点****/
//	               for(i=ROW-1;i>1;i--)
//	              {		      
//		         if(pData[i-1][1]<threshold_1 && (uint8)pData[i][1]>=threshold_1 && (uint8)pData[i+1][1]>=threshold_1)
//		          {
//		           P5_row=i;
//		           break;		 
//		          }			      
//	              }
//	
//		     /*****求出各点*****/
//		     if(P5_row!=0)
//		   {
//		        P1_col=Centreline[Startline];
//		        P2_col=P1_col-(Centreline[Startline]-1)/4;
//		        P3_col=P2_col-(Centreline[Startline]-1)/4;
//		        P4_col=P3_col-(Centreline[Startline]-1)/4;
//			P5_col=1;
//
//		        P1_row=Startline;
//	                P2_row= P1_row-(Startline-P5_row)/4;
//                        P3_row= P2_row-(Startline-P5_row)/4;
//	                P4_row= P3_row-(Startline-P5_row)/4;
//			P5_row=P5_row;
//		   }	
//                   
//          k = (float)(P1_row*(P1_col - MID) + P2_row*(P2_col - MID) + P3_row*(P3_col - MID) + P4_row*(P4_col - MID) +P5_row*(P5_col - MID))/4/ROW;
//
//	 } 
//
//       return k;
//
//}
//
//
//
//void renpro(int dirr,uint8 pData[ROW][COL]){
//  
//  int width = 1;
//  
//  width = widthmesure(dirr,pData);
////  uart_putchar (UART0, 'u');
//  if(dirr==1){
////    uart_putchar (UART0, 'R');
//    if(width>25){
//      renflag = 1;
////       uart_putchar (UART0, 'r');
//    }
//    if(renflag == 1){
//      renoffset = fivepoint(dirr,pData);
//
//      
//      if(ture_point>4){
//        renflag = 0;
//        RenRoadFLAG=0;
////        uart_putchar (UART0, 'e');
////        uart_putchar (UART0, '\n');
//      }
//      
//    }
//  }
//  else{
//////    uart_putchar (UART0, 'L');
//    if(width>25){
//      renflag = 1;
////      uart_putchar (UART0, 'l');
//    }
//    if(renflag == 1){
//      renoffset = fivepoint(dirr,pData);
//      
//      
//      if(ture_point>4){
//        renflag = 0;
//        RenRoadFLAG=0;
////        uart_putchar (UART0, 'f');
////        uart_putchar (UART0, '\n');
//      }
//      
//    }
//  }
//}


void count_ture_point(uint8 pData[ROW][COL]){
  int i = 0;
  ture_point = 0;
  
  for(i=Startline;i>Endline;i-=3){
      
        if(StartLeftLost[i]==1&&StartRightLost[i]==1)ture_point++;
      
      }
  
}

//int optimal_path(void)
//{
//  int k1=0;
//  int k2=0;
//  int threshold_zhidao=4;
//  int threshold_wandao=8; 
//  k1=(Centreline[Startline-12]+Centreline[Startline-15]-2*Centreline[Startline]);
//  k2=(Centreline[Startline-6]+Centreline[Startline-3]-2*Centreline[Startline]);
//
// if(abs(k2)<threshold_zhidao&&StartLeftLost[Startline-6]==1&&StartLeftLost[Startline-3]==1
//  &&StartRightLost[Startline-6]==1&&StartRightLost[Startline-3]==1)
// {
//  if(k1>threshold_wandao)
//   {
//    /*****右转偏差量增量_正值*****/
//    return k1;
//   }
//  else if(k1<-threshold_wandao)
//   {
//    /*****左转偏差量增量_负值*****/
//     return k1;
//   }
// }
//return 0;
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void offsetcal(uint8 pData[ROW][COL]){
  int i = 0,j = 0;
  float offset=0;
//  int roadfix = 0;
//  
//  roadfix = optimal_path();
  
  
  if(renflag == 1){
    g_fDIR = 2*renoffset;
    
    darw_ren(pData);

  }
  else if(CrosssroadFLAG==1){
    
    
    g_fDIR =crossroadpro(pData)*4/3; 
     
    darw_c(pData);

  }
  else if(Turnright==1||Turnleft==1||forwardture == 0){
    for(i=Startline;i>Endline;i-=3){
      
      if(Centreline[i]==0||Centreline[i]==COL)continue;
      
      offset+=Centreline[i]-MID;
      j++;
    }

    
    if(j>0)
      g_fDIR = (offset*4/3/j);

  }
  else{
    for(i=Startline;i>Endline;i-=3){
      
      if(Centreline[i]==0||Centreline[i]==COL)continue;
      
      offset+=Centreline[i]-MID;
      j++;
    }
    
    g_fDIR= (float)(Forwardcentreline[Forward]-MID)*2/3;
    if(j>0) 
      g_fDIR=(offset/3/j)*2;
    

  }
#if DARW_1  
    pData[ROW-2][(int)(g_fDIR+MID)]=~pData[ROW-2][(int)(g_fDIR+MID)];
    pData[ROW-1][(int)(g_fDIR+MID)]=~pData[ROW-1][(int)(g_fDIR+MID)];
#endif
    
}



void filter(uint8 pData[ROW][COL])
{   int i=0;int j=0;
   
	for ( i = 1; i < ROW -1; i++ )  
        for( j = 1; j < COL - 1; j++ )  
	{  
          if((uint8)pData[i][j-1]+(uint8)pData[i][j+1]+(uint8)pData[i-1][j]+(uint8)pData[i+1][j]>=600)
                  pData[i][j]=255;
          if((uint8)pData[i-1][j]+(uint8)pData[i+1][j]+(uint8)pData[i][j+1]+(uint8)pData[i][j-1]<300)
                  pData[i][j]=0;
	
	}
	
}



//void Kittler( uint8 pData[ROW][COL] )  
//{  
//    int sumGrads = 0;  
//    int sumGrayGrads = 0;  
//    
//    int Grads;
//    
//
//    int i = 0,j =0;
////    int threshold;
//    
////    gpio_set (PTE26, 0);
//    
//    
//   
//    for (  i = 1; i < ROW - 1; i++ )  
//        for(  j = 1; j < COL - 1; j++ )  
//        {  
//             
//              
// 
//                  //求水平或垂直方向的最大梯度  
//             Grads=MAX(abs(pData[i][j-1]-pData[i][j+1]),abs(pData[i+1][j] -pData[i-1][j]));  
//            sumGrads += Grads;  
//            //梯度与当前点灰度的积  
//            sumGrayGrads += Grads*((uint8)pData[i][j]);  
//          
//    }  
//   threshold_1 = sumGrayGrads / sumGrads;  
////    printf("%d\n",threshold);  
//  
////    for (  i = 0; i < ROW; ++i )  
////        for(  j = 0; j <COL; ++j )  
////        {
////             
////            pData[i][j] = (uint8)pData[i][j] > threshold ? 0xFF : 0;  
////        }  
////      
////    gpio_set (PTE26, 1);
//    
//}  


void process(uint8 s[ROW][COL])
{
 	int i,j;
        uint8 threshold=130; 
 	     
 	for(i=0;i<ROW;i++)
 		for(j=0;j<COL;j++)
 		{
 			if(s[i][j]>threshold)
 			s[i][j]=0xFF;
 			else s[i][j]=0;//二值化
 		}

}	



void imagepro(uint8 pData[ROW][COL]){
  
  
  drawstartline(pData);
  drawforwardline(pData);
  count_ture_point(pData);
//  
//  if(ture_point>7){
//    Qipaoxian(pData);
//  }
  
//  if(RenRoadFLAG==1){
//    renpro(dirdir,pData);
//    
//  }
  
  
  offsetcal(pData);
#if DARW_1
  if(RenRoadFLAG==1)darw_ren_hat(pData);
  darw_speed(pData);
  darw_speed_set(pData);
  darw_left(pData);
  darw_right(pData);
  darw_angle(pData);
  darw_ctrl(pData);
  if(Qipaoflag==1)darw_ren(pData);
#endif
  
}