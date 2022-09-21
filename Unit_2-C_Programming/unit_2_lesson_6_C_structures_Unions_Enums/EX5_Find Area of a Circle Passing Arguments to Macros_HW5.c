#include <stdio.h>
#define PI 3.14
#define area(r) (PI*r*r)
int main(int argc, char **argv)
{
    int r;
    float area;
    printf("\nEnter the radius: ");
    scanf("%d", &r);
    area=area(r);
    printf("\nArea= %.2f\n", area);

    return 0;
}