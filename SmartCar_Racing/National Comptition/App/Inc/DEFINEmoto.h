#ifndef __DEFINEMOTO_H__
#define __DEFINEMOTO_H__

#define MOTOR_TPM   TPM0

#define MOTOR1_PWM  TPM_CH1  //IN L2
#define MOTOR2_PWM  TPM_CH5  //IN L1 

#define MOTOR3_PWM  TPM_CH4  //IN R1
#define MOTOR4_PWM  TPM_CH2  //IN R2

#define MOTOR1_PWM_IO  TPM0_CH0
#define MOTOR2_PWM_IO  TPM0_CH1
#define MOTOR3_PWM_IO  TPM0_CH2
#define MOTOR4_PWM_IO  TPM0_CH3

#define MOTOR_L_EN PTE24
#define MOTOR_R_EN PTE30

#define MOTOR_DIR_L PTC11
#define MOTOR_DIR_R PTC10


#if 0
#define MOTOR_HZ    (50)
#else
#define MOTOR_HZ    (10*1000)
#endif

#define COM_SIZE_1 1

#endif  