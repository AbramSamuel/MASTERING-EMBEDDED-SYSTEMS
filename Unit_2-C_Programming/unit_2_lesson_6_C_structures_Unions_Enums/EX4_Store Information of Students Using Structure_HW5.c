#include <conio.h>
#include <stdio.h>
#include <string.h>

struct SStudent
{
    char s_name[100];
    int s_roll_number;
    float s_marks;
};

int main(int argc, char **argv)
{
    struct SStudent student[10];
    int i;
    char name[100];
    printf("Enter information of Students:\n");
    for ( i = 0; i < 10; i++)
    {
        student[i].s_roll_number = i+1;
        printf("\nFor roll number: %d", student[i].s_roll_number);
        printf("\nEnter name: ");
        scanf("%s", &student[i].s_name);
        printf("Enter  marks: ");
        scanf("%f", &student[i].s_marks);
    
    }
    for ( i = 0; i < 10; i++)
    {
        printf("\nFor roll number: %d\n", i + 1);
        printf("name: %s\n", student[i].s_name);
        
        printf("marks: %.1f\n", student[i].s_marks);
    }

    return 0;
}
