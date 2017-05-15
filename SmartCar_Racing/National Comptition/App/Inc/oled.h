#ifndef _OLED_H
#define _OLED_H
#include "FIRE_key.h"
#include  "MKL_PIT.h" 
#include  "MKL_SysTick.h"       //�δ�ʱ��
#include "DEFINECTRL.h"

void OLED_i2c_init();
//д����
void WriteCmd(unsigned char I2C_Command);
//д����
void WriteDat(unsigned char I2C_Data);
//OLED��ʼ��
void OLED_Init(void);
//������ʼ������
void OLED_SetPos(uint8 x,uint8 y);
//ȫ�����
void OLED_Fill(unsigned char fill_Data);
//����
void OLED_CLS(void);
//��OLED�������л���
void OLED_ON(void);
//��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
void OLED_OFF(void);
//��ʾ�ַ���
void OLED_ShowStr(uint8 x, uint8 y, uint8 ch[], uint8 TextSize);
//��ʾ����
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
//��ͼ
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

extern float OffsetQ;
extern int ren_startturn,ren_offset,zhang_offset,zhang_holdtime,R_ren,R_xiaos,R_qipao,R_shizi,R_zhang;

extern double Kw,Kb,Kv,Ka,P_Direction,D_Direction,uSet,uSet_pre,uSetFollow,dir_ctrl_lim,dir_ctrl_lim_set,Moto_dead;
#endif













