
// Write Source Code to Swap Two Numbers without temp variable.

#include <stdio.h>

void main()
{
    float a, b, swap;
    printf("Enter value of a: ");
    scanf("%f", &a);
    printf("Enter value of b: ");
    scanf("%f", &b);
    a = a+b;
    b= a-b;
    a = a-b;
    printf("\n");
    printf("After swapping, value of a = %f\n", a);
    printf("After swapping, value of b = %f", b);
}