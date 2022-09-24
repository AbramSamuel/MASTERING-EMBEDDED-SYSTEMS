#include "uart.h"

unsigned char string_buffer[100]="Learn-In-Depth:<ABRSM>";
unsigned char const string_buffer_2[100] = "Learn-In-Depth:<ABRSM>";

void main()
{
    Uart_Send_String(string_buffer);
}