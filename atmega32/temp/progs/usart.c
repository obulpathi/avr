#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include "usart.h"

void usart_init0(unsigned char baud)
{
	// Set Baud Rate
	UBRRH=0x00;
	UBRRL=(unsigned char)baud;
	// Enable Receiver and Transmitter
	UCSRA=0x02;	// 0000 0010; U2X enabled
	UCSRB=0x98;	// 1001 1000; Receiver and Transmitter enabled
	UCSRC=0x86;	// 1000 0110; Access UCSRC, Asynchronous 8N1
}

unsigned char usart_getc0(void)
{
	// Wait for data to be received
	while(!(UCSRA & (1<<RXC)));
	// Get and return received data from buffer
	return UDR;
}

void usart_putc0(unsigned char data)
{
	// Wait for empty tranmit buffer
	while(!(UCSRA & (1<<UDRE)));
	// Put data into buffer, sends the data
	UDR=data;
}

void usart_puti0(int data)
{
	int num[5],i=0,j=0;
	for(;;)
	{
	   num[i++]=data%10;
	   data=data/10;
	   if(data==0)
	      break;
        }
	for(j=i-1;j>=0;j--)
	{
	   while(!(UCSRA & (1<<UDRE)));
	   UDR=(num[j]+48);
	}
}
