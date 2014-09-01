//************************************************************************
// This code is taken from one of my project, you can't compile it like 
// it is,  That's only to help you to understand graphic LCD's
// 
// Sylvain Bissonnette
//************************************************************************

//*****************************************************************************
//
//                    R E T U R N   S T A C K   6 4
//                          X T A L  16 MHZ
//                      BootLoader of 1024 word
//
//*****************************************************************************
//
//                F U S E   B I T
//
//( )7      ( )6     (X)BL12 (X)BL11  ( )BL02   ( )BL01    ( )Lock2   ( )Lock1
//( )7      ( )6     ( )     ( )      ( )       ( )M103C   ( )WDTON   ( )
//( )RSTDIS ( )WDON  (X)SPIEN(X)CKOPT (X)EESAVE ( )BOOTSZ1 (X)BOOTSZ0 (X)BOOTRST
//(X)BODLEV (X)BODEN ( )SUT1 ( )SUT0  ( )CKSEL3 ( )CKSEL2  ( )CKSEL1  ( )CKSEL0
//
//*****************************************************************************
//                        P I N   U S A G E
//
// PC0 -> LCD Data bit 0
// PC1 -> LCD Data bit 1
// PC2 -> LCD Data bit 2
// PC3 -> LCD Data bit 3
// PC4 -> LCD Data bit 4
// PC5 -> LCD Data bit 5
// PC6 -> LCD Data bit 6
// PC7 -> LCD Data bit 7
//
// PD0 -> 
// PD1 -> 
// PD2 -> 
// PD3 -> 
// PD4 -> 
// PD5 -> LCD RESET
// PD6 -> LCD RD
// PD7 -> LCD WR
// PG0 -> LCD A0

//*****************************************************************************
//                              D E F I N E
//*****************************************************************************
#define XTAL                16000000

// LCD
#define LCDDATA_DDR         DDRC
#define LCDDATA_PIN         PINC
#define LCDDATA_PORT        PORTC

#define LCDCTRLA_DDR        DDRD
#define LCDCTRLA_PIN        PIND
#define LCDCTRLA_PORT       PORTD

#define LCDCTRLB_DDR        DDRG
#define LCDCTRLB_PIN        PING
#define LCDCTRLB_PORT       PORTG

#define LCDBACKLIGHT_DDR    DDRB
#define LCDBACKLIGHT_PIN    PINB
#define LCDBACKLIGHT_PORT   PORTB

#define LCD_A0              0x02
#define LCD_WR              0x80
#define LCD_RD              0x40
#define LCD_RES             0x20

#define LCD_X               320
#define LCD_Y               200
#define LCD_XTAL            6000000

#define LCD_BACKLIGHT       0x40

// code porting ... 
#define ushort unsigned char
#define uint unsigned int

 //**************************************
 //          P R O T O T LCD_Y P E
 //**************************************

 // LCD
void LCDInit (void);
void LCDWriteData (ushort byte);
void LCDWriteCmd (ushort byte);
ushort LCDReadData (void);
void LCDClrSCR (void);
void LCDGotoXY (ushort, ushort);
void LCDWriteString (char *ptr);
void LCDWriteConstString (const char *ptr);
void LCDCursor (ushort LCDCursor);
void LCDTextBox (int x, int y, int length, int stat);
void LCDDelay2ms (void);
void LCDDelay1us (void);

void LCDGraphClrSCR (void);
void LCDGraphPix (int x, int y, ushort stat);
void LCDGraphBox (int x1, int y1, int x2, int y2, int stat);
void LCDGraphLine (int x1, int y1, int x2, int y2);
