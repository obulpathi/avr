#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

#define DDR_SPI	DDRB
#define PORT_SPI PORTB

#define DUMMY 0x00

void spi_slave_init(void);
unsigned char spi_trx(unsigned char data);
