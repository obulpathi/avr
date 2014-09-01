void usart1_init(unsigned int baud, unsigned char frame_format)
{
	/* Set baud rate */
	UBRR1H = (unsigned char)(baud>>8);
	UBRR1L = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format */
	UCSR1C = frame_format;

	return;
}

unsigned char usart1_rx(void)
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) );
	/* Get and return received data from buffer */
	
	return UDR1;
}

void usart1_tx(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );
	/* Put data into buffer, sends the data */
	UDR1 = data;

	return;
}

void usart1_tx_hex(unsigned char c)
{
	unsigned char hex;

	hex = (c >> 4);
	if(hex < 10)
		usart1_tx( hex + 48 );
	else
		usart1_tx( hex + 55 );
		
	hex = (c & 0x0F);
	if(hex < 10)
		usart1_tx( hex + 48 );
	else
		usart1_tx( hex + 55 );
	
	return;
}

void usart1_print(unsigned char datac[], int length)
{
	int i;
	unsigned char c;

	for( i = 0 ; i < length ; i++ )
	{
		c = datac[i];
		usart1_tx( c );
	}

	return ;
}

void usart1_flush(void)
{
	unsigned char dummy;
	while ( UCSR1A & (1<<RXC1) ) dummy = UDR1;

	return;
}

void usart1_deinit(void)
{
	usart1_flush();
	UCSR1B = 0x00;
	
	return;
}
