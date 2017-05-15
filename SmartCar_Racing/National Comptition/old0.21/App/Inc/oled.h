#ifndef _OLED_H
#define _OLED_H

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


#endif













