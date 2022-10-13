#ifndef STACK_H_
#define STACK_H_

#include "stdio.h"
#include "stdint.h"

//USER CONFIGURATION

#define LIFO_BUFF_LENGTH 5
#define element_type uint8_t
// TYPE DEFENITIONS



typedef struct
{
	uint32_t length;
	uint32_t count;
	element_type *base;
	element_type*head;
} S_LIFO_BUFF_t;

typedef enum
{
	LIFO_no_error,
	LIFO_full,
	LIFO_not_full,
	LIFO_empty,
	LIFO_null
} LIFO_BUFF_status;


//APIs
LIFO_BUFF_status LIFO_BUFF_FULL(S_LIFO_BUFF_t *Lifo_Buf);
LIFO_BUFF_status PUSH_item(S_LIFO_BUFF_t *Lifo_Buf, element_type item);
LIFO_BUFF_status POP_item(S_LIFO_BUFF_t *Lifo_Buf, element_type *item);
LIFO_BUFF_status LIFO_INIT(S_LIFO_BUFF_t *Lifo_Buf, element_type *buff, uint32_t length);

#endif //STACK_H_
