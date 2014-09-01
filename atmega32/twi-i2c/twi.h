#define TWI_ENABLE_PULL_UP	0x03

#define TWI_READ_MODE	0x01
#define TWI_WRITE_MODE	0x00

#define TWI_INIT	0x44
#define TWI_START	0xE4
#define TWI_RESTART	0xE4
#define TWI_TRANSMIT	0xC4
#define TWI_RECEIVE	0xC4
#define TWI_RECEIVE_LAST_BYTE	0x84
#define TWI_STOP	0xD4

/*
#define TWI_TIMER	0x00
#define TWI_DEVICE1	0x00
#define TWI_DEVICE2	0x00
#define TWI_BROADCAST	0x00
*/

// Define error codes here ... note that prescalar bits should be masked ...
#define TWI_START_SUCESS	0x08
#define TWI_RESTART_SUCESS	0x10
#define TWI_TX_SL_ADD_SUCESS	0x18
#define TWI_TX_SL_ADD_FAILURE	0x20
#define TWI_TRANSMIT_SUCESS	0x28
#define TWI_TRANSMIT_FAILURE	0x30
#define TWI_ERROR		0x38

// baudrates : internal crystal "1MHz ..."
#define TWI_BAUD_2400 200 
#define TWI_PRESCALAR_2400 1
#define TWI_BAUD_4800 96
#define TWI_PRESCALAR_4800 1
#define TWI_BAUD_9600 44
#define TWI_PRESCALAR_9600 1


//function definitions

void twi_init(unsigned char baud, unsigned char prescalar);
int twi_start(void);
int twi_restart(void);
int twi_tx(unsigned char data);
unsigned char twi_rx(void);
unsigned char twi_rx_last_byte(void);
int twi_tx_slave_address(unsigned char address, unsigned char mode);
void twi_stop(void);
void twi_deinit(void);
