/*
 * queue.c
 *
 *  Created on: Oct 8, 2022
 *      Author: ABRAM
 */




#include "queue.h"
#include "stdint.h"

FIFO_BUFF_status FIFO_INIT(S_FIFO_BUFF_t *FIFO_buf, element_type *BUFFER, uint32_t length)
{

	// check if the buffer is empty
	if(BUFFER == NULL) return FIFO_null;

	FIFO_buf->base = BUFFER;
	FIFO_buf->head = BUFFER;
	FIFO_buf->tail = BUFFER;
	FIFO_buf->length = length;
	FIFO_buf->count = 0;
	return FIFO_no_error;
}
FIFO_BUFF_status FIFO_ENQUEUE(S_FIFO_BUFF_t* FIFO_buf, element_type* ENQ_Data)
{
	if(FIFO_IS_FULL(FIFO_buf) == FIFO_no_error)
	{
		//		enqueue data
		*(FIFO_buf->head) = *(ENQ_Data);
		FIFO_buf->count++;

		//	Circular FIFO
		if(FIFO_buf->head ==(FIFO_buf->base)+(FIFO_buf->length*sizeof(element_type)))
		{
			FIFO_buf->head =FIFO_buf->base;
		}
		else
			FIFO_buf->head++;
		return FIFO_no_error;
	}
	else
	{
		return FIFO_full;
	}

}
FIFO_BUFF_status FIFO_DEQUEUE(S_FIFO_BUFF_t* FIFO_buf, element_type* DEQ_Data)
{
	//	check if theFIFO buffer exist
	if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail)
	{
		return FIFO_null;
	}

	// check if the buffer is empty
	if (FIFO_buf->count == 0)
	{
		return FIFO_empty;
	}

	*DEQ_Data = *FIFO_buf->tail;
	FIFO_buf->count --;

	if (FIFO_buf->tail == (FIFO_buf->base)+(FIFO_buf->length*sizeof(element_type)))
	{
		FIFO_buf->tail = FIFO_buf->base;
	}
	else
		FIFO_buf->tail++;
	return FIFO_no_error;

}
FIFO_BUFF_status FIFO_IS_FULL(S_FIFO_BUFF_t* FIFO_buf)
{
	//	check if theFIFO buffer exist
	if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail)
	{
		printf("\nFIFO BUFFER DOES NOT EXIST!!\n");
		return FIFO_null;
	}
	if(FIFO_buf->count >= FIFO_buf->length)
	{
		printf("\nFIFO BUFFER IS FULL!\n");
		return FIFO_full;
	}
	return FIFO_no_error;
}
void FIFO_print(S_FIFO_BUFF_t* FIFO_buf)
{
	element_type* temp;
	unsigned int i;

	// check if the buffer is empty
		if (FIFO_buf->count == 0)
		{
			printf("\nFIFO BUFFER IS EMPTY!!\n");
			return FIFO_empty;
		}
		temp = FIFO_buf->tail;
		printf("========FIFO PRINT========\n");
		for(i=0; i<FIFO_buf->count;i++)
		{
			printf("Element %u in FIFO buffer : %u\n",i+1,*temp);
			temp++;
		}

		printf("\n=========================================\n");



}
