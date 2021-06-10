/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 定时器0的16位自动重装载模式举例---------------*/
/* --- Mobile: (86)13922805190 -------------- -------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/* 如果要在文章中应用此代码,请在文章中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//若无特别说明,工作频率一般为11.0592MHz


#include "reg51.h"
#include "intrins.h"
//#include	"moni_I2C_A.h"

//extern  set_i2c_slave(uchar xdevaddr,uchar xbyte_addr,uchar xbyte_data);
//-----------------------------------------------
typedef unsigned char BYTE;
typedef unsigned int WORD;
#define FOSC 11059200L

#define T1MS (65536-FOSC/1000)      //1T模式
//#define T1MS (65536-FOSC/12/1000) //12T模式

sfr AUXR = 0x8e;                    //Auxiliary register
sbit    FPGA_CTR = P3^4;
sbit	IIC_SDA	=	P3^3;//P2^7;
sbit	IIC_SCL	=	P3^2;//P2^6;

void display(unsigned char aa);
void delay(unsigned int t);
void delay_IIC(void);
void IIC_Init(void);
void IIC_start(void);
void IIC_stop(void);
bit IIC_Tack(void);
void IIC_single_byte_write(unsigned char Daddr,unsigned char Waddr,unsigned char Data);
unsigned char IIC_single_byte_read(unsigned char Daddr,unsigned char Waddr);
void IIC_write_byte(unsigned char Data);
unsigned char IIC_read_byte(void);
//-----------------------------------------------
int time = 0;
int s =0;
unsigned char math_data_H,math_data_L; 
	unsigned char end_data_H,end_data_L;
/* Timer0 interrupt routine */



//-----------------------------------------------
//========================== 功能子函数===============================
void delay(unsigned int t)
{// 延时函数
while(t){t--;}; //延时循环计数
}
//-------------------------------------------------------------------
void delay_IIC(void)
{//IIC 总线限速延时函数。
//该函数是空函数，延时4 个机器周期。
;;
}
//-------------------------------------------------------------------
void IIC_Init(void)
{//IIC 总线初始化函数
IIC_SDA=1;// 释放IIC 总线的数据线。
IIC_SCL=1;// 释放IIC 总线的时钟线。
}
//-------------------------------------------------------------------
void IIC_start(void)
{//IIC 总线产生起始信号函数
IIC_SDA=1;// 拉高数据线
IIC_SCL=1;// 拉高时钟线
delay_IIC();
IIC_SDA=0;// 在时钟线为高电平时，拉低数据线，产生起始信号。
delay_IIC();
IIC_SCL=0;// 拉低时钟线
}
//-------------------------------------------------------------------
void IIC_stop(void)
{//IIC 总线产生停止信号函数
IIC_SDA=0;// 拉低数据线
delay_IIC();
IIC_SCL=1;// 拉高时钟线。
delay_IIC();
IIC_SDA=1;// 时钟时线为高电平时，拉高数据线，产生停止信号。
delay_IIC();
}
//-------------------------------------------------------------------
bit IIC_Tack(void)
{// 接收应答信号函数
bit ack;// 定义一个位变量，来暂存应答状态。
IIC_SDA=1;// 释放数据总线，准备接收应答信号。
delay_IIC();
IIC_SCL=1;// 拉高时钟线。
delay_IIC();
ack=IIC_SDA;// 读取应答信号的状态。
delay_IIC();
IIC_SCL=0;// 拉低时钟线。
delay_IIC();
return ack;// 返回应答信号的状态， 0 表示应答， 1 表示非应答。
}
//-------------------------------------------------------------------
void IIC_write_byte(unsigned char Data)
{// 向IIC 总线写入一个字节的数据函数
unsigned char i;
for(i=0;i<8;i++)// 有8 位数据
{
IIC_SDA=Data&0x80;// 写最高位的数据
delay_IIC();
IIC_SCL=1; // 拉高时钟线，将数写入到设备中。
delay_IIC();
IIC_SCL=0;// 拉低时钟线，允许改变数据线的状态
delay_IIC();
Data=Data<<1;// 数据左移一位，把次高位放在最高位,为写入次高位做准备
}
}
//-------------------------------------------------------------------
unsigned char IIC_read_byte()
{// 从IIC 总线读取一个字节的数据函数
unsigned char i;
unsigned char Data; //定义一个缓冲寄存器。
for(i=0;i<8;i++)// 有8 位数据
{
IIC_SCL=1;// 拉高时钟线，为读取下一位数据做准备。
delay_IIC();
Data=Data<<1;// 将缓冲字节的数据左移一位，准备读取数据。
delay_IIC();
if(IIC_SDA)// 如果数据线为高平电平。
Data=Data|0x1;// 则给缓冲字节的最低位写1。
IIC_SCL=0;// 拉低时钟线，为读取下一位数据做准备。
delay_IIC();
}
return Data;// 返回读取的一个字节数据。
}
//-------------------------------------------------------------------
void IIC_single_byte_write(unsigned char Daddr,unsigned char Waddr,unsigned char Data)
{// 向任意地址写入一个字节数据函数
IIC_start();// 产生起始信号
IIC_write_byte(Daddr);// 写入设备地址（写）
FPGA_CTR=0;
IIC_Tack();// 等待设备的应答
FPGA_CTR=1;
IIC_write_byte(Waddr);// 写入要操作的单元地址。
FPGA_CTR=0;
IIC_Tack();// 等待设备的应答。
FPGA_CTR=1;
IIC_write_byte(Data);// 写入数据。
FPGA_CTR=0;
IIC_Tack();// 等待设备的应答。
FPGA_CTR=1;
IIC_stop();// 产生停止符号。
}
//-------------------------------------------------------------------
unsigned char IIC_single_byte_read(unsigned char Daddr,unsigned char Waddr)
{// 从任意地址读取一个字节数据函数
unsigned char Data;//定义一个缓冲寄存器。
IIC_start();// 产生起始信号
IIC_write_byte(Daddr);// 写入设备地址（写）
IIC_Tack();// 等待设备的应答
IIC_write_byte(Waddr);// 写入要操作的单元地址。
IIC_Tack();// 等待设备的应答。
IIC_start();// 产生起始信号
IIC_write_byte(Daddr+1);// 写入设备地址（读） 。
IIC_Tack();// 等待设备的应答。
Data=IIC_read_byte();// 写入数据。
IIC_Tack();
IIC_stop();// 产生停止符号。

//------------------- 返回读取的数据--------------------
return Data;// 返回读取的一个字节数据。
}
//-------------------------------------------------------------------
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//--------------------------------------------
