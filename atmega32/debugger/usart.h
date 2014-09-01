// baud rates for 1Mhz clock (clock speed dependent)
#define USART_BAUD_2400 25
#define USART_BAUD_4800 12
#define USART_BAUD_9600 6

//frame formats
#define USART_FRAME_8N1 0x86
#define USART_FRAME_8E1 0xA6
#define USART_FRAME_8O1 0xB6
#define USART_FRAME_8N2 0x8E
#define USART_FRAME_8E2 0xAE
#define USART_FRAME_8O2 0xBE

//error definitions
#define USART_FRAME_ERROR 0x00

void USART_Init(unsigned int baud, unsigned char frame_format);
void USART_Transmit(unsigned char c); 
unsigned char USART_Receive(void);
