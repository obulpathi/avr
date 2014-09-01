#define TIMER	0xD0
#define T100	0x90

#define REG_SEC 0x00
#define REG_STATUS 0x0F 
#define RTC_START 0x00

//#include "/home/naidu/projects/wildCENSE/os/atmega32/modules/usart/blocking/usart.h"
//#include "/home/naidu/projects/wildCENSE/os/atmega32/modules/usart/blocking/usart.c"

void RTC_Init(void);
char RTC_ReadTime(void);
void RTC_WriteTime(void);
