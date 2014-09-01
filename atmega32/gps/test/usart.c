void usart_init(unsigned int baud, unsigned char frame_format)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format */
	UCSRC = frame_format;

	return;
}

unsigned char usart_rx(void)
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	
	return UDR;
}

void usart_tx(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;

	return;
}

void usart_tx_hex(unsigned char c)
{
	unsigned char hex;

	hex = (c >> 4);
	if(hex < 10)
		usart_tx( hex + 48 );
	else
		usart_tx( hex + 55 );
		
	hex = (c & 0x0F);
	if(hex < 10)
		usart_tx( hex + 48 );
	else
		usart_tx( hex + 55 );
	
	return;
}

void usart_print(unsigned char datac[], int length)
{
	int i;
	unsigned char c;

	for( i = 0 ; i < length ; i++ )
	{
		c = datac[i];
		usart_tx( c );
	}

	return ;
}

void usart_flush(void)
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;

	return;
}

void usart_deinit(void)
{
	usart_flush();
	UCSRB = 0x00;
	
	return;
}
