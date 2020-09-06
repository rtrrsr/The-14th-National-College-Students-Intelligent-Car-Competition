#ifndef  __SYSTEMINIT_H_
#define  __SYSTEMINIT_H_

#include "headfile.h"

//���뿪�ؽӿڶ���
#define Key1 gpio_get(D11)
#define Key2 gpio_get(D12)
#define Key3 gpio_get(D13)
#define Key4 gpio_get(D14)
#define Key5 gpio_get(D15)
#define Key6 gpio_get(E0)
#define Key7 gpio_get(E1)
#define Key8 gpio_get(E2)
//����ӿ�
#define MOTOR_FTM   ftm0                //FTM0ģ��
#define MOTOR1_PWM  ftm_ch0		//PTC1     ͨ��0
#define MOTOR2_PWM  ftm_ch1		//PTC2     ͨ��1
#define MOTOR3_PWM  ftm_ch2		//PTC3     ͨ��2
#define MOTOR4_PWM  ftm_ch3		//PTC4     ͨ��3
#define MOTOR5_PWM  ftm_ch4             //PTD4     ͨ��4
#define MOTOR6_PWM  ftm_ch5             //PTD5     ͨ��5
#define MOTOR7_PWM  ftm_ch6             //PTD6     ͨ��6
#define MOTOR8_PWM  ftm_ch7             //PTD7     ͨ��7
#define MOTOR_HZ    (10*1000)           //���Ƶ�ʣ����ȣ�

//������������������
extern void SystemInit(void);
extern void UltrasonicInit();
extern void Switch();
extern uint16 speed0;
extern uint16 speed1;
extern uint16 speed2;
extern uint16 speed3;
extern uint16 speed4;
extern uint16 speed5;
extern uint16 speed6;

extern uint16 Infra_redL;
extern uint16 Infra_redR;
extern uint16 Infra_redM;


#endif
