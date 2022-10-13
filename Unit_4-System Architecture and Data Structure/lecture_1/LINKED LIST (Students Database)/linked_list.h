/*
 * linked list.h
 *
 *  Created on: Oct 9, 2022
 *      Author: ABRAM
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "stdint.h"
#include "stdlib.h"
#define  DPRINTF(...)       {fflush(stdout); \
							fflush(stdin); \
							printf(__VA_ARGS__); \
							fflush(stdout); \
							fflush(stdin);}
#define element_type uint32_t

typedef struct
{
	uint32_t ID;
	uint8_t name[40];
	float height;
}S_Data_t;


 struct S_Student
{
	S_Data_t student ;
	 struct S_Student* p_Next_Student;

};


void ADD_STUDENT();
void FILL_RECORD();
int DELELTE_STUDENT();
void VIEW_STUDENTS();
void DELETE_ALL();
int GET_the_Nth_STUDENT_DATA();
void LENGTH_OF_LIST_ITERATIVE();
int LENGTH_OF_LIST_RECURSIVE(struct S_Student* p_CurrentStudent);
int GET_the_Nth_STUDENT_DATA_FROM_THE_END();
int MIDDLE_of_LIST();
int DETECT_LIST_LOOP();
void REVERSE_LIST();



#endif /* LINKED_LIST_H_ */
