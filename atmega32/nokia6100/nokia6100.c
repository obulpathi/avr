
	/*

	   Nokia 6100 Display Test
	   Copyright 2006 Refik Hadzialic (http://www.e-dsp.com) but this code
	   was derived from Thomas Pfeifer's code at
	   http://thomaspfeifer.net/nokia_6100_display.htm and Owen Osborn's code
	   at http://www.sparkfun.com/datasheets/LCD/Nokia6100_Demo.c. I don't
	   the credits for it.


	   This program is free software; you can redistribute it and/or modify
	   it under the terms of the GNU General Public License as published by
	   the Free Software Foundation; either version 2 of the License, or
	   (at your option) any later version.

	   This program is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	   GNU General Public License for more details.

	   You should have received a copy of the GNU General Public License
	   along with this program; if not, write to the Free Software
	   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


	   Target: AVR-ATMega32
	   Compiler: AVRGcc

	   Note:

	 */

	//#### CONFIG ####

#define F_CPU 16000000UL	// 16 MHz

#define SPIPORT PORTC
#define SPIDDR DDRC
#define CS 4
#define CLK 7
#define SDA 5
#define RESET 6

	// Epson S1D15G10 Command Set
#define DISON       0xaf
#define DISOFF      0xae
#define DISNOR      0xa6
#define DISINV      0xa7
#define COMSCN      0xbb
#define DISCTL      0xca
#define SLPIN       0x95
#define SLPOUT      0x94
#define PASET       0x75
#define CASET       0x15
#define DATCTL      0xbc
#define RGBSET8     0xce
#define RAMWR       0x5c
#define RAMRD       0x5d
#define PTLIN       0xa8
#define PTLOUT      0xa9
#define RMWIN       0xe0
#define RMWOUT      0xee
#define ASCSET      0xaa
#define SCSTART     0xab
#define OSCON       0xd1
#define OSCOFF      0xd2
#define PWRCTR      0x20
#define VOLCTR      0x81
#define VOLUP       0xd6
#define VOLDOWN     0xd7
#define TMPGRD      0x82
#define EPCTIN      0xcd
#define EPCOUT      0xcc
#define EPMWR       0xfc
#define EPMRD       0xfd
#define EPSRRD1     0x7c
#define EPSRRD2     0x7d
#define NOP         0x25

	/********
	 Useful colors
	  ********/
#define lightgray 0x6E
#define brown 137
#define yellow 252
#define blue 7
#define red 128
#define white 255
#define black 0
#define orange 236
#define brightred 224
#define lightpurple 227
#define darkpurple 34
#define teal 31
#define aqua 30
#define green 28
#define trans 1

	//#################




#include <io.h>

#define cbi(reg, bit) (reg&=~(1<<bit))
#define sbi(reg, bit) (reg|= (1<<bit))

#define CS0 cbi(SPIPORT,CS);
#define CS1 sbi(SPIPORT,CS);
#define CLK0 cbi(SPIPORT,CLK);
#define CLK1 sbi(SPIPORT,CLK);
#define SDA0 cbi(SPIPORT,SDA);
#define SDA1 sbi(SPIPORT,SDA);
#define RESET0 cbi(SPIPORT,RESET);
#define RESET1 sbi(SPIPORT,RESET);

#define byte unsigned char

void sendCMD (byte cmd);
void sendData (byte cmd);
void shiftBits (byte b);
void LCD_put_pixel (unsigned char color, unsigned char x, unsigned char y);

#include <fonts.c>


void draw_font_12x12 (unsigned char letter, unsigned char x, unsigned char y);
void LCD_say (unsigned char *str, unsigned char x, unsigned char y);


void LCDInit (void)
{
  int i;

  SPIDDR = (1 << SDA) | (1 << CLK) | (1 << CS) | (1 << RESET);	//Port-Direction Setup

  CS0 SDA0 CLK1 RESET1 RESET0 RESET1 CLK1 SDA1 CLK1 delay_ms (10);

  //Software Reset
  sendCMD (DISCTL);

  //added
  sendData (0x03);
  sendData (32);
  sendData (12);
  sendData (0x00);

  sendCMD (0xbb);		// comscn
  sendData (0x01);

  sendCMD (0xd1);		// oscon

  sendCMD (0x94);		// sleep out

  sendCMD (0x81);		// electronic volume, this is kinda contrast/brightness
  sendData (5);			//ff);       //  this might be different for individual LCDs
  sendData (0x01);		//01);     //

  sendCMD (0x20);		// power ctrl
  sendData (0x0f);		//everything on, no external reference resistors
  delay_ms (100);

  sendCMD (0xa7);		// display mode

  sendCMD (0xbc);		// datctl
  sendData (0x00);
  sendData (0);
  sendData (0x01);
  sendData (0x00);

  sendCMD (0xce);		// setup color lookup table
  // color table
  //RED
  sendData (0);
  sendData (2);
  sendData (4);
  sendData (6);
  sendData (8);
  sendData (10);
  sendData (12);
  sendData (15);
  // GREEN
  sendData (0);
  sendData (2);
  sendData (4);
  sendData (6);
  sendData (8);
  sendData (10);
  sendData (12);
  sendData (15);
  //BLUE
  sendData (0);
  sendData (4);
  sendData (9);
  sendData (15);


  sendCMD (NOP);		// nop

  sendCMD (PASET);		// page start/end ram
  sendData (2);			// for some reason starts at 2
  sendData (131);

  sendCMD (CASET);		// column start/end ram
  sendData (0);
  sendData (131);

  sendCMD (RAMWR);		// write some stuff (background)

  for (i = 0; i < 18000; i++)
  {
    sendData (255);		// 28 is green
  }

  sendCMD (DISON);		// display on

  delay_ms (800);

  for (i = 0; i < 250; i++)
  {				// this loop adjusts the contrast, change the number of iterations to get
    sendCMD (0xd6);		// desired contrast.  This might be different for individual LCDs
    delay_ms (8);
  }

}





	/********
	 display.c
	
	  specific functions for displaying
	 character data
	
	  Copyright 2007 Christian Montoya & James Luk
	 Modified by Albert Liang and Greg Wu
	  (condensed code logic, different scan code lookup method, redefined function LCD_unsay, new function LCD_clear_ln, redefined clear_LCD)
	
	  This program is free software; you can redistribute it and/or modify
	  it under the terms of the GNU General Public License as published by
	  the Free Software Foundation; either version 2 of the License, or
	  (at your option) any later version.
	
	  This program is distributed in the hope that it will be useful,
	  but WITHOUT ANY WARRANTY; without even the implied warranty of
	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	  GNU General Public License for more details.
	
	  You should have received a copy of the GNU General Public License
	  along with this program; if not, write to the Free Software
	  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
	
	 ********/




void draw_font (unsigned char letter, unsigned char x, unsigned char y)
{

  unsigned int i, j, row;

  row = letter * 6;

  for (i = 0; i < 6; i++)
  {
    for (j = 0; j < 6; j++)
    {
      if (font6x6[i + row][j] != 0)
      {
	LCD_put_pixel (brightred, x + i, y + j);
      }
    }
  }
}


	 /********
	  LCD_say
	
	 writes a string to the lcd at x, y
	  adapted from video code by Prof. Bruce Land
	 ********/
void LCD_say (unsigned char *str, unsigned char x, unsigned char y)
{
  unsigned char i, j, k, row;

  for (k = 0; str[k] != 0; k++)
  {
    for (j = 0; j < 45; j++)
    {
      if (str[k] == letter_arr[j])
	break;
    }
    row = j * 6;
    for (i = 0; i < 6; i++)
    {
      for (j = 0; j < 6; j++)
      {
	if (font6x6[i + row][j] != 0)
	{
	  LCD_put_pixel (brightred, x + i, y + j);
	}
      }
    }
    y = y + Cshift;
  }
}

	 /********
	  LCD_unsay
	
	 draws a 6x6 white square
	  ********/
void LCD_unsay (unsigned char x, unsigned char y)
{
  unsigned char i, j, k, row;

  y = y - Cshift;

  for (i = 0; i < 6; i++)
  {
    for (j = 0; j < 6; j++)
    {
      LCD_put_pixel (white, x + i, y + j);
    }
  }
}

	/********
	 LCD_clear_ln
	
	  draws a 128x6 white strip
	 ********/
void LCD_clear_ln (unsigned char x)
{
  int i, j;

  for (i = 0; i < 128; i++)
  {
    for (j = 0; j < 6; j++)
    {
      LCD_put_pixel (white, x + j, i);
    }
  }
}


	 /********
	  clear_LCD
	
	 wipes whole screen to white
	  ********/
void clear_LCD ()
{

  unsigned int t;

  LCD_put_pixel (white, 0, 0);
  for (t = 0; t < 17160; t++)
  {
    sendData (white);
  }
}


	/*******************************
	
	        LCD functions
	
	********************************/
void shiftBits (byte b)
{

  CLK0 if ((b & 128) != 0)
      SDA1
    else
      SDA0 CLK1 CLK0 if ((b & 64) != 0)
        SDA1
      else
        SDA0 CLK1 CLK0 if ((b & 32) != 0)
	  SDA1
	else
	  SDA0 CLK1 CLK0 if ((b & 16) != 0)
	    SDA1
	  else
	    SDA0 CLK1 CLK0 if ((b & 8) != 0)
	      SDA1
	    else
	      SDA0 CLK1 CLK0 if ((b & 4) != 0)
	        SDA1
	      else
	        SDA0 CLK1 CLK0 if ((b & 2) != 0)
		  SDA1
		else
		  SDA0 CLK1 CLK0 if ((b & 1) != 0)
		    SDA1
		  else
		    SDA0 CLK1}

		  // draw a single colored pixel
		  void LCD_put_pixel (unsigned char color, unsigned char x,
				      unsigned char y)
  {
    x += 2;			// range goes from 2 to 130
    sendCMD (PASET);		// page start/end ram
    sendData (x);
    sendData (132);
    sendCMD (CASET);		// column start/end ram
    sendData (y);		// for some reason starts at 2
    sendData (131);
    sendCMD (RAMWR);
    sendData (color);
  }

  //send data
  void sendData (byte data)
  {

    CLK0 SDA1			//1 for param
      CLK1 shiftBits (data);
  }

  //send cmd
  void sendCMD (byte data)
  {

    CLK0 SDA0			//1 for cmd
      CLK1 shiftBits (data);
  }
