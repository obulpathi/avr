/************************************/
/****** USART BLOCKING IO ***********/
/************************************/

#include<avr/io.h>

void USART_Init(void);
void USART_transmit(char c);
//char USART_receive(void);

void delay_ms(int ms);

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x0F;

	USART_Init();
	while(1)
	{
		PORTA = ~PORTA;
		USART_transmit('4');
		delay_ms(1000);
	}
	
	//while(1);

	return 0;
}

void USART_Init(void)
{
	//set baud rate
	UBRRH = 0x00;
	UBRRL = 0x19;
	//enable Tx
	UCSRB = (1 << TXEN);
	//set frame format
	//DEFAULT (frame format is 8N1)

	return;
}

void USART_transmit(char data)
{
	//clear flag
	UCSRA = UCSRA | (1 << TXC);
	//transmit data
	UDR = data;
	//check for buffer empty
	while(!(UCSRA & (1 << TXC)));

	return;
}

char USART_receive(void)
{
	return;
}

void delay_ms(int ms)
{
	int i,j;
	
	for(i = 0; i <   ms; i++)
	for(j = 0; j < 1000; j++)
	{
		//do nothing;
	}
		
	return;
}
