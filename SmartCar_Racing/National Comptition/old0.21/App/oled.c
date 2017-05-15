#include "common.h"
#include "MKL_i2c.h"
#include "oled.h"
#include "MKL_lptmr.h"
#include "codetab.h"


#define	OLED_ADDR	0x3C			//OLED的地址要更改

void OLED_i2c_init()
{
	i2c_init(I2C0,200*1000);
}

//写命令
void WriteCmd(unsigned char I2C_Command)
{
	i2c_write_reg(I2C0, OLED_ADDR, 0x00, I2C_Command);
}

//写数据
void WriteDat(unsigned char I2C_Data)
{
	i2c_write_reg(I2C0,OLED_ADDR,0x40,I2C_Data);
}

void dely(uint16 time)
{
	 lptmr_delay_ms(time);
}

void OLED_Init(void)
{
	dely(100); //这里的延时很重要
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);//Set Memory Addressing Mode	
	WriteCmd(0x10);//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}


//设置起始点坐标
void OLED_SetPos(uint8 x,uint8 y) 
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}


//全屏填充
void OLED_Fill(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}

//清屏
void OLED_CLS(void)
{
	OLED_Fill(0x00);
}


//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(uint8 x, uint8 y, uint8 ch[], uint8 TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}

void OLED_ShowNum(uint8 x, uint8 y, int num, uint8 TextSize){
  int one = 0,ten = 0;
  one = num%10;
  ten = (num/10)%10;
  switch (ten){
    case 0:
    OLED_ShowStr(x,y,"0",TextSize);
    break;
    case 1:
    OLED_ShowStr(x,y,"1",TextSize);
    break;
    case 2:
    OLED_ShowStr(x,y,"2",TextSize);
    break;
    case 3:
    OLED_ShowStr(x,y,"3",TextSize);
    break;
    case 4:
    OLED_ShowStr(x,y,"4",TextSize);
    break;
    case 5:
    OLED_ShowStr(x,y,"5",TextSize);
    break;
    case 6:
    OLED_ShowStr(x,y,"6",TextSize);
    break;
    case 7:
    OLED_ShowStr(x,y,"7",TextSize);
    break;
    case 8:
    OLED_ShowStr(x,y,"8",TextSize);
    break;
    case 9:
    OLED_ShowStr(x,y,"9",TextSize);
    break;
  }
  switch (one){
    case 0:
    OLED_ShowStr(x+6,y,"0",TextSize);
    break;
    case 1:
    OLED_ShowStr(x+6,y,"1",TextSize);
    break;
    case 2:
    OLED_ShowStr(x+6,y,"2",TextSize);
    break;
    case 3:
    OLED_ShowStr(x+6,y,"3",TextSize);
    break;
    case 4:
    OLED_ShowStr(x+6,y,"4",TextSize);
    break;
    case 5:
    OLED_ShowStr(x+6,y,"5",TextSize);
    break;
    case 6:
    OLED_ShowStr(x+6,y,"6",TextSize);
    break;
    case 7:
    OLED_ShowStr(x+6,y,"7",TextSize);
    break;
    case 8:
    OLED_ShowStr(x+6,y,"8",TextSize);
    break;
    case 9:
    OLED_ShowStr(x+6,y,"9",TextSize);
    break;
  }
  
  
}



