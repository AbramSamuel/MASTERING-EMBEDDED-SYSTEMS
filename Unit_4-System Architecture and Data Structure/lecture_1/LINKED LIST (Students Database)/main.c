/*
 * main.c
 *
 *  Created on: Oct 9, 2022
 *      Author: ABRAM
 */
#include "stdio.h"
#include "stdint.h"
#include "linked_list.h"
int main(void)
{
	uint8_t temp[20];
	while (1)
	{
		DPRINTF("\nChoose one of the following options \n");
		DPRINTF("1: Add Student\n");
		DPRINTF("2: Delete Student\n");
		DPRINTF("3: View Students\n");
		DPRINTF("4: Delete All \n");
		DPRINTF("5: Show Student Data at Index\n");
		DPRINTF("6: Find the Number of Students\n");
		DPRINTF("7: Find the Student Data From the End\n");
		DPRINTF("8: Find the middle of the List\n");
		DPRINTF("9: Find If There is a Loop\n");
		DPRINTF("10: Reverse the List\n")
		DPRINTF("\nEnter Option Number (1,2,3,4,....,10) : ");

		gets(temp);
		DPRINTF("\n-----------------------------\n");
		switch (atoi(temp))
		{
		case 1:
			ADD_STUDENT();
			DPRINTF("-----------------------------\n");
			break;

		case 2:
			DELELTE_STUDENT();
			DPRINTF("-----------------------------\n");
			break;

		case 3:
			VIEW_STUDENTS();
			DPRINTF("-----------------------------\n");
			break;

		case 4:
			DELETE_ALL();
			DPRINTF("-----------------------------\n");
			break;
		case 5:
			GET_the_Nth_STUDENT_DATA();
			DPRINTF("-----------------------------\n");
			break;
		case 6:
			LENGTH_OF_LIST_ITERATIVE();
			DPRINTF("-----------------------------\n");
			break;
		case 7:
			GET_the_Nth_STUDENT_DATA_FROM_THE_END();
			DPRINTF("-----------------------------\n");
			break;
		case 8:
			MIDDLE_of_LIST();
			DPRINTF("-----------------------------\n");
			break;
		case 9:
			DETECT_LIST_LOOP();
			DPRINTF("-----------------------------\n");
			break;
		case 10:
			REVERSE_LIST();
			DPRINTF("-----------------------------\n");
			break;
		default:
			DPRINTF("\nWrong Option!");
			break;

		}
	}
}
