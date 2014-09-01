void usart_init(unsigned int baud)
{
	/* Set baud rate */
	UBRR = (unsigned char)baud;
	/* Enable receiver and transmitter */
	/* Set frame format */
	UCR = ( 1 << RXEN ) | ( 1 << TXEN );

	return;
}

unsigned char usart_rx_byte(void)
{
	/* Wait for data to be received */
	while ( !( USR & ( 1 << RXC ) ) );
	/* Get and return received data from buffer */
	
	return UDR;
}

void usart_tx_byte(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( USR & ( 1 << UDRE ) ) );
	/* Put data into buffer, sends the data */
	UDR = data;

	return;
}

void usart_flush(void)
{
	unsigned char dummy;
	while ( USR & ( 1 << RXC ) ) dummy = UDR;

	return;
}

void usart_deinit(void)
{
	usart_flush();
	UCR = 0x00;
	
	return;
}
