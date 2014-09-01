#include <avr/io.h>
#include "Dflash.h"


// This function initializes the ports and resets the DataFlash to
// SPI mode 3

void DFlashInit(void)
{
    // Initialize DataFlash port pins

    INIT_DFCS;
    INIT_DFCK;
    INIT_DFSI;
    INIT_DFSO;

 // SPI mode 3 is used, i.e. enable flash when DFCK is high
    CLR_DFCS;
    SET_DFCS;

}
void FlashToBufferDF(unsigned int Page,unsigned char Buffer)
{
	ReadyBusyDF();
	CLR_DFCS;
	((Buffer) ? SendByte(MEM_TO_BUFFER1) : SendByte(MEM_TO_BUFFER2));
	
	//Send 1 reserved bits + 7 MSB of Pg address
	SendByte((unsigned char) (Page >> 6));
	
	//Send 6 lsb of pg address + 2 dont care bits
	SendByte((unsigned char) (Page << 2));
	
	//Send 8 don't care bits
	SendByte(0);
	
	SET_DFCS;
}
	
// This function writes one byte to one of the page buffers

void WriteBufferDF(unsigned int Address, unsigned char Data, unsigned char Buffer)
{
    // Always wait until DataFlash is ready first
    ReadyBusyDF();
    DDRA=0xFF;
    //PORTA=~Data;
    // Enable dataflash
    CLR_DFCS;

    // Send command for either buffer1 or buffer2
    ((Buffer) ? SendByte(WRITE_BUFFER2) : SendByte(WRITE_BUFFER1));

    // Send 8 don't care bits
    SendByte(0);
    // Send 6 don't care bits + 2 MSB of buffer address
    SendByte((unsigned char) (Address >> 8));
    // Send 8 LSB of buffer address
    SendByte((unsigned char) (Address));
    // Send one byte of data to buffer
    SendByte(Data);
    // Disable dataflash
    SET_DFCS;
    
    //Update_Address(1);
    
}
void WriteBufferDF_Integer(unsigned int Address, unsigned int Data, unsigned char Buffer)
{
    // Always wait until DataFlash is ready first
    ReadyBusyDF();
    DDRA=0xFF;
   // PORTA=~Data;
    // Enable dataflash
    CLR_DFCS;

    // Send command for either buffer1 or buffer2
    ((Buffer) ? SendByte(WRITE_BUFFER2) : SendByte(WRITE_BUFFER1));

    // Send 8 don't care bits
    SendByte(0);
    // Send 6 don't care bits + 2 MSB of buffer address
    SendByte((unsigned char) (Address >> 8));
    // Send 8 LSB of buffer address
    SendByte((unsigned char) (Address));
    // Send one byte of data to buffer
    SendByte((unsigned char)Data);
    // Disable dataflash
    SET_DFCS;
    
    //Update_Address(1);
    
}

void WriteBufferDF_Array(unsigned int Address, unsigned char Data_Array[], unsigned char Buffer, unsigned int n)
{
    int i=0;
    DDRA=0xff;
    ReadyBusyDF();                             
    CLR_DFCS;                                  
    ((Buffer) ? SendByte(WRITE_BUFFER2) : SendByte(WRITE_BUFFER1)); 
    // Send 8 don't care bits
     SendByte(0);      
    // Send 6 don't care bits + 2 MSB of buffer address
    SendByte((unsigned char) (Address >> 8));  
    // Send 8 LSB of buffer address
    SendByte((unsigned char) (Address));       
    // Send one byte of data to buffer
    for(i=0;i<n;i++)
    { SendByte(Data_Array[i]); }
    SET_DFCS;                   
         
} 

void WriteBufferToPageDF(unsigned int Page,unsigned char Buffer)
{
	ReadyBusyDF();
	CLR_DFCS;
	((Buffer) ? SendByte(BUFFER2_TO_MEM_WE) : SendByte(BUFFER1_TO_MEM_WE));
	
	//Send 1 reserved bits + 7 MSB of Pg address
	SendByte((unsigned char) (Page >> 6));
	
	//Send 6 lsb of pg address + 2 dont care bits
	SendByte((unsigned char) (Page << 2));
	
	//Send 8 don't care bits
	SendByte(0);
	
	SET_DFCS;
}
//This function writes one buffer to one page without erasing the contents of the page
void WriteBufferToPageDF_NoErase(unsigned int Page,unsigned char Buffer)
{
	ReadyBusyDF();
	CLR_DFCS;
	((Buffer) ? SendByte(BUFFER2_TO_MEM_NE) : SendByte(BUFFER1_TO_MEM_NE));
	
	//Send 1 reserved bits + 7 MSB of Pg address
	SendByte((unsigned char) (Page >> 6));
	
	//Send 6 lsb of pg address + 2 dont care bits
	SendByte((unsigned char) (Page << 2));
	
	//Send 8 don't care bits
	SendByte(0);
	
	SET_DFCS;
}

unsigned char ReadFlashDF(unsigned int Page, unsigned int Byte)
{
	register unsigned char Data;
	ReadyBusyDF();
	CLR_DFCS;
	
	//Send Command
	SendByte(MEM_PAGE_READ);
	
	//Send 1 reserved bit + 7 MSB of Pg address
	SendByte((unsigned char) (Page >> 6));
	
	//Send 6 LSB of Pg addr + 2 MSB of Byte addr
	SendByte((unsigned char) (Page << 2) | (unsigned char) (Byte >> 8));
	
	//Send 8 LSB of Byte Addr
	SendByte((unsigned char) (Byte));
	
	//Send 32 Dont care bits
	SendByte(0);
	SendByte(0);
	SendByte(0);
	SendByte(0);
	
	Data=SendGetByte(0);
	SET_DFCS;
	return (Data);
	
}
/*unsigned char Continuous_ReadFlashDF(unsigned int Page,unsigned int Byte)
{
	register unsigned char Data;
	ReadyBusyDF();
	CLR_DFCS;
	//Send Command
	SendByte(CONT_MEM_PAGE_READ);
	
	//Send 1 reserved bit + 7 MSB of Pg address
	SendByte((unsigned char) (Page >> 6));
	
	//Send 6 LSB of Pg addr + 2 MSB of Byte addr
	SendByte((unsigned char) (Page << 2) | (unsigned char) (Byte >> 8));
	
	//Send 8 LSB of Byte Addr
	SendByte((unsigned char) (Byte));
	
	//Send 32 Dont care bits
	SendByte(0);
	SendByte(0);
	SendByte(0);
	SendByte(0);
	
	Data=SendGetByte(0);
	SET_DFCS;
	return (Data);
	
}*/
	
	
	//
// This function reads one byte from one of the page buffers

unsigned char ReadBufferDF(unsigned int Address, unsigned char Buffer)
{
    register unsigned char Data;

    // Always wait until DataFlash is ready first
    ReadyBusyDF();

    // Enable dataflash
    CLR_DFCS;

    // Send command for either buffer1 or buffer2
    ((Buffer) ? SendByte(READ_BUFFER2) : SendByte(READ_BUFFER1));

    // Send 8 don't care bits
    SendByte(0);
    // Send 6 don't care bits + 2 MSB of buffer address
    SendByte((unsigned char) (Address >> 8));
    // Send 8 LSB of buffer address
    SendByte((unsigned char) (Address));
    // Send 8 don't care bits
    SendByte(0);

    // Get one byte of data from buffer
    Data = SendGetByte(0);

    // Disable dataflash
    SET_DFCS;

    return (Data);

}


// This function will check if the DF is ready. This done by
// shifting out the first (MSB) bit of the DF status register
// and loop on it intil the device is ready

void ReadyBusyDF(void)
{
    // Enable dataflash
    CLR_DFCS;

    // Send command Read Status Register
    SendByte(READ_STATUS);

    // Shift out ReadyBusy bit
    PULSE_DFCK;

    // Wait until DataFlash is ready
    while (!GET_DFSO)
        {};

    // Disable dataflash
    SET_DFCS;

} // ReadyBusyDF

// This function read the contents of the status register
// and return it to the caller.

unsigned char GetStatusDF(void) // Not tested
{

    register unsigned char Received;

    // Enable dataflash
    CLR_DFCS;

    // Send command Read Status Register
    SendByte(READ_STATUS);

    Received = SendGetByte(0);

    // Disable dataflash
    SET_DFCS;

    return (Received);
}

// This function send out one byte. It does not read anything back
// This is done to save some clock cycles.

void SendByte(unsigned char Send)
{
    register unsigned char BitCount = 8;

    do
    {
        // Send bit to DataFlash (DFSI), MSB first
        if (Send & 0x80)
        {
            SET_DFSI;
        }
        else
        {
            CLR_DFSI;
        }

        // Toggle DFCK pin to send current bit
        PULSE_DFCK;

        // Get next bit to send
        Send <<= 1;
    }while (--BitCount);

}


// This function send one byte and read one byte back.
// It uses a separate varibel for transmit and receive.

unsigned char SendGetByte(unsigned char Send)
{
    register unsigned char Receive;
    register unsigned char BitCount = 8;
    do
    {
        // Need to Shift Receive buffer first
        Receive <<= 1;

        // Send bit to DataFlash (DFSI), MSB first
        if (Send & 0x80)
        {
            SET_DFSI;
        }
        else
        {
            CLR_DFSI;
        }

        // Toggle DFCK pin to send/get current bit
        PULSE_DFCK;

        // Get a bit from DataFlash (DFSO), sent MSB first
        if (GET_DFSO)
        {
            ++Receive;
        }

        // Get next bit to send
        Send <<= 1;
    }while (--BitCount);

    return (Receive);

}

// This function sends one byte and read one byte back.
// It uses one varibel for both transmit and receive.

unsigned char SendGetByte2(unsigned char Data)
{
    register unsigned char BitCount = 8;

    do
    {
        // Send bit to DataFlash (DFSI), MSB first
        if (Data & 0x80)
        {
            SET_DFSI;
        }
        else
        {
            CLR_DFSI;
        }

        // Toggle DFCK pin to send/get current bit
        PULSE_DFCK;

        // Get next bit to send
        Data <<= 1;

        // Get a bit from DataFlash (DFSO), sent MSB first
        if (GET_DFSO)
        {
            ++Data;
        }

    }while (--BitCount);

    return (Data);

}
