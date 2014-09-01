#define FOSC 2000000 // Clock Speed
#define BAUD 9600
#define (MYUBRR FOSC/16/BAUD-1)

void USART_Init(unsigned int ubrr);
void USART_Tx(unsigned char data);
unsigned char USART_Rx(void);
void USART_Flush( void );
