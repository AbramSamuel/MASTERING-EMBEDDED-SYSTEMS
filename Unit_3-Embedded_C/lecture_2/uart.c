#include "uart.h"
#define UART0DR *(volatile unsigned int *)((unsigned int*)0x101f1000)

void Uart_Send_String(unsigned char* P_tx_string)
{
    while (*P_tx_string != '\0')
    {
        UART0DR = (unsigned int )(*P_tx_string++);
    }
}