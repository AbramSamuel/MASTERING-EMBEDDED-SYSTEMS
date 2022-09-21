#include <stdio.h>
struct SEmployee
{
    char *Name;
    int Id;
};


int main(int argc, char **argv)
{
    struct SEmployee Employee1={"Abram",1001};
    struct SEmployee Employee2={"Alex",1002};
    struct Semployee *PEmployees[]={&Employee1,&Employee2};
    struct SEmployee *(*PEmployeesptr)[]=&PEmployees;

    printf("\nExmployee Name : %s",(**(*PEmployeesptr+1)).Name);
    printf("\nExmployee ID : %d\n",(*(*PEmployeesptr+1))->Id);
    
}