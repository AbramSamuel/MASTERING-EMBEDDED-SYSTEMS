#include <conio.h>
#include <string.h>
#include <stdio.h>

struct SStudent
{
    char s_name[100];
    int s_roll_number;
    float s_marks;
};

int main(int argc, char **argv)
{
    struct SStudent student[10];
    int count = 0;
    char name[100];
    printf("Enter information of Students:\n");
    do
    {
        printf("\nEnter name: ");
        scanf("%s", &student[count].s_name);
        printf("Enter roll number: ");
        scanf("%d", &student[count].s_roll_number);
        printf("Enter  marks: ");
        scanf("%f", &student[count].s_marks);
        count++;
        if (count == 100) break;
        printf("\nDo you want to add a new student? (y/n): ");

    } while (getch() == 'y');

    for (int i = 0; i < count; i++)
    {
        printf("\n\nname: %s\n", student[i].s_name);
        printf("roll number: %d\n", student[i].s_roll_number);
        printf("marks: %.2f",student[i].s_marks);
    }
    
    return 0;
}

