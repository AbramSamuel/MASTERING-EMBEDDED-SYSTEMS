#ifndef STUDENTS_LIST_H_
#define STUDENTS_LIST_H_

// USER CONFIGURATION
#include "stdint.h"
#include "stdio.h"
// select the elements FIFO type
#define element_type uint8_t
#define NAME_LENGTH 20
#define COURSES_NUMBER 5


// TYPE DEFENITIONS
typedef struct
{
    uint8_t First_Name[NAME_LENGTH];
    uint8_t Last_Name[NAME_LENGTH];
    uint32_t Roll_Number;
   float GPA;
   uint32_t Course_ID[COURSES_NUMBER];

}Student_Data_t;

typedef struct
{
    uint32_t length;
    uint32_t count;
    Student_Data_t *base;
    Student_Data_t *head;
    Student_Data_t *tail;
} Students_FIFO_BUFF_t;

typedef enum
{
    FIFO_no_error,
    FIFO_full,
    FIFO_not_full,
    FIFO_empty,
    FIFO_null,
    error
}Students_List_status;


// APIs functions
Students_List_status LIST_INITIALIZE(Students_FIFO_BUFF_t *student, Student_Data_t *students, uint32_t students_count);
Students_List_status ADD_STUDENTDES_DETAILS_MANUALLY(Students_FIFO_BUFF_t *student, uint32_t num);
Students_List_status ADD_STUDENTDES_DETAILS_FROM_FILE(Students_FIFO_BUFF_t *student, uint32_t num);
Students_List_status FIND_STUDENT_BY_ROLL_NUMBER(Students_FIFO_BUFF_t *student, uint32_t Student_roll);
Students_List_status FIND_STUDENT_BY_FIRST_NAME(Students_FIFO_BUFF_t *student);
Students_List_status FIND_NUMBER_OF_REGISTERED_STUDENTS_IN_COURSE(Students_FIFO_BUFF_t *student);
Students_List_status NUMBER_OF_STUDENTS(Students_FIFO_BUFF_t *student);
Students_List_status DELETE_STUDENT_BY_ROLL_NUMBER(Students_FIFO_BUFF_t *student);
Students_List_status UPDATE_STUDENT(Students_FIFO_BUFF_t *student);
void SHOW_STUDENT(Student_Data_t *student_info);
Students_List_status SHOW_ALL_STUDENTS(Students_FIFO_BUFF_t *student);

#endif //  STUDENTS_LIST_H_