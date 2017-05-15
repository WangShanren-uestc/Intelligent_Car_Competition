/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      Ұ��KL26 ƽ̨������
 * @author     Ұ��Ƽ�
 * @version    v5.0
 * @date       2013-12-14
 */
#include "define.h"
#include "common.h"
#include "include.h"
#include "DEFINEimg.h"
#include "DEFINEmoto.h"
#include "DEFINEADC.h"

//KL26 ֻ�� A ��C��D�˿ڿɴ��� IO�ж� �� DMA  ������ C/D �˿� ������ͬ�ж�������
extern void PIT_IRQHandler(void);
extern uint8 ov7725_eagle_reg_init(void);
extern void SysTick_IRQHandler(void);
extern void gyroadj(void);
extern void CTRL_Handler();
void all_init(void);

void PORTC_PORTD_IRQHandler(void);        //PORTA�˿��жϷ�����
void DMA_IRQHandler(void);




uint8  nrf_rx_buff[DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff[CAMERA_SIZE+1 + OUT_DATA_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff1[CAMERA_SIZE+1 + OUT_DATA_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8 *command = (uint8 *)(((uint8 *)&nrf_rx_buff));
uint8 *imgbuff = (uint8 *)(((uint8 *)&nrf_tx_buff) + COM_LEN);     //ͼ���ַ
uint8 *imgbuff1 = (uint8 *)(((uint8 *)&nrf_tx_buff1) + COM_LEN);     //ͼ���ַ
uint8 *data_point = (uint8 *)(((uint8 *)&nrf_tx_buff) + CAMERA_SIZE+1 + COM_LEN);
uint8 *data_point1 = (uint8 *)(((uint8 *)&nrf_tx_buff1) + CAMERA_SIZE+1 + COM_LEN);


uint8 ImageBuf[ROW][COL]; 
uint8 *ImagePointer = ImageBuf[0];

int sendimgflag=2,S_Ctrlflag=-1,A_Ctrlflag=-1,D_Ctrlflag=-1,carflag = 0;//ctrlflag


int sampleCnt = 0,ready2tx_Flag = 0; //sampleflag


uint8  var1 = 20, var2;
uint16 var3, var4;
uint32 var5, var6;




 void main()
{
  
    uint8  tx_buff[CAMERA_SIZE+1 + OUT_DATA_SIZE + 2*COM_LEN + DATA_PACKET];
    uint8 *img_buff = (uint8 *)(((uint8 *)&tx_buff) + COM_LEN); 
	uint8 *data_pointer = (uint8 *)(((uint8 *)&tx_buff) + CAMERA_SIZE+1 + COM_LEN); 
    uint32 mode = 0;
    
    all_init();
    gyroadj();

    

    while(1)
    {
      
      if(mode==0){
         if(ready2tx_Flag==1){
          if(nrf_tx_state() != NRF_TXING){
            
            
            if(sendimgflag==1){
                  //��ͼ�� ���ͳ�ȥ
              if(sampleCnt==1){
                save_data(data_point1);
                nrf_msg_tx(COM_MY,nrf_tx_buff1);
              }
              else{
		save_data(data_point);
                nrf_msg_tx(COM_MY,nrf_tx_buff);
              }
            }
            else if(sendimgflag==2){
              img_condense(img_buff+1, ImageBuf, CAMERA_SIZE);
              *img_buff = *(img_buff + CAMERA_SIZE);
		save_data(data_pointer);
              nrf_msg_tx(COM_MY,tx_buff);
            }
        
            ready2tx_Flag = 0;
            mode = 1;
          }
        }
      }
      else{
        if(ready2tx_Flag==1){
          
          
          
          if(sampleCnt==1){
            *(imgbuff1+CAMERA_SIZE) = *(imgbuff1);
            img_extract(ImageBuf, imgbuff1+1,CAMERA_SIZE);
          }
          else{
            *(imgbuff+CAMERA_SIZE) = *(imgbuff);
            img_extract(ImageBuf, imgbuff+1,CAMERA_SIZE);
          }
          imagepro(ImageBuf);

//          gpio_set (PTE26, 1);
//            imagpro_2(ImagePointer);
//          gpio_set (PTE26, 0);
          
          if(nrf_tx_state() != NRF_TXING){
            CTRL_Handler();
          }
          
          ready2tx_Flag = 0;
          if(sendimgflag>0){
            mode = 0;
          }
          
        }
          
      }
      
      
      
    }
}











void all_init(void){
  
  int i=0;
  
    gpio_init (PTA4 , GPO,0); //avoid NMI
  
  
    NVIC_SetPriority(PORTC_PORTD_IRQn,0);         //�������ȼ�
 
//    NVIC_SetPriority(PORTA_IRQn,1);         //�������ȼ�
    NVIC_SetPriority(SysTick_IRQn,2);          //�������ȼ�
    NVIC_SetPriority(PIT_IRQn,3);
    
//    disable_irq(PORTA_IRQn);
    disable_irq(PORTC_PORTD_IRQn);
      
    
    adc_init(ADC_Z);            
    adc_init(ADC_G);            
    adc_init(ADC_DG);           
    
    
      
    tpm_pwm_init(MOTOR_TPM, MOTOR1_PWM,MOTOR_HZ,0);      //��ʼ�� ��� PWM
    tpm_pwm_init(MOTOR_TPM, MOTOR2_PWM,MOTOR_HZ,0);      //��ʼ�� ��� PWM
    tpm_pwm_init(MOTOR_TPM, MOTOR3_PWM,MOTOR_HZ,0);      //��ʼ�� ��� PWM
    tpm_pwm_init(MOTOR_TPM, MOTOR4_PWM,MOTOR_HZ,0);      //��ʼ�� ��� PWM
    
    gpio_init (MOTOR_L_EN , GPO,1);
    gpio_init (MOTOR_R_EN , GPO,1);
    
    //moto init complete
    
    tpm_pulse_init(TPM1,TPM_CLKIN0,TPM_PS_1); //R
    tpm_pulse_init(TPM2,TPM_CLKIN1,TPM_PS_1); //L
    
    //��������
    gpio_init (MOTOR_DIR_L , GPI,0);
    gpio_init (MOTOR_DIR_R , GPI,0);
    //��������
    
    led_init(LED_MAX);  
    
    
    
    while(ov7725_eagle_reg_init() == 0);
    
    dma_portx2buff_init (DMA_CH0, (void *)&PTD_B0_IN, imgbuff, PTA7, DMA_BYTE1, DMA_COUNT);
    
    port_init(PTA7, ALT1 | DMA_RISING );         //PCLK
    DMA_DIS(DMA_CH0);
    DMA_IRQ_DIS(DMA_CH0);
    
    
//    port_init(PTC16, ALT1 | IRQ_RISING ); //HREF
    port_init(PTC17, ALT1 | IRQ_FALLING );//VSYN
    
    DMA_EN(DMA_CH0);                        //ʹ��DMA Ӳ������

         /************************ ����ģ�� NRF ��ʼ��  ***********************/
    while(!nrf_init());   
    //�����жϸ�λ����
    set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);                //���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn
    
    nrf_msg_init();                                                     //����ģ����Ϣ��ʼ��
    
    
    set_vector_handler(SysTick_VECTORn ,SysTick_IRQHandler);
    systick_timing_ms(1); 
    
    enable_irq(PORTC_PORTD_IRQn);
    
    i = 20;
    while(i--)
    {
        nrf_msg_tx(COM_RETRAN,nrf_tx_buff);                              //���Ͷ�� �� �����ȥ��������� ���ն˵Ļ�������
    }
    
    set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);    //���� PIT0 ���жϸ�λ����Ϊ PIT0_IRQHandler
//    pit_init_ms(PIT0,100);               //pit ��ʱ�ж�(���ڰ�����ʱɨ��)
//    enable_irq (PIT_IRQn);
//    gpio_init (PTB7 , GPO,1);
//    OLED_i2c_init();
//    OLED_Init();
//    OLED_Fill(0xFF);
    
}


void PORTC_PORTD_IRQHandler(void){
    
    if(PORTC_ISFR & (1 << 17))           //VSYN
    {
        PORTC_ISFR  = (1 << 17);        //д1���жϱ�־λ
        
//        PORTA_ISFR = 1 <<  PT7;            //���PCLK��־λ
        
        if(sampleCnt ==0){
          dma_repeat(DMA_CH0, (void *)&PTD_B0_IN, imgbuff, ROW*DMA_COUNT);
         
          sampleCnt = 1;
        }
        else{
          dma_repeat(DMA_CH0, (void *)&PTD_B0_IN, imgbuff1, ROW*DMA_COUNT);
         
          sampleCnt = 0;
        }
 
        ready2tx_Flag = 1;
        
    }
    if(PORTC_ISFR & (1 << 18))           //NRF
    {
        PORTC_ISFR  = (1 << 18);        //д1���жϱ�־λ

        nrf_handler();

    }
  
}



