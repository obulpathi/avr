#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define XTAL 4000000
#define BAUD 9600

int Uart_putchar(unsigned char character)
{
        loop_until_bit_is_set(UCSRA, UDRE);
        UDR = character;
        return 0;
}

SIGNAL(SIG_UART_RECV)
{
        unsigned char character;
        unsigned char dummy;

        character = UDR;
        PORTB = ~character;
        Uart_putchar(character);
        while ( UCSRA & (1<<RXC) ) dummy = UDR;

}

void Init_USART(void)
{
        // USART Mode: Asynchronous
        UBRRH = 0x00; // write high byte first
        UBRRL = ((XTAL/16)/BAUD)-1; // baud rate 9600
        UCSRA = 0x00;
        UCSRB |= (1 << 3); // TXEN ON, TX ON, xxxx 1xxx
        UCSRB |= (1 << 4); // RXEN, RX ON, xxx1 1xxx
        UCSRB |= (1 << 7); // RXIE, RX interrupt ON, 1xx1 1xxx
        UCSRC = 0x86; // 8 Data, 1 Stop, No Parity 1xxx x11x
        SREG = (1 << 7); // global interrupt ON 1xxx xxxx
}

int main(void)
{
        int i,j;
        unsigned int a;
        DDRB = 0xFF;
        PORTB= 0x00;
        Init_USART();
        sei();
        while(1);
        return 0;
}

