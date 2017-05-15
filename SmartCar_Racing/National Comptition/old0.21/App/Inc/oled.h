#ifndef _OLED_H
#define _OLED_H

void OLED_i2c_init();
//写命令
void WriteCmd(unsigned char I2C_Command);
//写数据
void WriteDat(unsigned char I2C_Data);
//OLED初始化
void OLED_Init(void);
//设置起始点坐标
void OLED_SetPos(uint8 x,uint8 y);
//全屏填充
void OLED_Fill(unsigned char fill_Data);
//清屏
void OLED_CLS(void);
//将OLED从休眠中唤醒
void OLED_ON(void);
//让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
void OLED_OFF(void);
//显示字符串
void OLED_ShowStr(uint8 x, uint8 y, uint8 ch[], uint8 TextSize);
//显示汉字
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
//画图
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


#endif













