 #include "nokia3310.h"

 //*****************************************************************************
 //                         L C D    F U N C T I O N
 //*****************************************************************************

 /******************************************************************************

 Name:         void LCDInit(void)
 Description:Initialize a graphic of LCD_X & LCD_Y SED1300 Input:
 #define  LCD_X  ...
 #define  LCD_Y  ...
     Output:none
 Misc:******************************************************************************/

void LCDInit (void)
{
  int i, j;

  // LCD BackLight
  LCDBACKLIGHT_DDR |= LCD_BACKLIGHT;
  LCDBACKLIGHT_PORT &= ~LCD_BACKLIGHT;


  // LCD Data Bus
  LCDDATA_PORT = 0x00;
  LCDDATA_DDR = 0xff;

  // LCD control Bus
  LCDCTRLA_DDR |= LCD_WR + LCD_RD + LCD_RES;
  LCDCTRLB_DDR |= LCD_A0;

  LCDCTRLA_PORT |= LCD_WR;	// LCD_WR -> 1
  LCDCTRLA_PORT |= LCD_RD;	// LCD_RD -> 1

  LCDCTRLA_PORT |= LCD_RES;
  LCDDelay2ms ();
  LCDCTRLA_PORT &= ~LCD_RES;	// Reset LCD
  LCDDelay2ms ();
  LCDCTRLA_PORT |= LCD_RES;
  for (i = 0; i < 200; i++)
  {
    LCDDelay2ms ();
  }

  // SYSTEM SET COMMAND
  LCDWriteCmd (0x40);		// SYSTEM SET COMMAND
  LCDWriteData (0x30);		// P1   -> PRT=0, IV=1, W/S=0, M0-M2=0
  LCDWriteData (0x87);		// FX   -> WF=1, FX=7
  LCDWriteData (0x07);		// FY   -> FY=7
  LCDWriteData ((LCD_X / 8) - 1);	// C/R  -> Char per line - 1
  LCDWriteData ((LCD_XTAL / 70 / LCD_Y) / 9);	// TC/R -> (f_osc/f_frame/[L/F]-1)/9
  LCDWriteData (LCD_Y - 1);	// L/F  -> Line per graphic screen - 1 (127)
  LCDWriteData (LCD_X / 8);	// APL  -> Virtual scr low byte (ch perline)
  LCDWriteData (00);		// APH  -> Virtual scr low byte

  // SCROLL COMMAND
  LCDWriteCmd (0x44);		// SCROLL COMMAND
  LCDWriteData (0x00);		// First Layer Low Byte  (0x0000)
  LCDWriteData (0x00);		// First Layer Hign Byte
  LCDWriteData (LCD_Y);		// 128 Line of scroll

  LCDWriteData (0x00);		// Second Layer Low Byte (0x1000)
  LCDWriteData (0x10);		// First Layer Hign Byte
  LCDWriteData (LCD_Y);		// 128 Line of scroll

  // HORIZONTAL SCROLL POSITION
  LCDWriteCmd (0x5a);		// HORIZONTAL SCROLL POSITION
  LCDWriteData (0x00);		// no scrool offset

  // OVERLAY COMMAND
  LCDWriteCmd (0x5b);		// OVERLAY COMMAND
  LCDWriteData (0x03);		// 2 layer (1-Text 2-Graphic)

  // DISPLAY ON/OFF COMMAND
  LCDWriteCmd (0x58);		// DISPLAY OFF COMMAND
  LCDWriteData (0x14);		// Layer 1 & 2 ON

  LCDClrSCR ();
  LCDGraphClrSCR ();

  // LCDCursor FORMAT COMMAND
  LCDWriteCmd (0x5d);		// LCDCursor FORMAT COMMAND
  LCDWriteData (0x07);		// LCDCursor width (7)
  LCDWriteData (0x87);		// LCDCursor Height(7) & Block type

  // DISPLAY ON/OFF COMMAND
  LCDWriteCmd (0x59);		// DISPLAY ON COMMAND
  LCDWriteData (0x14);		// Layer 1 & 2 ON

  // LCDCursor DIRECTION COMMAND
  LCDWriteCmd (0x4c);		// LCDCursor DIRECTION COMMAND (SHIFT RIGHT)

  // LCDCursor WRITE COMMAND
  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (0x00);		// LCDCursor position low byte
  LCDWriteData (0x00);		// LCDCursor position high byte
}

	/******************************************************************************
	
	Name:         void LCDClrSCR(void)
	
	Description:  Clear Text Screen layer 1
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDClrSCR (void)
{
  int i, j;

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (0x00);		// LCDCursor position low byte
  LCDWriteData (0x00);		// LCDCursor position high byte

  LCDWriteCmd (0x42);		// LCD WRITE MEMORY
  LCDDATA_PORT = ' ';
  LCDCTRLB_PORT &= ~LCD_A0;	// LCD_A0 -> 0
  j = ((LCD_X / 8) * (LCD_Y / 8));
  for (i = 0; i < j; i++)
  {
    LCDCTRLA_PORT &= ~LCD_WR;	// LCD_WR -> 0
    WDR ();
    LCDCTRLA_PORT |= LCD_WR;
  }

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (0x00);		// LCDCursor position low byte
  LCDWriteData (0x00);		// LCDCursor position high byte
}

	/******************************************************************************
	
	Name:         void LCDGotoXY(ushort x, ushort y)
	
	Description:  Goto LCD_X LCD_Y coor
	
	Input:        LCD_X,LCD_Y
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDGotoXY (ushort x, ushort y)
{
  int Address;
  ushort low;
  ushort high;

  x--;
  y--;
  Address = (y * (LCD_X / 8)) + x;

  low = (ushort) (Address & 0x00ff);
  high = (ushort) ((Address & 0xff00) >> 8);

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (low);		// LCDCursor position low byte
  LCDWriteData (high);		// LCDCursor position high byte
}

	/******************************************************************************
	
	Name:         void LCDWriteString(char *prt)
	
	Description:  Write a string to the LCD
	
	Input:        String
	
	Output:       none
	
	Misc:         String must be ended by \0
	
	******************************************************************************/
void LCDWriteString (char *ptr)
{
  int i;

  LCDWriteCmd (0x42);		// LCD WRITE MEMORY
  while (*ptr != 0x00)
    LCDWriteData (*ptr++);
}

void LCDWriteConstString (const char *ptr)
{
  int i;

  LCDWriteCmd (0x42);		// LCD WRITE MEMORY
  while (*ptr != 0x00)
    LCDWriteData (*ptr++);
}

	/******************************************************************************
	
	Name:         void LCDCursor(ushort)
	
	Description:  0-> LCDCursor off
	              1-> LCDCursor on
	
	Input:        ON/OFF
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDCursor (ushort LCDCursor)
{
  LCDWriteCmd (0x59);		// DISPLAY ON COMMAND
  if (LCDCursor == 0)
    LCDWriteData (0x14);
  else
    LCDWriteData (0x16);
}

	/******************************************************************************
	
	Name:         void LCDGraphClrSCR(void)
	
	Description:  Clear Graphic Screen layer 2
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDGraphClrSCR (void)
{
  int i, j;

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (0x00);		// LCDCursor position low byte
  LCDWriteData (0x10);		// LCDCursor position high byte

  LCDWriteCmd (0x42);		// LCD WRITE MEMORY COMMAND
  LCDDATA_PORT = 0x00;
  LCDCTRLB_PORT &= ~LCD_A0;	// LCD_A0 -> 0
  j = ((LCD_X / 8) * LCD_Y);
  for (i = 0; i < j; i++)
  {
    LCDCTRLA_PORT &= ~LCD_WR;	// LCD_WR -> 0 & LCD_WR -> 1
    WDR ();
    LCDCTRLA_PORT |= LCD_WR;
  }

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (0x00);		// LCDCursor position low byte
  LCDWriteData (0x10);		// LCDCursor position high byte
}

	/******************************************************************************
	
	Name:         void LCDGraphPix(int x, int y, ushort stat)
	
	Description:  Set of Clear a pixel
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDGraphPix (int x, int y, ushort stat)
{
  uint Address;
  ushort Offset;
  ushort low;
  ushort high;
  ushort byte;

  x--;
  y--;
  Address = (y * (LCD_X / 8)) + (x / 8);
  Offset = x - ((x / 8) * 8);

  low = (ushort) (Address & 0x00ff);
  high = (ushort) (((Address & 0xff00) >> 8) + 0x10);

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (low);		// LCDCursor position low byte
  LCDWriteData (high);		// LCDCursor position high byte

  LCDWriteCmd (0x43);		// READ LCD MEMORY COMMAND
  byte = LCDReadData ();	// Read data at position

  if (stat != 0)
    byte |= (0x80 >> Offset);
  else
    byte &= (~(0x80 >> Offset));

  LCDWriteCmd (0x46);		// LCDCursor WRITE COMMAND
  LCDWriteData (low);		// LCDCursor position low byte
  LCDWriteData (high);		// LCDCursor position high byte

  LCDWriteCmd (0x42);		// LCD WRITE MEMORY COMMAND
  LCDWriteData (byte);		// Write byte
}

	/******************************************************************************
	
	Name:         void LCDGraphBox(int x1, int y1, int x2, int y2)
	
	Description:  draw a box
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDGraphBox (int x1, int y1, int x2, int y2, int stat)
{
  int i;

  for (i = x1; i <= x2; i++)
    LCDGraphPix (i, y1, stat);	// Top line
  for (i = x1; i <= x2; i++)
    LCDGraphPix (i, y2, stat);	// Bottom line
  for (i = y1; i <= y2; i++)
    LCDGraphPix (x1, i, stat);	// Left side
  for (i = y1; i <= y2; i++)
    LCDGraphPix (x2, i, stat);	// Right side
}

	/******************************************************************************
	
	Name:         void LCDTextBox(int x, int y, int length,int stat)
	
	Description:
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDTextBox (int x, int y, int length, int stat)
{
  LCDGraphBox (((x - 1) * 8), ((y - 1) * 8),
	       (((length * 8) + ((x - 1) * 8)) - 2), (y * 8), stat);
}

	/******************************************************************************
	
	Name:         void LCDGraphLine(int x1, int y1, int x2, int y2)
	
	Description:  draw a line
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDGraphLine (int x1, int y1, int x2, int y2)
{
  int dx, dy, stepx, stepy, fraction;

  dy = y2 - y1;
  dx = x2 - x1;

  if (dy < 0)
  {
    dy = -dy;
    stepy = -1;
  }
  else
  {
    stepy = 1;
  }

  if (dx < 0)
  {
    dx = -dx;
    stepx = -1;
  }
  else
  {
    stepx = 1;
  }

  dy <<= 1;
  dx <<= 1;

  LCDGraphPix (x1, y1, 1);

  if (dx > dy)
  {
    fraction = dy - (dx >> 1);
    while (x1 != x2)
    {
      if (fraction >= 0)
      {
	y1 += stepy;
	fraction -= dx;
      }
      x1 += stepx;
      fraction += dy;
      LCDGraphPix (x1, y1, 1);
    }
  }
  else
  {
    fraction = dx - (dy >> 1);
    while (y1 != y2)
    {
      if (fraction >= 0)
      {
	x1 += stepx;
	fraction -= dy;
      }
      y1 += stepy;
      fraction += dx;
      LCDGraphPix (x1, y1, 1);
    }
  }
}

	/******************************************************************************
	
	Name:         void LCDWriteCmd(ushort byte)
	
	Description:  write a Cmd byte to the LCD
	
	Input:        Command (Byte)
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDWriteCmd (ushort byte)
{
  LCDDATA_DDR = 0xff;		// Data Port as output
  LCDDATA_PORT = byte;
  LCDCTRLB_PORT |= LCD_A0;	// LCD_A0 -> 1
  LCDCTRLA_PORT &= ~LCD_WR;	// LCD_WR -> 0
  WDR ();
  LCDCTRLA_PORT |= LCD_WR;	// LCD_WR -> 1
}

	/******************************************************************************
	
	Name:         void LCDWriteData(ushort byte)
	
	Description:  write a data byte to the LCD
	
	Input:        ushort byte -> data to write on the LCD
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDWriteData (ushort byte)
{
  LCDDATA_DDR = 0xff;		// Data Port as output
  LCDDATA_PORT = byte;
  LCDCTRLB_PORT &= ~LCD_A0;	// LCD_A0 -> 0
  LCDCTRLA_PORT &= ~LCD_WR;	// LCD_WR -> 0
  WDR ();
  LCDCTRLA_PORT |= LCD_WR;	// LCD_WR -> 1
}

	/******************************************************************************
	
	Name:         ushort LCDReadData(void)
	
	Description:  read a data byte to the LCD
	
	Input:        none
	
	Output:       ushort byte -> Data read from the LCD
	
	Misc:
	
	******************************************************************************/
ushort LCDReadData (void)
{
  ushort byte;
  int i;

  WDR ();
  LCDDATA_DDR = 0x00;		// Data Port as input
  LCDCTRLB_PORT |= LCD_A0;	// LCD_A0 -> 1
  LCDDelay1us ();
  LCDCTRLA_PORT &= ~LCD_RD;	// LCD_RD -> 0
  byte = LCDDATA_PIN;		// read byte
  byte = LCDDATA_PIN;		// read byte
  byte = LCDDATA_PIN;		// read byte
  byte = LCDDATA_PIN;		// read byte
  LCDCTRLA_PORT |= LCD_RD;	// LCD_RD -> 1
  return byte;
}

	/******************************************************************************
	
	Name:         void LCDDelay2ms(void)
	
	Description:  Delay of 2ms
	
	Input:        void
	
	Output:       void
	
	Misc:
	
	******************************************************************************/
void LCDDelay2ms (void)
{
  int i, j;

  for (i = 0; i < (XTAL / 36363); i++)
  {
    for (j = 1; j < 20; j++);
    asm ("WDR");
  }
}

	/******************************************************************************
	
	Name:         void LCDDelay1us()
	
	Description:  Delay of 1us
	
	Input:        none
	
	Output:       none
	
	Misc:
	
	******************************************************************************/
void LCDDelay1us (void)
{
  int i;

  for (i = 0; i < 13; i++)
    WDR ();
}
