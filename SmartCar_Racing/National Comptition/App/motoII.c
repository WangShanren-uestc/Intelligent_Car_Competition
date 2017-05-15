#include "motoII.h"
#include <math.h>

double GyroOffset=33500;
double GyroAngleSpeed;
double GyroAngleSpeed_pi;

double dGyroOffset = 30650;
double dGyroAngleSpeed;
double dGyroAngleSpeed_pi;

double CarAngle = 0,CarAngleQ=48.4;
double Kw,Kb,Ku,Kd,K;

double Kv,Ka;

double new_w=0,old_w=0;
double b=0;
double uSet = 0,uSetFollow = 0,uSet_pre=0;

double P_Direction,D_Direction,g_uDirectionControl; 
double Dir_P_val,Dir_D_val;



#if DOUBLE_CTRL
double NowSpeed_L=0,LastSpeed_L=0,aSpeed_L=0;
double NowSpeed_R=0,LastSpeed_R=0,aSpeed_R=0;

double g_uStandControl_L=0,g_uStandControl_R=0;

double NowCoderNumSum_L,LastCoderNumSum_L,NowCoderNumSum_R,LastCoderNumSum_R;
int DecoderNum_L[DECODER_NUM_LEN],DecoderNum_R[DECODER_NUM_LEN];

#else
double NowSpeed=0,LastSpeed=0,aSpeed=0;

double g_uStandControl=0;

double NowCoderNumSum,LastCoderNumSum;
float DecoderNum[DECODER_NUM_LEN];
#endif

double dir_ctrl_lim = 0,dir_ctrl_lim_set = 0;
double Ren_Turn_Inter = 0;

int qipao_time_cnt = 0,qipao_time_add_flag = 1,start_time_cnt = 0,start_time_add_flag = 1,stop_time_cnt = 0;

uint16 save_ctrl_data_cnt = 0;

float nErrors[DIRECTION_ERRORS_NUMS] = {0};
int dir_refresh_flag = 0;
float dError_new = 0,dError_old = 0;
float p_new = 0,p_old = 0;
float p_delta = 0,d_delta = 0;
float dir_ctrl_times = 1;

uint16 Acc_x=0,Acc_z=0;

int DD_Ratio = 1;

void Init_SetArguments(void)
{
	Kw = 20;//52;//3.25;//53.0; 
	Kb = 1.0;//3.25;//2.6;
	Ku = 14;
	
	Kd = 0.0;
	
	Kv = 4;//16.1;//9.0;
	Ka = 5;//18.0;//
        
        uSet_pre = 3.1;
        uSet = 0;
        uSetFollow = 0;
        
        P_Direction = 0.05;
        D_Direction = 0.178;
	
        dir_ctrl_lim_set = 1.6;
        dir_ctrl_lim = 1.6;
}

double fzx;
float x,z,xz;
void Ang_Calc(void){
    uint32 Gyro,dGyro;
	double Accelerometer_AngleSpeed,Acc_Angle;
	extern int turn_flag,Ren_Clean_Flag,herringbone_flag;
	
        
	Gyro= adc_once(ADC_G, ADC_16bit);
        dGyro=adc_once(ADC_DG, ADC_16bit);
        
        Gyro+= adc_once(ADC_G, ADC_16bit);
        dGyro+=adc_once(ADC_DG, ADC_16bit);
        Gyro+= adc_once(ADC_G, ADC_16bit);
        dGyro+=adc_once(ADC_DG, ADC_16bit);
        Gyro+= adc_once(ADC_G, ADC_16bit);
        dGyro+=adc_once(ADC_DG, ADC_16bit);
        
        Gyro = Gyro>>2;
        dGyro = dGyro>>2;
        
        dGyroAngleSpeed = -(dGyro - dGyroOffset) * GYRO_RATIO;
	GyroAngleSpeed = -(Gyro - GyroOffset) * GYRO_RATIO - DG_FIX*dGyroAngleSpeed; //角速度；向前加速为正；单位：°/s；
        
	GyroAngleSpeed_pi = GyroAngleSpeed * PI / 180.0;  //角速度；单位：rad/s；
        dGyroOffset = dGyroOffset * (1 - dt/Tw) + dGyro * dt/Tw;
	GyroOffset = GyroOffset * (1 - dt/Tw) + Gyro * dt/Tw; //对陀螺仪静态电压进行低通滤波
        
        Acc_x = adc_once(ADC_X, ADC_16bit);
		Acc_z = adc_once(ADC_Z, ADC_16bit);

		x = (float)((Acc_x - ACCX_OFFSET)>>4);
		z = (float)((ACCZ_OFFSET - Acc_z)>>4);

		xz = z*z + x*x + 0.001;
	//	fzx = InvSqrt(xz) * x;
                fzx = z/sqrt(xz);
        Acc_Angle = 13.3 * fzx * fzx + 57.32 * fzx - 1.056;
		
		Accelerometer_AngleSpeed = (Acc_Angle - CarAngleQ)/TIME_Z;
        CarAngleQ += (-GyroAngleSpeed*0.88 + Accelerometer_AngleSpeed)*dt;
	
          CarAngle = -(CarAngleQ -53);
//人字转向积分
        if(turn_flag){
          Ren_Turn_Inter+=dGyroAngleSpeed*dt;
          if(Ren_Turn_Inter>40||Ren_Turn_Inter<-40){
            Ren_Clean_Flag = 1;
          }
        }
        else{
          Ren_Turn_Inter = 0;
        }
//人字转向积分

          //OutData[2]=CarAngle*100;
}

void CalcAngleControl(void)
{	
	
	
	new_w = GyroAngleSpeed_pi;
	b = (new_w - old_w)/dt;//b为角加速度，单位：rad/(s^2)；
	old_w = new_w;
//	uSet = 2;//期望的控制电压，暂时取直道速度对应的控制电压uStr;

	//g_uStandControl += (Kw*new_w - K*D_Direction*fError + Kb*b + Ku*(g_uStandControl - uSet))*dt;
//	g_uStandControl += (Kw*new_w + Kb*b + Ku*(g_uStandControl - uSet))*dt;
	//增量控制，此处的new_w和b单位均取弧度制

//	if(ObstacleCntTime > 0)
//	{
//		g_uStandControl += (Kw*new_w + Kb*b + Ku*(g_uStandControl - uSetFollow))*dt;
//		ObstacleCntTime--;
//	}
//	else
//	{
//		g_uStandControl += (Kw*new_w + Kb*b + Kv*(NowSpeed - uSet) + Ka*aSpeed)*dt;
//		uSetFollow = uSetFollow*0.98 + g_uStandControl*0.02;
//	}
#if CTRL_METH
        
#if DOUBLE_CTRL	
	g_uStandControl_L += dt*(Kw*new_w + Kb*b + Ka*aSpeed_L + Kv*(NowSpeed_L - uSet - g_uDirectionControl));
        g_uStandControl_R += dt*(Kw*new_w + Kb*b + Ka*aSpeed_R + Kv*(NowSpeed_R - uSet + g_uDirectionControl));
    

        //OutData[1]=NowSpeed_R*100;
#else
        g_uStandControl += (Kw*new_w + Kb*b + Kv*(NowSpeed - uSet) + Ka*aSpeed)*dt;
        

#endif

#else
        g_uStandControl += (Kw*new_w + Kb*b + Ku*(g_uStandControl - uSetFollow))*dt;
#endif
        
        //OutData[1]=uSet*100;
       // OutData[2]=aSpeed*100;
       // OutData[3]=new_w*100;
        
}

void GetEncoderPluse(int* LSpeed,int* RSpeed)
{
	if(gpio_get (MOTOR_DIR_L)){
	  *LSpeed= (int)tpm_pulse_get(TPM1);
	}
	else{
	  *LSpeed= -(int)tpm_pulse_get(TPM1);
	}
	tpm_pulse_clean(TPM1);
        
	if(gpio_get (MOTOR_DIR_R)==0){
          *RSpeed= (int)tpm_pulse_get(TPM2);
	}
	else{
          *RSpeed= -(int)tpm_pulse_get(TPM2);
	}
	tpm_pulse_clean(TPM2);
	
}

/*
	计算速度控制参数
*/
void CalcSpeedControl(void)
{
	int	LSpeed,RSpeed;

	int i;

	
	GetEncoderPluse(&LSpeed,&RSpeed);
#if DOUBLE_CTRL
	//存放数据
	for(i=DECODER_NUM_LEN-1; i>0; i--)
	{
		DecoderNum_L[i] = DecoderNum_L[i-1];
	}	
	DecoderNum_L[0] = LSpeed*2;
        
        for(i=DECODER_NUM_LEN-1; i>0; i--)
	{
		DecoderNum_R[i] = DecoderNum_R[i-1];
	}	
	DecoderNum_R[0] = RSpeed*2;
	
	//计算速度
	NowCoderNumSum_L += (DecoderNum_L[0] - DecoderNum_L[SPEED_DATALEN]);
	LastCoderNumSum_L += (DecoderNum_L[SPEED_DATALEN] - DecoderNum_L[SPEED_DATALEN*2]);
	NowSpeed_L = NowCoderNumSum_L*SPEED_RATIO;
	LastSpeed_L = LastCoderNumSum_L*SPEED_RATIO;
	
	//计算加速度
	aSpeed_L = (NowSpeed_L - LastSpeed_L)/(SPEED_DATALEN * dt);
        
        NowCoderNumSum_R += (DecoderNum_R[0] - DecoderNum_R[SPEED_DATALEN]);
	LastCoderNumSum_R += (DecoderNum_R[SPEED_DATALEN] - DecoderNum_R[SPEED_DATALEN*2]);
	NowSpeed_R = NowCoderNumSum_R*SPEED_RATIO;
	LastSpeed_R = LastCoderNumSum_R*SPEED_RATIO;
	
	//计算加速度
	aSpeed_R = (NowSpeed_R - LastSpeed_R)/(SPEED_DATALEN * dt);
#else
        //存放数据
	for(i=DECODER_NUM_LEN-1; i>0; i--)
	{
		DecoderNum[i] = DecoderNum[i-1];
	}	
	DecoderNum[0] = LSpeed + RSpeed;
	
	//计算速度
	NowCoderNumSum += (DecoderNum[0] - DecoderNum[SPEED_DATALEN]);
	LastCoderNumSum += (DecoderNum[SPEED_DATALEN] - DecoderNum[SPEED_DATALEN*2]);
	NowSpeed = NowCoderNumSum*SPEED_RATIO;
	LastSpeed = LastCoderNumSum*SPEED_RATIO;
	
	//计算加速度
	aSpeed = (NowSpeed - LastSpeed)/(SPEED_DATALEN * dt);
        if(aSpeed>1.8)aSpeed = 1.8;
        else if(aSpeed<-1.8)aSpeed = -1.8;
#endif

}

void SetMotorVoltage_II(float fLeftVoltage, float fRightVoltage) {
  
  if(fLeftVoltage > 0)
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,fLeftVoltage);
    tpm_pwm_duty(MOTOR_TPM, MOTOR2_PWM,0);
  }
  else
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,0);
    tpm_pwm_duty(MOTOR_TPM, MOTOR2_PWM,-fLeftVoltage);
  }
  if(fRightVoltage > 0)
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR3_PWM,fRightVoltage);
    tpm_pwm_duty(MOTOR_TPM, MOTOR4_PWM,0);
  }
  else
  {
    tpm_pwm_duty(MOTOR_TPM, MOTOR3_PWM,0);
    tpm_pwm_duty(MOTOR_TPM, MOTOR4_PWM,-fRightVoltage);
  }
}

int stop_flag = 0,pre_stop_flag = 0,stop_flag_image = 0;
#define STOP_LIM 90

void CalcSumControl(void) 
{
	double LMotor_SumControl;
	double RMotor_SumControl;
#if DOUBLE_CTRL
        LMotor_SumControl = g_uStandControl_L - g_uDirectionControl;
        RMotor_SumControl = g_uStandControl_R + g_uDirectionControl;
#else
        LMotor_SumControl = g_uStandControl - g_uDirectionControl;
        RMotor_SumControl = g_uStandControl + g_uDirectionControl;
#endif	
        
	LMotor_SumControl *=100.0/MOTOR_OUT_MAX_II;
	RMotor_SumControl *=100.0/MOTOR_OUT_MAX_II;
        
      // moto_fix(&LMotor_SumControl,&RMotor_SumControl);
        
        	//左轮电机控制参数的饱和处理
	if(LMotor_SumControl > PWM_MAX )
	{
		LMotor_SumControl = PWM_MAX;
	}
	else if(LMotor_SumControl < PWM_MIN)
	{
		LMotor_SumControl = PWM_MIN;
	}
	
	//右轮电机控制参数的饱和处理
	if(RMotor_SumControl > PWM_MAX)
	{
		RMotor_SumControl = PWM_MAX;
	}
	else if(RMotor_SumControl < PWM_MIN)
	{
		RMotor_SumControl = PWM_MIN;
	}
        
        if(LMotor_SumControl>STOP_LIM||LMotor_SumControl<-STOP_LIM||RMotor_SumControl>STOP_LIM||RMotor_SumControl<-STOP_LIM){
          pre_stop_flag = 1;
        }
        else{
          pre_stop_flag = 0;
        }
        if(stop_flag){
          SetMotorVoltage_II(0,0);
        }
        else {
          SetMotorVoltage_II(-LMotor_SumControl,-RMotor_SumControl);
        }
        
}

void Gyro_Adj(void){
  
  double sampleGyro=0,Gyro=0;
  int i = 0,j = 0;
  uint16 Gyro_AD[AD_AVERAGE]={0};
  
  
  led(LED0,LED_ON);
  DELAY_MS(2000);
  led(LED0,LED_OFF);
  //GYRO
  for(j=0;j<2000;j++){
    sampleGyro = 0;
  
    for(i = 0; i < AD_AVERAGE; i ++){
      Gyro_AD[i]= adc_once   (ADC_G, ADC_16bit);
    }
    
    for(i=0;i<AD_AVERAGE;i++){
      sampleGyro += Gyro_AD[i];
    }
    sampleGyro /= (AD_AVERAGE);
    
    Gyro+= sampleGyro;
  }
  
  GyroOffset = Gyro/2000;
  //DGYRO
  Gyro = 0;
  for(j=0;j<2000;j++){
    sampleGyro = 0;
  
    for(i = 0; i < AD_AVERAGE; i ++){
      Gyro_AD[i]= adc_once   (ADC_DG, ADC_16bit);
    }
    
    for(i=0;i<AD_AVERAGE;i++){
      sampleGyro += Gyro_AD[i];
    }
    sampleGyro /= (AD_AVERAGE);
    
    Gyro+= sampleGyro;
  }
  
  dGyroOffset = Gyro/2000;
  
  
  led(LED0,LED_ON);
  
}



void DIR_fifo(void){
  int i = 0;
  extern float offset_line3;
  extern float line3_fifo[10];
  extern int line1lost_memo[2];
  extern int line2lost_memo[2];
  extern int line3lost_memo[2];
  extern int typememo[2];
  //更新数组
	for(i=DIRECTION_ERRORS_NUMS-1; i>0; i--)
	{          
            nErrors[i] = nErrors[i-1];
	}
        for(i=10;i>0;i--)
        {
           line3_fifo[i] = line3_fifo[i-1];
        }
        
        if(line3lost_memo[1]==0 && line3lost_memo[0]==1)
        {             
            line3_fifo[0] = offset_line3;
            line3_fifo[1] = offset_line3;
            line3_fifo[2] = offset_line3;
            line3_fifo[3] = offset_line3;
        }
        else
        {
            line3_fifo[0] = offset_line3;
        }
        
        if((line1lost_memo[1]==0 && line1lost_memo[0]==1) 
            || (line2lost_memo[1]==0 && line2lost_memo[0]==1)
            || (typememo[0]==1 && typememo[1]==0))
        {
	    //nErrors[0] = g_fDIR;
            //nErrors[1] = g_fDIR;
            //nErrors[2] = g_fDIR;
            //nErrors[3] = g_fDIR;
        }
        else
        {
            nErrors[0] = g_fDIR;
        }
        if((nErrors[1]>nErrors[0] && nErrors[1]>nErrors[2]) 
               || (nErrors[1]<nErrors[0] && nErrors[1]<nErrors[2]))
        {
          nErrors[1] = (nErrors[0] + nErrors[2])/2;
        }  
        
        dir_refresh_flag =1;
}

void CalcDirectionControl(void)
{
	
  //double fDelta;
	extern int left3lost_flag ;
        extern int right3lost_flag;
        extern uint8 *ImagePointer;
        extern int block_flag;
        
//        if(left3lost_flag==0&&right3lost_flag==0){
//          dError = line3_fifo[0]-line3_fifo[2];
//          dError*=0.3;
//
//          g_uDirectionControl = (P_Direction * line3_fifo[0]*0.5+DD_Ratio*D_Direction*dError);	
//          Dir_P_val = P_Direction * line3_fifo[0];
//          Dir_D_val = DD_Ratio*D_Direction*dError;
//          draw_renzi(ImagePointer);
//        }

        if(dir_refresh_flag){
          dir_refresh_flag = 0;
          p_old = p_new;
          dError_old = dError_new;
          
          p_new = nErrors[0];
          dError_new = nErrors[0]-nErrors[2];
          
          p_delta = (p_new - p_old)/4;
          d_delta = (dError_new - dError_old)/4;
          
          dir_ctrl_times = 1;
        }
          

          
          Dir_P_val = P_Direction * (p_old + p_delta * dir_ctrl_times);
          Dir_D_val = DD_Ratio * D_Direction * (dError_old + d_delta * dir_ctrl_times);
          
          g_uDirectionControl = Dir_P_val + Dir_D_val;
	
          if(herringbone_flag || block_flag){
            dir_ctrl_lim = 4;
          }
          else{
            dir_ctrl_lim = dir_ctrl_lim_set;
          }
          
        if(g_uDirectionControl>dir_ctrl_lim)g_uDirectionControl=dir_ctrl_lim;
        else if(g_uDirectionControl<-dir_ctrl_lim)g_uDirectionControl=-dir_ctrl_lim;
        
        dir_ctrl_times++;
        if(dir_ctrl_times>4)dir_ctrl_times = 4;
        
}

void Timing_Func(void){
	extern int startingline_flag;

	    if(qipao_time_add_flag==1){
          qipao_time_cnt++;
        }
        
        if(qipao_time_cnt>2500){
          startingline_flag = 1;
          qipao_time_add_flag = 0;
          qipao_time_cnt = 0;
        }
        if(start_time_add_flag==1){
          start_time_cnt++;
        }
        
        if(start_time_cnt>1000){
          uSet = uSet_pre;
          start_time_add_flag = 0;
          start_time_cnt = 0;
        }
          
        if(stop_flag_image==1){
          stop_time_cnt++;
        }
        if(stop_time_cnt>20){
          stop_flag = 1;
          stop_time_cnt=0;
        }
}


void Save_Ctrl_Data(void){
#define DATA_LEN 2*7
extern uint8 *data_pointer,*data_pointer1;
extern int frameCnt,now_data,linewidth,ren_turn_limit;
extern float g_fDIR;
  if(now_data==0){
        save_frame_cnt(frameCnt,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+0);
        save_double2int16(g_uStandControl*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+2);
        save_double2int16(g_fDIR,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+4);
//	save_double2int16(b*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+4);
	save_double2int16(NowSpeed*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+6);
//	save_double2int16(aSpeed*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+8);        
        save_double2int16(g_uDirectionControl*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+8);
//        save_frame_cnt(save_ctrl_data_cnt,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+2);
//        save_frame_cnt((int16)linewidth,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+2);

//        save_double2int16(CarAngle*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+4);
//        save_frame_cnt((int16)ren_turn_limit,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+6);

//        save_double2int16(g_fDIR,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+8);
//	save_uint16(Acc_x,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+10);
//	save_uint16(Acc_z,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+12);
        
	save_double2int16(Dir_P_val*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+10);
	save_double2int16(Dir_D_val*100,data_pointer+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+12);

	save_ctrl_data_cnt++;
  }
  else{
        save_frame_cnt(frameCnt,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+0);
        save_double2int16(g_uStandControl*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+2);
        save_double2int16(g_fDIR,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+4);
//	save_double2int16(b*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+4);
	save_double2int16(NowSpeed*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+6);
//	save_double2int16(aSpeed*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+8);        
        save_double2int16(g_uDirectionControl*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+8);
//        save_frame_cnt(save_ctrl_data_cnt,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+2);
//        save_frame_cnt((int16)linewidth,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+2);

//        save_double2int16(CarAngle*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+4);
//        save_frame_cnt((int16)ren_turn_limit,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+6);

//        save_double2int16(g_fDIR,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+8);
//	save_uint16(Acc_x,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+10);
//	save_uint16(Acc_z,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+12);
        
	save_double2int16(Dir_P_val*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+10);
	save_double2int16(Dir_D_val*100,data_pointer1+save_ctrl_data_cnt*DATA_LEN+FRAME_MARK_SIZE+12);

	save_ctrl_data_cnt++;
  }
  
        
}

void SysTick_IRQHandlerII(void){

  
  
  Ang_Calc();
  CalcSpeedControl();
  CalcAngleControl();
  CalcDirectionControl();
	CalcSumControl();
        
   Timing_Func();     
   if(NRF_on){
     Save_Ctrl_Data(); 
   }
       
        
}
