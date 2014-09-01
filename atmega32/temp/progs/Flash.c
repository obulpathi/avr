#include <avr/io.h>
#include "Dflash.h"
#include "Compress.h"
#include "Compress.c"
#include "Dflash.c"
#include "usart.h"

void write_firstdata(void);
void write_metadata(void);
void flash_write(void);
void flash_read(unsigned int page);
void flash_write_other(unsigned char Data_Array[]);
unsigned int get_freememory(void);
void get_metadata();
//declaring as global variables
unsigned int node_id=1;
unsigned int databyte=0;
unsigned int Bytecount=0;
unsigned int datacount=0;
unsigned int ByteAddress=0;
unsigned char Received;
int main(void)
{	
	DDRA=0xFF;
	DFlashInit();  
	//write_firstdata();
	//Received=ReadFlashDF(2,1);
	 //=~Received;
	flash_write();
	//flash_read(2);
	
	//get_metadata();
	//flash_write_other(data);
	//return 0;
	//Received=ReadBufferDF(0,0);
	//PORTA=~Received;
}
unsigned int get_freememory()
{
	PageAddress=((int)ReadFlashDF(1,0))*256;
	PageAddress+=(int)ReadFlashDF(1,1);
	return (5127-PageAddress);
	
}
void get_metadata()
{
	int i=0,j=0,k=0,byte=0;
	DDRA=0xFF;
	DFlashInit();
	usart_init0(USART_BAUDRATE(4800,1));
	for(;;)
	{
		//Received=ReadFlashDF(1,1);
		//PORTA=~Received;
		byte=((int)ReadFlashDF(2,0))*256;;
		byte=byte+((int)ReadFlashDF(2,0));
		PORTA=~byte;
		/*for(i=0;i<byte;i++)
		{
			Received=ReadFlashDF(2,i);
			for(j=0;j<30;j++)
			{
				for(k=0;k<31000;k++)
					PORTA=~Received;
			}
			usart_putc0(Received);
		}
		usart_putc0(13);usart_putc0(10);*/
	}
}
void flash_write_other(unsigned char Data_Array[])
{
	int temp,Byte=0,i=0,j=0;
	int node_id_other=0;
	DFlashInit();
	temp=(int)Data_Array[3];
	WriteBufferDF_Array(ByteAddress,packed_bits,1,temp);
	PageAddress=((int)ReadFlashDF(1,0))*256;
	PageAddress+=(int)ReadFlashDF(1,1);
	Bytecount+=(int)ReadFlashDF(1,2);
	WriteBufferToPageDF(PageAddress,1);
		
	
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	
	node_id_other=(int)Data_Array[0];
	///Updating metadata
	Byte=(unsigned int)ReadFlashDF(2,0)*256;
	Byte+=(unsigned int)ReadFlashDF(2,1);
	Bytecount+=(unsigned int)Data_Array[2];
	PORTA=~Byte;
	//Updating Metadata
	for(i=0;i<Byte;i++)
	{
		Received=ReadFlashDF(2,i);
		for(j=0;j<1000;j++){}
		WriteBufferDF(i,Received,0);
	}
	
	WriteBufferDF(Byte,(unsigned char)node_id,0);
	Byte++;
		WriteBufferDF(Byte,Data_Array[3],0);
		Byte++;
		WriteBufferDF(Byte,Data_Array[4],0);
		Byte++;
		WriteBufferDF(Byte,Data_Array[5],0);
		Byte++;
		WriteBufferDF(Byte,Data_Array[6],0);
		Byte++;
	if((int)Data_Array[2] & 1)
	{
		extra_timebit=((int)Data_Array[7]) & 128;
		WriteBufferDF(Byte,(unsigned char)extra_timebit,0);
		
	}
	else
	{
		WriteBufferDF(Byte,Data_Array[7],0);
	}
	Byte++;
	WriteBufferDF(Byte,((unsigned char)(PageAddress/256)),0);
	Byte++;
	WriteBufferDF(Byte,(unsigned char)(PageAddress),0);
	Byte++;
	
	WriteBufferDF(0,(unsigned char)(Byte/256),0);
	WriteBufferDF(1,(unsigned char)(Byte),0);
	WriteBufferToPageDF(2,0);
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	PageAddress++;
	WriteBufferDF_Integer(0,(PageAddress/256),1);
	WriteBufferDF_Integer(1,PageAddress,1);
	WriteBufferDF_Integer(2,Bytecount,1);
	WriteBufferToPageDF(1,1);
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	
	
	//write nodeid,timestamp,pgno
	
}
void flash_read(unsigned int page)
{
	int i=0,j=0,k=0;
	DDRA=0xFF;
	DFlashInit();
	usart_init0(USART_BAUDRATE(4800,1));
	for(;;)
	{
		//Received=ReadFlashDF(1,1);
		//PORTA=~Received;
		
		for(i=0;i<2;i++)
		{
			Received=ReadFlashDF(page,i);
			for(j=0;j<30;j++)
			{
				for(k=0;k<31000;k++)
					PORTA=~Received;
			}
			usart_putc0(Received);
		}
		for(i=8;i<17;i++)
		{
			Received=ReadFlashDF(page,i);
			for(j=0;j<30;j++)
			{
				for(k=0;k<31000;k++)
					PORTA=~Received;
			}
			usart_putc0(Received);
		}
		usart_putc0(13);usart_putc0(10);
	}
}
void flash_write(void)
{
	//unsigned char GPS_Data[38]={"010949,3242.9234,S,94920.0202,W,080506"};
	unsigned char GPS_Data[38]={"020945,2456.9493,S,83812.2522,E,120400"};
	unsigned char Time_Stamp[13]={"031103,122359"};
	unsigned char Temp_Data[6]={"-54.27"};
	unsigned char Humidity_Data[5]={"97.10"};
	unsigned char Orientation_Data[7]={"-34,+16"};
	unsigned char temp;
	int j=0,k=0,i=0;
	unsigned int Byte=0;
	DDRA=0xFF;
	DFlashInit();
	usart_init0(USART_BAUDRATE(4800,1));
	datacount=0;
	if(0)//GPS_Enabled)
	{
		databyte=databyte | 1;
		datacount+=12;
	}
	else//Time Stamp
	{
		databyte=databyte | 2;
		datacount+=5;
	}
	if(1)//Temp_Enabled)
	{
		databyte=databyte | 4;
		datacount+=2;
		
	}
	if(0)//Humid_Enabled)
	{
		databyte=databyte | 8;
		datacount+=2;
		
	}
	if(1) //Orientation_X_Enabled)
	{
		databyte=databyte | 16;
		datacount+=2;
	}
	if(0) //LDR_Enabled)
	{
		databyte=databyte | 32;
		datacount+=2;
	}
	
	write_metadata();//To write nodeid,databyte & datacount
	
	
	if(databyte & 1)
	{
		Compress_GPS(GPS_Data);
		WriteBufferDF_Array(ByteAddress,packed_bits,1,12);
		ByteAddress+=12;
	}
	if(databyte & 2)
	{
		Compress_TimeStamp(Time_Stamp);
		WriteBufferDF_Array(ByteAddress,packed_bits,1,5);
		ByteAddress+=5;
		
	}
	if(databyte & 4)
	{
		Compress_Temperature(Temp_Data);
		WriteBufferDF_Array(ByteAddress,packed_bits,1,2);
		ByteAddress+=2;
  	}
	if(databyte & 8)
	{
		Compress_Humidity(Humidity_Data);
		WriteBufferDF_Array(ByteAddress,packed_bits,1,2);
		
		ByteAddress+=2;
	}		
	if(databyte & 16)
	{
		Compress_Orientation(Orientation_Data);
		WriteBufferDF_Array(ByteAddress,packed_bits,1,2);
		ByteAddress+=2;
	}
	
	PageAddress=(unsigned int)(ReadFlashDF(1,0))*256;
	PageAddress+=(unsigned int)ReadFlashDF(1,1);
	Bytecount+=(unsigned int)ReadFlashDF(1,2);
	WriteBufferToPageDF(PageAddress,1);
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	/*for(i=0;i<10;i++)
	{
		Received=ReadFlashDF(PageAddress,i);
		for(k=0;k<30;k++)
		for(j=0;j<30000;j++)
		{
			PORTA=~(int)Received;
		}

		
	}*/
	
	///Updating metadata
	Byte=(unsigned int)ReadFlashDF(2,0)*256;
	Byte+=(unsigned int)ReadFlashDF(2,1);
	for(i=0;i<Byte;i++)
	{
		Received=ReadFlashDF(2,i);
		for(j=0;j<1000;j++){}
		WriteBufferDF(i,Received,0);
	}
	
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	WriteBufferDF(Byte,(unsigned char)node_id,0);
	Byte++;
	temp=ReadFlashDF(PageAddress,3);
	WriteBufferDF(Byte,temp,0);
	Byte++;
	temp=ReadFlashDF(PageAddress,4);
	WriteBufferDF(Byte,temp,0);
		Byte++;
	temp=ReadFlashDF(PageAddress,5);
		WriteBufferDF(Byte,temp,0);
		Byte++;
	temp=ReadFlashDF(PageAddress,6);
		WriteBufferDF(Byte,temp,0);
		Byte++;
	temp=ReadFlashDF(PageAddress,2);
	if((int)temp & 1)
	{
		temp=ReadFlashDF(PageAddress,7);
		extra_timebit=((int)temp) & 128;
		WriteBufferDF(Byte,(unsigned char)extra_timebit,0);
				
	}
	else
	{
		temp=ReadFlashDF(PageAddress,7);
		WriteBufferDF(Byte,temp,0);
		
	}
	Byte++;
	WriteBufferDF_Integer(Byte,(unsigned char)(PageAddress/256),0);
	Byte++;
	WriteBufferDF(Byte,(unsigned char)(PageAddress),0);
	Byte++;
	
	WriteBufferDF(0,(unsigned char)(Byte/256),0);
	WriteBufferDF(1,(unsigned char)(Byte),0);
	
	WriteBufferToPageDF(2,0);
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	PageAddress++;
	WriteBufferDF_Integer(0,(PageAddress/256),1);
	WriteBufferDF_Integer(1,PageAddress,1);
	WriteBufferDF_Integer(2,Bytecount,1);
	WriteBufferToPageDF(1,1);
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
	PORTA=~(ReadFlashDF(1,1));
	
	
}
void write_metadata(void)
{
	DDRA=0xFF;
	DFlashInit();
	Received=ReadFlashDF(1,0);
	PageAddress=((int)Received)*8;
	Received=ReadFlashDF(1,1);
	PageAddress+=((int)Received);;
	datacount+=3;
	WriteBufferDF_Integer(0,node_id,1);
	WriteBufferDF_Integer(1,databyte,1);
	WriteBufferDF_Integer(2,datacount,1);
	ByteAddress=3;
	Bytecount+=datacount;
	
}
void write_firstdata(void)
{
	int Byte_metadata=0;
	int i=0,j=0;
	Byte_metadata=8;
	DFlashInit();
	PageAddress=4;
	WriteBufferDF_Integer(0,node_id,1); 
	WriteBufferToPageDF(0,1);
	
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	WriteBufferDF_Integer(0,PageAddress/256,1);
	WriteBufferDF_Integer(1,PageAddress,1);
	WriteBufferDF_Integer(2,Bytecount,1);
	WriteBufferToPageDF(1,1);
	
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	WriteBufferDF_Integer(0,(Byte_metadata/256),1);
	WriteBufferDF_Integer(1,(Byte_metadata),1);
	WriteBufferToPageDF(2,1);
	for(i=0;i<100;i++)
	for(j=0;j<30000;j++)
	{}
	
}
