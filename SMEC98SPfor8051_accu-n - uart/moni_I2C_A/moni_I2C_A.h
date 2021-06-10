
#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 

// ES51 commands
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


// Result bytes
#define RESULT_SUCCESS                0xAA
#define RESULT_FAIL_PROTECTION        0x55
#define RESULT_FAIL_PARAMETETER       0x77
#define RESULT_FAIL_INVALID_SEQUENCE  0x33
#define RESULT_FAIL_DEVICE_DISABLED   0x88
#define RESULT_FAIL_VERIFY            0x00
#define RESULT_FAIL_MULT	          0x22 //for multiple crypt errors
#define RESULT_FAIL_ENTROPY			  0xDD

#define RESULT_FAIL_COMMUNICATION     0x11


#define PG_SECRET                6

void ow_write_byte(unsigned char Data);
unsigned char ow_read_byte();
void delay(unsigned int t);
void delay_us(unsigned int i);
bit ow_reset(void);
void ow_Init(void);
void delay_us(unsigned int i);