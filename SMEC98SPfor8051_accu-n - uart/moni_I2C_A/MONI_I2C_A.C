/*********************************************************************************************************************************/
//#include	"STC15Fxxxx.H"
#include	"moni_I2C_A.h"

#include "reg51.h"
#include "intrins.h"
//#include "uart.h"
//#include "gpio.h"

#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 
//void UART_SEND(BYTE dat);
//#define WD7188	0X40
//#define RD7188	0X41 

sbit    OW     =P3^3;			//����IIC SDA�ܽţ�
sbit    IO_INOUT    =P3^4;			//����IIC inout�ܽţ�
//sbit	pSCL	=	P1^1;//P3^6;
//sbit	pSDA	=	P2^2;//P2^4;//P3^2;  //7 
//sbit	pSCL	=	P2^1;//P3^3;  //8


bit   bACK;




//-----------------------------------------------
//========================== �����Ӻ���===============================
void delay(unsigned int t)
{// ��ʱ����
while(t){t--;}; //��ʱѭ������
}
//-------------------------------------------------------------------
void delay_us(unsigned int i)
{//IIC ����������ʱ������
//�ú����ǿպ�������ʱ4 ���������ڡ�
for(;i>0;i--)
	{
	   	delay(1);
			
	}

}
void set_io_in(void)
{
	//OW = 0;			//��Ϊ����
	IO_INOUT = 0;
}
void set_io_out(void)
{
	IO_INOUT = 1;
}
//-------------------------------------------------------------------
void ow_Init(void)
{//IIC ���߳�ʼ������
set_io_out();
OW=1;// �ͷ�IIC ���ߵ������ߡ�
delay_us(500);
}
//-------------------------------------------------------------------
bit ow_reset(void)
{
unsigned char j;
set_io_out();
OW=0;// ����������
j=0;
delay_us(200);
OW=1;// ����������
delay_us(30);
set_io_in();


if(!OW)// ���������Ϊ��ƽ��ƽ��
return 1;
else 
return 0;

OW=1;// ����������
delay_us(300);

}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
void ow_write_byte(unsigned char Data)
{// ��IIC ����д��һ���ֽڵ����ݺ���
unsigned char i;
for(i=0;i<8;i++)// ��8 λ����
{
set_io_out();		
if(Data&0x01)
{
OW=0;// д���λ������
delay_us(8/3);
OW=1;// д���λ������
delay_us(114/3);
}
else
{
OW=0;// д���λ������
delay_us(102/3);
OW=1;// д���λ������
delay_us(20/3);
}

Data=Data>>1;// ��������һλ���Ѵθ�λ�������λ,Ϊд��θ�λ��׼��
}
set_io_out();
OW=1;
delay_us(100);
}
//-------------------------------------------------------------------
unsigned char ow_read_byte()
{// ��IIC ���߶�ȡһ���ֽڵ����ݺ���
unsigned char i,j;
unsigned char Data; //����һ������Ĵ�����
Data = 0;
for(i=0;i<8;i++)// ��8 λ����
{
Data=Data>>1;// �������ֽڵ���������һλ��׼����ȡ���ݡ�
set_io_out();
OW=1;// ����ʱ���ߣ�Ϊ��ȡ��һλ������׼����
delay_us(2);
OW=0;// ����ʱ���ߣ�Ϊ��ȡ��һλ������׼����


delay_us(2);

set_io_in();
OW=1;// ����ʱ���ߣ�Ϊ��ȡ��һλ������׼����
delay_us(5);

if(OW)// ���������Ϊ��ƽ��ƽ��
{
Data |= 0x80;


}
else 
{
Data &= 0x7f;


}

OW=1;
delay_us(33);
}
set_io_out();
delay_us(33);
return Data;// ���ض�ȡ��һ���ֽ����ݡ�
}
//-------------------------------------------------------------------
