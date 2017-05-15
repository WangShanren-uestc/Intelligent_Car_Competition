#include"test.h"
/*
函数功能：查找数组中的roadtype
函数返回：找到：1
          没找到：0			
*/
unsigned char FindRoadType(int* array,int Length,int roadtype0)//查找数组中的Roadtype
{
  int i=0;
  int* tempaddress=array;
  for(i=0;i<Length;i++)
  {
    if(*(tempaddress++)==roadtype0)return 1;
  }
  return 0;
}

/*
输入： 勾线左边行计数起始指针及长度
	   勾线右边行计数起始指针及长度
	   左、右目标多少点的个数数组指针
	   左、右靠行索引的数组指针
	   勾线左、右列数起始指针
改变:  目标数组的内容，记录每行勾了多少个点
*/
void GetPointTab(int* Row_L,int length_L,int* Row_R,int length_R,int* array_aimnumL,int* array_aimnumR,
	int* array_aimdataL,int* array_aimdataR,int* Col_L,int* Col_R)
{
	int i=0;
	for(i=1;i<length_L;i++)
	{
		(*(array_aimnumL+*(Row_L+i)))++;
		*(array_aimdataL+*(Row_L+i))=*(Col_L+i);
	}

	for(i=1;i<length_R;i++)
	{
		(*(array_aimnumR+*(Row_R+i)))++;
		*(array_aimdataR+*(Row_R+i))=*(Col_R+i);
	}
}


/*
输入：识别结束行，左边界数组，右边界数组，

函数返回0： 没有识别到障碍物  
		1:  识别到右边障碍物
		-1：识别到左边障碍物
*/
signed char ChargeBarrier(int end_line,int* array_aimnumL,int* array_aimnumR,int* array_aimdataL,int* array_aimdataR)
{
	int i=0;
	for(i=3;i<=end_line;i++)
	{
		if(
                   (( (*(array_aimnumL+i)==1)&&(*(array_aimnumR+i)>0)&&(*(array_aimnumR+i)<=4) )
                   ||( (*(array_aimnumR+i)==1)&&(*(array_aimnumL+i)>0)&&(*(array_aimnumL+i)<=4) ))
			&&(*(array_aimnumL+i-3)==1)&&(*(array_aimnumR+i-3)==1)
			)//如果2差行勾边只有一个点障碍物边可能很多
		{
			if(
				(*(array_aimdataL+i)>*(array_aimdataL+i-3))&&(*(array_aimdataR+i)<*(array_aimdataR+i-3))
				&&(*(array_aimdataL+i-3)>=(ImageEdgeL+10))&&(*(array_aimdataR+i-3)<=(ImageEdgeR-10))
				)
			{
				if((*(array_aimdataL+i)-*(array_aimdataL+i-3))>=Door_Value)
				{
					return -1;
				}
				else if((*(array_aimdataR+i-3)-*(array_aimdataR+i))>=Door_Value)
				{
					return 1;
				}
			}


		}
	}
	return 0;
}


/*
处理障碍物函数

输入 勾边左行指针，长度
	 勾边右行指针，长度
	 勾边左列指针
	 勾边右列指针
	 搜索结束行（控制行）
	 控制行列数
	 控制行行数

函数改变： 控制行列数(中点)
*/

void  HandleBarrier(int* Row_L,int length_L,int* Row_R,int length_R,int* Col_L,int* Col_R,int end_line,int *centre_pos,int *centre_pos2,const int CtrRow)
{
	int i=0;
	int PosNum_L[ImageMaxRow]={0};
	int PosNum_R[ImageMaxRow]={0};
	int PosData_L[ImageMaxRow]={0};
	int PosData_R[ImageMaxRow]={0};
	static int RoadTypeRec[MaxRTRec]={0};


	GetPointTab(Row_L,length_L,Row_R,length_R,PosNum_L,PosNum_R,PosData_L,PosData_R,Col_L,Col_R);
	for(i=MaxRTRec-1;i>=1;i--)
	{
		RoadTypeRec[i]=RoadTypeRec[i-1];
	}
	RoadTypeRec[0]=ChargeBarrier(end_line,PosNum_L,PosNum_R,PosData_L,PosData_R);

	if(FindRoadType(RoadTypeRec,MaxRTRec,1)==1)//识别到右边障碍物
	{
                gpio_set(PTE0,1);
		*centre_pos=(((PosData_L[CtrRow]<<1)+RoadLengthBarrier)>>1);
                *centre_pos2=*centre_pos;
	}
	else if(FindRoadType(RoadTypeRec,MaxRTRec,-1)==1)//识别到左边障碍物
	{
                gpio_set(PTE0,1);
		*centre_pos=(((PosData_R[CtrRow]<<1)-RoadLengthBarrier)>>1);
                *centre_pos2=*centre_pos;
	}
        else
        {
              gpio_set(PTE0,0);
        }

}
