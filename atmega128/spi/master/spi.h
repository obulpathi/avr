#define SS		0
#define SCK 	1
#define MOSI	2
#define MISO	3

#define DDR_SPI	DDRB
#define PORT_SPI PORTB

#define DUMMY 0x00

void spi_init(void);
void spi_tx(unsigned char data);
unsigned char spi_rx(void);
void spi_start(void);
void spi_end(void);
