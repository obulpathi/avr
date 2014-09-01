#define SPIF_DDR	PORTF_DIR
#define SPIF_OUT	PORTF_OUT
#define DD_MOSI		6
#define DD_SCK		4
#define DD_SS		5

void SPI_Init(void);
void SPI_Tx(char data);
unsigned char SPI_Rx(void);
unsigned char SPI_TRx(unsigned char data);
