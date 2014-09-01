#include "avr/iom32.h"
#include "Compress.h"

int buffer[17];
int p=0;
int extra_timebit=0;
unsigned char Data[38];

void Compress_GPS(unsigned char data[])
{
	int i=0,temp=0;
	for(i=0;i<38;i++)	
		Data[i]=data[i];
	//Compress_GPS_Date
		temp=(C2I(Data[32])*10)+C2I(Data[33]);
		convert_binary(temp,5,4,0);
		temp=(C2I(Data[34])*10)+C2I(Data[35]);
		convert_binary(temp,4,8,0);
		temp=(C2I(Data[36])*10)+C2I(Data[37]);
		convert_binary(temp,7,15,0);
		convert_character();
		
	//Compress_GPS_Time();
		temp=(C2I(Data[0])*10)+C2I(Data[1]);
		convert_binary(temp,5,4,0);
		temp=(C2I(Data[2])*10)+C2I(Data[3]);
		convert_binary(temp,6,10,0);
		temp=(C2I(Data[4])*10)+C2I(Data[5]);
		convert_binary(temp,6,16,1);
		convert_character();
		
		
	//Compress_GPS_Latitude_Direction();
		buffer[0]=extra_timebit;
		if(Data[17]=='N')
			buffer[1]=0;
		else
			buffer[1]=1;

		if(Data[30]=='E')
			buffer[2]=0;
		else
			buffer[2]=1;
		buffer[3]=0;

		temp=(C2I(Data[7])*10)+C2I(Data[8]);
		convert_binary(temp,7,10,0);
		temp=(C2I(Data[9])*10)+C2I(Data[10]);
		convert_binary(temp,7,17,0);
		convert_character();

		temp=(C2I(Data[9])*10)+C2I(Data[10]);
		convert_binary(temp,7,1,0);
		temp=(C2I(Data[12])*10)+C2I(Data[13]);
		convert_binary(temp,7,8,0);
		temp=(C2I(Data[14])*10)+C2I(Data[15]);
		convert_binary(temp,7,15,0);
		convert_character();

	//Compress_GPS_Longitude();
		temp=(C2I(Data[19])*10)+C2I(Data[20]);
		convert_binary(temp,7,6,0);
		temp=(C2I(Data[21])*10)+C2I(Data[22]);
		convert_binary(temp,7,13,0);
		temp=(C2I(Data[23]));
		convert_binary(temp,4,17,0);
		convert_character();

		temp=(C2I(Data[23]));
		convert_binary(temp,4,1,0);
		temp=(C2I(Data[25])*10)+C2I(Data[26]);
		convert_binary(temp,7,8,0);
		temp=(C2I(Data[27])*10)+C2I(Data[28]);
		convert_binary(temp,7,15,0);
		convert_character();	
	//Uncompress_GPS();
}
void Compress_TimeStamp(unsigned char data[])
{
	int temp=0,i=0,j=0,k=0;
	unsigned char Received;
	for(i=0;i<13;i++)	
		Data[i]=data[i];
	temp=(C2I(Data[0])*10)+C2I(Data[1]);
	convert_binary(temp,5,4,0);
	temp=(C2I(Data[2])*10)+C2I(Data[3]);
	convert_binary(temp,4,8,0);
	temp=(C2I(Data[4])*10)+C2I(Data[5]);
	convert_binary(temp,7,15,0);
	p=0;
	
	convert_character();
	temp=(C2I(Data[7])*10)+C2I(Data[8]);
	convert_binary(temp,5,4,0);
	temp=(C2I(Data[9])*10)+C2I(Data[10]);
	convert_binary(temp,6,10,0);
	temp=(C2I(Data[11])*10)+C2I(Data[12]);
	convert_binary(temp,6,16,0);
	convert_character();
	packed_bits[p]=(char)buffer[16];
	p++;
	/*for(i=0;i<5;i++)
		{
		Received=packed_bits[i];
		for(k=0;k<30;k++)
		for(j=0;j<30000;j++)
		{
			PORTA=~(int)Received;
		}

		
		}*/
}
void convert_character(void)
{
 	    int bit=0,power=1,b=0;
	    //for(b=0;b<16;b++)
	  //  	printf("-%d-",buffer[b]);
 	    for(b=7;b>=0;b--)
	    {
			bit+=buffer[b]*power;
			power*=2;
	    }
	    packed_bits[p]=(char)bit;p++;
	    bit=0;power=1;
	    for(b=15;b>7;b--)
	    {
			bit+=buffer[b]*power;
			power*=2;
	    }
	    packed_bits[p]=(char)bit;p++;
}

void convert_binary(int temp,int par,int begin,int flag)
{
    int i=0;
    for(i=0;i<par;i++)
    {
		if((begin<16) && (begin >= 0))
			buffer[begin]=temp%2;
		if((flag==1) && (begin==16))
			extra_timebit=temp%2;
		if((flag==0) && (begin==16))			
			buffer[begin]=temp%2;
		temp=temp/2;
		begin--;

    }
}

int C2I(unsigned char data)
{
	return ((int)data-48);
}

void Compress_Temperature(unsigned char data[])
{
	int b=0,temp=0;
	for(b=0;b<6;b++)
		Data[b]=data[b];
		
	buffer[0]=0;
	if(Data[0]=='+') //+ represented as 0
		buffer[1]=0;
	else
		buffer[1]=1;
	temp=(C2I(Data[1])*10)+C2I(Data[2]);
	convert_binary(temp,7,8,0);
	temp=(C2I(Data[4])*10)+C2I(Data[5]);
	convert_binary(temp,7,15,0);
	p=0;
	convert_character();
	//Uncompress_Temp();
	
}
void Compress_Humidity(unsigned char data[])
{
	int b=0,temp=0;
	for(b=0;b<5;b++)
		Data[b]=data[b];
		
	buffer[0]=0;buffer[1]=0;
	temp=(C2I(Data[0])*10)+C2I(Data[1]);
	convert_binary(temp,7,8,0);
	temp=(C2I(Data[3])*10)+C2I(Data[4]);
	convert_binary(temp,7,15,0);
	p=0;
	convert_character();
	//Uncompress_Humidity();
	
}
void Compress_Orientation(unsigned char data[])
{
	int b=0,temp=0;
	for(b=0;b<7;b++)
		Data[b]=data[b];
	if(Data[0]=='+')
		buffer[0]=0; //0 if + and 1 if -
	else
		buffer[0]=1;
	temp=(C2I(Data[1])*10)+C2I(Data[2]);
	convert_binary(temp,7,7,0);
	if(Data[4]=='+')
		buffer[8]=0; //0 if + and 1 if -
	else
		buffer[8]=1;
	temp=(C2I(Data[5])*10)+C2I(Data[6]);
	convert_binary(temp,7,15,0);
	p=0;
	convert_character();
	//Uncompress_Orientation();
	
}
