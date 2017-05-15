#include "common.h"
#define ROW 60
#define COL 80
#define MaxNum 150

  int leftlinerow[150];
  int leftlinecol[150];
  int rightlinerow[150];
  int rightlinecol[150];
  int leftdirection[150];
  int rightdirection[150];
  int lefthighestpoint[3];
  int righthighestpoint[3];
  int leftpointnumber=0;
  int rightpointnumber=0;  

 

  /***中值滤波***/
void midfilter(uint8 *pData)
{
    int i=0;
    int j=0;
    int widthStep = COL;
    int curPos,up,down,left,right;
	  for(i=1;i<=ROW/2;i++)
	  {
		  for(j=1;j<COL;j++)
		  {   
                    curPos=i*widthStep+j;
		    up=(i+1)*widthStep+j;
		    down=(i-1)*widthStep+j;	
		    left=curPos-1;
		    right=curPos+1;

	           if(pData[up]==0&&pData[down]==0){pData[curPos]=0;}
		   else if(pData[left]==0&&pData[right]==0){pData[curPos]=0;}
		  }
	  }
}

  /**********采集起始线**********/
void getstartline(uint8 *pData)/***待改进（起始线读到起跑线和障碍物）***/
{  
  memset(leftlinerow,0,sizeof(int)*150);
  memset(leftlinecol,0,sizeof(int)*150);
  memset(rightlinerow,0,sizeof(int)*150);
  memset(rightlinecol,0,sizeof(int)*150);
  int i=0;
  int j=0; 
  int leftcol=3;
  int midcol_left=COL/2;
  int midcol_right=COL/2;
  int rightcol=COL-3;  
  int blackpointcount=0;

  int widthStep = COL;  
  int curPos=i*widthStep+j;
  int left1Pos,right1Pos;
  int left2Pos,right2Pos;

  /****采集左起始线****/
  for(i=ROW-3;i>2;i--)
  {
	  blackpointcount=0;
	  for(j=midcol_left;j>leftcol;j--)
	  {
		  curPos=i*widthStep+j;
		  left1Pos=curPos-1;
		  left2Pos=curPos-2;		 
		  if((uint8)pData[left2Pos]==0&&(uint8)pData[left1Pos]==0&&(uint8)pData[curPos]==255)
		  {
				leftlinerow[1]=ROW-i;//从下往上生长
	            leftlinecol[1]=j;
				leftdirection[1]=90;
				break;
		  }			 		  
		  if(pData[curPos]==0){blackpointcount++;}
	  }	
	  if(leftlinecol[1]==0){ midcol_left=8;}/**识别出十字路和弯道类型后midcol值要改**/
	 if((leftlinecol[1]!=0)||((blackpointcount>=3)&&(leftlinecol[1]==0))) break;/**找到线跳出||越界跳出**/
  }
  /*****采集右起始线****/
   for(i=ROW-3;i>2;i--)
 {
	  blackpointcount=0;
	  for(j=midcol_right;j<rightcol;j++)
	  {
		  curPos=i*widthStep+j;
		  right1Pos=curPos+1;
		  right2Pos=curPos+2;		 
		  if((uint8)pData[curPos]==255&&(uint8)pData[right1Pos]==0&&(uint8)pData[right2Pos]==0)
		  {
				rightlinerow[1]=ROW-i;//从下往上生长
	            rightlinecol[1]=j;
				rightdirection[1]=90;
				break;
		  }			  		
		  if(pData[curPos]==0){blackpointcount++;}
	  }	
	 if(rightlinecol[1]==0){ midcol_right=COL-8;}/**识别出十字路和弯道类型后midcol值要改**/
	 if((rightlinecol[1]!=0)||((blackpointcount>=3)&&(rightdirection[1]==0))) break;	/**找到线跳出||越界跳出**/
   } 
   
  

//   /*****防止冲出赛道第二方案****/
//   if((leftdirection[1]==0)&&(rightdirection[1]==0))
//   {        
//    for(j=5;j<=COL/2;j++)
//  	{
//	          curPos=(ROW-4)*widthStep+j;
//		  right1Pos=curPos+1;
//		  right2Pos=curPos+2;	
//
//		  if((uint8)pData[curPos]==255&&pData[right1Pos]==0&&pData[right2Pos]==0){rightlinerow[1]=3;rightlinecol[1]=j;rightdirection[1]=90;break;}
//	}
//   for(j=COL-5;j>=COL/2;j--)
//     {
//          curPos=(ROW-4)*widthStep+j;
//		  left1Pos=curPos-1;
//		  left2Pos=curPos-2;
//
//          if(pData[left2Pos]==0&&pData[left1Pos]==0&&(uint8)pData[curPos]==255)
//		  {  leftlinecol[1]=j;
//		      if(leftlinecol[1]-COL/2<COL/2-rightlinecol[1]){ leftlinerow[1]=3;leftdirection[1]=90;rightlinerow[1]=0;rightlinecol[1]=0;rightdirection[1]=0;}
//			  else leftlinecol[1]=0;
//			  break;}
//     }
//   }
 /**判断**/   
 if(leftdirection[1]==0||leftlinerow[1]>=ROW/2) {  leftdirection[1]=1;}
 if(rightdirection[1]==0||rightlinerow[1]>=ROW/2){ rightdirection[1]=1;}
  
}

void trackpoint(uint8 *pData)
{
        int i=0;
        int j=0; 
	int leftanglerange=0;
	int rightanglerange=0;
	int leftpeakFLAG=0;
	int rightpeakFLAG=0;
        leftpointnumber=0;
        rightpointnumber=0;  
	memset(righthighestpoint,0,sizeof(int)*3);
	memset(lefthighestpoint,0,sizeof(int)*3);


    int widthStep = COL;
    
    int curPos;
    int right;
    int rightup;
    int up;
    int leftup;
    int left;
    int leftdown;
    int down;
    int rightdown;	
    
	
     /*******寻找左边线*******/
	 for(i=2;i<MaxNum;i++)/*最多寻MaxNum个点*/
	{ 
          leftanglerange=leftdirection[i-1];
		if(leftlinerow[i-1]>lefthighestpoint[0])  { lefthighestpoint[0]=leftlinerow[i-1];lefthighestpoint[1]=leftlinecol[i-1];lefthighestpoint[2]=i-1;}

		if((leftlinerow[i-1]>ROW-12||leftlinerow[i-1]<2||leftlinecol[i-1]<2||leftlinecol[i-1]>COL-2)&&(!leftpeakFLAG))
		{ break;}
		else if(!leftpeakFLAG){leftpointnumber++;}
		else if(leftpeakFLAG){leftanglerange+=90;if(leftanglerange-leftdirection[i-1]>180){break;}if(leftanglerange>=360){leftanglerange-=360;}}

		

		curPos=(ROW-leftlinerow[i-1])*widthStep+leftlinecol[i-1];
		right=(ROW-leftlinerow[i-1])*widthStep+leftlinecol[i-1]+1;
		rightup=(ROW-leftlinerow[i-1]-1)*widthStep+leftlinecol[i-1]+1;
		up=(ROW-leftlinerow[i-1]-1)*widthStep+leftlinecol[i-1];
		leftup=(ROW-leftlinerow[i-1]-1)*widthStep+leftlinecol[i-1]-1;
		left=(ROW-leftlinerow[i-1])*widthStep+leftlinecol[i-1]-1;
		leftdown=(ROW-leftlinerow[i-1]+1)*widthStep+leftlinecol[i-1]-1;
		down=(ROW-leftlinerow[i-1]+1)*widthStep+leftlinecol[i-1];
		rightdown=(ROW-leftlinerow[i-1]+1)*widthStep+leftlinecol[i-1]+1;			

		/***按方向巡线并去除毛刺***/
		switch(leftanglerange)
		{
		 case 0:
			 if((uint8)pData[down]==255&&pData[rightdown]==0) 
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=270;leftpeakFLAG=0;}
			 else if((uint8)pData[rightdown]==255&&pData[right]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=315;leftpeakFLAG=0;}
			 else if((uint8)pData[right]==255&&pData[rightup]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=0;leftpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&pData[up]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=45;leftpeakFLAG=0;}
			 else if((uint8)pData[down]==255&&(uint8)pData[rightdown]==255&&(uint8)pData[right]==255&&(uint8)pData[rightup]==255&&(uint8)pData[up]==255) 
			 {leftpeakFLAG=1;i=i-1;}break;
		 case 45:
	         if((uint8)pData[rightdown]==255&&pData[right]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=315;leftpeakFLAG=0;}
			 else if((uint8)pData[right]==255&&pData[rightup]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=0;leftpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&pData[up]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=45;leftpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&pData[leftup]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=90;leftpeakFLAG=0;}
			 else if((uint8)pData[rightdown]==255&&(uint8)pData[right]==255&&(uint8)pData[rightup]==255&&(uint8)pData[up]==255&&(uint8)pData[leftup]==255) 
			{leftpeakFLAG=1;i=i-1;}break;
		 case 90:
			 if((uint8)pData[right]==255&&pData[rightup]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=0;leftpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&pData[up]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=45;leftpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&pData[leftup]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=90;leftpeakFLAG=0;}
			 else if((uint8)pData[leftup]==255&&pData[left]==0)
			 { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=135;leftpeakFLAG=0;}
			 else if((uint8)pData[right]==255&&(uint8)pData[rightup]==255&&(uint8)pData[up]==255&&(uint8)pData[leftup]==255&&(uint8)pData[left]==255) 
			 {leftpeakFLAG=1;i=i-1;}break;
		 case 135:
			 if((uint8)pData[rightup]==255&&pData[up]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=45;leftpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&pData[leftup]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=90;leftpeakFLAG=0;}
			 else if((uint8)pData[leftup]==255&&pData[left]==0)
			 { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=135;leftpeakFLAG=0;}
			 else if((uint8)pData[left]==255&&pData[leftdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=180;leftpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&(uint8)pData[up]==255&&(uint8)pData[leftup]==255&&(uint8)pData[left]==255&&(uint8)pData[leftdown]==255) 
			 {leftpeakFLAG=1;i=i-1;}break;
		 case 180:
			 if((uint8)pData[up]==255&&pData[leftup]==0)
		     { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=90;leftpeakFLAG=0;}
			 else if((uint8)pData[leftup]==255&&pData[left]==0)
			 { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=135;leftpeakFLAG=0;}
			 else if((uint8)pData[left]==255&&pData[leftdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=180;leftpeakFLAG=0;}
			 else if((uint8)pData[leftdown]==255&&pData[down]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=225;leftpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&(uint8)pData[leftup]==255&&(uint8)pData[left]==255&&(uint8)pData[leftdown]==255&&(uint8)pData[down]==255) 
			{leftpeakFLAG=1;i=i-1;}break;
		 case 225:
			 if((uint8)pData[leftup]==255&&pData[left]==0)
			 { leftlinerow[i]=leftlinerow[i-1]+1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=135;leftpeakFLAG=0;}
			 else if((uint8)pData[left]==255&&pData[leftdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=180;leftpeakFLAG=0;}
			 else if((uint8)pData[leftdown]==255&&pData[down]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=225;leftpeakFLAG=0;}
			  else if((uint8)pData[down]==255&&pData[rightdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=270;leftpeakFLAG=0;}
			  else if((uint8)pData[leftup]==255&&(uint8)pData[left]==255&&(uint8)pData[leftdown]==255&&(uint8)pData[down]==255&&(uint8)pData[rightdown]==255) 
			 {leftpeakFLAG=1;i=i-1;}break;
		 case 270:
			  if((uint8)pData[left]==255&&pData[leftdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=180;leftpeakFLAG=0;}
			 else if((uint8)pData[leftdown]==255&&pData[down]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=225;leftpeakFLAG=0;}
			  else if((uint8)pData[down]==255&&pData[rightdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=270;leftpeakFLAG=0;}
			  else if((uint8)pData[rightdown]==255&&pData[right]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=315;leftpeakFLAG=0;}
			  else if((uint8)pData[left]==255&&(uint8)pData[leftdown]==255&&(uint8)pData[down]==255&&(uint8)pData[rightdown]==255&&(uint8)pData[right]==255) 
			 {leftpeakFLAG=1;i=i-1;}break;
		 case 315:
			 if((uint8)pData[leftdown]==255&&pData[down]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]-1;leftdirection[i]=225;leftpeakFLAG=0;}
			  else if((uint8)pData[down]==255&&pData[rightdown]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1];leftdirection[i]=270;leftpeakFLAG=0;}
			  else if((uint8)pData[rightdown]==255&&pData[right]==0)
			 { leftlinerow[i]=leftlinerow[i-1]-1;leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=315;leftpeakFLAG=0;}
			  else if((uint8)pData[right]==255&&pData[rightup]==0)
			 { leftlinerow[i]=leftlinerow[i-1];leftlinecol[i]=leftlinecol[i-1]+1;leftdirection[i]=0;leftpeakFLAG=0;}
			  else if((uint8)pData[leftdown]==255&&(uint8)pData[down]==255&&(uint8)pData[rightdown]==255&&(uint8)pData[right]==255&&(uint8)pData[rightup]==255) 
			 {leftpeakFLAG=1;i=i-1;}break;
		
		}
	   	
     }

	

	 /*****寻找右边线*****/
	for(i=2;i<MaxNum;i++)/*最多寻MaxNum个点*/
    { 
      rightanglerange=rightdirection[i-1];
		if(rightlinerow[i-1]>righthighestpoint[0]){ righthighestpoint[0]=rightlinerow[i-1];righthighestpoint[1]=rightlinecol[i-1];righthighestpoint[2]=i-1;}

		if(((rightlinerow[i-1]>ROW-12||rightlinerow[i-1]<2||rightlinecol[i-1]<2||rightlinecol[i-1]>COL-2)&&(!rightpeakFLAG))){ break;}
		else if(!rightpeakFLAG){rightpointnumber++;}
		else if(rightpeakFLAG)
		{rightanglerange+=90;if(rightanglerange-rightdirection[i-1]>180){break;}if(rightanglerange>=360){rightanglerange-=360;}}

		

		curPos=(ROW-rightlinerow[i-1])*widthStep+rightlinecol[i-1];
		right=(ROW-rightlinerow[i-1])*widthStep+rightlinecol[i-1]+1;
		rightup=(ROW-rightlinerow[i-1]-1)*widthStep+rightlinecol[i-1]+1;
		up=(ROW-rightlinerow[i-1]-1)*widthStep+rightlinecol[i-1];
		leftup=(ROW-rightlinerow[i-1]-1)*widthStep+rightlinecol[i-1]-1;
		left=(ROW-rightlinerow[i-1])*widthStep+rightlinecol[i-1]-1;
		leftdown=(ROW-rightlinerow[i-1]+1)*widthStep+rightlinecol[i-1]-1;
		down=(ROW-rightlinerow[i-1]+1)*widthStep+rightlinecol[i-1];
		rightdown=(ROW-rightlinerow[i-1]+1)*widthStep+rightlinecol[i-1]+1;			
		
		/***按方向巡线***/
		switch(rightanglerange)
		{
		 case 0:
			 if((uint8)pData[down]==255&&pData[leftdown]==0) 
			 {rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=270;rightpeakFLAG=0;}
			 else if((uint8)pData[leftdown]==255&&pData[left]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=315;rightpeakFLAG=0;}
			 else if((uint8)pData[left]==255&&pData[leftup]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=0;rightpeakFLAG=0;}
			 else if((uint8)pData[leftup]==255&&pData[up]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=45;rightpeakFLAG=0;}
			 else if((uint8)pData[down]==255&&(uint8)pData[leftdown]==255&&(uint8)pData[left]==255&&(uint8)pData[leftup]==255&&(uint8)pData[up]==255)
			 {rightpeakFLAG=1;i-=1;}break;
		 case 45:
	        if((uint8)pData[leftdown]==255&&pData[left]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=315;rightpeakFLAG=0;}
			 else if((uint8)pData[left]==255&&pData[leftup]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=0;rightpeakFLAG=0;}
			 else if((uint8)pData[leftup]==255&&pData[up]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=45;rightpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&pData[rightup]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=90;rightpeakFLAG=0;}
			 else if((uint8)pData[leftdown]==255&&(uint8)pData[left]==255&&(uint8)pData[leftup]==255&&(uint8)pData[up]==255&&(uint8)pData[rightup]==255)
			 {rightpeakFLAG=1;i-=1;}break;
		 case 90:
			 if((uint8)pData[left]==255&&pData[leftup]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=0;rightpeakFLAG=0;}
			 else if((uint8)pData[leftup]==255&&pData[up]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=45;rightpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&pData[rightup]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=90;rightpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&pData[right]==0)
			 { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=135;rightpeakFLAG=0;}
			 else if((uint8)pData[left]==255&&(uint8)pData[leftup]==255&&(uint8)pData[up]==255&&(uint8)pData[rightup]==255&&(uint8)pData[right]==255)
			 {rightpeakFLAG=1;i=i-1;}break;
		 case 135:
			if((uint8)pData[leftup]==255&&pData[up]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=45;rightpeakFLAG=0;}
			 else if((uint8)pData[up]==255&&pData[rightup]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=90;rightpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&pData[right]==0)
			 { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=135;rightpeakFLAG=0;}
			 else if((uint8)pData[right]==255&&pData[rightdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=180;rightpeakFLAG=0;}
			  else if((uint8)pData[leftup]==255&&(uint8)pData[up]==255&&(uint8)pData[rightup]==255&&(uint8)pData[right]==255&&(uint8)pData[rightdown]==255)
			  {rightpeakFLAG=1;i-=1;}break;
		 case 180:
			  if((uint8)pData[up]==255&&pData[rightup]==0)
		     { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=90;rightpeakFLAG=0;}
			 else if((uint8)pData[rightup]==255&&pData[right]==0)
			 { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=135;rightpeakFLAG=0;}
			 else if((uint8)pData[right]==255&&pData[rightdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=180;rightpeakFLAG=0;}
			 else if((uint8)pData[rightdown]==255&&pData[down]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=225;rightpeakFLAG=0;}
			  else if((uint8)pData[up]==255&&(uint8)pData[rightup]==255&&(uint8)pData[right]==255&&(uint8)pData[rightdown]==255&&(uint8)pData[down]==255)
			 {rightpeakFLAG=1;i-=1;}break;
		 case 225:
			if((uint8)pData[rightup]==255&&pData[right]==0)
			 { rightlinerow[i]=rightlinerow[i-1]+1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=135;rightpeakFLAG=0;}
			 else if((uint8)pData[right]==255&&pData[rightdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=180;rightpeakFLAG=0;}
			 else if((uint8)pData[rightdown]==255&&pData[down]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=225;rightpeakFLAG=0;}
			  else if((uint8)pData[down]==255&&pData[leftdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=270;rightpeakFLAG=0;}
			  else if((uint8)pData[rightup]==255&&(uint8)pData[right]==255&&(uint8)pData[rightdown]==255&&(uint8)pData[down]==255&&(uint8)pData[leftdown]==255)
			 {rightpeakFLAG=1;i-=1;}break;
		 case 270:
			 if((uint8)pData[right]==255&&pData[rightdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=180;rightpeakFLAG=0;}
			 else if((uint8)pData[rightdown]==255&&pData[down]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=225;rightpeakFLAG=0;}
			  else if((uint8)pData[down]==255&&pData[leftdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=270;rightpeakFLAG=0;}
			  else if((uint8)pData[leftdown]==255&&pData[left]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=315;rightpeakFLAG=0;}
			  else if((uint8)pData[right]==255&&(uint8)pData[rightdown]==255&&(uint8)pData[down]==255&&(uint8)pData[leftdown]==255&&(uint8)pData[left]==255)
			  {rightpeakFLAG=1;i-=1;}break;
		 case 315:
			 if((uint8)pData[rightdown]==255&&pData[down]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]+1;rightdirection[i]=225;rightpeakFLAG=0;}
			  else if((uint8)pData[down]==255&&pData[leftdown]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1];rightdirection[i]=270;rightpeakFLAG=0;}
			  else if((uint8)pData[leftdown]==255&&pData[left]==0)
			 { rightlinerow[i]=rightlinerow[i-1]-1;rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=315;rightpeakFLAG=0;}
			  else if((uint8)pData[left]==255&&pData[leftup]==0)
			 { rightlinerow[i]=rightlinerow[i-1];rightlinecol[i]=rightlinecol[i-1]-1;rightdirection[i]=0;}
			  else if((uint8)pData[rightdown]==255&&(uint8)pData[down]==255&&(uint8)pData[leftdown]==255&&(uint8)pData[left]==255&&(uint8)pData[leftup]==255)
			 {rightpeakFLAG=1;i-=1;}break;
		 
		}
	   	
	 }	

	

	 /*****排除交叉线情况1****/
	 
 if((rightlinecol[rightpointnumber+1]==1)&&((righthighestpoint[0]-rightlinerow[rightpointnumber+1])<8)) 
	 {
		 if(leftlinerow[1]>rightlinerow[rightpointnumber]-5)  
		 {
			 for(i=1;i<=leftpointnumber+1;i++)
   		        {
				 leftlinerow[i]=0;leftlinecol[i]=0;leftdirection[i]=0;				 
			 }
			 leftpointnumber=0;
		 } 
	   
	 }  
	if((leftlinecol[leftpointnumber+1]>COL-2)&&((lefthighestpoint[0]-leftlinerow[leftpointnumber+1])<8))
	 {
	    if(rightlinerow[1]>leftlinerow[leftpointnumber]-5)
	    {
			 {
				 rightlinerow[i]=0;rightlinecol[i]=0;rightdirection[i]=0;
			 }	
			rightpointnumber=0;
	    }	
		
	 }
	 
	
	/*****排除交叉线情况2****/
	
	 if((righthighestpoint[0]==lefthighestpoint[0])&&(lefthighestpoint[0]<=ROW-12))
	 { 
           if((leftlinecol[leftpointnumber]>5)&&(rightlinecol[rightpointnumber]<COL-4))
	   {
		for(i=lefthighestpoint[2];i<=leftpointnumber+1;i++)
		{
		  leftlinerow[i]=0;leftlinecol[i]=0;leftdirection[i]=0;
		}
		for(i=righthighestpoint[2];i<=rightpointnumber+1;i++)
		{
		rightlinerow[i]=0;rightlinecol[i]=0;rightdirection[i]=0;
		}

	    leftpointnumber=lefthighestpoint[2]-2;
	    rightpointnumber=righthighestpoint[2]-2;
           }
	 }
	//if(leftlinerow[leftpointnumber+1]!=0)	{ leftpointnumber++;  }
	//if(rightlinerow[rightpointnumber+1]!=0) { rightpointnumber++; }
}


void drawpoint_2(uint8 *pData)
{
  int i = 0;  
  memset(pData,0,sizeof(uint8)*ROW*COL);
  
  for(i=1;i<=leftpointnumber;i++)
  {    
    pData[(ROW-leftlinerow[i])*COL+leftlinecol[i]] = 0xFF;
  } 

  for(i=1;i<=rightpointnumber+1;i++)
  {  
    pData[(ROW-rightlinerow[i])*COL+rightlinecol[i]] = 0xFF;      
  }
  
}


void imagpro_2(uint8 *pData){
  midfilter(pData);
  getstartline(pData);
  trackpoint(pData);
  
//  drawpoint_2(pData);
}

