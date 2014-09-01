void usart0_init(unsigned int baud, unsigned char frame_format)
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format */
	UCSR0C = frame_format;

	return;
}

unsigned char usart0_rx(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	
	return UDR0;
}

void usart0_tx(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;

	return;
}

void usart0_tx_hex(unsigned char c)
{
	unsigned char hex;

	hex = (c >> 4);
	if(hex < 10)
		usart0_tx( hex + 48 );
	else
		usart0_tx( hex + 55 );
		
	hex = (c & 0x0F);
	if(hex < 10)
		usart0_tx( hex + 48 );
	else
		usart0_tx( hex + 55 );
	
	return;
}

void usart0_print(unsigned char datac[], int length)
{
	int i;
	unsigned char c;

	for( i = 0 ; i < length ; i++ )
	{
		c = datac[i];
		usart0_tx( c );
	}

	return ;
}

void usart0_flush(void)
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;

	return;
}

void usart0_deinit(void)
{
	usart0_flush();
	UCSR0B = 0x00;
	
	return;
}
