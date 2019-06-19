#include "ladder.h"

#include "UartLib.h"

void UART_Init(unsigned char divisor, unsigned char brgh)
{
    // UART baud rate setup
    SPBRG = divisor;
    BRGH = brgh != 0;
    TXEN = 1;
    CREN = 1;
    SPEN = 1;
}

void UART_Transmit(unsigned char data)
{
    // Wait for empty transmit buffer
    //while(!TRMT)
    while(TXIF == 0) // 0 = The USART transmit buffer is full
        ; // Put data into buffer, sends the data
    TXREG = data;
}

unsigned char UART_Receive(void)
{
    // Wait for data to be received
    while(!RCIF)
        ; // Get and return received data from buffer
    return RCREG;
}

unsigned char UART_Transmit_Ready(void)
{
    //return TRMT;
    return TXIF == 1; // 1 = The USART transmit buffer is empty
}

unsigned char UART_Transmit_Busy(void)
{
    //return !TRMT;
    return TXIF == 0; // 0 = The USART transmit buffer is full
}

unsigned char UART_Receive_Avail(void)
{
    return RCIF;
}

void UART_Write(char *string)
{
    while(*string) {
        UART_Transmit(*string);
        string++;
    }
}