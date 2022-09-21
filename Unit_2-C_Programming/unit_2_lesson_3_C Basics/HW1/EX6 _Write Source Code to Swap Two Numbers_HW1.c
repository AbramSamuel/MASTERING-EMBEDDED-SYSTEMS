#include <stdio.h>

int main()
{
    float a, b,swap;
    printf("Enter value of a: ");
    scanf("%f",&a);
    printf("Enter value of b: ");
    scanf("%f",&b);
    swap = a;
    a = b;
    b=swap;
    
    printf("\n");
    printf("After swapping, value of a = %.2f\n",a);
    printf("After swapping, value of b = %.1f",b);
}