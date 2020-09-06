#include "headfile.h"

uint16 a[8]; //���������ݻ�����,��ʹ�ó�����

void UltrasonicRead()   //������adc�ɼ�������������ʹ��
{
  a[0] =  adc_ave(adc0,ADC0_SE8, ADC_12bit,100);
  a[1] =  adc_ave(adc0,ADC0_SE9, ADC_12bit,100);
  a[2] =  adc_ave(adc0,ADC0_SE12,ADC_12bit,100);
  a[3] =  adc_ave(adc0,ADC0_SE13,ADC_12bit,100);
  a[4] =  adc_ave(adc1,ADC1_SE10,ADC_12bit,100);
  a[5] =  adc_ave(adc1,ADC1_SE11,ADC_12bit,100);
  a[6] =  adc_ave(adc1,ADC1_SE12,ADC_12bit,100);
  a[7] =  adc_ave(adc1,ADC1_SE13,ADC_12bit,100);
}

/***********��λ����ʾ����**********************/
float OutData[4];


//**************************************************************************
/*
*  ����˵����SCIʾ����CRCУ��
�ڲ����ú���
*  ����˵���� ��
*  �������أ��޷��Ž��ֵ
*  �޸�ʱ�䣺2013-2-10
*/
//**************************************************************************
static unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
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

//************************************************
//
/*
*  ����˵����SCIʾ�������ͺ���

*  ����˵����
OutData[]  ��Ҫ���͵���ֵ���������
*  �������أ��޷��Ž��ֵ
*  �޸�ʱ�䣺2013-2-10
*/
//****************************************************
void OutPut_Data(void)
{
    int temp[4] = {0};
    unsigned int temp1[4] = {0};
    unsigned char databuf[10] = {0};
    unsigned char i;
    unsigned short CRC16 = 0;
    for(i=0;i<4;i++)
    {

        temp[i]  = (int)OutData[i];
        temp1[i] = (unsigned int)temp[i];

    }

    for(i=0;i<4;i++)
    {
        databuf[i*2]   = (unsigned char)(temp1[i]%256);
        databuf[i*2+1] = (unsigned char)(temp1[i]/256);
    }

    CRC16 = CRC_CHECK(databuf,8);
    databuf[8] = CRC16%256;
    databuf[9] = CRC16/256;

    for(i=0;i<10;i++)
    {
        uart_putchar (uart2,(char)databuf[i]);
    }
}

