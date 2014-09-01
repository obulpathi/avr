// finalized code ... done K ...

// base functions

// check for GPRMC
int gps_check_gprmc(void)
{
	// lock GPRMC start
	while(usart_rx() != '$');
	if(usart_rx() == 'G')
	if(usart_rx() == 'P')
	if(usart_rx() == 'R')
	if(usart_rx() == 'M')
	if(usart_rx() == 'C')
		return 0;

	return 1;
}

// check for data validity
int gps_check_data(void)
{
	int i;
	
	// check for A
	for( i = 0 ; i < 11 ; i++ )
		usart_rx();
	if( usart_rx() == 'A' )
		return 0;
	
	return 2;
}

// interface functions

// initialze the gps
void gps_init(void)
{
	// switch on power
	// intitialize the ports
	usart_init( USART_BAUD_4800, USART_FRAME_8N1 );

	return;
}

// check for data validity
int gps_check(void)
{
	// check for GPRMC
	if( gps_check_gprmc() )
		return 1;
	
	// check for data validity
	if( gps_check_data() )
		return 2;
		
	return 0;
}

// read and copy the data
int gps_read(void)
{
	int i;

	// lock GPRMC
	while( gps_check_gprmc() );
	// filter the .
	usart_rx();
	// copy time
	for( i = 0 ; i < 6 ; i++ )
		gpstime[i] = usart_rx();
	// filter 
	for( i = 0 ; i < 4 ; i++ )
		usart_rx();
	// check for A ... return this value ????
	usart_rx() == 'A';
	// filter ,
	usart_rx();
	// copy latitude
	for( i = 0 ; i < 4 ; i++ )
		gpslat[i] = usart_rx();
	// filter .
	usart_rx();
	// copy latitude
	for( i = 4 ; i < 6 ; i++ )
		gpslat[i] = usart_rx();
	// filter
	for( i = 0 ; i < 4 ; i++ )
		usart_rx();
	// copy longitude
	for( i = 0 ; i < 5 ; i++ )
		gpslong[i] = usart_rx();
	// filter .
	usart_rx();
	// copy longitude
	for( i = 5 ; i < 7 ; i++ )
		gpslong[i] = usart_rx();
	// filter
	for( i = 0 ; i < 12 ; i++ )
		usart_rx();
	// copy date
	for( i = 0 ; i < 6 ; i++ )
		gpsdate[i] = usart_rx();
			
	return 0;
}

// deinitialize the gps
void gps_deinit(void)
{
	// deintialize ports
	usart_deinit();
	// switch off power

	return;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// END end END ... 

// whats this?????????????
void setFrequency(int time)
{
    FREQUENCY=time;
}
