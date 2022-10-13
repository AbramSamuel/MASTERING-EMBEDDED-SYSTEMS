/*
 * linked list.c
 *
 *  Created on: Oct 9, 2022
 *      Author: ABRAM
 */


#include "linked_list.h"
#include "stdio.h"
struct S_Student* g_p_FirstStudent = NULL;

void ADD_STUDENT()
{
	struct S_Student* p_LastStudent;
	struct S_Student* p_NewStudent;

	//	if the list is empty
	if(g_p_FirstStudent == NULL)
	{
		//		create the first record
		g_p_FirstStudent =( struct S_Student*) malloc(sizeof(struct S_Student*));
		p_NewStudent = g_p_FirstStudent;
	}
	//	if the list contains records
	else
	{
		//		loop until the last record
		p_LastStudent =g_p_FirstStudent;
		while(p_LastStudent->p_Next_Student)
		{
			//
			p_LastStudent=p_LastStudent->p_Next_Student;
		}
		//		create new record
		p_NewStudent = (struct S_Student* )malloc(sizeof(struct S_Student* ));
		p_LastStudent->p_Next_Student = p_NewStudent;
	}
	//	fill the new record
	FILL_RECORD(p_NewStudent);

	//	set the next record to NULL
	p_NewStudent->p_Next_Student = NULL;

}




void FILL_RECORD(struct S_Student* New_Student)
{
	uint8_t data[40];


	DPRINTF("Enter the Student ID:");
	gets(data);
	New_Student->student.ID = atoi(data);
	DPRINTF("\nEnter the Student Name:");
	gets(New_Student->student.name);
	DPRINTF("\nEnter the Student Height:");
	gets(data);
	New_Student->student.height = atof(data);


}
int DELELTE_STUDENT()
{
	uint8_t tempText[20];
	uint32_t ID_Selected;

	DPRINTF("Enter The Student ID to be Deleted:\n");
	gets(tempText);
	ID_Selected = (uint32_t)atoi(tempText);

	//		Check if the list is empty
	if (g_p_FirstStudent)
	{
		struct S_Student* p_PreviousStudent = NULL;
		struct S_Student* p_SelectedStudent = g_p_FirstStudent;
		//			Loop on the elements of the list to find the selected ID to be deleted
		while (p_SelectedStudent)
		{
			//				Compare the current ID with the selected ID to be deleted
			if (p_SelectedStudent->student.ID == ID_Selected)
			{
				if (p_PreviousStudent)
				{
					p_PreviousStudent->p_Next_Student = p_SelectedStudent->p_Next_Student;

				}
				else
				{
					g_p_FirstStudent = (struct S_Student*)p_SelectedStudent->p_Next_Student;

				}
				free(p_SelectedStudent);
				return 1;
			}
			p_PreviousStudent = p_SelectedStudent;
			p_SelectedStudent = p_SelectedStudent->p_Next_Student;
		}

	}
	DPRINTF("Can't find Student ID\n ");
	return 0;

}
void VIEW_STUDENTS()
{
	uint32_t count=0;
	struct S_Student* p_CurrentStudent =g_p_FirstStudent;
	if(g_p_FirstStudent == NULL)
		DPRINTF("\nEMPTY LIST!!");

	while(p_CurrentStudent)
	{
		DPRINTF("Record Number %d\n", count + 1);
		DPRINTF("Name: %s\n", p_CurrentStudent->student.name);
		DPRINTF("ID: %d\n", p_CurrentStudent->student.ID);
		DPRINTF("Height: %0.2f\n", p_CurrentStudent->student.height);
		DPRINTF("-----------------------------\n");
		p_CurrentStudent =p_CurrentStudent->p_Next_Student;
		count++;
	}




}

void DELETE_ALL()
{
	struct S_Student* p_CurrentStudent =g_p_FirstStudent;

	if(g_p_FirstStudent == NULL)
		DPRINTF("\nEMPTY LIST!!");

	while(p_CurrentStudent)
	{
		struct S_Student* p_TempStudent = p_CurrentStudent;
		p_CurrentStudent = p_CurrentStudent->p_Next_Student;
		free(p_TempStudent);
	}
	g_p_FirstStudent= NULL;
}


int GET_the_Nth_STUDENT_DATA()
{
	uint32_t count =0;
	uint8_t temp_text[20];
	struct S_Student* p_CurrentStudent =g_p_FirstStudent;
	DPRINTF("\n Enter the index: ");
	gets(temp_text);
	//check list is empty
	if(g_p_FirstStudent == NULL)
	{
		DPRINTF("list is empty");
	}
	else
	{
		while(p_CurrentStudent)
			if(count == atoi(temp_text))
			{
				DPRINTF("Record Number %d\n", count + 1);
				DPRINTF("Name: %s\n", p_CurrentStudent->student.name);
				DPRINTF("ID: %d\n", p_CurrentStudent->student.ID);
				DPRINTF("Height: %0.2lf\n", p_CurrentStudent->student.height);
				DPRINTF("-----------------------------\n");
				return 1;
			}

			else
			{
				p_CurrentStudent =p_CurrentStudent->p_Next_Student;
				count++;
			}

	}


	return 0;

}


void LENGTH_OF_LIST_ITERATIVE()
{
	uint32_t count =0;
	uint8_t temp_text[20];
	struct S_Student* p_CurrentStudent =g_p_FirstStudent;
	DPRINTF("\n Enter the index: ");
	gets(temp_text);
	//check list is empty
	if(g_p_FirstStudent == NULL)
	{
		DPRINTF("list is empty");
	}
	else
	{
		while(p_CurrentStudent)
		{
			p_CurrentStudent =p_CurrentStudent->p_Next_Student;
			count++;
		}
		printf("The Number of Elements in The List using Iterative method is:%d\n", count);

	}

}


int LENGTH_OF_LIST_RECURSIVE(struct S_Student* p_CurrentStudent)
{
	//check list is empty
	if(g_p_FirstStudent == NULL)
	{
		DPRINTF("list is empty");
	}
	else
	{
		return (1+ LENGTH_OF_LIST_RECURSIVE(p_CurrentStudent->p_Next_Student));
	}
}

int GET_the_Nth_STUDENT_DATA_FROM_THE_END()
{
	struct S_Student* main_ptr= g_p_FirstStudent;
	struct S_Student* ref_ptr= g_p_FirstStudent;
	uint8_t temp_text[20];
	uint32_t NfromEnd,i,count=0;
	DPRINTF("\n Enter the node number from the end: ");
	gets(temp_text);
	NfromEnd = atoi(temp_text);
	if(g_p_FirstStudent == NULL)
	{
		DPRINTF("list is empty\n");
	}
	else
	{
		for(i=0 ; i<NfromEnd;i++)
		{
			ref_ptr=ref_ptr->p_Next_Student;
		}
		while(ref_ptr)
		{
			ref_ptr=ref_ptr->p_Next_Student;
			main_ptr = main_ptr->p_Next_Student;
			count++;
		}
		DPRINTF("\nData of the node at index %d from the end is:\n",NfromEnd);
		DPRINTF("Record Number %d\n", count + 1);
		DPRINTF("Name: %s\n", main_ptr->student.name);
		DPRINTF("ID: %d\n", main_ptr->student.ID);
		DPRINTF("Height: %0.2lf\n", main_ptr->student.height);
		printf("-----------------------------\n");
		return 0;
	}
	return 1;
}

int MIDDLE_of_LIST()
{
	if(g_p_FirstStudent == NULL)
	{
		DPRINTF("list is empty\n");
	}
	else
	{
		uint32_t count=0;
		struct S_Student* fast_ptr= g_p_FirstStudent;
		struct S_Student* slow_ptr= g_p_FirstStudent;
		while(fast_ptr && slow_ptr && fast_ptr->p_Next_Student)
		{
			fast_ptr = fast_ptr->p_Next_Student->p_Next_Student;
			slow_ptr = slow_ptr->p_Next_Student;
			count++;
		}
		DPRINTF("\nData of the node at index %d from the end is:\n",count);
		DPRINTF("Record Number %d\n", count + 1);
		DPRINTF("Name: %s\n", slow_ptr->student.name);
		DPRINTF("ID: %d\n", slow_ptr->student.ID);
		DPRINTF("Height: %0.2lf\n", slow_ptr->student.height);
		printf("-----------------------------\n");
		return 0;

	}


}



int DETECT_LIST_LOOP()
{
	struct S_Student* fast_ptr= g_p_FirstStudent;
	struct S_Student* slow_ptr= g_p_FirstStudent;
	while(fast_ptr && slow_ptr && fast_ptr->p_Next_Student)
	{
		fast_ptr = fast_ptr->p_Next_Student->p_Next_Student;
		slow_ptr = slow_ptr->p_Next_Student;

		if(slow_ptr == fast_ptr)
		{
			DPRINTF("\nFOUND LOOP IN YOUR LIST");
			return 1;
		}

	}
	DPRINTF("\nTHERE IS NO LOOP IN YOUR LIST");

	return 0;
}


void REVERSE_LIST()
{
	struct S_Student* p_PrevStudent = g_p_FirstStudent;
	struct S_Student* p_HeadStudent = g_p_FirstStudent;
	struct S_Student* p_CurrStudent = g_p_FirstStudent->p_Next_Student;
	struct S_Student* p_NextStudent = p_CurrStudent->p_Next_Student;

	while(p_CurrStudent != NULL)
	{
		p_NextStudent = p_CurrStudent->p_Next_Student;
		p_CurrStudent->p_Next_Student =p_PrevStudent;
		p_PrevStudent=p_CurrStudent;
		p_CurrStudent = p_NextStudent;
	}
	g_p_FirstStudent= p_PrevStudent;
}





