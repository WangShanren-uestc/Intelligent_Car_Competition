#include "tool.h"

int16 OutData[4];

float Rsqrt(float number)
{
	long i;	
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 一阶牛顿迭代
	
	return y;
}

float InvSqrt(float x)
{
  float xhalf = 0.5f*x;
  int64 i = *(int64*)&x; // get bits for floating VALUE
  i = 0x5f375a86- (i>>1); // gives initial guess y0
  x = *(float*)&i; // convert bits BACK to float
  x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
  return x;
} 

void save_data(uint8 *sendbuf)
{
    sendbuf[0]   =  (uint8)OutData[0];
    sendbuf[0+1] =  (uint8)(OutData[0]>>8);
    sendbuf[0+2] =  (uint8)OutData[1];
    sendbuf[0+3] =  (uint8)(OutData[1]>>8);

    sendbuf[0+4] =  (uint8)OutData[2];
    sendbuf[0+5] =  (uint8)(OutData[2]>>8);
    sendbuf[0+6] =  (uint8)OutData[3];
    sendbuf[0+7] =  (uint8)(OutData[3]>>8);
}

void write_frame_mark(uint8 *datapointer){
//  *datapointer=0xF0;
//  *(datapointer+1)=0xF0;
//  *(datapointer+2)=0xF0;
//  *(datapointer+3)=0xF0;
//  *(datapointer+4)=0xF0;
//  *(datapointer+5)=0xF0;
//  *(datapointer+6)=0xF0;
//  *(datapointer+7)=0xF0;
//  *(datapointer+8)=0xF0;
//  *(datapointer+9)=0xF0;
  *(datapointer+OUT_DATA_SIZE-2)=0x0F;
  *(datapointer+OUT_DATA_SIZE-1)=0x0F;
}

void save_frame_cnt(int16 src,uint8 *dst){
    dst[0]   =  (uint8)src%256;
    dst[0+1] =  (uint8)(src/256);
}

void save_uint16(uint16 src,uint8 *dst){

    dst[0]   =  (uint8)src%256;
    dst[0+1] =  (uint8)(src/256);
}

void save_double2int16(double src,uint8 *dst){
    int16 temp = 0;
    temp = (int16)src;

    dst[0]   =  (uint8)temp;
    dst[0+1] =  (uint8)(temp>>8);
}

void sendimg(uint8 *imgaddr, uint32 imgsize)
{
    uint8 cmd[4] = {0, 255, 1, 0 };    //yy_摄像头串口调试 使用的命令

    uart_putbuff(FIRE_PORT, cmd, sizeof(cmd));    //先发送命令

    uart_putbuff(FIRE_PORT, imgaddr, imgsize); //再发送图像
}

/*!
 *  @brief      二值化图像解压（空间 换 时间 解压）
 *  @param      dst             图像解压目的地址
 *  @param      src             图像解压源地址
 *  @param      srclen          二值化图像的占用空间大小
 *  @since      v5.0            img_extract(img, imgbuff,CAMERA_SIZE);
 *  Sample usage:   sendimg(imgbuff, CAMERA_W * CAMERA_H);                    //发送到上位机
 */
void img_extract(uint8 *dst, uint8 *src, uint32 srclen)
{
    uint8 colour[2] = {255, 0}; //0 和 1 分别对应的颜色
    //注：野火的摄像头 0 表示 白色，1表示 黑色
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}

void img_condense(uint8 *dst, uint8 *src, uint32 srclen){
   
  memset(dst,0,sizeof(uint8)*srclen);
  
    while(srclen--){
      *dst |= (*src++ & 0x80);
      *dst |= (*src++ & 0x40);
      *dst |= (*src++ & 0x20);
      *dst |= (*src++ & 0x10);
      *dst |= (*src++ & 0x08);
      *dst |= (*src++ & 0x04);
      *dst |= (*src++ & 0x02);
      *dst |= (*src++ & 0x01);
      *dst = ~*dst;
      dst++;
    }
  
}

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}
/*

*/

void OutPut_Data()
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int16)OutData[i];
    temp1[i] = (uint16)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (int8)(temp1[i]%256);
    databuf[i*2+1] = (int8)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
  uart_putchar (UART0, databuf[i]); 
  
  
}