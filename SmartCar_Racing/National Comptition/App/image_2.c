/************************************************************************** 
Copyright (C): UESTC.쫷�֮�� 
FileName: image_2.c 
Author: ��ɽ��
Version :7.2
Date: 2014/7/2
**************************************************************************/ 
  
#include "image.h"

/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:confine
*  ����˵��:��Ұ�޶��Ϳ������޶�
*  ����˵��:
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void confine(uint8 *pData)
{
    int i = 0;
    int j = 0;
  
    view_limit = 0;
    control_limit = 0;
  
   /***************��Ұ�޶�******************/ 
  
    if (CarAngle>10)
    {
        view_limit = 0;       
    }  
    else if (CarAngle<11 && CarAngle>-10)
    {
        view_limit = 10-(int)CarAngle;       
    } 
    else if (CarAngle<-9)
    {
        view_limit = 20;       
    }  
  
    for (i=0;i<view_limit;i++)
    {
        for (j=0;j<COL;j++)
        {
            pData[i*COL+j] = 0;
        }
    }
  
    /***********���������޶�**************/
    
    if (CarAngle>35)
    {
        control_limit = -15;       
    }        
    else if (CarAngle<36 && CarAngle>-20)
    {
        control_limit = conntrol_array[(int)CarAngle+20];       
    }        
    else
    {
        control_limit = 20;       
    }      
}  
  
 
/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:compare
*  ����˵��:�Ƚ�����ֵ��С
*  ����˵��:����һ�����������Ƿ�����ϴ�ֵ
*  ��������:����ϴ�ֵ����Сֵ
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

int compare(int a,int b,int big)
{   
    if (a>b)
    {
        if (big==1)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
    else 
    {
        if (big==1)
        {
            return b;
        }
        else
        {
            return a;
        }
    }
}


 
/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:widthmeasure
*  ����˵��:��������е��������
*  ����˵��:��������
*  ��������:������ֵ
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

int widthmeasure(uint8 *pData,int row)
{
    int i = 0;
    int left = 0;
    int right = COL-1;  
        
    for(i=COL/2;i<COL-5;i++)
    {
        if(pData[row*COL+i]==255 && pData[row*COL+i+1]==0 && pData[row*COL+i+2]==0)
        {
            right = i;
            break;
        }
    }
    
    for(i=COL/2;i>5;i--)
    {
        if(pData[row*COL+i]==255 && pData[row*COL+i-1]==0 && pData[row*COL+i-2]==0)
        {
            left = i;
            break;
        }
    }
    
    return(right-left);  
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:countblackpoint
*  ����˵��:������У��ײ��������ɣ��ڵ���
*  ����˵��: ��������
*  ��������:���кڵ���
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

int countblackpoint(uint8 *pData,int hang) 
{
    int i = 0;
    int count = 0;
    int curPos = 0;
   
    for (i=0;i<COL;i++)
    {
        curPos = (ROW-hang) * COL+i;
        if (pData[curPos]==0)
        {
            count++;
         }   
    } 
    
    return count;  
} 


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:count
*  ����˵��:���������߻��ұߺڵ���
*  ����˵��: �������У������������ɣ�����߻����ұ�
*  ��������:���е��ߺڵ���
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

int count(uint8 *pData,int hang,int right)
{
    int j = 0;
    int blackpoint = 0;
    
    if (right)
    {
        for (j=COL/2;j>=3;j--)
        {
            if (pData[hang*COL+j]==0)
            {
                blackpoint++;
            }  
        }
    }
    else 
    {
        for (j=COL/2;j<COL-1;j++)
        {
            if (pData[hang*COL+j]==0)
            {
                blackpoint++;
            }
        } 
    }
 
    return blackpoint;
} 


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:typememo_fifo
*  ����˵��:������λ����
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void typememo_fifo(void)
{
    typememo[0] = typememo[1];
    
    control_row[1] = fixedrow1;
    control_row[0] = control_row[1];
    
    centreline1[0] = centreline1[1];
    centreline2[0] = centreline2[1];
    centreline3[0] = centreline3[1];
    
    line1_width[0] = line1_width[1];
    line2_width[0] = line2_width[1];
    line3_width[0] = line3_width[1];
    
    
    line1lost_memo[0] = line1lost_memo[1];
    line2lost_memo[0] = line2lost_memo[1];
    line3lost_memo[0] = line3lost_memo[1];

} 


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:structinit
*  ����˵��:���ڳ�ʼ��ͳ�Ƶõ��ı߽��߽Ƕ�ֵ
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void structinit(void)
{
    leftposmaxangle.angle = 0;
    leftnegmaxangle.angle = 0;
    leftfoldangle.angle = 0;
    
    rightposmaxangle.angle = 0;
    rightnegmaxangle.angle = 0;
    rightfoldangle.angle = 0;
    
    leftsixtyone.angle = 0;
    leftsixtytwo.angle = 0;
    leftsixtythree.angle = 0;
    
    rightsixtyone.angle = 0;
    rightsixtytwo.angle = 0;
    rightsixtythree.angle = 0; 
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:midfilter
*  ����˵��:��ֵ�˲�������Ϊ�ڼ�Ϊ�ڣ�����Ϊ�ڼ�Ϊ�ڣ�ֻ���ϰ벿�ֵİ׵㡣
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void midfilter(uint8 *pData)
{ 
    int i = 0;
    int j = 0;   
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    int curPos = 0;
    int widthStep = COL;
    
    for (i=1;i<=ROW/2;i++)
    {
        for (j=1;j<COL-1;j++)
  	{   
            curPos = i * widthStep+j;
  	    up = curPos+widthStep;
  	    down = curPos-widthStep;	
  	    left = curPos-1;
  	    right = curPos+1;
         
            if(pData[up]==0 && pData[down]==0)
            {
                pData[curPos] = 0;
            }
  	    else if(pData[left]==0 && pData[right]==0)
            {
                pData[curPos] = 0;
            }
        }
    }
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:getstartline
*  ����˵��:�Ź����㷨Ҫ��ɼ�һ����ʼ����Ϊ��׼�㲢�ڴ˻������ɱ߽���
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void getstartline(uint8 *pData)
{  
    memset(leftlinerow,0,sizeof(int)*MaxNum);
    memset(leftlinecol,0,sizeof(int)*MaxNum);
    memset(leftdirection,0,sizeof(int)*MaxNum);
    
    memset(rightlinerow,0,sizeof(int)*MaxNum);
    memset(rightlinecol,0,sizeof(int)*MaxNum); 
    memset(rightdirection,0,sizeof(int)*MaxNum); 
    
    int i = 0;
    int j = 0; 
    
    int leftcol = 3;
    int midcol_left = COL/2;
    int midcol_right = COL/2;
    int rightcol = COL-3;  
    
    int startline = ROW-3;
    int endline = 20;
    int blackpointcount = 0;    
    
    int curPos = 0;
    int left1Pos = 0;
    int right1Pos = 0;
    int left2Pos = 0;
    int right2Pos = 0;
    int widthStep = COL;     
  
  
    /****�ɼ�����ʼ��****/
    for (i=startline;i>endline;i--)
    {
        blackpointcount = 0;
          
	for (j=midcol_left;j>leftcol;j--)
	{
	    curPos = i*widthStep+j;
            left1Pos = curPos-1;
            left2Pos = curPos-2;		
                
            if (pData[left2Pos]==0 && pData[left1Pos]==0 && pData[curPos]==255)
            {
                leftlinerow[1] = ROW-i;//������������
      	        leftlinecol[1] = j;
                leftdirection[1] = 90;
                break;
            }	
                
	    if (pData[curPos]==0)
            {
                blackpointcount++;
            }
        }	
         
	if (leftlinecol[1]==0)
        {
            midcol_left = 16;/******/
        }     
        
	if ((leftlinecol[1]!=0) || ((blackpointcount>=3) && (leftlinecol[1]==0)))
        {
            break;/**�ҵ�������||Խ������**/
        }
    }
    
    /*****�ɼ�����ʼ��****/
    for (i=startline;i>endline;i--)
    {
        blackpointcount = 0;
          
	for (j=midcol_right;j<rightcol;j++)
	{
            curPos = i*widthStep+j;
	    right1Pos = curPos+1;
	    right2Pos = curPos+2;	
                   
	    if (pData[curPos]==255 && pData[right1Pos]==0 && pData[right2Pos]==0)
	    {
	        rightlinerow[1] = ROW-i;//������������
	        rightlinecol[1] = j;
	    	rightdirection[1] = 90;
	    	break;
	    }	
                   
	    if (pData[curPos]==0)
            {
                blackpointcount++;
            }
        }	
          
	if (rightlinecol[1]==0)
        {
            midcol_right=COL-16;
        }  
        
	if ((rightlinecol[1]!=0) || ((blackpointcount>=3) && (rightdirection[1]==0))) 
        {
            break;/**�ҵ�������||Խ������**/
        }
    }
 
   /**********�ж�*********/  
 
   if (leftdirection[1]==0)
   {
       leftlinerow[1] = 0; 
       leftlinecol[1] = 0;
       leftdirection[1] = 1;
   }  
   if (rightdirection[1]==0)
   {
       rightlinerow[1] = 0;
       rightlinecol[1] = 0;
       rightdirection[1] = 1;
   } 
//   /*****��ֹ��������ڶ�����****/
//   if((leftdirection[1]==0)&&(rightdirection[1]==0))
//   {        
//    for(j=5;j<=COL/2;j++)
//     {
//	  curPos=(ROW-3)*widthStep+j;
//	  right1Pos=curPos+1;
//	  right2Pos=curPos+2;	
//
//	 if(pData[curPos]==255&&pData[right1Pos]==0&&pData[right2Pos]==0)
//         {
//           rightlinerow[1]=3;rightlinecol[1]=j;rightdirection[1]=90;break;
//         }
//      }
//   for(j=COL-5;j>=COL/2;j--)
//     {
//         curPos=(ROW-3)*widthStep+j;
//         left1Pos=curPos-1;
//	 left2Pos=curPos-2;
//
//         if(pData[left2Pos]==0&&pData[left1Pos]==0&&pData[curPos]==255)
//	  {  
//            leftlinecol[1]=j;leftlinerow[1]=3;leftdirection[1]=90;break;
//          }
//     }
// }
 
  
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:trackpoint
*  ����˵��:�ڻ�׼����Χ���þŹ����㷨�õ��߽��ߣ����ұ߽��߷ֿ�����
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void trackpoint(uint8 *pData)
{
    int i = 0;     
    
    int right = 0;
    int rightup = 0;
    int up = 0;
    int leftup = 0;
    int left = 0;
    int leftdown = 0;
    int down = 0;
    int rightdown = 0;
    int widthStep = COL;
    
    int leftpeakFLAG = 0;
    int rightpeakFLAG = 0;
    int leftanglerange = 0;
    int rightanglerange = 0;
   
    /****����ֵ***/      
    leftpointnumber = 0;
    rightpointnumber = 0;  
    memset(righthighestpoint,0,sizeof(int)*3);       
    memset(lefthighestpoint,0,sizeof(int)*3);   
    memset(leftcolmaxpoint,0,sizeof(int)*3);       
    memset(rightcolminpoint,0,sizeof(int)*3);
        
/**********************************Ѱ�������**********************************/
        
    for (i=2;i<MaxNum;i++)/*���ѰMaxNum����*/
    {         
        leftanglerange = leftdirection[i-1];
                
	if (leftlinerow[i-1]>lefthighestpoint[0]) //������ߵ�
        {
            lefthighestpoint[0] = leftlinerow[i-1];
            lefthighestpoint[1] = leftlinecol[i-1];
            lefthighestpoint[2] = i-1;
        }                
        if (leftlinecol[i-1]>=leftcolmaxpoint[1])//��������
        {
            leftcolmaxpoint[0] = leftlinerow[i-1];
            leftcolmaxpoint[1] = leftlinecol[i-1];
            leftcolmaxpoint[2] = i-1;                
        }
                
                /****ֹͣ��������***/
	if (((leftlinerow[i-1]>ROW-2-control_limit || leftlinerow[i-1]<2 || leftlinecol[i-1]<2 
             || leftlinecol[i-1]>COL-2) && (!leftpeakFLAG)) || leftdirection[i-1]==1)
	{
            break;
        }
	else if (!leftpeakFLAG)
        {
            leftpointnumber++;
        }
	else if (leftpeakFLAG)
        {
            leftanglerange+=90;
            if (leftanglerange-leftdirection[i-1]>180)
            {
                break;
            }
            if (leftanglerange>=360)
            {
                leftanglerange-=360;
            }
        }
        /*******�Ÿ��������Ϣ*****/
	//curPos = (ROW-leftlinerow[i-1]) * widthStep + leftlinecol[i-1];
	right = (ROW-leftlinerow[i-1]) * widthStep + leftlinecol[i-1] + 1;
	rightup = (ROW-leftlinerow[i-1]-1) * widthStep + leftlinecol[i-1] + 1;
	up = (ROW-leftlinerow[i-1]-1) * widthStep + leftlinecol[i-1];
	leftup = (ROW-leftlinerow[i-1]-1) * widthStep + leftlinecol[i-1] - 1;
	left = (ROW-leftlinerow[i-1]) * widthStep + leftlinecol[i-1] - 1;
	leftdown = (ROW-leftlinerow[i-1]+1) * widthStep + leftlinecol[i-1] - 1;
	down = (ROW-leftlinerow[i-1]+1) * widthStep + leftlinecol[i-1];
	rightdown = (ROW-leftlinerow[i-1]+1) * widthStep + leftlinecol[i-1] + 1;			

	/***������Ѳ�߲�ȥ��ë��***/
	switch (leftanglerange)
	{
	    case 0:
	           if (pData[down]==255 && pData[rightdown]==0) 
	           { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 270;
                       leftpeakFLAG = 0;
                   }
	           else if (pData[rightdown]==255 && pData[right]==0)
	           { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 315;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[right]==255 && pData[rightup]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 0;
                       leftpeakFLAG = 0;
                   }
	           else if (pData[rightup]==255 && pData[up]==0)
		   { 
                        leftlinerow[i] = leftlinerow[i-1]+1;
                        leftlinecol[i] = leftlinecol[i-1]+1;
                        leftdirection[i] = 45;
                        leftpeakFLAG = 0;
                   }
		   else if (pData[down]==255 && pData[rightdown]==255 
                              && pData[right]==255 && pData[rightup]==255 && pData[up]==255) 
		   {
                        leftpeakFLAG = 1;
                        i = i-1;
                   }                   
                   break;
                   
            case 45:
	           if (pData[rightdown]==255 && pData[right]==0)
	           { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 315;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[right]==255 && pData[rightup]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 0;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[rightup]==255 && pData[up]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 45;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[up]==255 && pData[leftup]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 90;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[rightdown]==255 && pData[right]==255 
                              && pData[rightup]==255 && pData[up]==255 && pData[leftup]==255) 
		   {
                       leftpeakFLAG = 1;
                       i = i-1;
                   }
                   break;

            case 90:
		   if (pData[right]==255 && pData[rightup]==0)
	           { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 0;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[rightup]==255 && pData[up]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 45;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[up]==255 && pData[leftup]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 90;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[leftup]==255 && pData[left]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 135;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[right]==255 && pData[rightup]==255
                              && pData[up]==255 && pData[leftup]==255 && pData[left]==255) 
	           {
                       leftpeakFLAG = 1;
                       i = i-1;
                   }
                   break;
                   
            case 135:
  		   if (pData[rightup]==255 && pData[up]==0)
  	           { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 45;
                       leftpeakFLAG = 0;
                   }
  		   else if (pData[up]==255 && pData[leftup]==0)
  	           { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 90;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[leftup]==255 && pData[left]==0)
                   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 135;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftdown]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 180;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[rightup]==255 && pData[up]==255
                              && pData[leftup]==255&&pData[left]==255&&pData[leftdown]==255) 
		   {
                       leftpeakFLAG = 1;
                       i = i-1;
                   }
                   break;
                   
	    case 180:
		   if (pData[up]==255 && pData[leftup]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 90;
                       leftpeakFLAG = 0;
                   }
	           else if (pData[leftup]==255 && pData[left]==0)
	           { 
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 135;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftdown]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 180;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[leftdown]==255 && pData[down]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 225;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[up]==255 && pData[leftup]==255 
                              && pData[left]==255 && pData[leftdown]==255 && pData[down]==255) 
		   {
                       leftpeakFLAG = 1;
                       i = i-1;
                   }
                   break;
                   
	    case 225:
		   if (pData[leftup]==255 && pData[left]==0)
		   {
                       leftlinerow[i] = leftlinerow[i-1]+1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 135;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftdown]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 180;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[leftdown]==255 && pData[down]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 225;
                       leftpeakFLAG = 0;
                   }
	           else if (pData[down]==255 && pData[rightdown]==0)
	           {
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 270;
                       leftpeakFLAG = 0;
                   }
	           else if (pData[leftup]==255 && pData[left]==255
                              && pData[leftdown]==255 && pData[down]==255 && pData[rightdown]==255) 
	           {
                       leftpeakFLAG = 1;
                       i = i-1;
                   }
                   break;
                   
            case 270:
	           if (pData[left]==255 && pData[leftdown]==0)
	           {
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 180;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[leftdown]==255 && pData[down]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 225;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[down]==255 && pData[rightdown]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 270;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[rightdown]==255 && pData[right]==0)
                   {
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 315;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftdown]==255
                             && pData[down]==255 && pData[rightdown]==255 && pData[right]==255) 
		   {
                       leftpeakFLAG = 1;
                       i = i-1;
                   }
                   break;
                   
	    case 315:
		   if (pData[leftdown]==255 && pData[down]==0)
                   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]-1;
                       leftdirection[i] = 225;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[down]==255 && pData[rightdown]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1];
                       leftdirection[i] = 270;
                       leftpeakFLAG = 0;
                   }
                   else if (pData[rightdown]==255 && pData[right]==0)
                   { 
                       leftlinerow[i] = leftlinerow[i-1]-1;
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 315;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[right]==255 && pData[rightup]==0)
		   { 
                       leftlinerow[i] = leftlinerow[i-1];
                       leftlinecol[i] = leftlinecol[i-1]+1;
                       leftdirection[i] = 0;
                       leftpeakFLAG = 0;
                   }
		   else if (pData[leftdown]==255 && pData[down]==255
                           && pData[rightdown]==255 && pData[right]==255 && pData[rightup]==255) 
		   {
                       leftpeakFLAG=1;
                       i=i-1;
                   }
                   break; 		
        }	   	
    }
    
/***********************************Ѱ���ұ���***************************************/
    
    for (i=2;i<MaxNum;i++)/*���ѰMaxNum����*/
    { 
        rightanglerange = rightdirection[i-1];
                
	if (rightlinerow[i-1]>righthighestpoint[0])//������ߵ�
        { 
            righthighestpoint[0] = rightlinerow[i-1];
            righthighestpoint[1] = rightlinecol[i-1];
            righthighestpoint[2] = i-1;
        }                
        if (rightlinecol[i-1]!=0 && rightcolminpoint[1]<=rightlinecol[i-1])//������С��
        {
            rightcolminpoint[0] = rightlinerow[i-1];
            rightcolminpoint[1] = rightlinecol[i-1];
            rightcolminpoint[2] = i-1;
        }

	if (((rightlinerow[i-1]>ROW-2-control_limit || rightlinerow[i-1]<2 || rightlinecol[i-1]<2 
             || rightlinecol[i-1]>COL-2) && (!rightpeakFLAG)) || rightdirection[i-1]==1)
        {
            break;
        }
	else if (!rightpeakFLAG)
        {
            rightpointnumber++;
        }
	else if (rightpeakFLAG)
	{
            rightanglerange+=90; 
            if (rightanglerange-rightdirection[i-1]>180)
            {
                break;
            }
            if (rightanglerange>=360)
            {
                rightanglerange-=360;
            }
        }	

	//curPos = (ROW-rightlinerow[i-1]) * widthStep + rightlinecol[i-1];
	right = (ROW-rightlinerow[i-1]) * widthStep + rightlinecol[i-1] + 1;
	rightup = (ROW-rightlinerow[i-1]-1) * widthStep + rightlinecol[i-1] + 1;
	up = (ROW-rightlinerow[i-1]-1) * widthStep + rightlinecol[i-1];
	leftup = (ROW-rightlinerow[i-1]-1) * widthStep + rightlinecol[i-1] - 1;
	left = (ROW-rightlinerow[i-1]) * widthStep + rightlinecol[i-1] - 1;
	leftdown = (ROW-rightlinerow[i-1]+1) * widthStep + rightlinecol[i-1] - 1;
	down = (ROW-rightlinerow[i-1]+1) * widthStep + rightlinecol[i-1];
	rightdown=(ROW-rightlinerow[i-1]+1) * widthStep + rightlinecol[i-1] + 1;			
		
	/***������Ѳ��***/
	switch (rightanglerange)
	{
            case 0:
	           if (pData[down]==255 && pData[leftdown]==0) 
		   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 270;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[leftdown]==255 && pData[left]==0)
		   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]-1; 
                       rightdirection[i] = 315;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftup]==0)
		   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 0;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[leftup]==255 && pData[up]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 45;
                       rightpeakFLAG = 0;
                   }
		   else if(pData[down]==255 && pData[leftdown]==255
                            && pData[left]==255 && pData[leftup]==255 && pData[up]==255)
		   {
                       rightpeakFLAG=1;
                       i-=1;
                   }
                   break;
	    case 45:
	           if (pData[leftdown]==255 && pData[left]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 315;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftup]==0)
		   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 0;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[leftup]==255 && pData[up]==0)
		   { 
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 45;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[up]==255 && pData[rightup]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 90;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[leftdown]==255 && pData[left]==255
                             &&pData[leftup]==255 && pData[up]==255 && pData[rightup]==255)
                   {
                       rightpeakFLAG = 1;
                       i-=1;
                   }
                         break;
            case 90:
		   if (pData[left]==255 && pData[leftup]==0)
		   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 0;
                       rightpeakFLAG = 0;
                   }  
                   else if (pData[leftup]==255 && pData[up]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 45;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[up]==255 && pData[rightup]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 90;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightup]==255 && pData[right]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 135;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[left]==255 && pData[leftup]==255
                             && pData[up]==255 && pData[rightup]==255 && pData[right]==255)
                   {
                       rightpeakFLAG = 1;
                       i=i-1;
                   }
                   break;
                  
	    case 135:
		   if (pData[leftup]==255 && pData[up]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 45;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[up]==255 && pData[rightup]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 90;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightup]==255 && pData[right]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 135;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[right]==255 && pData[rightdown]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 180;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[leftup]==255 && pData[up]==255
                            && pData[rightup]==255 && pData[right]==255 && pData[rightdown]==255)
                   {
                       rightpeakFLAG = 1;
                       i-=1;
                   }
                   break;
                  
	    case 180:
		   if (pData[up]==255 && pData[rightup]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 90;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightup]==255 && pData[right]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 135;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[right]==255 && pData[rightdown]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 180;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightdown]==255 && pData[down]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 225;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[up]==255 && pData[rightup]==255
                             &&pData[right]==255 && pData[rightdown]==255 && pData[down]==255)
                   {
                       rightpeakFLAG = 1;
                       i-=1;
                   }
                   break;
                  
	    case 225:
		   if (pData[rightup]==255 && pData[right]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]+1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 135;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[right]==255 && pData[rightdown]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 180;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightdown]==255 && pData[down]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 225;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[down]==255 && pData[leftdown]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 270;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightup]==255 && pData[right]==255
                             && pData[rightdown]==255 && pData[down]==255 && pData[leftdown]==255)
                   {
                       rightpeakFLAG = 1;
                       i-=1;
                   }
                   break;
                  
	    case 270:
		   if (pData[right]==255 && pData[rightdown]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 180;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[rightdown]==255 && pData[down]==0)
		   { 
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 225;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[down]==255 && pData[leftdown]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 270;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[leftdown]==255 && pData[left]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 315;
                       rightpeakFLAG = 0;
                   }
                   else if (pData[right]==255 && pData[rightdown]==255
                             && pData[down]==255 && pData[leftdown]==255 && pData[left]==255)
                   {
                       rightpeakFLAG = 1;
                       i-=1;
                       
                   }
                   break;
                   
	    case 315:
		   if (pData[rightdown]==255 && pData[down]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]+1;
                       rightdirection[i] = 225;
                       rightpeakFLAG = 0;                   
                   }
                   else if (pData[down]==255 && pData[leftdown]==0)
                   {
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1];
                       rightdirection[i] = 270;
                       rightpeakFLAG = 0;
                   }    
                   else if (pData[leftdown]==255 && pData[left]==0)
                   { 
                       rightlinerow[i] = rightlinerow[i-1]-1;
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 315;
                       rightpeakFLAG = 0;
                   }
		   else if (pData[left]==255 && pData[leftup]==0)
		   { 
                       rightlinerow[i] = rightlinerow[i-1];
                       rightlinecol[i] = rightlinecol[i-1]-1;
                       rightdirection[i] = 0;
                   }
                   else if (pData[rightdown]==255 && pData[down]==255
                            && pData[leftdown]==255 && pData[left]==255 && pData[leftup]==255)
                   {
                       rightpeakFLAG=1;
                       i-=1;
                   }                   
                   break;		 
        }
	   	
    }	

   /**********************************�ų�������***********************************/
    
   if (rightpointnumber!=0 && leftpointnumber!=0 &&  herringbone_flag==0)
   {	
             /*****�ų����������1****/
       if ((leftlinecol[leftpointnumber+1]>COL-3) && ((lefthighestpoint[0]-leftlinerow[leftpointnumber+1])<8))
       {
           if (rightlinerow[1]>leftlinerow[leftpointnumber]-5)
           {			
               rightpointnumber = 0;                                 
           }			
       } 
       else if ((rightlinecol[rightpointnumber+1]<3) && ((righthighestpoint[0]-rightlinerow[rightpointnumber+1])<8)) 
       {
           if (leftlinerow[1]>rightlinerow[rightpointnumber]-5)  
           {			
               leftpointnumber = 0;                                           
           } 	   
       }  
	 
	
       /*****�ų����������2****/
     
       if ((righthighestpoint[0]==lefthighestpoint[0]) && (lefthighestpoint[0]<ROW-1))
       { 
           if ((leftlinecol[leftpointnumber]>5) && (rightlinecol[rightpointnumber]<COL-4))
           {             
               leftpointnumber = lefthighestpoint[2]-2;
               rightpointnumber = righthighestpoint[2]-2;         
           }
       }
         
       /*****�ų����������3****/
         
       if (leftlinerow[leftpointnumber]<10)
       { 
	   leftpointnumber = lefthighestpoint[2];          
       }       
       if (rightlinerow[rightpointnumber]<10)
       {          
	   rightpointnumber = righthighestpoint[2];
       }
        
     /*****�ų����������4****/





     /*****�ų����������5****/
        
   }	
}

/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:dataprocess
*  ����˵��:�õ��߽��ߵ��С��кͽǶȺ����ҷֿ�Ѱ�ҽǶȱ仯���㼰������Ϣ
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void dataprocess(void)
{
    int i = 0; 
    int j = 0;
    int lefttime = 0;
    int righttime = 0;  
    
    int AV_leftrow = 0;      
    int AV_leftdir = 0;
    
    int AV_rightrow = 0;      
    int AV_rightdir = 0;   
    
    int AV_lastfivepoint = 0;
    int AV_nowfivepoint = 0;     
    
    /******��ʼ��****/       
    structinit();
    AV_leftcol = 0;
    AV_rightrow = 0;     
  
    /***********************************left**************************************/
      
    /************ǰ��***********/
   
    if (leftpointnumber>20)
    { 
        lefttime = 0;
     
        for (i=7;i<leftpointnumber;i++)
        {   
	    AV_leftrow+=leftlinerow[i];
	    AV_leftcol+=leftlinecol[i];
	    AV_leftdir+=leftdirection[i];	
            
	    if ((i<lefthighestpoint[2]+6) && (i<leftpointnumber-4))
	    {		 
                AV_lastfivepoint = (leftdirection[i-5]+leftdirection[i-4]+leftdirection[i-3]
                                    +leftdirection[i-2]+leftdirection[i-1])/5;
	        AV_nowfivepoint = (leftdirection[i+1]+leftdirection[i+2]+leftdirection[i+3]
                                   +leftdirection[i+4]+leftdirection[i+5])/5;		
		
                if (abs(AV_nowfivepoint-AV_lastfivepoint)>=180)
                {
                    for (j=i;j<=leftpointnumber;j++)
                    {
                        leftlinerow[j] = 0;
                        leftlinecol[j] = 0;
                        leftdirection[j] = 0;                  
                    }
                    leftpointnumber = i;                  
                    break;
                }                               
                else if (AV_nowfivepoint-AV_lastfivepoint> leftposmaxangle.angle)
		{                  
		    leftposmaxangle.angle = AV_nowfivepoint-AV_lastfivepoint; 
                    leftposmaxangle.row = leftlinerow[i];
                    leftposmaxangle.col = leftlinecol[i];
                    leftposmaxangle.pointnumber = i; 
                  
                    if (AV_nowfivepoint-AV_lastfivepoint>18)
		    {
		        switch (lefttime) 
		        {
                            case 0: 
                                   leftsixtyone.angle=AV_nowfivepoint-AV_lastfivepoint;
                                   leftsixtyone.row=leftlinerow[i];
                                   leftsixtyone.col=leftlinecol[i];
                                   leftsixtyone.pointnumber=i;
                                   lefttime++;
                                   break;
		            case 1:
                                   leftsixtytwo.angle=AV_nowfivepoint-AV_lastfivepoint;
                                   leftsixtytwo.row=leftlinerow[i];
                                   leftsixtytwo.col=leftlinecol[i];
                                   leftsixtytwo.pointnumber=i;
                                   lefttime++;
                                   break;
                        }
                    }
		}  
	        else if (AV_nowfivepoint-AV_lastfivepoint< leftnegmaxangle.angle)
		{ 
		    leftnegmaxangle.angle = AV_nowfivepoint-AV_lastfivepoint; 
                    leftnegmaxangle.row = leftlinerow[i]; 
                    leftnegmaxangle.col = leftlinecol[i]; 
                    leftnegmaxangle.pointnumber = i; 
                   
		    if (AV_nowfivepoint-AV_lastfivepoint<-18)
		    {
	                leftsixtythree.angle = AV_nowfivepoint-AV_lastfivepoint;
                        leftsixtythree.row = leftlinerow[i];
                        leftsixtythree.col = leftlinecol[i];
                        leftsixtythree.pointnumber = i;
                    }
		}
            }	  
        } 
  
        /***************�ۻ�***********/
    
        if (leftpointnumber-lefthighestpoint[2]>20)
        {
	    for (i=lefthighestpoint[2]+6;i<leftpointnumber-5;i++)
	    {
	        AV_lastfivepoint = (leftdirection[i-5]+leftdirection[i-4]+leftdirection[i-3]
                                    +leftdirection[i-2]+leftdirection[i-1])/5;
	        AV_nowfivepoint = (leftdirection[i+1]+leftdirection[i+2]+leftdirection[i+3]
                                   +leftdirection[i+4]+leftdirection[i+5])/5;	
              
	        if ((AV_nowfivepoint-AV_lastfivepoint<-135) || (AV_nowfivepoint-AV_lastfivepoint>135))
                {
                    for (j=i;j<=leftpointnumber;j++)
                    {
                        leftlinerow[j] = 0;
                        leftlinecol[j] = 0;
                        leftdirection[j] = 0;                  
                    }
                    leftpointnumber=i;
                    break;
                }
	        else if (AV_nowfivepoint-AV_lastfivepoint>leftfoldangle.angle)
                {
                    leftfoldangle.angle = AV_nowfivepoint-AV_lastfivepoint; 
                    leftfoldangle.row = leftlinerow[i];
                    leftfoldangle.col = leftlinecol[i]; 
                    leftfoldangle.pointnumber = i; 
                }  		
            }	 
        }
        
        AV_leftrow = AV_leftrow/leftpointnumber;
        AV_leftcol = AV_leftcol/leftpointnumber;
        AV_leftdir = AV_leftdir/leftpointnumber;

	/**������ߵ���Ϣ**/
        
	if (lefthighestpoint[2]>leftpointnumber)
	{
            lefthighestpoint[0] = leftlinerow[leftpointnumber];
            lefthighestpoint[1] = leftlinecol[leftpointnumber]; 
            lefthighestpoint[2] = leftpointnumber;
        }	
        
        /**�ж��۽���ʵ**/
        
        if (leftposmaxangle.pointnumber-lefthighestpoint[2]>5)
        {
            leftposmaxangle.angle = 0;
        }
        if (leftnegmaxangle.pointnumber-lefthighestpoint[2]>5)
        {
            leftnegmaxangle.angle = 0;
        }
        if (leftfoldangle.pointnumber-leftpointnumber>-5)
        {
            leftfoldangle.angle = 0;
        }
	if (abs(leftsixtyone.pointnumber-leftposmaxangle.pointnumber)<5)
        { 
            leftsixtyone.angle = 0;
        }
	if (abs(leftsixtytwo.pointnumber-leftposmaxangle.pointnumber)<5)
        { 
            leftsixtytwo.angle = 0;
        }
	if (abs(leftsixtythree.pointnumber-leftnegmaxangle.pointnumber)<5)
        {
            leftsixtythree.angle = 0;
        }
        
    }
 
    /*************************************right***********************************/
  
    AV_lastfivepoint = 0;
    AV_nowfivepoint = 0;
   
    /**************ǰ��*************/
   
    if (rightpointnumber>20)
    {    
        righttime = 0;
        
        for (i=7;i<rightpointnumber;i++)
        {   
	    AV_rightrow+=rightlinerow[i];
	    AV_rightcol+=rightlinecol[i];
	    AV_rightdir+=rightdirection[i];
            
	    if ((i<righthighestpoint[2]+6) && (i<rightpointnumber-4))
	    {
                AV_lastfivepoint = (rightdirection[i-5]+rightdirection[i-4]+rightdirection[i-3]
                                    +rightdirection[i-2]+rightdirection[i-1])/5;
	        AV_nowfivepoint = (rightdirection[i+1]+rightdirection[i+2]+rightdirection[i+3]
                                   +rightdirection[i+4]+rightdirection[i+5])/5;		
		
                if (abs(AV_nowfivepoint-AV_lastfivepoint)>=180)
                {
                    for (j=i;j<=rightpointnumber;j++)
                    {
                        rightlinerow[j] = 0;
                        rightlinecol[j] = 0;
                        rightdirection[j] = 0;                  
                    }
                    rightpointnumber = i;
                    break;
                }               
                else if (AV_nowfivepoint-AV_lastfivepoint>rightposmaxangle.angle)
		{ 
		    rightposmaxangle.angle = AV_nowfivepoint-AV_lastfivepoint; 
                    rightposmaxangle.row = rightlinerow[i];
                    rightposmaxangle.col = rightlinecol[i];
                    rightposmaxangle.pointnumber = i;
                    
		    if (AV_nowfivepoint-AV_lastfivepoint>18)
		    { 
		        switch (righttime)
		        {
                            case 0:
                                   rightsixtyone.angle = AV_nowfivepoint-AV_lastfivepoint;
                                   rightsixtyone.row = rightlinerow[i];
                                   rightsixtyone.col = rightlinecol[i]; 
                                   rightsixtyone.pointnumber = i;
                                   righttime++;
                                   break;
			    case 1:
                                   rightsixtytwo.angle = AV_nowfivepoint-AV_lastfivepoint; 
                                   rightsixtytwo.row = rightlinerow[i]; 
                                   rightsixtytwo.col = rightlinecol[i]; 
                                   rightsixtytwo.pointnumber = i;
                                   righttime++;
                                   break;
                        }	   
                    }
		}
	        else if (AV_nowfivepoint-AV_lastfivepoint< rightnegmaxangle.angle)
		{ 
                    rightnegmaxangle.angle = AV_nowfivepoint-AV_lastfivepoint; 
                    rightnegmaxangle.row = rightlinerow[i];
                    rightnegmaxangle.col = rightlinecol[i];
                    rightnegmaxangle.pointnumber = i;
                    
		    if (AV_nowfivepoint-AV_lastfivepoint<-18)
		    {
		        rightsixtythree.angle = AV_nowfivepoint-AV_lastfivepoint;
                        rightsixtythree.row = rightlinerow[i];
                        rightsixtythree.col = rightlinecol[i];
                        rightsixtythree.pointnumber = i;
                    }
		}		  
            }
        }  
        /**********�ۻ�**********/
	if (rightpointnumber-righthighestpoint[2]>20)
	{
	    for (i=righthighestpoint[2]+6;i<rightpointnumber-5;i++)
	    {
	        AV_lastfivepoint = (rightdirection[i-5]+rightdirection[i-4]+rightdirection[i-3]
                                   +rightdirection[i-2]+rightdirection[i-1])/5;
	        AV_nowfivepoint = (rightdirection[i+1]+rightdirection[i+2]+rightdirection[i+3]
                                  +rightdirection[i+4]+rightdirection[i+5])/5;
	       
                if ((AV_nowfivepoint-AV_lastfivepoint<-135) || (AV_nowfivepoint-AV_lastfivepoint>135))
                {
                    for (j=i;j<=rightpointnumber;j++)
                    {
                        rightlinerow[j] = 0;
                        rightlinecol[j] = 0;
                        rightdirection[j] = 0;                  
                    }
                  
                    rightpointnumber=i;
                    break;
                }
	        else if ( AV_nowfivepoint-AV_lastfivepoint> rightfoldangle.angle)
	        { 
                    rightfoldangle.angle = AV_nowfivepoint-AV_lastfivepoint;
                    rightfoldangle.row = rightlinerow[i];
                    rightfoldangle.col = rightlinecol[i];
                    rightfoldangle.pointnumber = i;
                }  		
            }	 
        }
        
        AV_rightrow = AV_rightrow/rightpointnumber;
	AV_rightcol = AV_rightcol/rightpointnumber;
	AV_rightdir = AV_rightdir/rightpointnumber;	
        
        /**������ߵ���Ϣ**/
        
	if (righthighestpoint[2]>rightpointnumber)
	{
            righthighestpoint[0] = rightlinerow[rightpointnumber];
            righthighestpoint[1] = rightlinecol[rightpointnumber];
            righthighestpoint[2] = rightpointnumber;
        }
        
	/**�ж��۽���ʵ**/
        
        if (rightposmaxangle.pointnumber-righthighestpoint[2]>5)
        {
            rightposmaxangle.angle = 0;
        }
        if (rightnegmaxangle.pointnumber-righthighestpoint[2]>5)
        {
            rightnegmaxangle.angle = 0;
        }
        if (rightfoldangle.pointnumber-rightpointnumber>-5)
        {
            rightfoldangle.angle = 0;
        }
	if (abs(rightsixtyone.pointnumber-rightposmaxangle.pointnumber)<5)
        { 
            rightsixtyone.angle = 0;
        } 
	if (abs(rightsixtytwo.pointnumber-rightposmaxangle.pointnumber)<5)
        { 
            rightsixtytwo.angle = 0;
        }
	if (abs(rightsixtythree.pointnumber-rightnegmaxangle.pointnumber)<5)
        {
            rightsixtythree.angle = 0;
        }
    }
  
// /************** �����ǶȲ�Ϊ0,180�ĵ����������****************/
//  
// if(leftpointnumber>10 && rightpointnumber>10)
// {    	 	  
//	  for(i=2;i<=lefthighestpoint[2];i++)
//	  {
//	   if(leftdirection[i]!=0 && leftdirection[i]!=180)
//	    { 
//		   j = leftlinerow[i];
//                   leftline[j] = leftlinecol[i];	
//	    }	  
//	  }  	 
//          
//	  for(i=2;i<=righthighestpoint[2];i++)
//	  {
//	   if(rightdirection[i]!=0 && rightdirection[i]!=180)
//	   {
//	          j = rightlinerow[i];
//                  rightline[j] = rightlinecol[i];
//	   }
//	  }
//          
//         for(j=5;j<60;j++)
//         { 
//            if(leftline[j]!=0 && rightline[j]!=0)
//            {
//     	      roadwidth[j] = rightline[j]-leftline[j];    
//              centreline[j] = (rightline[j]+leftline[j])/2;
//            }
//         }
// }
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:rec_startingline
*  ����˵��:������ʶ��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void rec_startingline(uint8 *pData)
{
    int i = 0;
    int j = 0;   
    int left = 0;
    int right = 0;   
    int leftup = 0;
    int rightup = 0;   
    int blackpoint = 0;
    int rect_p1_row = 0;
    int rect_p1_col = 0;
//    int rect_p2_row = 0;
    int rect_p2_col = COL-1;   
    
    int scan_array[COL] = {0};
    int up_jump_cnt = 0,down_jump_cnt = 0;
  
    extern int stop_flag_image,OLED_stop_flag;
    
    for (i=ROW-2;i>ROW-21;i--)
    {
        for (j=COL/2;j<COL-2;j++)
        {
            if (pData[i*COL+j]==255 && pData[i*COL+j+1]==0)
            {               
                right = j;
                break;
            }
        }               
        for (j=COL/2;j>2;j--)
        {
            if (pData[i*COL+j]==255 && pData[i*COL+j-1]==0)
            {               
                left = j;
                break;
            }
        }              
        
        for (j=COL/2;j<COL-3;j++)
        {
            if (pData[(i-10)*COL+j]==255 && pData[(i-10)*COL+j-1]==0)
            {
                rightup = j;
                break;
            }
        }
        for (j=COL/2;j>2;j--)
        {
            if (pData[(i-10)*COL+j]==255 && pData[(i-10)*COL+j-1]==0)
            {
                leftup = j;
                break;
            }
        }                        
         
        if ((right-left<50) && (right-left>15) && (rightup-leftup>70)  && (rightup-leftup<120))
        {
            if (startingline_flag==1)
            {
                stop_flag_image = 1;
                if(OLED_stop_flag==0){
                  OLED_ShowStr(0,0,"Qipao1  ",1);
                }
                OLED_stop_flag = 1;
                //gpio_set(PTE0,1);
            }              
        }             
    }  
    
     /************�ڶ��׷���ֱ��ͼ��һ��*************/
        
    if (leftlinerow[1]<10 && leftpointnumber>30)
    {
        for (i=1;i<leftpointnumber;i++)
        {                     
           if (leftlinecol[i]>rect_p1_col)
           {
               rect_p1_col = leftlinecol[i];
           }           
           if (leftlinerow[i]==20)
           {
               break;
           } 
        }
        
//        rect_p1_row = ROW-18;       
    }
    if (rightlinerow[1]<10 && rightpointnumber>30)
    {
        for (i=1;i<rightpointnumber;i++)
        {                     
           if (rightlinecol[i]<rect_p2_col && rightlinecol[i]!=0)
           {
               rect_p2_col = rightlinecol[i];
           }       
           if (rightlinerow[i]==20)
           {
               break;
           } 
        }
        
//        rect_p2_row = ROW-18;       
    }
    
    if(rect_p2_col-rect_p1_col>60 && rect_p2_col-rect_p1_col<150)
    {
        for(i=rect_p1_col;i<rect_p2_col;i++)  
        {
            for(j=ROW-2;j>ROW-18;j--)
            {
                if(pData[j*COL+i]==0)
                {
                    scan_array[i] = 1;
                    break;
                }                
            }
        }
    }
    
    for(i = 0;i < COL-2;i++){
      if(scan_array[i]==0&&scan_array[i+1]==1)up_jump_cnt++;
      if(scan_array[i]==1&&scan_array[i+1]==0)down_jump_cnt++;
    }
    
    if(up_jump_cnt>1&&down_jump_cnt>1)
    {
        if (startingline_flag==1&&crossroad_flag==0)
        {
            stop_flag_image = 1;
            if(OLED_stop_flag==0){
                  OLED_ShowStr(0,0,"Qipao2  ",1);
                }
                OLED_stop_flag = 1;
            //gpio_set(PTE0,1);
        }  
    }
    
    
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:rec_crossroad
*  ����˵��:ʮ��ʶ��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void rec_crossroad(uint8 *pData)
{
    int i = 0;  
    int blackpoint = 0;
    
    
    
    if (lefthighestpoint[0]!=0 || righthighestpoint[0]!=0)
    {
        i = compare(lefthighestpoint[0],righthighestpoint[0],1);
        blackpoint = countblackpoint(pData,i+1)+countblackpoint(pData,i+2);
     
        if (blackpoint<6)
        {
            crossroad_flag = 1;              
            return;
        }
     
        if (leftposmaxangle.angle>70 && rightposmaxangle.angle>70)
        {
            if (leftlinecol[leftpointnumber]<4 && rightlinecol[rightpointnumber]>COL-5)
            {
                crossroad_flag = 1;              
                return;                
            }
        }
        
    }  
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:rec_ramp
*  ����˵��:�µ�ʶ��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void rec_ramp()
{    
    int standwidth = 0;
    int nowwidth = line1_width[0] * 2;
    
    if (CarAngle<25 && CarAngle>-10)
    {
        standwidth = ramp_array[(int)CarAngle+20];
    }    
    
    if(nowwidth>standwidth+10 && leftlinerow[leftpointnumber]>=ROW-4-view_limit
                              && rightlinerow[rightpointnumber]>=ROW-4-view_limit)
    {
        ramp_flag = 1;
    }
}



/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:rec_block
*  ����˵��:�ϰ���ʶ��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void rec_block()
{
    int i = 0;
    int leftcount = 0;
    int rightcount = 0;
    
    if(leftpointnumber>30)
    {      
        for(i=1;i<leftpointnumber;i++)
        {
           // if(leftlinerow[i]=)
            
        }
    }
}



/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:rec_s_bend
*  ����˵��:Сsʶ��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void rec_s_bend(uint8 *pData)
{
    if (leftpointnumber>20 && rightpointnumber>20)
    {
        if ((leftlinerow[leftpointnumber]>=ROW-4-view_limit) && (rightlinerow[rightpointnumber]>=ROW-4-view_limit))
        {
            if (leftposmaxangle.angle>=20 && rightposmaxangle.angle>=20
                && leftnegmaxangle.angle<=-20 && rightnegmaxangle.angle<=-20
                &&(abs(leftposmaxangle.row-leftnegmaxangle.row)>=5 
                || abs(rightposmaxangle.row-rightnegmaxangle.row)>=5))
            {        
                if (!((leftcolmaxpoint[0]>=ROW/2 && leftcolmaxpoint[1]>COL/2-15) 
                   ||(rightcolminpoint[0]>=ROW/2 && rightcolminpoint[1]<COL/2+15)))
       
                { 
                    s_bend_flag = 1;
                    return;
                }
            }       
        }
    }

}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:rec_herringbone
*  ����˵��:����·ʶ��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/

void rec_herringbone(uint8 *pData)
{    

    if (leftpointnumber>20 && rightpointnumber>20)
    {
        if (leftlinecol[leftpointnumber]<=3 && rightlinecol[rightpointnumber]<=3
            && leftlinecol[leftpointnumber]!=0 && rightlinecol[rightpointnumber]!=0)
        {
            if (lefthighestpoint[0]-leftlinerow[leftpointnumber]>5)
            {           
                if (leftlinerow[1]<=10 && rightlinerow[1]<=10)
                {
                    if (righthighestpoint[1]+8<rightnegmaxangle.col && rightnegmaxangle.angle<=-27)  
                    {
                        if (leftposmaxangle.angle>=108 && leftnegmaxangle.angle>=-18)
                        {     
                            if ((leftdirection[leftposmaxangle.pointnumber-1]
                                +leftdirection[leftposmaxangle.pointnumber-2]
                                  +leftdirection[leftposmaxangle.pointnumber-3]
                                    +leftdirection[leftposmaxangle.pointnumber-4]
                                     +leftdirection[leftposmaxangle.pointnumber-5])/5<=72)
                            {
                                if ((leftdirection[leftposmaxangle.pointnumber+1]
                                     +leftdirection[leftposmaxangle.pointnumber+2]
                                      +leftdirection[leftposmaxangle.pointnumber+3]
                                       +leftdirection[leftposmaxangle.pointnumber+4]
                                        +leftdirection[leftposmaxangle.pointnumber+5])/5>162)
                                {
                                     herringbone_flag = 1;
                                     return; 
                                }   
                            }
                        }
                    }
                }
            }
        }
        else if (leftlinecol[leftpointnumber]>COL-4 && rightlinecol[rightpointnumber]>COL-4)
        {
            if (righthighestpoint[0]-rightlinerow[rightpointnumber]>5)
            {         
                if (leftlinerow[1]<=10 && rightlinerow[1]<=10)
                {
                    if (lefthighestpoint[1]>leftnegmaxangle.col+8 && leftnegmaxangle.angle<-27)
                    {
                        if (rightposmaxangle.angle>=108 && rightnegmaxangle.angle>=-18)
                        {
                            if ((rightdirection[rightposmaxangle.pointnumber-1]
                                 +rightdirection[rightposmaxangle.pointnumber-2]
                                   +rightdirection[rightposmaxangle.pointnumber-3]
                                     +rightdirection[rightposmaxangle.pointnumber-4]
                                      +rightdirection[rightposmaxangle.pointnumber-5])/5<72)
                            {
                                if ((rightdirection[rightposmaxangle.pointnumber+1]
                                     +rightdirection[rightposmaxangle.pointnumber+2]
                                      +rightdirection[rightposmaxangle.pointnumber+3]
                                       +rightdirection[rightposmaxangle.pointnumber+4]
                                        +rightdirection[rightposmaxangle.pointnumber+5])/5>162)
                                {
                                     herringbone_flag = 2;
                                     return; 
                                }   
                            }   
                        }
                    }
                }        
            }
        }
    }
}



/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:drawpoint_2
*  ����˵��:���ɼ��ı߽��ߴ���ͼƬ�ϣ����ڷ���
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/
void drawpoint_2(uint8 *pData)
{ 
    int i = 0;   
    memset(pData,0,sizeof(uint8)*ROW*COL);
 
    for (i=1;i<=leftpointnumber;i++)
    {    
        pData[(ROW-leftlinerow[i]) * COL+leftlinecol[i]] = 0xFF;
    } 
    
    for (i=1;i<=rightpointnumber;i++)
    {  
        pData[(ROW-rightlinerow[i]) * COL+rightlinecol[i]] = 0xFF;  
    }     
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:errorfinder
*  ����˵��:Ѱ�������߽��߶����ڣ��������ұ߽��߶���һ���߽�����
*  ����˵��: 
*  ��������:��һ���߽��߷��� 1�������� 2�������ߣ�
            �ڶ����߽��߷��� 3�������� 4�������ߣ�
            ����0����δ����
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

int errowfinder(int first)
{
    int i = 0;
    int left1equal = 0;
    int right1equal = 0;
    int left2equal = 0; 
    int right2equal = 0;
    int left11equal = 0;
    int right11equal = 0;
    int left22equal = 0; 
    int right22equal = 0;
    
    
    /******************************firstline***********************************/
    if(first)
    {
        /**********������*********/
        if (leftpointnumber>10)
        {
            for (i=1;i<leftpointnumber;i++)
            {
                if(leftlinerow[i]==ROW-fixedrow1)
                {
                    if(leftline1==leftlinecol[i])
                    {
                        left1equal = 1;
                    }
                    if(rightline1==leftlinecol[i])
                    {
                        right1equal = 1;
                    }
                }
            }
            
            if (left1equal==1 && right1equal==1)
            {
               return 1;
            }
        }
        
        /**********������*********/
        if (rightpointnumber>10)
        {
            for (i=1;i<rightpointnumber;i++)
            {
                if (rightlinerow[i]==(ROW-fixedrow1))
                {
                    if (leftline1==rightlinecol[i])
                    {
                        left11equal = 1; 
                    }
                    if (rightline1==rightlinecol[i])
                    {
                        right11equal = 1; 
                    }
                }
            }
            
            if (left11equal==1 && right11equal==1)
            {
                return 2;
            }
        }
    }
    /******************************secondline***********************************/
    if(!first)
    {
        /**********������*********/
        if (leftpointnumber>10)
        {
            for (i=1;i<leftpointnumber;i++)
            {
                if (leftlinerow[i]==(ROW-fixedrow2))
                {
                    if (leftline2==leftlinecol[i])
                    {
                        left2equal = 1; 
                    }
                    if (rightline2==leftlinecol[i])
                    {
                        right2equal = 1; 
                    }
                }
            }
            
            if (left2equal==1 && right2equal==1)
            {
               return 3;
            }
        }
        
        /**********������*********/
        if (rightpointnumber>10)
        {
            for (i=1;i<rightpointnumber;i++)
            {
                if (rightlinerow[i]==(ROW-fixedrow2))
                {
                    if (leftline2==rightlinecol[i])
                    {
                        left22equal = 1; 
                    }
                    if (rightline2==rightlinecol[i])
                    {
                        right22equal = 1; 
                    }
                }
            }
            
            if (left22equal==1 && right22equal==1)
            {
                return 4;
            }
        }
    }
    return 0;
}

/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:widthjudge
*  ����˵��:������ߺ��ж��Ƿ�·���б�ʲ�·��
*  ����˵��: ,rightΪ1 Ϊ�����ߣ�Ϊ0������
*  ��������: ����1���ɲ�·�� ����0���ɲ�б��
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

int widthjudge(int right)
{   
    int av_direction = 0;
      
    if (right && rightpointnumber>10 && abs(righthighestpoint[2]-rightpointnumber)<3)//rightline lost
    {
        av_direction = (rightdirection[rightpointnumber-1]+rightdirection[rightpointnumber-2]
                      +rightdirection[rightpointnumber-3]+rightdirection[rightpointnumber-4]
                      +rightdirection[rightpointnumber-5])/5;
        
        if (av_direction<150 && av_direction>90)
        {
            if (leftlinecol[leftpointnumber]<COL-10 || leftposmaxangle.angle>140 
                || leftnegmaxangle.angle<-140)
            {  
              return 1;
            }
        }
      
    }
    else if (!right && leftpointnumber>10 && abs(lefthighestpoint[2]-leftpointnumber)<3)//leftline lost
    {
        av_direction = (leftdirection[leftpointnumber-1]+leftdirection[leftpointnumber-2]
                      +leftdirection[leftpointnumber-3]+leftdirection[leftpointnumber-4]
                      +leftdirection[leftpointnumber-5])/5;
        
        if (av_direction<150 && av_direction>90 )
        {
            if (rightlinecol[rightpointnumber]>10 || rightposmaxangle.angle>140
                || rightnegmaxangle.angle<-140)
            {  
                return 1;
            }      
        }
    }    
    
    return 0;    
}



/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:fillwhite
*  ����˵��:������ߺ���ݱ߽���б�ʲ���
*  ����˵��: ,rightΪ1������,xΪ��row��yΪ��col
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

int fillwhite(uint8 *pData,int right,int searchrow)
{  
    int i = 0;	    
    int y = 0;
    float k = 0;
    float b = 0;
    int num_p1 = 0;
    int num_p2 = 0;
    int startrow = 0;
    int startcol = 0;   
       
    float AV_direction = 0;    
  
    /******�Ƕ�ƽ��ֵ��б�ʣ�ƽ��������׼��******/
    if (right==1 && righthighestpoint[0]-rightlinerow[1]>5)
    {
        for(i=1;i<rightpointnumber;i++)
        {
            if(rightlinerow[i]==righthighestpoint[0]-5)
            {
                num_p1 = i;
                break;
            }
        }      
      
        for (i=num_p1;i<=righthighestpoint[2];i++)
        {     
            //startrow += (ROW-rightlinerow[i]);
            //startcol += rightlinecol[i];
            AV_direction += rightdirection[i];             
        }         
        
        startrow = ROW-righthighestpoint[0];
        startcol = righthighestpoint[1];
        AV_direction /=  (righthighestpoint[2]-num_p1+1);
        
        /******��ĸ��Ϊ0ʱ�������*******/
        if (AV_direction==180 || AV_direction==0)
        {
            return 0;
        }
        else 
        {
            k = 2 - AV_direction / 45;        
            b = startcol-k * startrow;	 
            y = (int)(k * searchrow + b);
            
//            /*********���*********/
//            for (i=startrow;i>0;i--)
//            {
//                if(i*COL+(int)(k*i+b)<COL-1 || i*COL+(int)(k*i+b)>0)
//                {
//                    pData[i*COL+(int)(k*i+b)] = 0;
//                }
//            }
            
            return y;
        }	
    }     
    else if ((right==0) && lefthighestpoint[0]-leftlinerow[1]>5)
    {
        for(i=1;i<leftpointnumber;i++)
        {
            if(leftlinerow[i]==lefthighestpoint[0]-5)
            {
                num_p2 = i;
                break;
            }
        }         
      
        for(i=num_p2;i<=lefthighestpoint[2];i++)
        {  
            //startrow += (ROW-leftlinerow[i]);
            //startcol += leftlinecol[i];
            AV_direction += leftdirection[i]; 
        }         
        startrow = ROW-lefthighestpoint[0];
        startcol = lefthighestpoint[1];
        AV_direction /= (lefthighestpoint[2]-num_p2+1);
        
        /******��ĸ��Ϊ0ʱ�������*******/
        if (AV_direction==180 || AV_direction==0)
        {
            return 0;
        }
        else 
        {
            k = AV_direction / 45 - 2;        
            b = startcol-k * startrow;	
            y = (int)(k * searchrow + b);
            
//            /*********���*********/
//            for (i=startrow;i>0;i--)
//            {
//                if(i*COL+(int)(k*i+b)<COL-1 || i*COL+(int)(k*i+b)>0)
//                {
//                    pData[i*COL+(int)(k*i+b)] = 0;
//                }
//            }
            
            return y;
        }	
    }     
    else
    {
        return 0;
    }
    
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:fixedline
*  ����˵��:��'�̶�'�вɼ�����������ת��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/           
void fixedline(uint8 *pData)
{
   
    int j = 0;	 
    int line1error = 0;
    int line2error = 0;
    
    int left1width_conform = 0;
    int right1width_conform = 0;
    int left2width_conform = 0;
    int right2width_conform = 0;
    
    int left1blackpoint = 0;
    int right1blackpoint = 0;
    int left2blackpoint = 0;
    int right2blackpoint = 0;
   
    
    leftline1 = 0;
    rightline1 = COL-1;
    leftline2 = 0;
    rightline2 = COL-1;
  
    
    left1lost_flag = 1;
    right1lost_flag = 1;
    left2lost_flag = 1;
    right2lost_flag = 1;
   
    
    /**************************firstline*********************************/    
   
    for (j=centreline1[0];j<COL-2;j++)
    {
        if (pData[fixedrow1*COL+j]==255 && pData[fixedrow1*COL+j+1]==0 && pData[fixedrow1*COL+j+2]==0)
        {
            rightline1 = j;
            right1lost_flag = 0;
            break;
        }
        
        if(pData[fixedrow1*COL+j]==0)
        {
            left1blackpoint++;
        }
    }    
    for (j=centreline1[0];j>1;j--)
    {
        if (pData[fixedrow1*COL+j]==255 && pData[fixedrow1*COL+j-1]==0 && pData[fixedrow1*COL+j-2]==0)
        {
            leftline1 = j;
            left1lost_flag = 0;
            break;
        }
        
        if(pData[fixedrow1*COL+j]==0)
        {
            right1blackpoint++;
        }
    }
    
    if(left1blackpoint>2 || right1blackpoint>2)
    {
        left1lost_flag=1;
        right1lost_flag=1;
    }
    
    /*********��ͬһ���߽���*********/
    if(left1lost_flag==0 && right1lost_flag==0)
    {
        line1error = errowfinder(1);        
        
        if(line1error==1)
        {
            right1lost_flag=1;
        }
        else if(line1error==2)
        {
            left1lost_flag=1;
        }
    }
    
    /***********���ߴ���***********/ 
    if(left1lost_flag==0 && right1lost_flag==0)
    {
        line1_width[1] = (rightline1-leftline1)/2;  
        centreline1[1] = (rightline1+leftline1)/2;
        line1lost_memo[1] = 0;        
    }
    else if(left1lost_flag==1 && right1lost_flag==0)
    {
        centreline1[1] = rightline1-line1_width[0];
        
        left1width_conform = widthjudge(0);
        
        if(left1width_conform==0)
        {
            leftline1 = fillwhite(pData,0,fixedrow1);
            
            if(leftline1!=0)
            {
                centreline1[1] = (rightline1+leftline1)/2;
                
                if(centreline1[1]>COL-1)
                {
                    centreline1[1] = COL-1;
                }
                else if(centreline1[1]<0)
                {
                    centreline1[1] = 0;
                }
            }
        }
        
        line1lost_memo[1] = 1;
    }
    else if(left1lost_flag==0 && right1lost_flag==1)
    {
        centreline1[1] = leftline1+line1_width[0];
        
        right1width_conform = widthjudge(1);
        
        if(right1width_conform==0)
        {
            rightline1 = fillwhite(pData,1,fixedrow1);
            
            if(rightline1!=0)
            {
                centreline1[1] = (rightline1+leftline1)/2;
                
                if(centreline1[1]>COL-1)
                {
                    centreline1[1] = COL-1;
                }
                else if(centreline1[1]<0)
                {
                    centreline1[1] = 0;
                }
            }   
        }
        
        line1lost_memo[1] = 1;
    }
    else
    {
         centreline1[1] = (rightline1+leftline1)/2;
         line1lost_memo[1] = 1;
    }
   
    
    /**************************secondline*********************************/
 
    for (j=centreline2[0];j<COL-2;j++)
    {
        if (pData[fixedrow2*COL+j]==255 && pData[fixedrow2*COL+j+1]==0 && pData[fixedrow2*COL+j+2]==0)
        {
            rightline2 = j;          
            right2lost_flag = 0;
            break;
        }
    }    
    for (j=centreline2[0];j>1;j--)
    {
        if (pData[fixedrow2*COL+j]==255 && pData[fixedrow2*COL+j-1]==0  && pData[fixedrow2*COL+j-2]==0)
        {
            leftline2=j;            
            left2lost_flag = 0;
            break;
        }
    }   
    
    if(left2blackpoint>2 || right2blackpoint>2)
    {
        left2lost_flag=1;
        right2lost_flag=1;
    }    

    /*********��ͬһ���߽���*********/
    if(left2lost_flag==0 && right2lost_flag==0)
    {
        line2error = errowfinder(0);  
        
        if(line2error==3)
        {
            right2lost_flag=1;
        }
        else if(line2error==4)
        {
            left2lost_flag=1;
        }
    }
    
    /***********���ߴ���***********/    
    if(left2lost_flag==0 && right2lost_flag==0)
    {
        line2_width[1] = (rightline2-leftline2)/2;         
        centreline2[1] = (rightline2+leftline2)/2;
        line2lost_memo[1] = 0;
    }
    else if(left2lost_flag==1 && right2lost_flag==0)
    {
        centreline2[1] = rightline2-line2_width[0];
        
        left2width_conform = widthjudge(0);
        
        if(left2width_conform==0)
        {        
            leftline2 = fillwhite(pData,0,fixedrow2);
            
            if(leftline2!=0)
            {
                centreline2[1] = (rightline2+leftline2)/2;
                
                if(centreline1[1]>COL-1)
                {
                    centreline1[1] = COL-1;
                }
                else if(centreline1[1]<0)
                {
                    centreline1[1] = 0;
                }
            }
        }
        
        line2lost_memo[1] = 1;
    }
    else if(left2lost_flag==0 && right2lost_flag==1)
    {
        centreline2[1] = leftline2+line2_width[0];
        
        right2width_conform = widthjudge(1);
        
        if(right2width_conform==0)
        {
            rightline2 = fillwhite(pData,1,fixedrow2);
            
            if(rightline2!=0)
            {
                centreline2[1] = (rightline2+leftline2)/2;
                
                if(centreline1[1]>COL-1)
                {
                    centreline1[1] = COL-1;
                }
                else if(centreline1[1]<0)
                {
                    centreline1[1] = 0;
                }
            }
        }
        
        line2lost_memo[1] = 1;
    }
    else
    {
        centreline2[1] = (rightline2+leftline2)/2;
        line2lost_memo[1] = 1;
    }
    
    if(fixedrow3==0)
    {
        return;
    }
    
//    /**************************thirdline*********************************/
//    for (j=centreline3[0];j<COL-2;j++)
//    {
//        if (pData[fixedrow3*COL+j]==255 && pData[fixedrow3*COL+j+1]==0 && pData[fixedrow3*COL+j+2]==0)
//        {
//            rightline3 = j;          
//            right3lost_flag = 0;
//            break;
//        }
//        if(pData[fixedrow3*COL+j]==0)
//        {
//            right3blackpoint++;
//        }
//    }    
//    for (j=centreline3[0];j>1;j--)
//    {
//        if (pData[fixedrow3*COL+j]==255 && pData[fixedrow3*COL+j-1]==0  && pData[fixedrow3*COL+j-2]==0)
//        {
//            leftline3=j;            
//            left3lost_flag = 0;
//            break;
//        }
//        if(pData[fixedrow3*COL+j]==0)
//        {
//            left3blackpoint++;
//        }
//    }   
//    
//    if(left3blackpoint>2 || right3blackpoint>2)
//    {
//        left3lost_flag=1;
//        right3lost_flag=1;
//    }
//    
//    if(left3lost_flag==0 && right3lost_flag==0)
//    {
//        line3_width[1] = (rightline3-leftline3)/2;         
//        centreline3[1] = (rightline3+leftline3)/2;
//        line3lost_memo[1] = 0;
//        
//    }
//    else if(left3lost_flag==1 && right3lost_flag==0)
//    {
//        centreline3[1] = rightline3-line3_width[0];
//        line3lost_memo[1] = 1;
//    }
//    else if(left3lost_flag==0 && right3lost_flag==1)
//    {
//        centreline3[1] = leftline3+line3_width[0];
//        line3lost_memo[1] = 1;
//    }
//    else
//    {  
//        line3lost_memo[1] = 1;
//        centreline3[1] = (rightline3+leftline3)/2;
//    } 
//    
    
   
}  


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:drawline
*  ����˵��:�����������������ϲ���
*  ����˵��: ��rightΪ1ʱ�����ߣ���һ�У���һ�У�����У������
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

void drawline(uint8 *pData,int right,int startrow,int startcol)
{
    int i = 0;	
    float k = 0;
    float b = 0;
    int p_row = 0;
    int p_col = 0;     
    int length_point = 0;    
    
    float AV_direction = 0;
    
    /******�Ƕ�ƽ��ֵ��б�ʣ�ƽ��������׼��******/
    if (right && rightposmaxangle.pointnumber>10)
    {
        for (i=1;i<rightposmaxangle.pointnumber;i++)
        {            
            AV_direction += rightdirection[i]; 
        }         
        
        AV_direction /= rightposmaxangle.pointnumber;
        
        /******��ĸ��Ϊ0ʱ�������*******/
        if (AV_direction==180 || AV_direction==0)
        {
            return;
        }
        else 
        {
            k = 2 - AV_direction / 45;        
            b = startcol-k * startrow;	 
        }	
    }     
    else if ((!right) && leftposmaxangle.pointnumber>10)
    {
        for(i=1;i<leftposmaxangle.pointnumber;i++)
        {            
            AV_direction += leftdirection[i]; 
        }         
        
        AV_direction /= leftposmaxangle.pointnumber;
        
        /******��ĸ��Ϊ0ʱ�������*******/
        if (AV_direction==180 || AV_direction==0)
        {
            return;
        }
        else 
        {
            k = AV_direction / 45 - 2;        
            b = startcol-k * startrow;	 
        }	
    }     
    else
    {
        return;
    }
    
    /**********��������**********/       
    for (i=startrow;i>=0;i--)
    {
        p_row = i; 
        p_col = (int)(k * p_row + b);	  
        /********Խ������********/
        if(p_col<4 || p_col>COL-5)
        {
          break;
        }
                      
        length_point++;
                      
        /**��Χ�кڵ�����**/
        if (length_point>5)
        {
            if( pData[p_row*COL+p_col]==0 || pData[p_row*COL+p_col+1]==0 || pData[p_row*COL+p_col+2]==0
        	 || pData[p_row*COL+p_col-1]==0|| pData[p_row*COL+p_col-2]==0 )
            {
                break;
            }
        }
                      
        /*************����************/
        pData[p_row*COL+p_col] = 0;
    }
}

/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:crossline
*  ����˵��:�ж�ʮ�ֺ󣬸�����ʼ�������۽ǵ㣬����drawline��������
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

void crossline(uint8 *pData)
{
    int p1_row = 0;
    int p1_col = 0;
    int p2_row = 0;
    int p2_col = 0;
           
    /*********************ȷ���������*********************/
    if(leftposmaxangle.pointnumber!=0)
    {
        if (abs(leftcolmaxpoint[2]-leftposmaxangle.pointnumber)<5)
        {
            p1_row = ROW-leftcolmaxpoint[0];
            p1_col = leftcolmaxpoint[1];
        }
        else
        {
            p1_row = ROW-leftposmaxangle.row;
            p1_col = leftposmaxangle.col;
        }
    }
     
    if(rightposmaxangle.pointnumber!=0)
    {
        if (abs(rightcolminpoint[2]-rightposmaxangle.pointnumber)<5)
        {
            p2_row = ROW-rightcolminpoint[0];
            p2_col = rightcolminpoint[1];	   
        } 
        else
        {
            p2_row = ROW-rightposmaxangle.row;
            p2_col = rightposmaxangle.col;
        }
    }

    /****************************����*******************************/
      
    if(leftlinerow[1]<10 && leftpointnumber>10)
    {
        drawline(pData,0,p1_row,p1_col);   
    }
    if(rightlinerow[1]<10 && rightpointnumber>10)
    {
        drawline(pData,1,p2_row,p2_col);   
    }
}


/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:addline
*  ����˵��:1:ȷ���ƶ��� 2:�ƶ��߽��߲���
*  ����˵��: ����תʱ��directionΪ1����תΪ0
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  
void addline(uint8 *pData,int direction)
{
    int i = 0;
    int j = 0;
    int left = 0;
    int time = 0;
    int right = COL-1;
    int up = 0;
    int down = ROW-1;
    int searchcol = 0;
    int offset = 0;
    int row_move = 0;
    int col_move = 0; 
    int path_row[120];
    int path_col[120];
    
    memset(path_row,0,sizeof(int)*120);
    memset(path_col,0,sizeof(int)*120);    
   
    /*******************************ȷ������******************************/
    if (direction==1)//��ת
    {
        searchcol = COL-3;
        time = leftpointnumber;
    }
    else//��ת
    {
        searchcol = 2;
        time = rightpointnumber;
    }

    /*********************************ȷ���ƶ���***************************/
    
    /**********��һ*********/
    for (j=COL/2;j<COL-1;j++)
    {
        if (pData[(ROW-3)*COL+j]==255 && pData[(ROW-3)*COL+j+1]==0)
        {
            right = j;
            break;
        }  
    }    
    for (j=COL/2;j>0;j--)
    {
        if (pData[(ROW-3)*COL+j]==255 && pData[(ROW-3)*COL+j-1]==0)
        {
            left = j;
            break;
        }  
    }       
   /*********���*********/
    for (j=ROW-1;j>9;j--)
    {
        if (pData[j*COL+searchcol]==255 && pData[(j-1)*COL+searchcol]==255 
                                        && pData[(j-2)*COL+searchcol]==255
                                        && pData[(j-1)*COL+searchcol]==255
                                        && pData[(j-3)*COL+searchcol]==0)
        {
            up = j;
            break;
        }  
    }    
    if (up!=0)
    {
        for (j=ROW-1;j>up;j--)
        {
            if (pData[j*COL+searchcol]==0 && pData[(j-1)*COL+searchcol]==255
                                          && pData[(j-2)*COL+searchcol]==255
                                          && pData[(j-3)*COL+searchcol]==255
                                          && pData[(j-4)*COL+searchcol]==255)
            {
                down = j;
                break;
            }  
        }
    }

    row_move = abs((down-up)/2);   
    col_move = abs((right-left)/2);
    
    /**********************************����***********************************/

    if (direction==1)//��ת ������
    {
        if (leftpointnumber>20)//���ߴ���
        {
            for (i=1;i<leftpointnumber;i++)
            {	        
    	        leftlinecol[i] += col_move;
                
    	        /********��Խ���ж�*********/
                if (leftlinecol[i]>COL-1)
    	        {		  
    	            leftlinecol[i] = 0;
    	   	    leftlinerow[i] = 0;	
    		    time--;
                }			
            }
    	 
           /************�ж��ƶ��к��Ƿ��ƶ���*******/
           if (time>10)
           {
    	       for (i=1;i<leftpointnumber;i++)//���жϿ��ƶ���ʣ������
    	       {			
    	           leftlinerow[i] -= row_move;
    		   /********��Խ���ж�*********/		     
    		   if (leftlinerow[i]<5)
    	           {
    	               time--;
    	           }			  		     
               }
    	       /*�ƶ��к���������������ƶ�*/
    	       if (time<10)
    	       {
    	           for (i=1;i<leftpointnumber;i++)
    	           {
    	   	       leftlinerow[i] += row_move;	
    		       pData[(ROW-leftlinerow[i])*COL+leftlinecol[i]]=0;
                   }	       
               }
    	       else
    	       {  	      
    	           for (i=1;i<leftpointnumber;i++)
    	           {	
    	       	       if (leftlinerow[i]<5)
    	               {
    	                   leftlinerow[i] = 0;
    	                   leftlinecol[i] = 0;			  	   
    	     	       }
    	       	       pData[(ROW-leftlinerow[i])*COL+leftlinecol[i]]=0;
                   }		      	
               }
           }
        }
    }
    else  //��ת
    {
        if(rightpointnumber>20)//���ߴ���
        {
            for(i=1;i<rightpointnumber;i++)
            {	        
                rightlinecol[i] -= col_move;		     
                /********��Խ���ж�*********/
                if(rightlinecol[i]<0)
                {		  
                    rightlinecol[i] = 0;
         	    rightlinerow[i] = 0;	
      	            time--;
                }			
            }
            /************�ж��ƶ��к��Ƿ��ƶ���*******/
            if(time>10)
            {
                for(i=1;i<rightpointnumber;i++)//���жϿ��ƶ���ʣ������
                {			
      	            rightlinerow[i] -= row_move;
      	            /********��Խ���ж�*********/		     
      	            if(rightlinerow[i]<5)
                    {
                        time--;
                    }			  		     
                }
                /*�ƶ��к���������������ƶ�*/
                if(time<10)
                {
                    for(i=1;i<rightpointnumber;i++)
                    {						 
         	        rightlinerow[i] += row_move;	
      	                pData[(ROW-rightlinerow[i])*COL+rightlinecol[i]]=0;
                    }	       
                }
                else
                {  	      
      	            for(i=1;i<rightpointnumber;i++)
                    {	
      	  	        if(rightlinerow[i]<5)
                        {
      	                    rightlinerow[i] = 0;
      	                    rightlinecol[i] = 0;			  	   
      	                }
      	   	        pData[(ROW-rightlinerow[i])*COL+rightlinecol[i]]=0;
                    }
                }
            }
        }
    }
	
    /********************************�����Ų��߽��߲���һ������Ȩ��*******************************/
 
    if(direction==1)//��ת
    {
        time = 0;
        
	for(i=1;i<=leftpointnumber;i++)
	{
	    if(leftlinerow[i]!=0 && leftlinecol[i]!=0)
	    {
                path_row[time] = leftlinerow[i];
                path_col[time] = leftlinecol[i];
                time++;		   
            }
        }	
	 
	if(time>0)
	{
	    for(i=0;i<time;i++)
            {         
	 	offset +=(path_col[i]-MID);
            }	           
	    offset = offset/time;	   
	}
    }
    else//��ת
    {
	time = 0;
	for(i=1;i<=rightpointnumber;i++)
	{
	    if(rightlinerow[i]!=0 && rightlinecol[i]!=0)
	    {
	        path_row[time] = rightlinerow[i];
	        path_col[time] = rightlinecol[i];
	        time++;		   
	    }
	}	
	if(time>0)
	{
	    for(i=0;i<time;i++)
            {
            
	  	offset +=(path_col[i]-MID);
            }	            
	    offset = offset/time;	  
	}
    }
}
/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:renziroll
*  ����˵��:���ִ����ɼ��ײ��ͱ߽���Ϣ������ƫת��
*  ����˵��: ��rightΪ1ʱ������
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  
void renziroll(uint8 *pData,int direction)
{  
    int j = 0;
  
    int left = 2;
    int right = COL-3;
    int up = 2;
    int down = ROW-3;
    int searchcol = 0;
    int sum = 0;
    
    int one_row = 0;
    int one_col = 0;
    int two_row = 0;
    int two_col = 0;
    int three_row = 0;  
    int three_col = 0;
    int four_row = 0;
    int four_col = 0;  
    int five_row = 0;
    int five_col = 0;
  
    if (direction==1)//��ת
    {
        searchcol = COL-1;
    }
    else//��ת
    {
        searchcol = 1;
    }
  
     /////////////////////////////////////////////////////////////////////////////
  
    for (j=COL/2;j<COL-2;j++)
    {
        if (pData[(ROW-1)*COL+j]==255 && pData[(ROW-1)*COL+j+1]==0)
        {
             right = j;
             break;
        }  
    }
  
    for (j=COL/2;j>2;j--)
    {
        if (pData[(ROW-1)*COL+j]==255 && pData[(ROW-1)*COL+j-1]==0)
        {
            left = j;
            break;
        }  
    }
  
    one_row = ROW-1;
    one_col = (right+left)/2; 
  
    ////////////////////////
 
    for (j=ROW-1;j>=10;j--)
    {
        if (pData[j*COL+searchcol]==255 && pData[(j-1)*COL+searchcol]==255 
                                        && pData[(j-2)*COL+searchcol]==255
                                        && pData[(j-1)*COL+searchcol]==255
                                        && pData[(j-3)*COL+searchcol]==0  )
        {
            up = j;
            break;
        }  
    }  
    for (j=ROW-1;j>=up;j--)
    {
        if (pData[j*COL+searchcol]==0 && pData[(j-1)*COL+searchcol]==255
                                      && pData[(j-2)*COL+searchcol]==255
                                      && pData[(j-3)*COL+searchcol]==255
                                      && pData[(j-4)*COL+searchcol]==255)
        {                        
            down = j;
            break;
        }  
    }
    
    five_row = (up+down)/2;
    five_col = searchcol;
  
    ////////////////////////////////////////
    
    two_row = one_row+(five_row-one_row)/4;
    three_row = two_row+(five_row-one_row)/4;
    four_row = three_row+(five_row-one_row)/4;
    
    two_col = one_col+(five_col-one_col)/4;
    three_col = two_col+(five_col-one_col)/4;
    four_col = three_col+(five_col-one_col)/4;
    
    sum = one_row*(one_col-MID) + two_row*(one_col-MID) + three_row*(three_col-MID)
                                + four_row*(four_col-MID) + five_row*(five_col-MID);
    if(direction==1)
    {
        g_fDIR = sum/(one_row+two_row+three_row+four_row+five_row)*0.5+25+NowSpeed*0.1;  
    }
    else
    {
        g_fDIR = sum/(one_row+two_row+three_row+four_row+five_row)*0.5-25-NowSpeed*0.1;  
    }
}

/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:crossroll
*  ����˵��:ʮ�ִ������ߺ���������
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  
void crossroll(uint8 *pData,int up)
{
    int i = 0; 
    int leftline = 0;
    int rightline = 0; 
    int crossrow = 0;
    int middle = 0;
    
    centreline[0] = 0;    
    
    if (up)
    {
        crossrow = fixedrow1;        
        if (leftposmaxangle.col!=0 && rightposmaxangle.col!=0)
        {
            middle = (leftposmaxangle.col+rightposmaxangle.col)/2;
        }
        else if (leftposmaxangle.col==0 && rightposmaxangle.col!=0)
        {
            middle = rightposmaxangle.col/2;
        }
        else if (leftposmaxangle.col!=0 && rightposmaxangle.col==0)
        {
            middle = (leftposmaxangle.col+COL)/2;
        }  
        else
        {
            middle =COL/2;
        }
          
        while (crossrow>0)
        {   
            
            for (i=middle;i>3;i--)
            {
                if (pData[crossrow*COL+i]==255 && pData[crossrow*COL+i-1]==0)
                {
                    leftline = i;
                    break;
                }   
            }
            for (i=middle;i<COL-4;i++)
            {
                if(pData[crossrow*COL+i]==255 && pData[crossrow*COL+i+1]==0)
                {
                    rightline = i;
                    break;
                }      
            }       
            
            if(rightline!=0 && leftline!=0 && (rightline-leftline<65))
            {
                centreline[0] = (rightline+leftline)/2; 
                break;
            }
            
             crossrow--;            
        }
    }
    else
    {
         crossrow = ROW-10;
        
         for (i=COL/2;i>3;i--)
         {
             if (pData[crossrow*COL+i]==255 && pData[crossrow*COL+i-1]==0)
             {
                 leftline = i;
                 break;
             }   
         }
         for (i=COL/2;i<COL-4;i++)
         {
             if(pData[crossrow*COL+i]==255 && pData[crossrow*COL+i+1]==0)
             {
                 rightline = i;
                 break;
             }      
         }    
         
        if(rightline!=0 && leftline!=0)
        {
            centreline[0] = (rightline+leftline)/2;       
        }    
    }
    
    draw_point_anti(pData,crossrow,(int)centreline[0]);
    
}



/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:protect
*  ����˵��:���籣�������ײ����ֺڵ��������Ϊ�ѳ��߽�����ͣ������
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

void protect(uint8 *pData)
{
    int i = 0; 
    int blackpoint = 0;
    extern int OLED_stop_flag;
  
    for(i=0;i<COL;i++)
    {
        if(pData[(ROW-5)*COL+i]==0)
        {
            blackpoint++;
        }
    }
  
    if(blackpoint>COL-20)
    {
        stop_flag = 1; 
        if(OLED_stop_flag==0){
                  OLED_ShowStr(0,0,"Chujie",1);
                }
                OLED_stop_flag = 1;
    }
}  

/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:offsetcal
*  ����˵��:����������Ϣ����ƫ��������������������������ͬƫ�����ļ����봦��
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  

void offsetcal(uint8 *pData)
{   
    typememo[1] = 0;
      
    /**************************���ִ���**********************/
    if (herringbone_flag)  
    {          
        //gpio_set(PTE0,1);
        typememo[1] = 1; 
        crossroad_flag = 0;
        ramp_flag = 0;
        s_bend_flag = 0;
        block_flag = 0;
        
        if (CarAngle>35)
        {
            ren_turn_limit = 23;
        }
        else if (CarAngle<36 && CarAngle>-21)
        {
            ren_turn_limit = ren_array[(int)CarAngle+20];
        }
        else
        {
            ren_turn_limit = 55;
        }
        
        linewidth = widthmeasure(pData,ren_turn_limit);       
        
        /****��ת����****/
        if ((linewidth>90) && turn_flag==0)
        {                                  
            turn_flag = herringbone_flag;            
        }
        
        if (turn_flag==1)
        {              
            if (Ren_Clean_Flag==1)
            {               
                Ren_Clean_Flag = 0;     //�����־λ 
                herringbone_flag=0;
                turn_flag=0;     
               // gpio_set(PTE0,0);                
            }
            else
            {
                renziroll(pData,0);              
                return;    
            }
        }
        else if (turn_flag==2)
        { 
            if (Ren_Clean_Flag==1)
            {
                Ren_Clean_Flag = 0;     //�����־λ 
                herringbone_flag=0;
                turn_flag=0;     
                //gpio_set(PTE0,0);
                
            }
            else
            {     
                renziroll(pData,1);   
                return;    
            }
        }  
    }
  
  
    /***********************ʮ�ִ���**********************/
  
    if (crossroad_flag)
    {   
        //gpio_set(PTE0,1);
        typememo[1] = 2;           
        herringbone_flag = 0;
        ramp_flag = 0;
        s_bend_flag = 0;
        block_flag = 0;
        
        if (right1lost_flag==0 && left1lost_flag==0 && right2lost_flag==0 && left2lost_flag==0)
        {             
            crossroad_flag = 0;           
            //gpio_set(PTE0,0);
        } 
        
        if (crossroad_flag!=0)
        {             
            draw_shizi(pData);  
            crossline(pData);           
            crossroll(pData,1);           
            
            g_fDIR = (centreline[0] - MID) * OffsetQ;  
            
            #if draw_1
            draw_point_anti(pData,fixedrow1,(int)centreline1[1]);
            draw_point_anti(pData,fixedrow2,(int)centreline2[1]);            
            draw_point_anti(pData,ROW-1,MID+(int)g_fDIR/2);
            draw_point_anti(pData,ROW-2,MID+(int)g_fDIR/2);  
            #endif
            
            return;
        }
    }    
    
   /***********************s�䴦��**********************/
    if(s_bend_flag)
    {       
        //gpio_set(PTE0,1);
        if((leftlinecol[leftpointnumber]<3 && rightlinecol[rightpointnumber]<3)
           || (leftlinecol[leftpointnumber]>COL-4 && rightlinecol[rightpointnumber]>COL-4)
           || ramp_flag==1)
        {
            ///gpio_set(PTE0,0);
            s_bend_flag = 0;
            OffsetQ = 0.8;
        }
        else
        {
             OffsetQ = 0.5;
        }
    }    
    
    /****************************ƫ�����***************************/ 
 
    if (pData[fixedrow1*COL+centreline1[1]]==255 && pData[fixedrow2*COL+centreline2[1]]==255)
    {
        g_fDIR = ((centreline1[1]+centreline2[1])/2-MID);  
        g_fDIR = g_fDIR * OffsetQ; 
      
    } 
    else if (pData[fixedrow1*COL+centreline1[1]]==255 && pData[fixedrow2*COL+centreline2[1]]==0)
    {
        g_fDIR = (centreline1[1]-MID);
        g_fDIR = g_fDIR * OffsetQ;
    }
    else if (pData[fixedrow1*COL+centreline1[1]]==0 && pData[fixedrow2*COL+centreline2[1]]==255)
    {
        g_fDIR = (centreline2[1]-MID); 
        g_fDIR = g_fDIR * OffsetQ;  
    }
    else if (pData[fixedrow1*COL+centreline1[1]]==0 && pData[fixedrow2*COL+centreline2[1]]==0)
    {
        g_fDIR = nErrors[0];
    }     
  
    
  /****************************ƫ�����ٶ����************************/
    if (NowSpeed<2)
    {
        g_fDIR *= (2.0 / 3.2); 
    }
    else
    {
        g_fDIR *= (NowSpeed / 3.2); 
    }
       
   
  
    /************************�ϰ��ﴦ��**************************/
  
    if (block_flag==1)
    {            
        herringbone_flag = 0;
        ramp_flag = 0;
        s_bend_flag = 0;
        crossroad_flag = 0;        
       
        g_fDIR = (rightline1-20-MID);// * OffsetQ;/********/   
        //gpio_set(PTE0,1);
        
        hold_flag++;
        
        /******����5֡*�����־λ**/   
        if (hold_flag>=(25-NowSpeed/4))
        {
            //gpio_set(PTE0,0);  
            block_flag = 0;
            hold_flag = 0;                
        }
    }   
    else if (block_flag==2)
    {             
        g_fDIR = (leftline1+20-MID); //* OffsetQ;/********/
        hold_flag++;
        //gpio_set(PTE0,1);                
     
       
        /******����5֡*�����־λ**/   
        if (hold_flag>=(25-NowSpeed/4))
        {
            //gpio_set(PTE0,0);  
            block_flag = 0;
            hold_flag = 0;                
        }
    }   
   
    #if draw_1
         draw_point_anti(pData,fixedrow1,(int)centreline1[1]);
         draw_point_anti(pData,fixedrow2,(int)centreline2[1]);         
         
         draw_point_anti(pData,ROW-1,MID+(int)g_fDIR/2);
         draw_point_anti(pData,ROW-2,MID+(int)g_fDIR/2);  
    #endif
}
   
/*************************************************************************
*         �             ��             ֮               ��			                               
*
*  ��������:imagpro_2
*  ����˵��:�����������ã�ȫ��ͼ�������ڴ˵���
*  ����˵��: 
*  ��������:
*  �޸�ʱ��:
*  ��    ע: 
*************************************************************************/  
void imagpro_2(uint8 *pData)
{        
  
  
    typememo[1] = 0;    
    
    /*****************���籣��****************/    
    protect(pData);
    
    /**********��Ұ�޶��Ϳ������޶�***********/
    confine(pData);
    
    /*****************��ֵ�˲�****************/     
    midfilter(pData);
    
    /************ȡ�߽��߻�׼��***************/  
    getstartline(pData);
    
    /*****************���ɱ߽���**************/  
    trackpoint(pData);  
    
    /*****************���ݴ���****************/
    dataprocess();      
    
    /*****************ʶ������****************/
    if ((lefthighestpoint[0]<45-view_limit || righthighestpoint[0]<45-view_limit) && R_ren)
    {
        rec_herringbone(pData);             
    }    
    
    /*****************����й�****************/            
    fixedrow1 =  limit_down-line_move;
    fixedrow1 = fixedrow1+control_limit; 
    fixedrow2 = fixedrow1+2;  
    
    /****************ʶ��s��******************/        
    if (left1lost_flag==0 && right1lost_flag==0
             && left2lost_flag==0 && right2lost_flag==0 
             && NowSpeed>2.2 && ramp_flag==0 && R_xiaos)
    {
        rec_s_bend(pData);    
    }
    
    
    /*****************Ѱ���е�****************/
    fixedline(pData);   
    
    /*****************ʶ��ʮ��****************/
    if ((left1lost_flag==1 ||  right1lost_flag==1
          || left2lost_flag==1 ||  right2lost_flag==1) && crossroad_flag==0 && R_shizi)
    {
        rec_crossroad(pData);        
    }    
    
    else if (left1lost_flag==0 && right1lost_flag==0
             && left2lost_flag==0 && right2lost_flag==0 && abs(centreline1[1]-centreline2[1])<3)
    {
        if(R_qipao)
        {
            /****************ʶ��������***************/
            rec_startingline(pData);        
        }
        /****************ʶ���µ�*****************/
        rec_ramp();
    }
    
    if (left1lost_flag==0 && right1lost_flag==0
             && left2lost_flag==0 && right2lost_flag==0 && R_zhang)
    {           
        /****************ʶ���ϰ���***************/
        HandleBarrier(&leftlinerow[0],leftpointnumber,&rightlinerow[0],rightpointnumber,&leftlinecol[0],&rightlinecol[0],59-fixedrow1,&centreline2[1],&centreline1[1],59-fixedrow1);

    }
    
    if (ramp_flag!=0)
    {
        //gpio_set(PTE0,1); 
//        uSet = uSet_pre-0.8;
        hold_flag++;
        block_flag = 0;
        
        if (hold_flag>50)
        {
            //gpio_set(PTE0,0); 
//            uSet = uSet_pre;
            hold_flag = 0;
            ramp_flag = 0;
        }
    }   
       

    /*****************����ƫ��****************/
    offsetcal(pData); 
    
    /***********��¼�������ͺ�ƫ��************/
    DIR_fifo();
    typememo_fifo();     
   
//    draw_angle(pData);
//    draw_width(pData);
    
    if (sendimgflag>0)
    {
        drawpoint_2(pData);
    }  
}

