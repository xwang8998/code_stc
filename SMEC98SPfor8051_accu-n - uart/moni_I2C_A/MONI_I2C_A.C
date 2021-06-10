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

sbit    OW     =P3^3;			//定义IIC SDA管脚，
sbit    IO_INOUT    =P3^4;			//定义IIC inout管脚，
//sbit	pSCL	=	P1^1;//P3^6;
//sbit	pSDA	=	P2^2;//P2^4;//P3^2;  //7 
//sbit	pSCL	=	P2^1;//P3^3;  //8


bit   bACK;




//-----------------------------------------------
//========================== 功能子函数===============================
void delay(unsigned int t)
{// 延时函数
while(t){t--;}; //延时循环计数
}
//-------------------------------------------------------------------
void delay_us(unsigned int i)
{//IIC 总线限速延时函数。
//该函数是空函数，延时4 个机器周期。
for(;i>0;i--)
	{
	   	delay(1);
			
	}

}
void set_io_in(void)
{
	//OW = 0;			//设为输入
	IO_INOUT = 0;
}
void set_io_out(void)
{
	IO_INOUT = 1;
}
//-------------------------------------------------------------------
void ow_Init(void)
{//IIC 总线初始化函数
set_io_out();
OW=1;// 释放IIC 总线的数据线。
delay_us(500);
}
//-------------------------------------------------------------------
bit ow_reset(void)
{
unsigned char j;
set_io_out();
OW=0;// 拉高数据线
j=0;
delay_us(200);
OW=1;// 拉高数据线
delay_us(30);
set_io_in();


if(!OW)// 如果数据线为高平电平。
return 1;
else 
return 0;

OW=1;// 拉高数据线
delay_us(300);

}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
void ow_write_byte(unsigned char Data)
{// 向IIC 总线写入一个字节的数据函数
unsigned char i;
for(i=0;i<8;i++)// 有8 位数据
{
set_io_out();		
if(Data&0x01)
{
OW=0;// 写最高位的数据
delay_us(8/3);
OW=1;// 写最高位的数据
delay_us(114/3);
}
else
{
OW=0;// 写最高位的数据
delay_us(102/3);
OW=1;// 写最高位的数据
delay_us(20/3);
}

Data=Data>>1;// 数据左移一位，把次高位放在最高位,为写入次高位做准备
}
set_io_out();
OW=1;
delay_us(100);
}
//-------------------------------------------------------------------
unsigned char ow_read_byte()
{// 从IIC 总线读取一个字节的数据函数
unsigned char i,j;
unsigned char Data; //定义一个缓冲寄存器。
Data = 0;
for(i=0;i<8;i++)// 有8 位数据
{
Data=Data>>1;// 将缓冲字节的数据左移一位，准备读取数据。
set_io_out();
OW=1;// 拉高时钟线，为读取下一位数据做准备。
delay_us(2);
OW=0;// 拉高时钟线，为读取下一位数据做准备。


delay_us(2);

set_io_in();
OW=1;// 拉高时钟线，为读取下一位数据做准备。
delay_us(5);

if(OW)// 如果数据线为高平电平。
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
return Data;// 返回读取的一个字节数据。
}
//-------------------------------------------------------------------

