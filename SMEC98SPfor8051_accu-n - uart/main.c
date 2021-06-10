#include <STC15F2K60S2.H>
#include "string.h"
#include <stdlib.h>
#include <SMEC98SP.h>
#include <iic_smec98sp.h>
//#include "my.h"
#include	"moni_I2C_A.h"
#include<stdio.h>

#define FPGA_ADDR	0xA0
#define HIGH	1
#define LOW		0
#define IIC_NOACK 1
#define IIC_ACK 0
#define IIC_DELAYTIME 5			//IIC通讯速率大约100K
#define IIC_ADDR	0x00			//对应SMEC98SP中地址
#define ACKCHECKTIME 600
#define BAUD  0xFEC8  

#define CMD_WRITE_MEM            0x96
#define CMD_WRITE_MEM_EX         0x97
#define CMD_READ_MEM             0x44
#define CMD_READ_STATUS		     0xAA 
#define CMD_SET_PAGE_PROT        0xC3 
#define CMD_DECREMENT_CNT        0xC9 
#define CMD_READ_RNG             0xD2 
#define CMD_ENC_READ_MEM         0x4B 
#define CMD_COMP_READ_AUTH       0xA5
#define CMD_ENH_CRPA             0x5A
#define CMD_AUTH_SHA3_WRITE      0x99 
#define CMD_AUTH_SHA3_WRITE_EX   0x9A 
#define CMD_COMP_LOCK_SHA3       0x3C 
#define CMD_DISABLE_DEVICE       0x33
#define CMD_AUTH_REFRESH_PG      0xA3


typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;

BYTE TBUF,RBUF;
BYTE TDAT,RDAT;
BYTE TCNT,RCNT;
BYTE TBIT,RBIT;
BOOL TING,RING;
BOOL TEND,REND;

#define STACK_MAX  16

//unsigned char gi, gj,gk,gm,gn,gret,gfail; //changed linsd //xdata
//unsigned char gi, gj,gk,gm,gn,gret,gfail,; //changed linsd //xdata
 //unsigned char code InternalKey[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};//内部认证密钥,必须和SMEC98SP一致
// unsigned char buf[20];



/******************************************************************************************
/*延时us函数22.1184M  1T
/******************************************************************************************/

                 //38400bps @ 11.0592MHz
sbit    IO_INOUT    =P3^4;			//定义IIC inout管脚，
sbit    IIC_SCL     =P2^2;			//定义IIC SCL管脚
sbit    IIC_SDA     =P2^2;			//定义IIC SCL管脚
sbit    OW     =P3^3;			//定义IIC SDA管脚，
sbit    EN     =P3^5;			//定义IIC en管脚，
sbit 		RXB = P3^0;                        //define UART TX/RX port
sbit 		TXB = P3^1;




void IIC_Delayus(unsigned int n);
void UART_SEND(BYTE dat);
extern unsigned char i2c_single_byte_read(unsigned char xdevaddr,unsigned char RdAddr);
extern void  i2c_single_byte_write(unsigned char xdevaddr,unsigned char xbyte_addr,unsigned char xbyte_data);

void StartUART( void );
void Starttimer0(void);
void delay_nms(unsigned int i);
void print_string(char *str);
void PrintHex(unsigned char *str,unsigned int len);
void UART_INIT();

//BYTE t, r;
BYTE buf[70] ={0};
// BYTE idata buf[39] ={0};
// BYTE idata buf[39] ={0};

 uchar code PG0_data[32] = 	   { 0xBC,0xAE,0x45,0xDE,0x69,0xAF,0x83,0x34,0xD2,0x63,0x60,0x69,0x4E,0x38,0x4E,0xA7,0x54,0xD0,0x1D,0x2A,0x7D,0xF3,0x96,0x3E,0x75,0x98,0xB0,0xBA,0x1B,0xBD,0xFC,0xE0 };//32  PG0
 //uchar code PG0_data[32] =     { 0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11 };
 uchar code PG6_data[32] =     { 0x2A,0xAE,0x45,0xDE,0x69,0x5B,0x83,0x34,0xD2,0x63,0x60,0x69,0x4E,0x38,0x4E,0x97,0x54,0xD0,0x1D,0x2A,0x7D,0xF3,0x96,0x3E,0x75,0x98,0xB0,0xBA,0x1B,0xBD,0xFC,0xE0 };//32 PG6
 uchar code hmac_secret[32] =  { 0x11,0xEE,0xAA,0xBB,0x22,0x55,0x88,0x33,0xDD,0x66,0x60,0x99,0x44,0x33,0x44,0x99,0x55,0xDD,0x1D,0x22,0x77,0xFF,0x99,0x33,0x77,0x99,0xBB,0xBB,0x11,0xBB,0xFF,0xEE };//32
 uchar code ROM_NO[8] =  { 0x05,0xAF,0x61,0x38,0x00,0x00,0x00,0x39 };//32
 uchar code MANID[2] =  { 0x00,0x00 };//32
//-----------------------------------------
//Timer interrupt routine for UART

void tm0() interrupt 1 using 1
{
	
    if (RING)
    {
        if (--RCNT == 0)
        {
            RCNT = 3;                   //reset send baudrate counter
            if (--RBIT == 0)
            {
                RBUF = RDAT;            //save the data to RBUF
                RING = 0;               //stop receive
                REND = 1;               //set receive completed flag
            }
            else
            {
                RDAT >>= 1;
                if (RXB) RDAT |= 0x80;  //shift RX data to RX buffer
            }
        }
    }
    else if (!RXB)
    {
        RING = 1;                       //set start receive flag
        RCNT = 4;                       //initial receive baudrate counter
        RBIT = 9;                       //initial receive bit number (8 data bits + 1 stop bit)
    }

    if (--TCNT == 0)
    {
        TCNT = 3;                       //reset send baudrate counter
        if (TING)                       //judge whether sending
        {
            if (TBIT == 0)
            {
                TXB = 0;                //send start bit
                TDAT = TBUF;            //load data from TBUF to TDAT
                TBIT = 9;               //initial send bit number (8 data bits + 1 stop bit)
            }
            else
            {
                TDAT >>= 1;             //shift data to CY
                if (--TBIT == 0)
                {
                    TXB = 1;
                    TING = 0;           //stop send
                    TEND = 1;           //set send completed flag
                }
                else
                {
                    TXB = CY;           //write CY to TX port
                }
            }
        }
    }
}

//-----------------------------------------
//initial UART module variable

void UART_INIT()
{
    TING = 0;
    RING = 0;
    TEND = 1;
    REND = 0;
    TCNT = 0;
    RCNT = 0;
}
void UART_SEND(BYTE dat)
{
    while (!TEND);
    TEND = 0;
    TBUF = dat;
    TING = 1;
}
/*
void UART_HEX(unsigned char *buf, unsigned char len)
{
	unsigned int i;
    for(i=0;i<len;i++)
		{
			UART_SEND(buf[i]);
		}
}

void IIC_Delayus(unsigned int n)
{
	//unsigned char i;
	for(;n>0;n--)
	{
 		;//i = 1;
	}	
}
void    IIC_SetSDA(unsigned char level)
{
	if(level == HIGH)
	{
		IIC_SDA = 1;
	}else
	{
		IIC_SDA = 0;
	}
}
void    IIC_SetSCL(unsigned char level)
{
	if(level == HIGH)
	{
		IIC_SCL = 1;
	}else
	{
		IIC_SCL = 0;
	}
}
void SetSDAto_InputMode(void)
{
	//根据芯片手册配置
	IIC_SDA = 1;			//设为输入
	IO_INOUT = 0;
	
}
void SetSDAto_OutputMode(void)
{
	//根据芯片手册配置
	//本单片机不用设置可直接输出
	IO_INOUT = 1;
	
}

void   IIC_Start(void)
{
	SetSDAto_OutputMode();			//SDA设为输出模式
	IIC_SetSDA(HIGH);
	IIC_SetSCL(HIGH);
	IIC_Delayus(IIC_DELAYTIME);			
	IIC_SetSDA(LOW);
	IIC_Delayus(IIC_DELAYTIME);
	IIC_SetSCL(LOW);
}

void   IIC_Stop(void)
{	
	SetSDAto_OutputMode();			//SDA设为输出模式
	IIC_SetSDA(LOW);
	IIC_SetSCL(HIGH);
	IIC_Delayus(IIC_DELAYTIME);
	IIC_SetSDA(HIGH);
	IIC_Delayus(IIC_DELAYTIME);
}
unsigned char IIC_GetSdaStus(void)
{
	unsigned char tmp;

	if(IIC_SDA == 1)	
		tmp=1;
	else 
		tmp=0;
	return tmp;
}


unsigned char  IIC_Send(unsigned char IIC_data)
{
	unsigned char Ack ;
	unsigned int AckLoop;
	unsigned char xtmp;
	unsigned char i;
	SetSDAto_OutputMode();			//SDA设为输出模式
    //xtmp = IIC_data;//50;
	//while(1)
	//{IIC_SDA = 1;
     //IIC_Delayus(8);
	 //IIC_SDA = 0;
     //IIC_Delayus(8);
	 //IIC_SDA = 0;
     //IIC_Delayus(8);
	//}
    //while(1){
	xtmp = IIC_data;//50;
	for(i=0;i<8;i++)
	{
		IIC_SetSCL(LOW);
		IIC_Delayus(IIC_DELAYTIME);
		if((xtmp&0x80)==0)
		   IIC_SetSDA(0);
		else
		   IIC_SetSDA(1);
		IIC_Delayus(IIC_DELAYTIME);
		IIC_SetSCL(HIGH);
		IIC_Delayus(IIC_DELAYTIME);
		IIC_Delayus(IIC_DELAYTIME);
		xtmp<<= 1;
	}
	//IIC_Delayus(1000);
   //}
	
	IIC_SetSCL(LOW);
	IIC_Delayus(IIC_DELAYTIME);
	IIC_Delayus(IIC_DELAYTIME);
    SetSDAto_InputMode();//SDA设为输入模式
	IIC_SetSCL(HIGH);
	IIC_Delayus(IIC_DELAYTIME);
	IIC_Delayus(IIC_DELAYTIME);
	Ack = IIC_NOACK;
				
	for(AckLoop=0;AckLoop<ACKCHECKTIME;AckLoop++) //260us
	{
		if(!IIC_GetSdaStus())
		{
			Ack = IIC_ACK;
			break;
		}
		IIC_Delayus(IIC_DELAYTIME);
	}
	IIC_SetSCL(LOW);
	
	
	return Ack;			//return success=0 / failure=1
}

unsigned char IIC_Read(unsigned char bACK)
{
	unsigned char Data;
	unsigned char i;
	Data = 0;
	SetSDAto_InputMode();			//SDA设为输入模式
	for(i=0;i<8;i++)
	{
		Data <<= 1;
		IIC_SetSCL(LOW);
		IIC_Delayus(IIC_DELAYTIME);
		IIC_Delayus(IIC_DELAYTIME);
		IIC_Delayus(IIC_DELAYTIME);
		IIC_SetSCL(HIGH);
		IIC_Delayus(IIC_DELAYTIME);
		IIC_Delayus(IIC_DELAYTIME);
		if(IIC_GetSdaStus())
			Data |= 1;
		else
			Data &= 0xfe;
	}
	IIC_SetSCL(LOW);
	
	IIC_Delayus(IIC_DELAYTIME);   
  	IIC_SetSDA(bACK);
	IIC_Delayus(IIC_DELAYTIME);
    SetSDAto_OutputMode();			//SDA设为输出模式	
	IIC_SetSCL(HIGH);
	IIC_Delayus(IIC_DELAYTIME);
	IIC_Delayus(IIC_DELAYTIME);
	IIC_SetSCL(LOW);
	return Data;
}


bit IIC_ReadWithAddr(unsigned char addr, unsigned char *buf, unsigned char len)
{
  	unsigned char i;
	
	
	i = 10;
    while (i) 
	{
		
		IIC_Start();
        if (IIC_Send(addr) == IIC_ACK) break;
        if (--i == 0) return IIC_NOACK;
    }
	for(i = 0; i < len -1 ; i++)
	{
		buf[i] = IIC_Read(IIC_ACK);
	}
	buf[i] = IIC_Read(IIC_NOACK);
	IIC_Stop();

	return IIC_ACK;
}

bit IIC_WriteWithAddr(unsigned char addr, unsigned char *buf, unsigned char len)
{
  	unsigned char i,xaddr,get_ret;
	i = 10;
	xaddr = addr;//0x50;
	
    while (i>0) //for(i = 0; i < 10; i++)//
	{
		//IIC_Send(xaddr);
		
		IIC_Start();
		get_ret = IIC_Send(xaddr);
		if(get_ret==IIC_ACK){break;}
        if (IIC_Send(xaddr) == IIC_ACK) break;
		i--;
        if (i >= 10){
			return IIC_NOACK;}
    }
	for(i = 0; i < len; i++)
	{
		
		get_ret = IIC_Send(buf[i]);
		if(get_ret!=0)
			return IIC_NOACK;
	}
    
	IIC_Delayus(IIC_DELAYTIME);
	IIC_Delayus(IIC_DELAYTIME);
	
	IIC_Stop();
    
	
	
	return IIC_ACK;
}
*/
//----------------------------------------------------------------------------------------
//22.1184M  1T   
// void delay_nms(unsigned int i)
// {
// 	unsigned int  j;	
// 	
// 	for(;i>0;i--)
// 	{
// 		OW =1;
// 	   	j = 1580;

// 		while(--j);	
// 			
// 	}
// }

void delay_nms(unsigned int i)
{
	unsigned int  j;	
	
	for(;i>0;i--)
	{
		
	   	

		for(j = 1580;j>0;j--)	
			{
				OW =1;
			}
			
	}
}
void sd_delay(unsigned char x)
{
	unsigned char  i;
	i = x;
	while(--i);
}


//-----------------------------------------
void ow_read_page(unsigned char len,unsigned char page )//66 02 44 07 [32][75] AA 
{
	unsigned char  i;
	unsigned char getreset_ok;
	delay_us(1000);
		getreset_ok = ow_reset();delay_us(500);
		if(getreset_ok)
		{
		getreset_ok = 0;
		ow_write_byte(0xCC);
		delay_us(100);
		ow_write_byte(0x66);
		ow_write_byte(len);
		ow_write_byte(CMD_READ_MEM);
		ow_write_byte(page);
		delay_us(100);
		buf[0] = ow_read_byte();//crc
		buf[1] = ow_read_byte();//crc
		//UART_SEND(buf[0]);UART_SEND(buf[1]);
		delay_us(100);
		ow_write_byte(0xAA);
		//P3M1 = 0x20;
		//P3M0 = 0x00;
		delay_nms(50);
		
		
		for(i=2;i<39;i++)
			{
				buf[i] = ow_read_byte();
				UART_SEND(buf[i]);
				delay_us(100);
			}
		}
		else ;
		delay_us(1000);

}
void ow_write_page(unsigned char len,unsigned char page,uchar *write_data )//66 22 96 06 2A AE 45 DE 69 5B 83 34 D2 63 60 69 4E 38 4E 97 54 D0 1D 2A 7D F3 96 3E 75 98 B0 BA 1B BD FC E0 [FC][67] AA 
{
	int  i,j;
	unsigned char getreset_ok;
	//uchar buf[39];
	delay_us(1000);
///////////////////////////////////////
			memcpy(&buf[0],write_data,32);
			delay_us(100);

		getreset_ok = ow_reset();delay_us(500);
		if(getreset_ok)
		{
		getreset_ok = 0;
		ow_write_byte(0xCC);
		delay_us(100);
		ow_write_byte(0x66);
		ow_write_byte(len);
		ow_write_byte(CMD_WRITE_MEM);
		ow_write_byte(page);
		delay_us(100);
		//memcpy(&buf[0],write_data,32);
		
		for(i=0;i<=31;i++)
			{
				ow_write_byte(  buf[i]);
				//UART_SEND(buf[i]);
				delay_us(100);
			}
		
		buf[32] = ow_read_byte();
		buf[33] = ow_read_byte();
		//UART_SEND(buf[0]);UART_SEND(buf[1]);
		delay_us(100);
		ow_write_byte(0xAA);
		delay_us(100);delay_us(100);delay_us(100);delay_us(100);
		
		delay_nms(100);
		//delay_us(60000);
		for(j=0;j<5;j++)
		{
			buf[34+j] = ow_read_byte();
			delay_us(100);
		}
		
		
		}
		else ;
		delay_us(1000);

}
void ow_write_crpa(unsigned char page,uchar at,uchar *challenge )
{
	int  i,j;
	unsigned char getreset_ok;
	delay_us(1000);
	memcpy(&buf[0],challenge,32);
		getreset_ok = ow_reset();delay_us(500);
		if(getreset_ok)
		{
		getreset_ok = 0;
		ow_write_byte(0xCC);
		delay_us(100);
		ow_write_byte(0x66);
		ow_write_byte(0x23);
		ow_write_byte(0xa5);
		ow_write_byte(page);
		ow_write_byte(at);
		delay_us(100);
		for(i=0;i<=31;i++)
			{
				ow_write_byte(buf[i]);
				UART_SEND(buf[i]);
				delay_us(100);
			}
		
		buf[32] = ow_read_byte();
		buf[33] = ow_read_byte();
		//UART_SEND(buf[0]);UART_SEND(buf[1]);
		delay_us(100);
		ow_write_byte(0xAA);
		//P3M1 = 0x20;
		//P3M0 = 0x00;
		delay_nms(50);
		
		for(j=0;j<37;j++)
		{
			buf[j] = ow_read_byte();
			UART_SEND(buf[j]);
			delay_us(100);
		}
		
		}
		else ;
		delay_us(1000);

}
void ow_write_sha3_256(uchar len,uchar *message)
{
	
}

//////////////////////////////////////////////////////////////////////
void main(void)
{
	unsigned char  ret,i,flag;
	unsigned char  k,j;
	unsigned char getreset_ok;
	TMOD = 0xf0;                        //timer0 in 16-bit auto reload mode
    AUXR = 0x80;                        //timer0 working at 1T mode
    TL0 = 0x30;//0x8f+0x05;//BAUD;
    TH0 = 0xff;//0xfd;//BAUD>>8;                      //initial timer0 and set reload value
	TF0 =0;
    TR0 = 1;                            //tiemr0 start running
    ET0 = 1;                            //enable timer0 interrupt
    PT0 = 1;                            //improve timer0 interrupt priority
    EA = 1;                             //open global interrupt switch

	
    UART_INIT();
	EN = 1;	
  
	
	//gstacki = 0;
	ow_Init();delay_us(100);
	k=0;j = 0;
	//printf("chushihuawancheng!\r\n");
	while(1)
	{
		
		//UART_SEND(0xAA);UART_SEND(0xAA);UART_SEND(0x01);UART_SEND(0xAA);UART_SEND(0xAA);
		//ow_Init();delay_us(1000);
// 		getreset_ok = ow_reset();delay_us(500);
// 		if(getreset_ok)
// 		{
// 		getreset_ok = 0;
// 		ow_write_byte(0xCC);
// 		delay_us(100);
// 		ow_write_byte(0x66);
// 		ow_write_byte(0x02);
// 		ow_write_byte(0x44);
// 		ow_write_byte(0x07);delay_us(100);
// 		buf[0] = ow_read_byte();
// 		buf[1] = ow_read_byte();
// 		//UART_SEND(buf[0]);UART_SEND(buf[1]);
// 		delay_us(100);
// 		ow_write_byte(0xAA);
// 		P3M1 = 0x20;
// 		P3M0 = 0x00;
// 		delay_nms(50);
// 		
// 		
// 		for(i=2;i<=39;i++)
// 			{
// 				buf[i] = ow_read_byte();
// 				UART_SEND(buf[i]);
// 				delay_us(100);
// 			}
// 		}
// 		else ;
// 		delay_us(1000);
//------------------------------CMD_DISABLE_DEVICE       0x33-----------------------------
		UART_SEND(0xAA);UART_SEND(0xAA);UART_SEND(0x02);UART_SEND(0xAA);UART_SEND(0xAA);

		getreset_ok = ow_reset();delay_us(500);
		if(getreset_ok)
		{
			getreset_ok = 0;
			ow_write_byte(CMD_DISABLE_DEVICE);delay_us(100);
			for(i=0;i<=7;i++)
			{
				buf[i] = ow_read_byte();
				//UART_SEND(buf[i]);
				delay_us(100);
			}
// 		k++;
// 		if(k>10)
// 			{
// 				k = 0;
// 				
// 			}
// 		else if(k==10)
// 			{
// 				j++;
// 				UART_SEND(j);
 			}
		else;

		
 		delay_us(1000);
 		UART_SEND(0xAA);UART_SEND(0xAA);UART_SEND(0x01);UART_SEND(0xAA);UART_SEND(0xAA);
		ow_write_page(0x22,0x00,PG0_data );
		delay_us(1000);
		ow_read_page(0x02,0x00 );
		delay_us(1000);
		ow_write_page(0x22,0x06,PG6_data );
		delay_us(1000);
		UART_SEND(0xAA);UART_SEND(0xAA);UART_SEND(0x02);UART_SEND(0xAA);UART_SEND(0xAA);
 		ow_read_page(0x02,0x07 );
		delay_us(1000);
		UART_SEND(0xAA);UART_SEND(0xAA);UART_SEND(0x03);UART_SEND(0xAA);UART_SEND(0xAA);
		ow_write_crpa(0x00,0x00,hmac_secret);
		delay_us(1000);
		
	}

} 







