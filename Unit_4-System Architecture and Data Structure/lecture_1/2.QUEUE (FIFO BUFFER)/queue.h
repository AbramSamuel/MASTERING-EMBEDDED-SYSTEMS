/*
 * queue.h
 *
 *  Created on: Oct 8, 2022
 *      Author: ABRAM
 */

#ifndef QUEUE_H_
#define QUEUE_H_


//USER CONFIGURATION
#include "stdio.h"
#include "stdint.h"
//select the elements FIFO type
#define element_type uint8_t



// TYPE DEFENITIONS

typedef struct
{
	uint32_t length;
	uint32_t count;
	element_type* base;
	element_type* head;
	element_type* tail;
} S_FIFO_BUFF_t;

typedef enum
{
	FIFO_no_error,
	FIFO_full,
	FIFO_not_full,
	FIFO_empty,
	FIFO_null
} FIFO_BUFF_status;

//APIs
FIFO_BUFF_status FIFO_INIT(S_FIFO_BUFF_t *FIFO_buf, element_type *BUFFER, uint32_t length);
FIFO_BUFF_status FIFO_ENQUEUE(S_FIFO_BUFF_t* FIFO_buf, element_type* ENQ_Data);
FIFO_BUFF_status FIFO_DEQUEUE(S_FIFO_BUFF_t* FIFO_buf, element_type* DEQ_Data);
FIFO_BUFF_status FIFO_IS_FULL(S_FIFO_BUFF_t* FIFO_buf);
void FIFO_print(S_FIFO_BUFF_t* FIFO_buf);



#endif /* QUEUE_H_ */
