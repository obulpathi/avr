void USART_Init( unsigned int baud, unsigned char frame_format )
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

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	
	return UDR;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;

	return;
}

void USART_DeInit( void )
{
	// write the code for de initializing the USAT here ...
	// deinit both the Tx and Rx
	// celar the buffer contents if any ...
	// USART_Flush();
	
	return;
}

void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;

	return;
}
