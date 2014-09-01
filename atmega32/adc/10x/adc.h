#include<inttypes.h> 

#define x10_10 0x09
#define x200_10 0x
#define left_adjust ( 1 << ADLAR )
#define right_adjust ( 0 << ADLAR )

void adc_init(void);
uint8_t adc_read(void);


