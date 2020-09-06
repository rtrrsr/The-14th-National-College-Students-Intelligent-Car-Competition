#include "headfile.h"

void SystemInit()  
{
  get_clk();                   //�ϵ���������һ�������������ȡ����ģ���Ƶ����Ϣ�����ں������ģ��Ĳ�������
  gpio_init(A25,GPO,0);        //A25�ӿڶ��嵫��δʹ��
                              
  //���뿪�س�ʼ��
  gpio_init(D11, GPI,0);       //����D11�ӿ�ΪIO�ӿڣ���0
  gpio_init(D12, GPI,0);       //ͬ��
  gpio_init(D13, GPI,0);
  gpio_init(D14, GPI,0);             
  gpio_init(D15, GPI,0);
  gpio_init(E0, GPI,0);
  gpio_init(E1, GPI,0);
  gpio_init(E2, GPI,0);
  port_init_NoAlt(D11,PULLUP);//��D11�ӿ�����
  port_init_NoAlt(D12,PULLUP);//ͬ��
  port_init_NoAlt(D13,PULLUP);
  port_init_NoAlt(D14,PULLUP);
  port_init_NoAlt(D15,PULLUP);
  port_init_NoAlt(E0,PULLUP);
  port_init_NoAlt(E1,PULLUP);
  port_init_NoAlt(E2,PULLUP);  
                          
  Switch();                   //ͨ�����뿪��2�ŵ���8�ŵ�ѡ��7���ٶȵ�֮һ����ʵ�ֳ��ӵ��ٶȿ��ƺ��˶�������ƣ�Switch()�����SystemDeal.c�·�
  
  ftm_pwm_init(ftm1,ftm_ch0,50,830);//�����ʼ������һ��C��������Ҫ�������Կ��Ƴ����˶�����h�ű공����˾���������޸ģ�
  
 //�����ʼ������ʼ�����Ƶ��Ϊ0
  ftm_pwm_init(MOTOR_FTM,MOTOR1_PWM,MOTOR_HZ,0);   //ǰ����
  ftm_pwm_init(MOTOR_FTM,MOTOR2_PWM,MOTOR_HZ,0);
  ftm_pwm_init(MOTOR_FTM,MOTOR3_PWM,MOTOR_HZ,0);   //ǰ����
  ftm_pwm_init(MOTOR_FTM,MOTOR4_PWM,MOTOR_HZ,0);
  
  ftm_pwm_init(MOTOR_FTM,MOTOR5_PWM,MOTOR_HZ,0);   //������
  ftm_pwm_init(MOTOR_FTM,MOTOR6_PWM,MOTOR_HZ,0);
  ftm_pwm_init(MOTOR_FTM,MOTOR7_PWM,MOTOR_HZ,0);   //������
  ftm_pwm_init(MOTOR_FTM,MOTOR8_PWM,MOTOR_HZ,0);
  
                                                      //��������ʼ������h�ű공���վ�����ʹ�ñ��������бջ����٣��������������㷨˵�����ٶȿ���ƪ����
//  ftm_quad_init(ftm2);                              //��������
//  port_init_NoAlt(FTM2_QDPHA_PIN,PULLUP);
//  lptmr_pulse_init(lpt0_alt1,0xFFFF,LPT_Rising);    //��������
  
 
  uart_init (uart2, 115200);                          //��ʼ�������������ͨ�ţ������ڵ���ʱ�����ô���ͨ�ţ�ͨ��TFT��ʾ����ͼ�����Ե��Գ���������
  
  lcd_init();            //СҺ����ʼ��                    
 
  camera_init();         //����ͷ��ʼ��
   
  UltrasonicInit();      //��������ʼ����������ʹ�ó��������������ϣ����Դ���䣩
 
  led_init(LED_MAX);     //���İ��LED�Ƴ�ʼ��  
  
  pit_init_ms(pit0,5);   //pit��ʱ����0�ţ���ʼ�����������������趨Ϊ5ms �������������޸�
  
  enable_irq (PIT0_IRQn);//��0�Ŷ�ʱ��PIT0�ж�
  
  gpio_init(E10,GPI,0);  //����Թܳ�ʼ��
  gpio_init(E8,GPI,0); 
  gpio_init(E9,GPI,0); 
  
  set_irq_priority(DMA0_IRQn,2);//����ͷͼ��DMA�����жϳ�ʼ������
  set_irq_priority(PIT0_IRQn,3);//�ٶȿ��ƺ�ͼ��������жϳ�ʼ������
 
  
}

void UltrasonicInit()      //�������ź�adcģ��ɼ�������������ʹ�ó��������������ϣ����Դ˶���䣩
{
  adc_init(ADC0_SE8);//B0
  adc_init(ADC0_SE9);//B1
  adc_init(ADC0_SE12);//B2
  adc_init(ADC0_SE13);//B3
  adc_init(ADC1_SE10);//B4
  adc_init(ADC1_SE11);//B5
  adc_init(ADC1_SE12);//B6
  adc_init(ADC1_SE13);//B7
}


uint8 status2=1;          //���岦�뿪��2�ŵ���Ӧ�ı���status2����ֵΪ1
uint8 status3=1;          //ͬ��
uint8 status4=1;
uint8 status5=1; 
uint8 status6=1;
uint8 status7=1; 
uint8 status8=1; 
uint16 speed0=0;          //����ȫ���ٶȱ���speed0����ֵΪ0
uint16 speed1=0;          //ͬ��
uint16 speed2=0;
uint16 speed3=0;
uint16 speed4=0;
uint16 speed5=0;
uint16 speed6=0;

void Switch()            //ͨ�����뿪��2�ŵ���8�ŵ�ѡ��7���ٶȵ�֮һ����ʵ�ֳ��ӵ��ٶȿ��ƺ��˶��������
{
  status2= gpio_get(D12);//��D12�ӿڶ�ȡ���ĵ�ƽֵ�������뿪��2�ŵ���Ӧ�ı���status2
  status3= gpio_get(D13);//ͬ��
  status4= gpio_get(D14);
  status5= gpio_get(D15);
  status6= gpio_get(E0);
  status7= gpio_get(E1);
  status8= gpio_get(E2);
  
 if(status2==0)         //(2 312 500)
  {                     //(3 363 550)
    speed0=1;           //(4 365 550 ������)
    speed1=0;           //(5 395 600)
    speed2=0;           //(6 396 600)
    speed3=0;           //(7 411 600)
    speed4=0;           //(8 314 400 ͬ���ھ��淨)
    speed5=0;
    speed6=0;
    Steer_Mid=60;       //�����ֵ�趨����һ��C��������Ҫ�������Կ��Ƴ����˶�����h�ű공����˾���������޸ģ�
    SeekSpeedL=312;     //��2�ŵ��У�ǰ�����ٶ�ֵ�趨�����ֵ1000������1000���ջٵ������оƬ����
    SeekSpeedR=500;     //��2�ŵ��У�ǰ�����ٶ�ֵ�趨�����ֵ1000������1000���ջٵ������оƬ����
    SeekSpeedLL=312;    //��2�ŵ��У��������ٶ�ֵ�趨�����ֵ1000������1000���ջٵ������оƬ���� 
    SeekSpeedRR=500;    //��2�ŵ��У��������ٶ�ֵ�趨�����ֵ1000������1000���ջٵ������оƬ����
  }
   else if(status3==0) //ͬ��
  { 
    speed0=0;
    speed1=1;
    speed2=0;
    speed3=0;
    speed4=0;
    speed5=0;
    speed6=0;
    Steer_Mid=60;
    SeekSpeedL=363;
    SeekSpeedR=550;
    SeekSpeedLL=363;
    SeekSpeedRR=550;
  }
  else if(status4==0) //ͬ��
  { 
    speed0=0;
    speed1=0;
    speed2=1;
    speed3=0;
    speed4=0;
    speed5=0;
    speed6=0;
    Steer_Mid=60;
    SeekSpeedL=365;
    SeekSpeedR=550;
    SeekSpeedLL=365;
    SeekSpeedRR=550;
  }
  else if(status5==0) //ͬ��
  { 
    speed0=0;
    speed1=0;
    speed2=0;
    speed3=1;
    speed4=0;
    speed5=0;
    speed6=0;
    Steer_Mid=60;
    SeekSpeedL=420;
    SeekSpeedR=600;
    SeekSpeedLL=420;
    SeekSpeedRR=600;
  }
  else if(status6==0) //ͬ��
  {
    speed0=0;
    speed1=0;
    speed2=0;
    speed3=0;
    speed4=1;    
    speed5=0;
    speed6=0;
    Steer_Mid=60;
    SeekSpeedL=425;
    SeekSpeedR=600;
    SeekSpeedLL=425;
    SeekSpeedRR=600;
  }
  else if(status7==0) //ͬ��
  {
    speed0=0;
    speed1=0;
    speed2=0;
    speed3=0;
    speed4=0;    
    speed5=1;
    speed6=0;
    Steer_Mid=60;
    SeekSpeedL=430;
    SeekSpeedR=600;
    SeekSpeedLL=430;
    SeekSpeedRR=600;
  }
  else if(status8==0) //ͬ��
  {
    speed0=0;
    speed1=0;
    speed2=0;
    speed3=0;
    speed4=0;    
    speed5=0;
    speed6=1;
    Steer_Mid=60;
    SeekSpeedL=486;
    SeekSpeedR=650;
    SeekSpeedLL=486;
    SeekSpeedRR=650;
  }
}
  