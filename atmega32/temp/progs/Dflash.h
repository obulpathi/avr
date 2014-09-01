#ifndef __DFLASH_H
#define __DFLASH_H

// Function prototypes

void DFlashInit(void);
void GetPageToBufferDF(unsigned int Page, unsigned char Buffer);
void WriteBufferToPageDF(unsigned int Page, unsigned char Buffer);
void WriteBufferDF(unsigned int Address, unsigned char Data, unsigned char Buffer);
void WriteBufferDF_Integer(unsigned int Address, unsigned int Data, unsigned char Buffer);
void WriteBufferDF_Array(unsigned int Address, unsigned char Data_Array[], unsigned char Buffer,unsigned int n);
void FlashToBufferDF(unsigned int Page,unsigned char Buffer);
unsigned char ReadBufferDF(unsigned int Address, unsigned char Buffer);
extern unsigned char ReadFlashDF(unsigned int Page, unsigned int Byte);
void BlockEraseDF(void);
void ReadyBusyDF(void);     
unsigned char GetStatusDF(void);
void SendByte(unsigned char Send);
unsigned char SendGetByte(unsigned char Send);
unsigned char SendGetByte2(unsigned char Data);


// Bit macro definitions

#define SetBit(x,y) (x |=  (y))   // Set bit y in byte x
#define ClrBit(x,y) (x &= (~y))   // Clear bit y in byte x
#define ChkBit(x,y) (x &   (y))   // Check bit y in byte x

// I/O port bit macroes
// NOTE!! These macroes only work for ports in I/O data space with address below 0x20.

//#define sbi(port,bit)  (port |=  ( 1 << bit ))
//#define cbi(port,bit)  (port &= ~( 1 << bit ))


// Pseudo Port definitions. 
// NOTE!! Change this definition if another port is used.

#define DF_PORT    PORTB // DataFlash PORT Register
#define DF_DIR     DDRB  // DataFlash DDR Register
#define DF_PIN     PINB  // DataFlash PIN Register


// Pseudo SPI Port Pin definitions
// NOTE!! Change this definition if other pins are used.

#define DFSI       (5)  // (output), DataFlash Serial Input
#define DFSO       (6)  // (input), DataFlash Serial Output
#define DFCK       (7)  // (output), DataFlash Serial clock Input
#define DFCS       (4)  // (output), Chip Select for Dataflash


// DataFlash SPI bus macroes

#define INIT_DFCS  {sbi(DF_DIR, DFCS); sbi(DF_PORT, DFCS);}   // Output and set High, i.e. active low
#define INIT_DFCK  {sbi(DF_DIR, DFCK); sbi(DF_PORT, DFCK);}   // Output and set High, i.e. active low in SPI mode 3
#define INIT_DFSI  {sbi(DF_DIR, DFSI); cbi(DF_PORT, DFSI);}   // Output and set Low, i.e. active high

#define INIT_DFSO  {cbi(DF_DIR, DFSO); sbi(DF_PORT, DFSO);}   // Input with pull-up enabled

#define PULSE_DFCK  {cbi(DF_PORT, DFCK); sbi(DF_PORT, DFCK);} // Note, clock is active low for SPI mode 3


#define SET_DFCS    sbi(DF_PORT, DFCS)       // DFCS = High
#define CLR_DFCS    cbi(DF_PORT, DFCS)       // DFCS = Low

#define SET_DFSI    sbi(DF_PORT, DFSI)       // DFSI = High
#define CLR_DFSI    cbi(DF_PORT, DFSI)       // DFCS = Low

#define SET_DFCK    sbi(DF_PORT, DFCK)       // DFCK = High
#define CLR_DFCK    cbi(DF_PORT, DFCK)       // DFCS = Low

#define GET_DFSO    (DF_PIN & ( 1 << DFSO )) // Read DFSO pin


// Define Dataflash commands. For further details, see datasheet.
// Note!! All possible commands are not implemented yet.

#define BLOCK_ERASE         0x50
#define MEM_PAGE_READ       0x52
#define READ_BUFFER1        0x54
#define READ_BUFFER2        0x56
#define MEM_TO_BUFFER1      0x53
#define MEM_TO_BUFFER2      0x55
#define MEM_COMP_BUFFER1    0x60
#define MEM_COMP_BUFFER2    0x61
#define WRITE_BUFFER1       0x84
#define WRITE_BUFFER2       0x87
#define BUFFER1_TO_MEM_WE   0x83
#define BUFFER2_TO_MEM_WE   0x86
#define BUFFER1_TO_MEM_NE   0x88
#define BUFFER2_TO_MEM_NE   0x89
#define MEM_WR_TH_BUFFER1   0x82
#define MEM_WR_TH_BUFFER2   0x85
#define AUTO_RW_TH_BUFFER1  0x58
#define AUTO_RW_TH_BUFFER2  0x59
#define READ_STATUS         0x57

// General DataFlash defines

#define BUFFER1 0
#define BUFFER2 1

// Defines for AT45D021

#define BUFFER_SIZE  528
#define NUM_PAGES   8192

#endif 
