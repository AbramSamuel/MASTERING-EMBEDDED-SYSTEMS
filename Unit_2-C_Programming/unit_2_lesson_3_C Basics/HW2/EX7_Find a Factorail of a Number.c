#include <stdio.h>

int main()
{
    int n;
    int factorial = 1;
    printf("Enter an integer: ");
    scanf("%d", &n);
    if (n == 0 || n == 1)
    {
        printf("Factorial = 1\n");
    }
    else if (n > 1)
    {
        while(n>0)
        {
            factorial *= n;
            n--;
        }
        printf("Factorial = %d\n", factorial);
    }
    else
    {
        printf("Error!!! Factorial of negative number does not exist!\n");
    }
}