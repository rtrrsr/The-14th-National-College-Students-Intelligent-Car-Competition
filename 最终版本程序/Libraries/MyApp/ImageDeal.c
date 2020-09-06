#include "headfile.h"

uint16 X_sum = 0;                //��ߺ��������
uint16 Y_sum = 0;                //������������
uint16 threshold=14;            //����ͼ���ֵ����ֵ���˴�Thresholdֵ����ImageDeal.h�е�Thresholdֵ�޸�һ��
uint8  ADdata1[ROW][COL];        //������ֵ��������ͼ�����ݴ����ڴ������У������Ķ�ֵ��ͼ�����ʾ��TFT��ʾ����
uint16 MIDX = 0;                 //����������λ�ú����겢��0
uint16 MIDY = 0;                 //����������λ�������겢��0
uint16 i;
uint16 j;
uint16 Dir_Mid;       //ͼ�񾭹�ȫ��������󣬽��ű�ƹ�����ĺ�����MIDX����Dir_Mid 
uint16 Distance;      //ͼ�񾭹�ȫ��������󣬽��ű�ƹ������������MIDY����Distance
uint8 flag_beacon=0;  //��⵽�ű�ƹ�߱�־��flag_beacon����1��־û�з����ű�ƣ��෴Ϊ0����ʼ����0
uint16 count_beacon=0;//�����ű�ƹ�߳��ִ���������־λ��ͨ�������ű�ƹ�����ĺ�������ֵĴ������������߳��ֵĴ������������ж�ͼ�����Ƿ�����ű��
uint16 begin_beacon=0;//�����������������־����ʼ����0


void Binaryzation()  //�˺����Ǿ����ͼ���ֵ��������,�����Ķ�ֵ��ͼ����ʾ��TFT��ʾ����
{ 
  
  uint16 m,n;            //m��n���������ֱ�����ͼ����м������м���
  for(m=0; m<ROW; m++)   //m�����޼�ͼ��ĸ߶ȣ�������ROW��ROW�ľ���ֵ���ImageDeal.h
  { 
    for(n=0; n<COL; n++) //n�����޼�ͼ��Ŀ�ȣ�������COL��COl�ľ���ֵ���ImageDeal.h
    { 
      if(image[m][n]>Threshold) //����ĳ�����ص㣨�õ������λ��Ϊm��������λ��Ϊn������Ҷ�������image[m][n]�������ڶ�ֵ����ֵThreshold��image[m][n]��255�����ж���Ϊ�Ҷ����㣨�ж�Ϊ�׵㣩��������ADdata1[m][n]������ֵ��������ͼ������255����������ADdata1[ROW][COL]��
        ADdata1[m][n] = 255; 
      else                     //����ĳ�����ص㣨�õ������λ��Ϊm��������λ��Ϊn������Ҷ�������image[m][n]����С�ڶ�ֵ����ֵThreshold��image[m][n]��0�����ж���Ϊ�ҶȰ��㣨�ж�Ϊ�ڵ㣩��������ADdata1[m][n]������ֵ��������ͼ������0����������ADdata1[ROW][COL]��
        ADdata1[m][n] = 0;     
      
    }
  }
}


void find()                  //����find()������find()��������Ŀ���ǽ�ԭʼ�Ҷ�ͼ���еİ�ɫ���ʶ���������Ϊ�ðװ߾����ű�ƹ�ߡ� �����������Ķ�����ע�ͣ�����ϡ��㷨˵����ͼ����ƪ���������
{
  uint16 n = 0;  
  uint8 data[1000][2];       //�������ű�����ߵĺᡢ�����������data[1000][2]
  uint32 sumx = 0,sumy = 0;  
  n=0;
  for(i=0;i<ROW-35;i++)   //�������35�У���ԭʼ�Ҷ�ͼ������·�35���������������ͼ�����Ч�ʡ���Ϊ�����ű�ƾ��복��Զ����ͼ������·�35�о����ò������û����;���ʺ��Ե���
  {
    for(j=0;j<COL-1;j++)  //����ĳһ����i���������У�j=0���У�Ϊ��׼ˮƽ���������У����������������ص㡣������������ص㶼�����㣬������¼���������������֮�ͼ�������֮�͡�Ȼ���ڸú�������ƽ��һ�У�j=1��Ϊ��׼�������������н�����ͬ�Ĳ���ֱ����ɶԸú����������ص���жϡ����Ƕ�ÿ3������ĺ��������ֵ�������������ͼ�����������ߵ����ĵ������ ���޻����ӹ���ţ���׼ȷ����ű�ƹ�����ĺ����ꣻ�л����ӹ���ţ�Ҳ���԰Ѹ��Ź�ߵ�Ӱ�콵����ͣ�����������»��׼ȷ���ű�ƹ�����ĺ����꣩������������Ҳͬ��
    {
      if((image[i][j-1]>Threshold)&&(image[i][j]>Threshold)&&(image[i][j+1]>Threshold))//�����������ж�Ϊ�ű�
      {
        data[n][1]  = i; //��¼���������������֮��
        data[n++][0] = j;//��¼��������ĺ�����֮��
        if(n >=1000)     //������data[1000][2]�ĸ���ά��Ԫ�ص���������Ϊ���1000�������������㡣���������Ӧ�趨Ϊ���޸�
          n = 0;
      }
    }
  }
  
  for(i=0;i<n;i++)
  {                               
    sumx += data[i][0];//sumx += data[i][0]�ǽ�ÿ������õ���������ֵ�ۼ���ͣ�Ȼ�����������������MIDX = (uint16)sumx/n ������������յ��ű�ƹ������λ�ú�����MIDX
    sumy += data[i][1];//�����꣬����ͬ������
  }
  
  MIDX = (uint16)sumx/n;        
  MIDY = (uint16)sumy/n;
       
  if(MIDX==0)          //����������λ�ú�����Ϊ0����˵��ͼ����û���ű�ƹ�߳���
  {
    {count_beacon++;}  //ÿ��һ��ͼ������ϣ����÷�ͼ���д����ű�ƹ�ߣ����ű�ƹ�߳��ִ���������־λ��һ
    if(count_beacon>=5)//�������5��ͼ��û���ű�ƹ�ߣ��Ž���if������䣬�Ա����ű���˸��ɵ�Ӱ�졪��ԭ��������������㷨˵����ͼ����ƪ��
    { 
      flag_beacon=1;   //flag_beacon����1��־û�з����ű�ƣ���ʱ��������������з��򣩿��ƻ����ԭ��˳ʱ�������ҵ�ģʽ����������������
      Dir_Mid = 0;     //û���ű�ƹ�ߴ��ڣ�Dir_Mid=0��ͨ��������ĺ�����MIDX������ֱ�ߵ�Ȼ������
      Distance = 0;    //û���ű�ƹ�ߴ��ڣ�Distance=0���ű공����Ƶ�������뵱Ȼ������
    }
  }
  else                //����������λ�ú����겻Ϊ0����˵��ͼ�������ű�ƹ�߳���
  {
    begin_beacon=1;   //�����������������־��1���ɴ�ָ��ĸ��������ת��
    count_beacon=0;   //��⵽�ű�ƹ�߱�־����
    flag_beacon=0;    //flag_beacon����0��־�����ű��
    Dir_Mid = MIDX;   //ͼ�񾭹�ȫ��������󣬽��ű�ƹ�����ĺ�����MIDX����Dir_Mid 
    Distance = MIDY;  //ͼ�񾭹�ȫ��������󣬽��ű�ƹ������������MIDY����Distance
  }
  
}


int16 NewPWMValue = 0; 
float PWM_P ;          
int Steering_Engine=915; //��һ��C����������ֵ�趨��h�ű공����˾���������޸ġ�
uint16 Steer_Mid=60;     //����һ����������׼��������ֵ�趨Ϊ60����Ҫ�Ķ���
uint16 SeekSpeedL=100;   //������ǰ�ֵ��ת�ٻ�׼��������ֵ�趨Ϊ100����Ҫ�Ķ���
uint16 SeekSpeedR=100;   //������ǰ�ֵ��ת�ٻ�׼��������ֵ�趨Ϊ100����Ҫ�Ķ���
uint16 SeekSpeedLL=100;  //��������ֵ��ת�ٻ�׼��������ֵ�趨Ϊ100����Ҫ�Ķ���
uint16 SeekSpeedRR=100;  //�����Һ��ֵ��ת�ٻ�׼��������ֵ�趨Ϊ100����Ҫ�Ķ���

void Steering_Engine_PWM()  //���(�������˶�����)���ƺ����� �����������Ķ�����ע�ͣ�����ϡ��㷨˵����ͼ����ƪ���͡��㷨˵�����ٶȿ���ƪ���������
{
  
 if(begin_beacon==1)        //�����������������־����1ʱ���ɴ�ָ��ĸ��������ת��
 {
    
  if(flag_beacon==1)        //flag_beacon����1��־û�з����ű��        
  {
    ftm_pwm_duty(ftm1,ftm_ch0,915); //��һ��C��������Ҫ��������ʹ�ó�������תȦѰ���ű�ƣ�h�ű공����˾���������޸ġ�
    MotorSpeed4(260,290,260,290);  //h�ű공ԭ��˳ʱ�루��ת��תȦ����Ѱ����һ���ű�� 
  }
  else                     //else��flag_beacon����0��־�����ű��
  {    
    PWM_P =1.1;            //��ѡȡ����·���Ҳ��Ƶ�ʱ����������PWM_PӦΪ1 ,��ѡȡֱ��·��ֱ��ײ��ʱ��PWM_Pѡ1.1���ɡ�
    NewPWMValue=(int16)((Steer_Mid-Dir_Mid)*PWM_P);  //ע�⣺�������������һ��C���������ƫ��ֵ����䣬��ƫ���㷨���������䣬���������������ж��������ƫ��NewPWMValue�Ĵ���������ͬ��
                                                     //Steer_Mid=60Ϊһ����������׼��������������ֱ������Dir_Mid��������ĺ�����MIDX������������ٳ�����������PWM_P������������ƫ��ת��Ϊ�ĸ������PWMռ�ձ�ƫ��ֵ��ת��ƫ��ֵ��NewPWMValue���� MotorSpeed1���(�������˶�����)���ƺ����У�����ǰ���������ת�ٻ�׼����SeekSpeedL����NewPWMValue����Ϊ�õ������ƫ������ʵ�������PWMռ�ձ�
   
    ftm_pwm_duty(ftm1,ftm_ch0,830+NewPWMValue);     //210 ��һ��C��������Ҫ��������ʹ�ó�������תȦѰ���ű�ƣ��ö����ֵ��NewPWMValue��ӣ�h�ű공����˾���������޸ġ�
    MotorSpeed1(SeekSpeedL-NewPWMValue,SeekSpeedR+NewPWMValue,SeekSpeedLL-NewPWMValue,SeekSpeedRR+NewPWMValue);  //�����λ��ͼ���Ұ벿��ʱ��������ĺ����������ƫ������NewPWMValueС��0��������ּ��������˶����Ҳ����ּ�����ǰ�˶�������һ�߳����ű���˶���һ������С��ƫ�ֱ�����������У�ƫ����СΪ�㣩�������λ��ͼ����벿��ʱ��ͬ��

  }
}
 else             //else�������������������־����0ʱ���ɴ�ָ��ĸ������������ת��
  {
  MotorSpeed1(0,0,0,0);
  }
 
}


void MotorSpeed1(int speed1,int speed3,int speed11,int speed33)   //�����ĸ�ͬ���͵�pwmռ�ձȵ�����ٿ��ƺ������ĸ��������ڿ��Ƴ����Ĳ�ͬ�˶�״̬�����ຯ���а���h�ű공�ĸ��������ת�������ĸ��ֲ�����������ǰ��ǰ�ҡ����󡢺����ĸ������ռ�ձ�ֵ��ռ�ձ�ֵ���ܳ���1000���������ٶȿ��ƺ����Ķ��壬�����ռ�ձ�ֵ��SystemInit()�е�7���ٶȵ����趨����Ӧ2����7�Ų��뿪�ء�
{                                                                   //���Ͼ��塶�㷨˵�����ٶȿ���ƪ�������h�ű공�����ķ�ֵ��̵Ļ������Ʒ������Լ���֮��Ӧ�ĵ�����Ƴ���
  ftm_pwm_duty(MOTOR_FTM,MOTOR1_PWM,0);          //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR2_PWM,speed1);
  ftm_pwm_duty(MOTOR_FTM,MOTOR3_PWM,speed3);     //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR4_PWM,0);
  ftm_pwm_duty(MOTOR_FTM,MOTOR5_PWM,0);          //�����ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR6_PWM,speed11);
  ftm_pwm_duty(MOTOR_FTM,MOTOR7_PWM,speed33);    //�Һ���ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR8_PWM,0);
}

void MotorSpeed2(int speed101,int speed301,int speed1101,int speed3301)
{
  ftm_pwm_duty(MOTOR_FTM,MOTOR1_PWM,speed101);   //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR2_PWM,0);  
  ftm_pwm_duty(MOTOR_FTM,MOTOR3_PWM,speed301);   //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR4_PWM,0);
  ftm_pwm_duty(MOTOR_FTM,MOTOR5_PWM,0);          //�����ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR6_PWM,speed1101);
  ftm_pwm_duty(MOTOR_FTM,MOTOR7_PWM,0);          //�Һ�ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR8_PWM,speed3301);
}

void MotorSpeed3(int speed102,int speed302,int speed1102,int speed3302)
{
  ftm_pwm_duty(MOTOR_FTM,MOTOR1_PWM,0);           //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR2_PWM,speed102);  
  ftm_pwm_duty(MOTOR_FTM,MOTOR3_PWM,0);           //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR4_PWM,speed302);
  ftm_pwm_duty(MOTOR_FTM,MOTOR5_PWM,speed1102);   //���ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR6_PWM,0);
  ftm_pwm_duty(MOTOR_FTM,MOTOR7_PWM,speed3302);   //�Һ���ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR8_PWM,0);
}

void MotorSpeed4(int speed103,int speed303,int speed1103,int speed3303)
{
  ftm_pwm_duty(MOTOR_FTM,MOTOR1_PWM,0);          //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR2_PWM,speed103);
  ftm_pwm_duty(MOTOR_FTM,MOTOR3_PWM,0);          //��ǰ��ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR4_PWM,speed303);
  ftm_pwm_duty(MOTOR_FTM,MOTOR5_PWM,0);          //�����ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR6_PWM,speed1103);
  ftm_pwm_duty(MOTOR_FTM,MOTOR7_PWM,0);          //�Һ�ת
  ftm_pwm_duty(MOTOR_FTM,MOTOR8_PWM,speed3303);
}


float P_SpeedL=20;        //��h�ű공���վ�����ʹ�ñ��������бջ����٣�����Ե��������㷨˵�����ٶȿ���ƪ����������Щ�ջ�pid����ٶȿ��Ʊ���,��δʹ��
float P_SpeedR=20;
float I_SpeedL=3;
float I_SpeedR=3;
float D_SpeedL=0;
float D_SpeedR=0;

int GoalSpeedL=100;
int GoalSpeedR=100;
static int OlderrorL=0;
static int OlderrorR=0;
int NewL=0;
int NewR=0;
static int errorL=0;
static int errorR=0;
int SpeedL;
int SpeedR;
int Speed;

void motor_L()
{
  errorL=GoalSpeedL-SpeedL;
  NewL=NewL+(P_SpeedL*(errorL-OlderrorL)+ I_SpeedL*(errorL));
  OlderrorL=errorL;
  if(NewL>800)   NewL=800;
  if(NewL<=0)    NewL=0;    
  ftm_pwm_duty(MOTOR_FTM,MOTOR1_PWM,0);
  ftm_pwm_duty(MOTOR_FTM,MOTOR2_PWM,NewL);		   
}
void motor_R()
{
  errorR=GoalSpeedR-SpeedR;
  NewR=NewR+(P_SpeedR*(errorR-OlderrorR)+ I_SpeedR*(errorR));
  OlderrorR=errorR;
  if(NewR>800)   NewR=800;
  if(NewR<=0)    NewR=0;    
  ftm_pwm_duty(MOTOR_FTM,MOTOR3_PWM,0);
  ftm_pwm_duty(MOTOR_FTM,MOTOR4_PWM,NewR);
}


void motor()
{
  motor_L();
  motor_R();
}


