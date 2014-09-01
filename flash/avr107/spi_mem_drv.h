// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
*
* Atmel Corporation
*
* - File              : spi_mem.h
* - Compiler          : IAR EWAAVR 3.20c
*
* - Support mail      : avr@atmel.com
*
* - Supported devices : All AVR with a SPI interface and SRAM ( 1kB SRAM for 4 Meg SPI memory is recommended) can be used.
*                       
*
* - AppNote           : AVR107 - Basic AVR Drivers for SPI Serial Memory Devices
*
* - Description       :     · Devices : AT25128A/256A, AT25F1024/2048/4096
*                           · Full Serial Memory Functions Support
*                           · Memory Array Burst Read
*                           · Page Burst Write
*                           · Write Protection Detection
*                           · On Going Access Detection
*                           · Non-blocking Write Access
*                           · Access Status Information
*
* $Revision: 1.3 $
* $Date: Wednesday, March 02, 2005 13:33:00 UTC $
*****************************************************************************/

#ifndef __SPI_MEMORY_H
#define __SPI_MEMORY_H


//////////////////////////////////////////////////////////////////////////
// UNCOMMENT THE LINE CORRESPONDING TO THE CONNECTED SPI SERIAL MEMORY 
/////////////////////////////////////////////////////////////////////////
//#define AT25128A
//#define AT25256A
//#define AT25F1024
//#define AT25F2048
//#define AT25F4096


#if (defined(AT25128A) | defined(AT25256A))
  #define EEPROM_TYPE
#endif


#ifdef EEPROM_TYPE
/////////////////////////////////////
// SPI SERIAL EEPROMs (AT25256A/128A) 
/////////////////////////////////////
  #define PAGE_SIZE        64        //! page size
  #define NB_ADDR_BYTE 2             //!< The serial memory has a 2 bytes long address phase
  /////////////////////////////
  // Block Write Protect Bits
  ////////////////////////////
  #define WPB_MASK     0x0C
  #define NONE        (0x00 << 2)
  #define TOP_QUARTER (0x01 << 2)
  #define TOP_HALF    (0x02 << 2)
  #define ALL         (0x03 << 2)
  /////////////////////////////
  // INSTRUCTION CODES
  ////////////////////////////
  #define WREN 0x06
  #define WRDI 0x04
  #define RDSR 0x05
  #define WRSR 0x01
  #define READ 0x03
  #define WRITE 0x02
  /////////////////////////////
  // ADDRESS SPACE
  ////////////////////////////
  #ifdef AT25256A
    #define TOPQ_ADDR 0x6000 //!< Serial memory top quarter address
    #define HALF_ADDR 0x4000 //!< Serial memory half address
    #define TOP_ADDR 0x7FFF  //!< Serial memory top address
  #else
    #define TOPQ_ADDR 0x3000
    #define HALF_ADDR 0x2000
    #define TOP_ADDR 0x3FFF
  #endif
#else
/////////////////////////////////////////
// SPI SERIAL FLASH (AT25F1024/2048/4096) 
/////////////////////////////////////////
  #define PAGE_SIZE        256        //!< The page size
  #define NB_ADDR_BYTE 3 //!< The serial memory has a 2 bytes long address phase
  /////////////////////////////
  // Block Write Protect Bits
  ////////////////////////////
  #define WPB_MASK     0x1C
  #define NONE        (0x00 << 2)
  #define TOP_EIGHTH  (0x01 << 2)
  #define TOP_QUARTER (0x02 << 2)
  #define TOP_HALF    (0x03 << 2)
  #define ALL         (0x04 << 2)
  /////////////////////////////
  // INSTRUCTION CODES
  ////////////////////////////
  #define WREN 0x06
  #define WRDI 0x04
  #define RDSR 0x05
  #define WRSR 0x01
  #define READ 0x03
  #define PROGRAM 0x02
  #define SECTOR_ERASE 0x52
  #define CHIP_ERASE 0x62
  #define RDID 0x15
  /////////////////////////////
  // ADDRESS SPACE
  ////////////////////////////
  #ifdef AT25F4096
    #define TOP8TH_ADDR 0x70000 //!< Serial memory top eighth address
    #define TOPQ_ADDR 0x60000 //!< Serial memory top quarter address
    #define HALF_ADDR 0x40000 //!< Serial memory half address
    #define TOP_ADDR 0x7FFFF //!< Serial memory top address
    #define BP2 4            //! Block Write Protect Bit only for AT25F4096 Devices      
  #elif (defined(AT25F2048))
    #define TOPQ_ADDR 0x30000 //!< Serial memory top quarter address
    #define HALF_ADDR 0x20000 //!< Serial memory half address
    #define TOP_ADDR 0x3FFFF //!< Serial memory top address
  #else
    #define TOPQ_ADDR 0x18000 //!< Serial memory top quarter address
    #define HALF_ADDR 0x10000 //!< Serial memory half address
    #define TOP_ADDR 0x1FFFF //!< Serial memory top address
  #endif
#endif

// STATUS REGISTER BIT
#define RDY 0//! Busy Indicator Bit
#define WEN 1//! Write Enable Bit
#define BP0 2//! Block Write Protect Bit
#define BP1 3//! Block Write Protect Bit
#define WPEN 7//! Software Write Protect Enable Bit



/////////////////////////////////////////
// MACROs 
/////////////////////////////////////////
//! Marco :Pull down the chip select line of the serial memory
#define Select_Serial_Memory PORTB=(PORTB & ~(1<<DDB2));
//! Macro Pull high the chip select line of the serial memory
#define Deselect_Serial_Memory PORTB=(PORTB | (1<<DDB2));
//! Enable the SPI Interrupt Macro
#define Enable_SPI_Interrupt SPCR|=(1 << SPIE)
//! Disable the SPI Interrupt Macro
#define Disable_SPI_Interrupt SPCR&=~(1 << SPIE)




//! The op_code has been transferred
#define INSTRUCTION 0x1
//! One of the address bytes has been transferred
#define ADDRESS 0x2
//! The current data byte has been transferred
#define DATA 0x4
//! The SPI interface is ready to send
#define READY_TO_SEND 0x0

//Access Status
#define TRANSFER_STARTED 0x0    //!< The write access is started whithout error
#define TRANSFER_COMPLETED 0x1  //!< The read access is completed whithout error
#define OUT_OF_RANGE 0xFD       //!< The address is out of range of available memory
#define DATA_WR_PROTECTED 0xFE       //!< The write access aborted due to write protection
#define BUSY        0xFF        //!< The SPI memory or the SPI interface is busy.

//Error code
#define WRITE_PROTECTED   0x1   //!< The address matches a write protected location.
#define WRITE_ALLOWED     0x0   //!< The address does not matche a write protected location.
#define HW_PROTECTED   0x2   //!< The serial memory is hardware write protected.
 



#ifdef EEPROM_TYPE
  //!The address global variable contains the address of the serial memory where the current byte must be written.
  static int address; 
  char TestWriteProtect(int address, int StatusRegister);
  char GetCharArray(int address, int nb_of_byte, char* destination);
  char PutCharArray(int start_add, char nb_of_byte, char* source); 
  char GetChar(int address, char *data);
  char PutChar(int address, char data);
#else
  //!The address global variable contains the address of the serial memory where the current byte must be written.
  static unsigned long address; 
  char TestWriteProtect(unsigned long address, int StatusRegister);
  char GetCharArray(unsigned long address, unsigned long nb_of_byte, char* destination);
  char PutCharArray(unsigned long start_add, char nb_of_byte, char* source); 
  char GetChar(unsigned long address, char *data);
  char EraseChip(void);
  char EraseSector(unsigned long long_add);
  char GetMemID(char *MemId);
#endif

/////////////////////////////////////////////////////////////
// COMMON GLOBALE VARIABLES 
/////////////////////////////////////////////////////////////
//!The state global variable describes the phase of the write access.
static char state;
//!The nb_byte global variable contains the number of data byte to be written minus one.
static char nb_byte;
//!The byte_cnt global variable count the number of data byte already written.
static char byte_cnt;
//!The data_ptr variable contains the address of the SRAM where the current byte is located . 
static char *data_ptr;
//!The glb_char variable is used as one byte static buffer for the PutChar function
static char glb_char;

/////////////////////////////////////////////////////////////
// COMMON FUNCTION 
/////////////////////////////////////////////////////////////
void init_spi_master();
char spi_transfer(char data);
char WriteStatusRegister(char StatusRegister);
char GetStatusRegister(char *status);
char WriteCommand(char StatusRegister);
char SetWriteProtectedArea(char area);

#endif // __SPI_MEMORY_H
