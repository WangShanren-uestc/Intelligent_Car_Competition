#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */
#include  "MKL_BME.h"           //λ����
#include  "MKL_wdog.h"          //���Ź�
#include  "MKL_gpio.h"          //IO�ڲ���
#include  "MKL_uart.h"          //����
#include  "MKL_SysTick.h"       //�δ�ʱ��
#include  "MKL_lptmr.h"         //�͹��Ķ�ʱ��(��ʱ�������������ʱ����ʱ)
#include  "MKL_i2c.h"           //I2C
#include  "MKL_spi.h"           //SPI
#include  "MKL_tpm.h"           //TPM������K60�� FTM ��pwm�����������
#include  "MKL_pit.h"           //PIT
#include  "MKL_adc.h"           //ADC
#include  "MKL_dac.h"           //DAC
#include  "MKL_dma.h"           //DMA
#include  "MKL_FLASH.h"         //FLASH


#include  "FIRE_LED.H"          //LED
#include  "FIRE_KEY.H"          //KEY
#include  "FIRE_MMA7455.h"      //������ٶ�MMA7455
#include  "FIRE_NRF24L0.h"      //����ģ��NRF24L01+

#include  "FIRE_camera.h"       //����ͷ��ͷ�ļ�
#include  "FIRE_LCD.h"          //Һ����ͷ�ļ�

#include  "FIRE_TSL1401.h"      //����CCD
#include  "FIRE_key_event.h"    //������Ϣ����
#include  "FIRE_NRF24L0_MSG.h"  //����ģ����Ϣ����




#endif  //__INCLUDE_H__
