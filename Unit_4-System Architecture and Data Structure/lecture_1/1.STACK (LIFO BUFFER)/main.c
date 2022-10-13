#include "stdio.h"
#include "stdint.h"
#include "stack.h"

element_type static_buffer[LIFO_BUFF_LENGTH];

int main()
{
	element_type temp ,i;

	S_LIFO_BUFF_t buffer ;

	// Using static allocation

	// Initialization function of static buffer
	LIFO_INIT(&buffer,static_buffer,LIFO_BUFF_LENGTH);
	printf("<<<<<<LIFO BUFFER INITIALIZATION DONE >>>>>>>\n");

	// PUSH_item function of static buffer
	printf("\nBuffer LIFO push items (static allocation) : \n");
	for (i=0; i<LIFO_BUFF_LENGTH; i++)
	{
		if(PUSH_item(&buffer,i)== LIFO_no_error)
			printf("FIFO buffer add: %d\n", i);
	}
	printf("\n<<<<<<LIFO BUFFER PUSH DONE >>>>>>>\n");

	// POP_item function for getting elements from the buffer
	printf("\nBuffer LIFO pop items (static allocation) : \n");
	for (i = 0; i < LIFO_BUFF_LENGTH; i++)
	{
		if (POP_item(&buffer, &temp) == LIFO_no_error)
			printf("FIFO buffer get: %d\n" , temp);
	}
	printf("\n<<<<<<LIFO BUFFER POP DONE >>>>>>>\n");

	return 0;
}
