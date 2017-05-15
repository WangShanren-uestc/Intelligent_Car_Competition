#include "moto.h"

void SampleInputVoltage(int i){
  g_Ang_AD[i] = adc_once   (ADC_Z, ADC_16bit);
  g_Gyro_AD[i]= adc_once   (ADC_G, ADC_16bit);
  
}

void GetInputVoltageAverage(void){
  int i;
  float temp=0;
  VOLTAGE_GRAVITY = 0;
  VOLTAGE_GYRO = 0;
  
  for(i=0;i<INPUT_VOLTAGE_AVERAGE;i++){
    temp += g_Ang_AD[i];//-27944;
  }
  temp/= INPUT_VOLTAGE_AVERAGE;
  
  VOLTAGE_GRAVITY = temp;
  
  temp=0;
  for(i=0;i<INPUT_VOLTAGE_AVERAGE;i++){
    temp += g_Gyro_AD[i];
  }
  
  temp /= INPUT_VOLTAGE_AVERAGE;
  VOLTAGE_GYRO = temp;

  
}


void AngleCalculate(void) { 
  float fDeltaValue,angel; 
//  angel = VOLTAGE_GRAVITY * GRAVITY_ANGLE_RATIO_1;
//  if(angel>1)angel=1;
//  else if(angel<-1)angel=-1;
//  angel = acosf(angel);
//  g_fGravityAngle = angel * ANGLE_RATIO - 90; 
  g_fGravityAngle = -(VOLTAGE_GRAVITY - GRAVITY_OFFSET) * GRAVITY_ANGLE_RATIO;
  g_fGyroscopeAngleSpeed = (VOLTAGE_GYRO - GYROSCOPE_OFFSET) * GYROSCOPE_ANGLE_RATIO; 
  g_fCarAngle = g_fGyroscopeAngleIntegral; 
  fDeltaValue = (g_fGravityAngle - g_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT; 
  g_fGyroscopeAngleIntegral += (g_fGyroscopeAngleSpeed + fDeltaValue) / GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
  

}

void AngleControl(void) { 
  float fValue; 

   fValue = (CAR_ANGLE_SET - g_fCarAngle) * ANGLE_CONTROL_P + (CAR_ANGLE_SPEED_SET - g_fGyroscopeAngleSpeed) * ANGLE_CONTROL_D; 
  
  g_fAngleControlOut = fValue;
 

} 

void SetMotorVoltage(float fLeftVoltage, float fRightVoltage) {

  
  if(fLeftVoltage > 0)
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,(int)fLeftVoltage);
    tpm_pwm_duty(MOTOR_TPM, MOTOR2_PWM,0);
  }
  else
  {

    tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,0);
    tpm_pwm_duty(MOTOR_TPM, MOTOR2_PWM,(int)-fLeftVoltage);
  }
  if(fRightVoltage > 0)
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR3_PWM,(int)fRightVoltage);
    tpm_pwm_duty(MOTOR_TPM, MOTOR4_PWM,0);
  }
  else
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR3_PWM,0);
    tpm_pwm_duty(MOTOR_TPM, MOTOR4_PWM,(int)-fRightVoltage);

  }
  

  
}

void MotorSpeedOut(void) {
  float fLeftVal, fRightVal;
  fLeftVal = g_fLeftMotorOut;
  fRightVal = g_fRightMotorOut;
  if(g_fCarAngle>60|g_fCarAngle<-60|A_Ctrlflag<0){
    fLeftVal = 0;
    fRightVal= 0;
  }
  if(fLeftVal > 0) fLeftVal += MOTOR_OUT_DEAD_VAL;
  else if(fLeftVal < 0) fLeftVal -= MOTOR_OUT_DEAD_VAL;
  if(fRightVal > 0) fRightVal += MOTOR_OUT_DEAD_VAL;
  else if(fRightVal < 0) fRightVal -= MOTOR_OUT_DEAD_VAL;
  if(fLeftVal > MOTOR_OUT_MAX) fLeftVal = MOTOR_OUT_MAX;
  if(fLeftVal < MOTOR_OUT_MIN) fLeftVal = MOTOR_OUT_MIN;
  if(fRightVal > MOTOR_OUT_MAX) fRightVal = MOTOR_OUT_MAX;
  if(fRightVal < MOTOR_OUT_MIN) fRightVal = MOTOR_OUT_MIN;
  
  
  SetMotorVoltage(fLeftVal,fRightVal);
}

void MotorOutput(void) {
  float fLeft, fRight;
#if DIR_CTRL_1
  fLeft = g_fAngleControlOut - g_fSpeedControlOut + g_fDirectionControlOut_left;
  fRight = g_fAngleControlOut - g_fSpeedControlOut + g_fDirectionControlOut_right;
#else
  fLeft = g_fAngleControlOut - g_fSpeedControlOut + g_fDirectionControlOut;
  fRight = g_fAngleControlOut - g_fSpeedControlOut - g_fDirectionControlOut;
#endif
  g_fLeftMotorOut = fLeft;
  g_fRightMotorOut = fRight;
  MotorSpeedOut();
}

void SpeedControl(void) {
  float fDelta;
  float fP, fI;
  g_fCarSpeed = (g_nLeftMotorPulseSigma + g_nRightMotorPulseSigma) / 2;
  g_nLeftMotorPulseSigma = g_nRightMotorPulseSigma = 0;
  g_fCarSpeed *= CAR_SPEED_CONSTANT;
  
  
  DIR_CONTROL_P =  turn_value *g_fCarSpeed;
//  if(carflag<2){
//    fDelta = CAR_SPEED_SETfDelta  - g_fCarSpeed;
//  }
//  else if(Superborderjump==1){
//    fDelta = CAR_SPEED_SETfDelta - 4 - g_fCarSpeed;
//  }
//  else{
//    fDelta = CAR_SPEED_SETfDelta - super_forward_offset*0.15 - g_fCarSpeed;
//  }
//  fDelta = CAR_SPEED_SETfDelta - abs(g_fDIR) * 0.1 - g_fCarSpeed;
  fDelta = CAR_SPEED_SETfDelta  - g_fCarSpeed;
#if SPEED_METH
  fP = g_fCarSpeed * SPEED_CONTROL_P;
  
  fI = fDelta * SPEED_CONTROL_I;
  g_fSpeedControlIntegral += fI;
  
  g_fSpeedControlOutOld = g_fSpeedControlOutNew;
  g_fSpeedControlOutNew = -fP + g_fSpeedControlIntegral;
  
#else
  fP = fDelta * SPEED_CONTROL_P;

  fI = fDelta * SPEED_CONTROL_I;
  g_fSpeedControlIntegral += fI;

  
//  if(g_fSpeedControlIntegral>20)g_fSpeedControlIntegral=20;
//  else if(g_fSpeedControlIntegral<-20)g_fSpeedControlIntegral=-20;
  
  g_fSpeedControlOutOld = g_fSpeedControlOutNew;
  g_fSpeedControlOutNew = fP + g_fSpeedControlIntegral;
  
#endif
  

  
}
void SpeedControlOutput(void) {
  float fValue;
  fValue = g_fSpeedControlOutNew - g_fSpeedControlOutOld;
  g_fSpeedControlOut = fValue * (g_nSpeedControlPeriod + 1) / SPEED_CONTROL_PERIOD + g_fSpeedControlOutOld;
}

void DirectionControl(void) {
  float fValue,fPValue,fValue_left,fValue_right;
  float fDValue;
#if DIR_CTRL_1  
  g_fLeftspeed = g_nLeftVoltageSigma * DIR_SPEED_CONSTANT - g_fCarSpeed;
  g_fRightspeed= g_nRightVoltageSigma* DIR_SPEED_CONSTANT - g_fCarSpeed;
  

  
  g_nLeftVoltageSigma = 0;
  g_nRightVoltageSigma = 0;
  
  
  g_fDirectionControlOutOld_left = g_fDirectionControlOutNew_left;
  g_fDirectionControlOutOld_right = g_fDirectionControlOutNew_right;

//    fPValue = (g_fDIR) * DIR_CONTROL_P ;
    fDValue = DIR_CONTROL_D_VALUE-DIRECTION_OFFSET;

    
//    if(fDValue<0)fDValue*=DGYRO_ERROR;
    fDValue *= DIR_CONTROL_D;
    fValue_left  =-(g_fDIR + g_fLeftspeed)* DIR_CONTROL_P  -fDValue;
    fValue_right =(g_fDIR - g_fRightspeed)* DIR_CONTROL_P  +fDValue;
    g_fDirectionControlOutNew_left = fValue_left;
    g_fDirectionControlOutNew_right = fValue_right;
#else
    g_fDirectionControlOutOld = g_fDirectionControlOutNew;

    fValue = (-g_fDIR) * DIR_CONTROL_P ;
    fDValue = DIR_CONTROL_D_VALUE-DIRECTION_OFFSET;
//    if(fDValue<0)fDValue*=DGYRO_ERROR;
    fDValue *= DIR_CONTROL_D;
    fValue -= fDValue;
    g_fDirectionControlOutNew = fValue;
#endif
    
}

void DirectionControlOutput(void) {
  float fValue_left,fValue_right,fValue;
#if DIR_CTRL_1
  fValue_left = g_fDirectionControlOutNew_left - g_fDirectionControlOutOld_left;
  fValue_right = g_fDirectionControlOutNew_right - g_fDirectionControlOutOld_right;
  g_fDirectionControlOut_left = fValue_left * (g_nDirectionControlPeriod + 1) / DIRECTION_CONTROL_PERIOD + g_fDirectionControlOutOld_left; 
  g_fDirectionControlOut_right = fValue_right * (g_nDirectionControlPeriod + 1) / DIRECTION_CONTROL_PERIOD + g_fDirectionControlOutOld_right; 
#else
  fValue = g_fDirectionControlOutNew - g_fDirectionControlOutOld;
  g_fDirectionControlOut = fValue * (g_nDirectionControlPeriod + 1) / DIRECTION_CONTROL_PERIOD + g_fDirectionControlOutOld; 
#endif
}

void GetMotorPulse(void) {
  int left,right;
  left = tpm_pulse_get(TPM1);
  right = tpm_pulse_get(TPM2);
  
  if(gpio_get (MOTOR_DIR_L)){
  g_nLeftMotorPulseSigma += left;
  g_nLeftVoltageSigma += left;
  }
  else{
  g_nLeftMotorPulseSigma -= left;
  g_nLeftVoltageSigma -= left;
  }
  if(gpio_get (MOTOR_DIR_R)==0){
  g_nRightMotorPulseSigma+= right;
  g_nRightVoltageSigma += right;
  }
  else{
  g_nRightMotorPulseSigma-= right;
  g_nRightVoltageSigma -= right;
  }
  
  tpm_pulse_clean(TPM1);
  tpm_pulse_clean(TPM2);
  
}

void DirectionVoltageSigma(void){
  
  int i;
  
  if(g_nDirectionControlCount >= DIRECTION_CONTROL_COUNT) return;
  
  VOLTAGE_dGYRO = 0;
  
  for(i = 0; i < INPUT_VOLTAGE_AVERAGE; i ++)
  d_Gyro_AD[i]= adc_once   (ADC_DG, ADC_16bit);
  
  for(i=0;i<INPUT_VOLTAGE_AVERAGE;i++){
    VOLTAGE_dGYRO += d_Gyro_AD[i];
  }
  VOLTAGE_dGYRO /= (INPUT_VOLTAGE_AVERAGE);
  

  
  DIR_CONTROL_D_VALUE = VOLTAGE_dGYRO;
}


void gyroadj(void){
  
  float dGyro=0,Gyro=0;
  int i = 0,j = 0;
  
  led(LED0,LED_OFF);
  while(1){
    if(g_fCarAngle>15||g_fCarAngle<-15)break;
  }
  
  
  led(LED0,LED_ON);
  DELAY_MS(2000);
  led(LED0,LED_OFF);
  
  
  for(j=0;j<20;j++){
    VOLTAGE_dGYRO = 0;
  
    for(i = 0; i < INPUT_VOLTAGE_AVERAGE; i ++)
    d_Gyro_AD[i]= adc_once   (ADC_DG, ADC_16bit);
    
    for(i=0;i<INPUT_VOLTAGE_AVERAGE;i++){
      VOLTAGE_dGYRO += d_Gyro_AD[i];
    }
    VOLTAGE_dGYRO /= (INPUT_VOLTAGE_AVERAGE);
    
    dGyro+= VOLTAGE_dGYRO;
  }
  
  DIRECTION_OFFSET = dGyro/20;
  
  for(j=0;j<20;j++){
    VOLTAGE_GYRO = 0;
  
    for(i = 0; i < INPUT_VOLTAGE_AVERAGE; i ++)
    g_Gyro_AD[i]= adc_once   (ADC_G, ADC_16bit);
    
    for(i=0;i<INPUT_VOLTAGE_AVERAGE;i++){
      VOLTAGE_GYRO += g_Gyro_AD[i];
    }
    VOLTAGE_GYRO /= (INPUT_VOLTAGE_AVERAGE);
    
    Gyro+= VOLTAGE_GYRO;
  }
  
  GYROSCOPE_OFFSET = Gyro/20;
  
  while(1){
    DELAY();
    led_turn (LED0);
    if(g_fCarAngle<15&&g_fCarAngle>-15)break;
  }
  
  led(LED0,LED_OFF);
  A_Ctrlflag=1;
}

void CTRL_Handler()
{
   uint8 relen;
   extern double uSet_pre;

      relen = nrf_rx(nrf_rx_buff,DATA_PACKET);               //等待接收一个数据包，数据存储在buff里
        
            if(relen != 0)
            {
              switch(*command){
                      case '`':
                        uSet = 0;
                        //S_Ctrlflag=-S_Ctrlflag;
                        break;
                      case '1':
                        uSet =0.0;
                        break;
                      case '2':
                        uSet =uSet_pre;

                        break;   
                      case 's':
//                        sendimgflag=-sendimgflag;
                        break; 
                      case 'a':
                        stop_flag = 1;
//                        A_Ctrlflag=-A_Ctrlflag;
                        break; 
                      case 'd':
                        sendimgflag++;
                        if(sendimgflag>1)sendimgflag=0;
                        break;   
                      case '-':
                        
                        break; 
                      case '+':
                        
                        break; 
              }
              
              
            }
    
  
}

//void uart0_test_handler(void)
//{
//    UARTn_e uratn = UART0;
//    
//    //led_turn (LED0);
//
//    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   //接收数据寄存器满
//    {
//        //用户需要处理接收数据
//      
//      led_turn (LED1);
//      
//      switch(UART0_D){
//        
//      case 'c':
//        if(comm>=3)comm=0;
//        else comm++;
//      break; 
//      
//      
//      case 'v':
//        renflag=0;
//        RenRoadFLAG=0;
//      break; 
//      
//      case '[':
//        GRAVITY_OFFSET+=50;
//        break;
//      case ']':
//        GRAVITY_OFFSET-=50;
//        break;
//
//      case '`':
//        CAR_SPEED_SETfDelta=0;
//        g_fDIR = 0;
//        g_fSpeedControlIntegral=0;
//        break;
//      case '1':
//        CAR_SPEED_SETfDelta+=1;
//        break;
//      case '2':
//        CAR_SPEED_SETfDelta-=1;
//        break;   
//      case 's':
//        S_Ctrlflag=-S_Ctrlflag;
//        break; 
//      case 'a':
//        A_Ctrlflag=-A_Ctrlflag;
//        break; 
//      case 'd':
//        D_Ctrlflag=-D_Ctrlflag;
//        break;   
//        
//      case 'l':
//        g_fDIR+=0.2;
//        break;  
//      case 'r':
//        g_fDIR-=0.2;
//        break;  
//         
//        
////      case 'Y':
////        ANGLE_CONTROL_P+=0.3;
////        break;
////      case 'y':
////        ANGLE_CONTROL_P-=0.3;
////        break;
////      case 'U':
////        ANGLE_CONTROL_D+=0.005;
////        break;
////      case 'u':
////        ANGLE_CONTROL_D-=0.005;
////        break;
//      }
//
//    }
//
//    if(UART_S1_REG(UARTN[uratn]) & UART_S1_TDRE_MASK )  //发送数据寄存器空
//    {
//        //用户需要处理发送数据
//
//    }
//}
int stop_pre = 0;
extern int stop_flag,pre_stop_flag,OLED_stop_flag;
void PIT_IRQHandler(void){
  
  
  if(PIT_TFLG(PIT0) == 1 )        //判断是否 PIT0 进入中断
    {
      if(pre_stop_flag){
        if(stop_pre){
          stop_flag = 1;
          if(OLED_stop_flag==0){
                  OLED_ShowStr(0,0,"Fengzhuan",1);
                }
                OLED_stop_flag = 1;
        }
        stop_pre = 1;
      }
      else{
        stop_pre = 0;
      }
      
      
      PIT_Flag_Clear(PIT0);       //清中断标志位
    }
  
  if(PIT_TFLG(PIT1) == 1 )        //判断是否 PIT1 进入中断
    {
      
      key_IRQHandler(); 
      
      
      PIT_Flag_Clear(PIT1);       //清中断标志位
    }
}

void SysTick_IRQHandler(void)
{
    int i;
    
//    gpio_set (PTE26 , 1);
    
    g_nSpeedControlPeriod ++; 
    if(S_Ctrlflag>0){
      SpeedControlOutput(); 
    }
    else{
      g_fSpeedControlOut = 0;
    }
    
    g_nDirectionControlPeriod ++; 
    if(D_Ctrlflag>0){
      DirectionControlOutput(); 
    }
    else{
      g_fDirectionControlOut_left = 0;
      g_fDirectionControlOut_right = 0;
      g_nLeftVoltageSigma = 0;
      g_nRightVoltageSigma = 0;
    }
    
    
    
    if(g_n1MSEventCount >= CONTROL_PERIOD) 
      { 
        g_n1MSEventCount = 0; 
        
          GetMotorPulse(); //读取两个电极脉冲计数值 
        
            tpm_pulse_clean(TPM1);
            tpm_pulse_clean(TPM2);

      } 
    else if(g_n1MSEventCount == 1) 
      { 
        for(i = 0; i < INPUT_VOLTAGE_AVERAGE; i ++) 
        SampleInputVoltage(i); 
      } 
    else if(g_n1MSEventCount == 2) 
      { 
        GetInputVoltageAverage(); 
        AngleCalculate(); 
        AngleControl(); 
        
          MotorOutput();
        
      } 
    else if(g_n1MSEventCount == 3) 
    { 
      g_nSpeedControlCount ++; 
      if(g_nSpeedControlCount >= SPEED_CONTROL_COUNT) 
        { 
          
            SpeedControl(); 
          
          g_nSpeedControlCount = 0; 
          g_nSpeedControlPeriod = 0; 
        } 
    } 
    else if(g_n1MSEventCount == 4) 
    { 
      g_nDirectionControlCount ++; 
      DirectionVoltageSigma(); 
      if(g_nDirectionControlCount >= DIRECTION_CONTROL_COUNT1) 
      { 
        DirectionControl(); 
        g_nDirectionControlCount = 0; 
        g_nDirectionControlPeriod = 0; 
      }
    }
    g_n1MSEventCount++;
    
    
//    gpio_set (PTE26 , 0);

}