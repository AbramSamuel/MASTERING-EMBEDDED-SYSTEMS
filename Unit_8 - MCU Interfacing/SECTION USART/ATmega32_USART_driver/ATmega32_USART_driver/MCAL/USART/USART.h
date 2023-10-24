/*
 * USART.h
 *
 * Created: 10/17/2023 7:39:32 PM
 *  Author: ABRAM
 */ 


#ifndef USART_H_
#define USART_H_
#include "..\..\SERVICES\MEMORY_MAP.h"
#include "..\..\SERVICES\STD_TYPES.h"
#include "..\..\SERVICES\UTILITIES.h"

#define DefaultStop		'\r'
////////////////APIS///////////////////
/*
======================================================================================================================
* @Func_name	:   USART_INIT
* @brief		:   Initializes the USART module with a char size of 8 bits, no parity, one stop bit and 9600 baud-rate.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void USART_INIT();


/*
======================================================================================================================
* @Func_name	:   USART_SEND
* @brief		:   Send an 8 bit character through the USART.
* @param [in]	:   data: the 8 bit data to be sent.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void USART_SEND(u8 data);

/*
======================================================================================================================
* @Func_name	:   USART_RECEIVE
* @brief		:   Recives an 8 bit character from the USART.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   The data to be received.
* Note			:   none.
======================================================================================================================
*/
u8 USART_RECEIVE(void);


/*
======================================================================================================================
* @Func_name	:   USART_SEND_STRING
* @brief		:   Sends a string through the USART.
* @param [in]	:   string to send.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/

void USART_SEND_STRING(u8* str);

/*
======================================================================================================================
* @Func_name	:   USART_RECEIVE_STRING
* @brief		:   Receives a string through the USART.
* @param [in]	:   buffer the buffer to store the string in.
* @param [in]	:   bufferSize: maximum length of the string to be received.
* @return_value :   none.
* Note			:   This function will receive characters until the end of the string or until press ENTER '\r'.
======================================================================================================================
*/
void USART_RECEIVE_STRING(u8* buff);
void USART_SEND_NUMBER_U32(u32 num);
u32 USART_RECEIVE_NUMBER_U32(void);
#endif /* USART_H_ */