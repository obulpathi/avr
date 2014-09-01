/* Baudrate settings
   br=baudrate, fosc=clock frequency in megahertz */
#define USART_BAUDRATE(br,fosc)(fosc*125000/br-1)

void usart_init0(unsigned char baud);
void usart_putc0(unsigned char data);
void usart_puti0(int data);
unsigned char usart_getc0(void);
