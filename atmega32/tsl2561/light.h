#define LIGHT_SENSOR 0x52
#define POWER_UP 0x03
#define CONTROL_REG 0x80
#define ADC_CHANNEL0_HIGH 0x0D

void light_init(void);
unsigned char light_read(void);
