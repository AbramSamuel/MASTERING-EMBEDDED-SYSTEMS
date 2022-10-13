

#include "stack.h"

// APIs


LIFO_BUFF_status LIFO_INIT(S_LIFO_BUFF_t * Lifo_Buf,element_type*  buff, uint32_t length)
{

	// check if the buffer is empty
	if(buff == NULL) return LIFO_null;

	Lifo_Buf->base = buff;
	Lifo_Buf->head = buff;
	Lifo_Buf->length = length;
	Lifo_Buf->count = 0;
	return LIFO_no_error;


}
// check if the stack is full
LIFO_BUFF_status LIFO_BUFF_FULL(S_LIFO_BUFF_t *Lifo_Buf)
{
	// check if the pointer is valid
	if (!Lifo_Buf || !Lifo_Buf->base || !Lifo_Buf->head)
		return LIFO_null;

	if(Lifo_Buf->count >= Lifo_Buf->length)
	{
		return LIFO_full;
	}
	else
		return LIFO_not_full;
}
// add item to the stack
LIFO_BUFF_status PUSH_item(S_LIFO_BUFF_t *Lifo_Buf, element_type item)
{
	// check if the pointer is valid
	if (!Lifo_Buf || !Lifo_Buf->base || !Lifo_Buf->head)
		return LIFO_null;

	// check if the buffer is full
	if (LIFO_BUFF_FULL(Lifo_Buf) == LIFO_full)
	{
		return LIFO_full;
	}
	//	push elements
	*(Lifo_Buf->head) = item;
	Lifo_Buf ->head++;  // move the head of the buffer to the next pointer
	Lifo_Buf ->count++;    // increment the count of items

	return LIFO_no_error;
}

// get item from the buffer
LIFO_BUFF_status POP_item (S_LIFO_BUFF_t *Lifo_Buf, element_type *item)
{
	// check if the buffer is valid
	if (!Lifo_Buf || !Lifo_Buf->base || !Lifo_Buf->head)
		return LIFO_null;

	// check if the buffer is empty
	if (Lifo_Buf->count == 0)
	{
		return LIFO_empty;
	}
	//	pop elements
	Lifo_Buf->head--;
	*(item) = *(Lifo_Buf->head) ;
	Lifo_Buf->count--;

	return LIFO_no_error;


}
