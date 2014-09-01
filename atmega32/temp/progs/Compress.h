
#ifndef __Compress_H
#define __Compress_H

unsigned char packed_bits[12];
unsigned int PageAddress=0;
// Function prototypes

void Compress_GPS(unsigned char Data_Array[]);
void convert_binary(int temp,int par,int begin,int flag);
void convert_character(void);
int C2I(unsigned char data);
void Compress_Temperature(unsigned char Data_Array[]);
void Compress_Humidity(unsigned char Data_Array[]);
void Compress_Orientation(unsigned char Data_Array[]);
void Compress_TimeStamp(unsigned char Data_Array[]);
void Compress_Humidity(unsigned char Data_Array[]);
void Compress_Orientation(unsigned char Data[]);



#endif
