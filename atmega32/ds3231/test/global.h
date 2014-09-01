#define LOW_NIBBLE 0x0F
#define HIGH_NIBBLE 0xF0

// redefine them ... structure them ... 
// gps and timer varables
// format time : hhmmss, date : ddmmyy
unsigned char day, time[6], date[6], lat[10], lon[11];
// flash and xbee buffer
unsigned char data[528];
