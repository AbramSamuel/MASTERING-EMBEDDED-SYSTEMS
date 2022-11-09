#include "Students_List.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENTS_NUMBER 50

Student_Data_t students[STUDENTS_NUMBER];
Students_FIFO_BUFF_t list;
char str_temp[20]; 
void main()
{
    if (LIST_INITIALIZE(&list, students,STUDENTS_NUMBER) == FIFO_no_error)
    {
        printf("\n                                      >>>>>>>LIST IS INITIALIZED SUCCESSUFULLY.<<<<<<<<\n");
    }
    printf("\n*** WELCOME TO THE STUDENTS MANAGEMENT SYSTEM ***\n");
    while(1)
    {
        printf("\nchose the task that you want perform :");
        printf("\n1:Add The Student Details Manually");
        printf("\n2:Add The Student Details From Text File");
        printf("\n3:Find The Student Details By Roll Number");
        printf("\n4:Find The Student Details By First Name");
        printf("\n5:Find The Number of Students Registered in a Course By Course ID");
        printf("\n6:Find The Total Number of student");
        printf("\n7:Delete The Student Details By Roll NUmber");
        printf("\n8:Update The Student Details By Roll NUmber");
        printf("\n9:Show All Students Information");
        printf("\n10:Exit");
        printf("\n______________________________________________________");
        printf(" \n Enter Your Choice: ");
        gets(str_temp);
        switch (atoi(str_temp))
        {
        case 1:
            ADD_STUDENTDES_DETAILS_MANUALLY(&list, STUDENTS_NUMBER);
            break;
        case 2:
            ADD_STUDENTDES_DETAILS_FROM_FILE(&list, STUDENTS_NUMBER);
            break;
        case 3:
            printf("\nEnter The Roll Number of the Student: ");
            gets(str_temp);
            if (FIND_STUDENT_BY_ROLL_NUMBER(&list, atoi(str_temp)) != error)
            {
                SHOW_STUDENT(list.tail);
            }
            else
            {
                printf("\n[INFO] This Roll Number %d not Found",atoi(str_temp));
                printf("\n________________________________________________");
            }
            break;
        case 4:
            FIND_STUDENT_BY_FIRST_NAME(&list);
            break;
        case 5:
            FIND_NUMBER_OF_REGISTERED_STUDENTS_IN_COURSE(&list);
            break;
        case 6:
            NUMBER_OF_STUDENTS(&list);
            break;
        case 7:
            DELETE_STUDENT_BY_ROLL_NUMBER(&list);
            break;
        case 8:
            UPDATE_STUDENT(&list);
            break;
        case 9:
            SHOW_ALL_STUDENTS(&list);
            break;
        case 10:
            exit(1);
            break;
        default:
            printf("\nERROR: Unknown Option");
            printf("\n________________________________________________");

            break;
        }
    }
}