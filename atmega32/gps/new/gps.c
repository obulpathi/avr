int good_data=0,print=0,time=0,delayed=0,FREQUENCY=2,base=0;
char data[38],gpstime[6],gpsdate[6],gpslat[10],gpslong[11],a;

// cehck for GPRMC
int checkGPRMC()
{
	if(usart_rx() == '$')
	if(usart_rx() == 'G')
	if(usart_rx() == 'P')
	if(usart_rx() == 'R')
	if(usart_rx() == 'M')
	if(usart_rx() == 'C')
		return 1;

	return 0;
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
