/*
 * main.c
 *
 *  Created on: Oct 8, 2022
 *      Author: ABRAM
 */


#include "stdint.h"
#include "queue.h"
#define FIFO_BUFF_LENGTH 5



element_type buff[FIFO_BUFF_LENGTH];


void main()
{
	S_FIFO_BUFF_t  uart_fifo;
	unsigned int i,temp=0;

	//	Initialize the UART FIFO buffer
	if(FIFO_INIT(&uart_fifo, buff, FIFO_BUFF_LENGTH)==FIFO_no_error)
	{
		printf("<<<<<<<<<<<<<<<<FIFO INITIALIZATION DONE>>>>>>>>>>>>>>\n");
	}

	for (i=0; i<7;i++)
	{
		printf("FIFO enqueue element : %u\n",i);
		if (FIFO_ENQUEUE(&uart_fifo, &i)== FIFO_no_error)
		{
			printf("FIFO ENQUEUE (%u) ................DONE\n",i);
		}
		else
			printf("FIFO ENQUEUE(%u)..................FAILED!!!!\n",i);
	}


	FIFO_print(&uart_fifo);

	for(i=0; i<7;i++)
	{
		printf("FIFO enqueue element : %u\n",i);
		if (FIFO_DEQUEUE(&uart_fifo, &i)== FIFO_no_error)
		{
			printf("FIFO DEQUEUE (%u) ................DONE\n",i);
		}
		else
			printf("FIFO DEQUEUE(%u)..................FAILED!!!!\n",i);


	}
	FIFO_print(&uart_fifo);

}

