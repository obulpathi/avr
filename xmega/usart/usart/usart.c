#include <stdio.h>
#include <avr/io.h> 
 
static void uart_init (void);
 
 


void main () { 
   InitializePLL(); 

   _delay_ms(40); 

   InitializeUSARTC0(); 

   _delay_ms(40); 

   while (! (USARTC0.STATUS & USART_DREIF_bm)) { 
      // wait 
   } 

   USARTC0.DATA = 0xAA; 

   for (;;); 
} 

void InitializeUSARTC0() { 
   // Baud Rate variables 
   // (3317, -4) = 9600 (at 32Mhz fper) 
   // (3301, -5) = 19200 
   // (2094, -7) = 115200 
   int bsel = 3317; 
   int bscale = -4; 

   // Set Tx pin to an output 
   PORTC_DIR |= PIN3; 

   // Set Baud Rate 
   USARTC0.BAUDCTRLB = ((unsigned char)(bscale & 0x0F) << 4) | ((unsigned char)(bsel >> 8) & 0x0F); 
   USARTC0.BAUDCTRLA = (unsigned char)(bsel & 0xFF); 

   // Set Control Reg C 
   // CMODE = 00 (Async USART) 
   // PMODE = 00 (No Parity) (10 = Even, 11 = Odd) 
   // SBMODE = 0 (1-Stop) (1 = 2-Stop Bits) 
   // CHSIZE = 011 (8bit) 
   USARTC0.CTRLC = (USARTC0.CTRLC & ~USART_CHSIZE_gm) | USART_CHSIZE_8BIT_gc; 

   // Set Control Reg B 
   // Enable Rx and Tx 
   USARTC0.CTRLB = (USART_RXEN_bm | USART_TXEN_bm); 
} 

// Init USART.  Transmit only (we're not receiving anything)
// We use USARTC0, transmit pin on PC3.
// Want 9600 baud. Have a 2 MHz clock. BSCALE = 0
// BSEL = ( 2000000 / (2^0 * 16*9600)) -1 = 12
// Fbaud = 2000000 / (2^0 * 16 * (12+1))  = 9615 bits/sec
void USART_Init(unsigned int baudrate)
{
    // Set the TxD pin high - set PORTC DIR register bit 3 to 1
    PORTC.OUTSET = PIN3_bm;
 
    // Set the TxD pin as an output - set PORTC OUT register bit 3 to 1
    PORTC.DIRSET = PIN3_bm;
 
    // Set baud rate & frame format
    USARTC0.BAUDCTRLB = 0;			// BSCALE = 0 as well
    USARTC0.BAUDCTRLA = 12;
 
    // Set mode of operation
    USARTC0.CTRLA = 0;				// no interrupts please
    USARTC0.CTRLC = 0x03;			// async, no parity, 8 bit data, 1 stop bit
 
    // Enable transmitter only
    USARTC0.CTRLB = USART_TXEN_bm;
}



	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<USBS)|(3<<UCSZ0);
}

void USART_Tx(unsigned char data)
{
	/* Wait for empty transmit buffer */
    while ( !( USARTC0.STATUS & USART_DREIF_bm) );
 
   	/* Put data into buffer, sends the data */
    USARTC0.DATA = data; 
}

unsigned char USART_Rx(void)
{
	/* Wait for data to be received */
	while (!(UCSRnA & (1<<RXCn)));
	
	/* Get and return received data from buffer */
	return UDRn;
}

void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSRnA & (1<<RXCn) ) dummy = UDRn;
}
