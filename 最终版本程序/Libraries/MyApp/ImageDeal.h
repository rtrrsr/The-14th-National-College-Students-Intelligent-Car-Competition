#ifndef _IMAGEDEAL_H_
#define _IMAGEDEAL_H_
#include "headfile.h"

#define Threshold 14        //����ͷ��ֵ����ֵ 14 18
#define Black_Point 0       //����ͷ��ֵ���������ص�ĻҶ�������С����ֵ���ж�Ϊ�ڵ㣬�ڵ���ֵ��0 �����
#define White_Point 255     //����ͷ��ֵ���������ص�ĻҶ�������������ֵ���ж�Ϊ�׵㣬�׵���ֵ��255��������
extern uint16 Dir_Mid;    //ͼ�񾭹�ȫ��������󣬽��ű�ƹ�����ĺ�����MIDX����Dir_Mid 
extern uint16 Distance;   //ͼ�񾭹�ȫ��������󣬽��ű�ƹ������������MIDY����Distance
extern uint8 flag_beacon; //��⵽�ű�ƹ�߱�־��flag_beacon����1��־û�з����ű�ƣ��෴Ϊ0
extern uint16 count_beacon;//�ű�ƹ�߳��ִ���������־λ��ͨ�������ű�ƹ�����ĺ�������ֵĴ������������߳��ֵĴ������������ж�ͼ�����Ƿ�����ű��
extern uint16 begin_beacon;//�����������������־
extern void find();  //����find()������find()��������Ŀ���ǽ�ԭʼ�Ҷ�ͼ���еİ�ɫ���ʶ���������Ϊ�ðװ߾����ű�ƹ��
#define COL     188//ͼ���ȣ�������    ��Χ1-752     ��K60�ɼ���������188����Ҫ�޸�
#define ROW     120//ͼ��߶ȣ�������	��Χ1-480    ��K60�ɼ���������120����Ҫ�޸�
extern void Binaryzation(); //��������ͼ���ֵ��������Binaryzation()�������ImageDeal.c
extern uint8 ADdata1[ROW][COL]; //��ֵ���������������ݴ洢������ADdata1[ROW][COL]
extern uint32 sumx,sumy; 
extern int16 NewPWMValue; //���������ͼ�����ߵĺ���ƫ�����֮�󣬵ó��������Ҳ���ռ�ձ��ٶ�/�˶���������ռ�ձ�ֵ
extern void Steering_Engine_PWM();//���(�������˶�����)���ƺ��� 
extern void MotorSpeed(int speedL,int speedR,int speedLL,int speedRR);          //������ͬ���͵�pwmռ�ձȵ�����ٿ��ƺ���������������ڿ��Ƴ����Ĳ�ͬ�˶�״̬�����ຯ���а���h�ű공�ĸ��������ת�������ĸ��ֲ�����������ǰ��ǰ�ҡ����󡢺����ĸ������ռ�ձ�ֵ��ռ�ձ�ֵ���ܳ���1000
extern void MotorSpeed1(int speed1,int speed3,int speed11,int speed33);
extern void MotorSpeed2(int speed101,int speed301,int speed1101,int speed3301);
extern void MotorSpeed3(int speed102,int speed302,int speed1102,int speed3302);
extern void MotorSpeed4(int speed103,int speed303,int speed1103,int speed3303);
extern int16 flag_steer; //�����Ǳ�־���˱�������������һ��c�ű공��h�ű공��ʹ�ã����������޸�

extern int SpeedL;       //��h�ű공���վ�����ʹ�ñ��������бջ����٣�����Ե��������㷨˵�����ٶȿ���ƪ����������Щ�ջ�pid����ٶȿ��Ʊ���,��δʹ��
extern int SpeedR;
extern int Speed;
extern int NewL;
extern int NewR;
extern int GoalSpeedL;
extern int GoalSpeedR;
extern uint16 Steer_Mid;
extern uint16 SeekSpeedR;
extern uint16 SeekSpeedL;
extern uint16 SeekSpeedLL;
extern uint16 SeekSpeedRR;
extern void motor();

#endif