#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>

int good_data=0,print=0,time=0,delayed=0,FREQUENCY=2,base=0;
char data[38],gpstime[6],gpsdate[6],gpslat[10],gpslong[11],a;

int gps(void);
void continuous(void);
void setFrequency(int);
int checkGPRMC(void);
int read_GPS(void);
void print_gps_data(void);
void getTime(void);
void getDate(void);
void getLatitude(void);
void getLongitude(void);

void InitUART( unsigned char baudrate );
unsigned char ReceiveByte( void );
void TransmitByte( unsigned char data );

/*Initialize UART */
void InitUART( unsigned char baudrate )
{
/* Set baud rate */
UBRRH = (unsigned char)(baudrate>>8);
UBRRL = (unsigned char)baudrate;

UCSRB = (1<<RXEN)|(1<<TXEN);  /* Enable receiver and transmitter */
UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);   /* Set frame format: 8data, 2stop bit */
//        UCSRA = 0x00;
}

/* Read and write functions */
unsigned char ReceiveByte( void )
{
while ( !(UCSRA & (1<<RXC)) )  /* Wait for data to be received */
;
return UDR;  /* Get and return received data from buffer */
}

void TransmitByte( unsigned char data )
{
while ( !( UCSRA & (1<<UDRE)))  /* Wait for empty transmit buffer */
;
UDR = data;  /* Put data into buffer, sends the data */
}



char usart_getc0()
{
   return(ReceiveByte());
}

int checkGPRMC()
{
    int check=0;
    char b,c,d,e,f,g;
    b=usart_getc0();
    if(b=='$')
    { 
//      TransmitByte('A');
      c=usart_getc0();
      if(c=='G')
      {
//        TransmitByte('N');
        d=usart_getc0();
        if(d=='P')
        {
//          TransmitByte('U');
          e=usart_getc0();
          if(e=='R')
          {
//            TransmitByte('N'); 
            f=usart_getc0();
            if(f=='M')
            {
//              TransmitByte('A');
              g=usart_getc0();
              if(g=='C')
              {
//                 TransmitByte('G');
                 check=1;
              }
            }
          }
        }
      }
    }
    return(check);
}

int main(void)
{
   int  chk=0;
   InitUART( 12 );        // 4800 at 4
   gps();
}

int gps()
{
int status=1,c;
   for(;;)
   {

        status=read_GPS();
        while(status==0)// Do not proceed from this point unless $GPRMC is obtained.
           status=read_GPS();


        if(status==1)
           TransmitByte('V');
	  
        if(status==2)
        {
             for(c=0;c<38;c++)
              TransmitByte(data[c]);
           TransmitByte(13);TransmitByte(10);
		TransmitByte(13);
             /*getLatitude();
                for(c=0;c<=9;c++)
                  TransmitByte(gpslat[c]);
             TransmitByte(13);
             getLongitude();
                for(c=0;c<=10;c++)
                  TransmitByte(gpslong[c]);
             TransmitByte(13);
             getTime();
                for(c=0;c<6;c++)
                  TransmitByte(gpstime[c]);
             TransmitByte(13);
             getDate();
                for(c=0;c<6;c++)
                  TransmitByte(gpsdate[c]);
             TransmitByte(13);*/
         }
    }
}


int read_GPS()
{
    int cnt=0;
    if(checkGPRMC()==1)
    {
       if(good_data==0)
       {
           while(cnt!=11)
           {
              usart_getc0();
              cnt++;
	   }
	   a=usart_getc0();
	   if(a=='A')
	   {
		TransmitByte('H');
                TransmitByte(a);
		TransmitByte('H');
		good_data=1;
            	return 0;   
	   }
	   else
	   {
		TransmitByte('H');
                TransmitByte(a);
                TransmitByte('H');
	       time++;
	       return 1;
	   }
       }
       else
       {
	   print_gps_data();
	   return 2;
       }
    }
   else
       return 0;
}

void print_gps_data()
{
    int cnt=0,i=0,j=0;
    usart_getc0();
    while(1)
    {
       char a=usart_getc0();
       if(a==',')
	  cnt++;
       if((cnt==1)&&(a=='V'))
       {
	   good_data=0;
	   time=0;
       }
       if(cnt==9)
	  break;
       if(!((cnt==1)||(cnt==6)||(cnt==7)))
          data[i++]=a;
    }
}

void getLatitude()
{
   int i;
   for(i=0;i<9;i++)
      gpslat[i]=data[i+7];
   gpslat[9]=data[17];
}

void getLongitude()
{
    int i;
    for(i=0;i<10;i++)
       gpslong[i]=data[i+19];
    gpslong[10]=data[30];
}

void getTime()
{
    int i;
    for(i=0;i<6;i++)
	gpstime[i]=data[i];
}

void getDate()
{
   int i;
   for(i=0;i<6;i++)
	gpsdate[i]=data[i+32];
}

void setFrequency(int time)
{
    FREQUENCY=time;
}
