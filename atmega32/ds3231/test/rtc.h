// module names
#define TIMER	0xD0
#define T100	0x90

// register names
#define RTC_REG_SEC	0x00
#define RTC_REG_MIN	0x01
#define RTC_REG_HOUR	0x02
#define RTC_REG_DAY	0x03
#define RTC_REG_DATE	0x04 
#define RTC_REG_MONTH	0x05
#define RTC_REG_YEAR	0x06
#define RTC_REG_ALARM1_SEC	0x07
#define RTC_REG_ALARM1_MIN	0x08
#define RTC_REG_ALARM1_HR	0x09
#define RTC_REG_ALARM1_DATE	0x0A
#define RTC_REG_ALARM2_MIN	0x0B
#define RTC_REG_ALARM2_HR	0x0C
#define RTC_REG_ALARM2_DATE	0x0D
#define RTC_REG_CTRL	0x0E
#define RTC_REG_STATUS	0x0F
#define RTC_REG_AGE_OFFSET	0x10
#define RTC_REG_TMP_MSB		0x11
#define RTC_REG_TMP_LSB		0x12

// function definitions
#define RTC_START	0x00
#define RTC_BUSY	0x00
#define RTC_EN_INT1	0x01
#define RTC_CLR_INT1	0xFE
#define RTC_DIS_EN_INT1	0xFE
#define RTC_EN_INT2	0x00
#define RTC_DIS_EN_INT2	0x00
#define RTC_CLR_INT2	0x00
#define RTC_STOP	0x80

// mask definitions
#define RTC_BUSY_MASK 0x00

void RTC_Init(void);
char RTC_ReadTime(void);
void RTC_WriteTime(void);
