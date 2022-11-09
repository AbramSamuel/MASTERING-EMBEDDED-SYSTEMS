
#include "Students_List.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENTS_NUMBER 50
#define COURSES_NUMBER 5

extern Students_FIFO_BUFF_t list;

Students_List_status LIST_INITIALIZE(Students_FIFO_BUFF_t *student, Student_Data_t *students, uint32_t students_count)
{
    // check if the buffer is empty
    if (students == NULL)
        return FIFO_null;

        student->base = students;
        student->head = students;
        student->tail = students;
        student->count = 0;
        student->length = students_count;
        return FIFO_no_error;
}
Students_List_status ADD_STUDENTDES_DETAILS_MANUALLY(Students_FIFO_BUFF_t *student,uint32_t num)
{
    uint8_t temp[20];
    uint32_t i;
    // check if the list is existing
    if (!student->head|| !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    // check if the list is full
    if (student->count == student->length)
    {
        printf("\n[INFO] The list is full ");
        printf("\n______________________________________________");

        return FIFO_full;
    }
    Student_Data_t *temp_roll= student->base;
    printf("\nEnter the roll number: ");
    gets(temp);
    student->head->Roll_Number = atoi(temp);

    while (temp_roll != student->head)
    {
        if (temp_roll->Roll_Number == student->head->Roll_Number)
        {
            printf("\nRoll %d Number is already taken\n", temp_roll->Roll_Number);
            return error;
        }
        temp_roll++;
    }
    printf("\nEnter the first name: ");
    gets(student->head->First_Name);

    printf("\nEnter the last name: ");
    gets(student->head->Last_Name);

    printf("\nEnter GPA: ");
    gets(temp);
    student->head->GPA = atof(temp);

    printf("\nEnter Courses: ");
    for(i= 0; i<COURSES_NUMBER; i++)
    {
        printf("\nEnter the Course( %d ) ID: ",i+1);
        gets(temp);
        student->head->Course_ID[i]=atoi(temp);
    }
    student->head ++;
    student->count++;
    printf("\n[INFO] You can add %d more students", num - student->count);
    printf("\n ______________________________________________________");
    return FIFO_no_error;

    
}
Students_List_status ADD_STUDENTDES_DETAILS_FROM_FILE(Students_FIFO_BUFF_t *student, uint32_t num)
{
    uint32_t i;
    // check list initialized

    if (!student->base || !student->head)
        return FIFO_null;
    // check if the list is full
    if (student->count == student->length)
    {
        printf("\n[INFO] The list is full");
        printf("\n______________________________________________");

        return FIFO_full;
    }
FILE *txt_file;
txt_file = fopen("ABRAM.txt", "r");
while (!feof(txt_file))
{

    fscanf(txt_file, "%d", &student->head->Roll_Number);
    if (FIND_STUDENT_BY_ROLL_NUMBER(&list,student->head->Roll_Number)!= error)
    {
        printf("\nRoll %d Number is already taken\n", student->head->Roll_Number);
        fscanf(txt_file, "%*[^\n]");
        continue;
    }
    fscanf(txt_file, "%s", &student->head->First_Name);
    fscanf(txt_file, "%s", &student->head->Last_Name);
    fscanf(txt_file, "%f", &student->head->GPA);
    for (i = 0; i < COURSES_NUMBER;i++)
    {
        fscanf(txt_file, "%d", &student->head->Course_ID[i]);
    }
    student->head++; 
    student->count++;

}
fclose(txt_file);

printf("\n[INFO] You can add %d more students", num - student->count);
printf("\n ______________________________________________________");
return FIFO_no_error;
}
Students_List_status FIND_STUDENT_BY_ROLL_NUMBER(Students_FIFO_BUFF_t *student,uint32_t Student_roll_selected)
{
    // check if the list is existing
    if (!student->head || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }

    Student_Data_t *Find_Roll = student->base;
    while (Find_Roll != student->head)
    {
        if (Student_roll_selected == Find_Roll->Roll_Number)
        {
            student->tail = Find_Roll;
            return FIFO_no_error;
        }
        Find_Roll++;
    }
    return error;
}
Students_List_status FIND_STUDENT_BY_FIRST_NAME(Students_FIFO_BUFF_t *student)
{
    uint8_t temp[20];
    uint32_t i;

    // check if the list is existing
    if (!student->head || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    if (student->count == 0)
    {
        printf("\n[INFO] The list is empty");
        printf("\n______________________________________________");
        return FIFO_empty;
    }

    Student_Data_t *Student_first_name = student->base;
    uint32_t flag=0;
        printf("\nEnter the First Name of the Student: ");

    gets(temp);
    while (Student_first_name != student->head)
    {
        if (strcmp(temp, Student_first_name->First_Name) == 0)
        {
            flag=1;
            printf("\n______________Student Details are_________________ ");
            SHOW_STUDENT(Student_first_name);
        }
        Student_first_name++;
    }
    if(flag ==0)
    {
        printf("\n[ERROR] First Name %s not found",temp);
        printf("\n______________________________________________");
        return error;
    }
    return FIFO_no_error;
}
Students_List_status FIND_NUMBER_OF_REGISTERED_STUDENTS_IN_COURSE(Students_FIFO_BUFF_t *student)
{
    uint8_t temp[20];
    uint32_t i;
    // check if the list is existing
    if (!student->head || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    if (student->count == 0)
    {
        printf("\n[INFO] The list is empty");
        printf("\n______________________________________________");
        return FIFO_empty;
    }

    Student_Data_t *student_Course= student->base;
    printf("\nEnter the Course ID: ");
    gets(temp);
    int course_id=atoi(temp),flag = 0 , counter=0;
    
    while(student_Course != student->head)
    {
        for(i=0; i<COURSES_NUMBER; i++)
        {
            if (student_Course->Course_ID[i] == course_id)
            {
                flag =1;
                counter++;
            }
        }
        student_Course++;
    }
    if(flag ==0)
    {
        printf("\n[INFO] Course ID %d not found.",course_id);
        printf ("\n______________________________________________");
        return error;
    }
    else
    {
        printf("\nTotal Number of Students Enrolled in Course ID (%d) = %d\n", course_id, counter);
        printf("\n______________________________________________");
        return FIFO_no_error;
    }

}
Students_List_status NUMBER_OF_STUDENTS(Students_FIFO_BUFF_t *student)
{
    // check if the list is existing
    if (!student->base || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    if (student->count == 0)
    {
        printf("\n[INFO] The list is empty");
        printf("\n[INFO] Total Number of Students = %d", student->count);
        printf("\n[INFO] You can add up to %d students", STUDENTS_NUMBER);
        printf("\n[INFO] You can add %d more students", STUDENTS_NUMBER - student->count);
        printf("\n______________________________________________");
        return FIFO_empty;
    }

    printf("\n[INFO] Total Number of Students = %d", student->count);
    printf("\n[INFO] You can add up to %d students", STUDENTS_NUMBER);
    printf("\n[INFO] You can add %d more students", STUDENTS_NUMBER - student->count);
    printf("\n______________________________________________");
    return FIFO_no_error;
}
Students_List_status DELETE_STUDENT_BY_ROLL_NUMBER(Students_FIFO_BUFF_t *student)
{
    uint8_t temp[20];
    uint32_t i;
    int flag =0;
    // check if the list is existing
    if (!student->base || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    if(student->count == 0)
    {
        printf("\n[INFO] The list is empty you cannot delete any students");
        printf("\n______________________________________________");
        return FIFO_empty;
    }
    Student_Data_t *Current_Student = student->base;
    Student_Data_t *Next_Student =(Student_Data_t*)(Current_Student+1);
    printf("\nEnter the Roll Number which will be deleted: ");
    gets(temp);
    int roll_number_deleted;
    roll_number_deleted = atoi(temp);
    while (Current_Student != student->head)
    {
        if (roll_number_deleted==Current_Student->Roll_Number || flag==1)
        {
            flag =1;
            strcpy(Current_Student->First_Name,Next_Student->First_Name);
            strcpy(Current_Student->Last_Name,Next_Student->Last_Name);
            Current_Student->GPA = Next_Student->GPA;
            Current_Student->Roll_Number = Next_Student->Roll_Number;
            for(i=0; i<COURSES_NUMBER; i++)
            {
                Current_Student->Course_ID[i]= Next_Student->Course_ID[i];
            }
           
        }
        
        Current_Student ++;
        Next_Student ++;
    }
    if(flag ==0)
    {
        printf("\n[INFO] This Roll Number %d not Found", roll_number_deleted);
        printf("\n______________________________________________");
        return error;
    }
    else{
        printf("\n[INFO] THE ROLL NUMBER %d IS REMOVED SUCCESSFULLY", roll_number_deleted);
        printf("\n______________________________________________");
        student->head--;
        student->count--;
       
        return FIFO_no_error;
    }
        
}
Students_List_status UPDATE_STUDENT(Students_FIFO_BUFF_t *student)
{
    uint8_t temp[20];
    int flag = 0;

    // check if the list is existing
    if (!student->base || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    if (student->count == 0)
    {
        printf("\n[INFO] The list is empty you can't update the list");
        printf("\n______________________________________________");
        return FIFO_empty;
    }
    Student_Data_t *Student_update = student->base;
    printf("\nEnter the Roll Number of the student to be updated: ");
    gets(temp);
    int updated_roll ;
    updated_roll = atoi(temp);
    while (Student_update != student->head)
    {
        uint32_t i;
        char str_temp2[COURSES_NUMBER];

        if (updated_roll == Student_update->Roll_Number)
        {
            flag =1;
            printf("\nChoose the element to be updated: ");
            printf("\n1: first name");
            printf("\n2: last name");
            printf("\n3: roll number");
            printf("\n4: GPA");
            printf("\n5: courses");
            printf("\nYour Choice: ");
            gets(temp);
            switch (atoi(temp))
            {
            case 1:
                printf("\nEnter the new first name: ");
                gets(Student_update->First_Name);
                printf("\n______________________________________________");

                break;
            case 2:
                printf("\nEnter the new last name: ");
                gets(Student_update->Last_Name);
                printf("\n______________________________________________");

                break;
            case 3:
                printf("\nEnter the new roll number: ");
                printf("\n______________________________________________");

                gets(temp);
                int new_roll = atoi(temp);
                if (FIND_STUDENT_BY_ROLL_NUMBER(&list, new_roll) != error)
                {
                    printf("\nRoll %d Number is already taken\n", new_roll);
                    printf("\n______________________________________________");
                    break;
                }
                Student_update->Roll_Number = new_roll;
                break;
            case 4:
                printf("\nEnter the new GPA: ");
                gets(temp);
                Student_update->GPA = atof(temp);
                break;
            case 5:
                printf("\nEnter the new courses: ");
                for (i = 0; i < COURSES_NUMBER; i++)
                {
                    printf("\nEnter the Course %d ID", i + 1);
                    gets(str_temp2);
                    Student_update->Course_ID[i] = atoi(str_temp2);
                }
                break;

            default:
                break;
            }
       }
        Student_update++;
    }

    if (flag==0)
    {
        printf("\n[INFO] This Roll Number %d not Found ", updated_roll);
        printf("\n______________________________________________");
        return error;
    }
    else
    return FIFO_no_error;
}
void SHOW_STUDENT(Student_Data_t *student_info)
{
    int i=0;
    printf("\nThe First Name is: %s ", student_info->First_Name);
    printf("\nThe First Last is: %s ", student_info->Last_Name);
    printf("\nThe Roll Number is: %d ", student_info->Roll_Number);
    printf("\nThe GPA is: %.2f ", student_info->GPA);
    printf("\nCourses of the student are:- ");
    for(i=0;i<COURSES_NUMBER;i++)
    {
        printf("\nCourse (%d) ID is: %d ", i + 1, student_info->Course_ID[i]);
    } 
    printf("\n______________________________________________");
}
Students_List_status SHOW_ALL_STUDENTS(Students_FIFO_BUFF_t *student)
{
    int counter = 0;
    // check if the list is existing
    if (!student->base || !student->tail || !student->head)
    {
        printf("\n[INFO] The list does not exist");
        printf("\n______________________________________________");

        return FIFO_null;
    }
    if (student->count == 0)
    {
        printf("\n[INFO] The list is empty");
        printf("\n______________________________________________");
        return FIFO_empty;
    }
    if (student->count == 0)
    {
        printf("\n[INFO] The list is empty");
        printf("\n______________________________________________");
        return FIFO_empty;
    }
    printf("\n                        **** ALL STUDENTS INFORMATION ****                            :-");

    Student_Data_t *students = student->base;

    while (students != student->head)
    {
        printf("\n__________________ Student Number (%d) Information _______________________",counter+1);
        SHOW_STUDENT(students);
        students++;
        counter++;
    }
    return FIFO_no_error;
    

}