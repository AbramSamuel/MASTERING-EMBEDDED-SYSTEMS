#include <stdio.h>

struct SDistance
{
    int s_feet;
    float s_inches;
} d1, d2, result;

int main(int argc, char **argv)
{
     printf("\nEnter information of 1st distance\n");
    printf("Enter feet : ");
    scanf("%d",&d1.s_feet);
    printf("Enter inches : ");
    scanf("%f",&d1.s_inches);
    printf("\nEnter information of 2nd distance\n");
    printf("Enter feet : ");
    scanf("%d",&d2.s_feet);
    printf("Enter inches : ");
    scanf("%f",&d2.s_inches);
    result.s_feet = d1.s_feet + d2.s_feet;
    result.s_inches = d2.s_inches + d1.s_inches;
    if (result.s_inches > 12.0)
    {
        result.s_inches = result.s_inches - 12.0;
        result.s_feet++;
    }

    printf("\nSum of distances = %d\' - %.1f\"\n", result.s_feet, result.s_inches);
    return 0;

}