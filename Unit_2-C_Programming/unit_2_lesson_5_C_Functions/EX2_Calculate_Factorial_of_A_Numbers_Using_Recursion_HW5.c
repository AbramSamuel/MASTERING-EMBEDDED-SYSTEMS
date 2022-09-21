#include <stdio.h>

int factorial(int n);

int main(int argc, char const *argv[])
{
    int n;
    printf("Enter a positive integer number: ");
    scanf("%d", &n);
    printf("\n Factorial of %d = %d\n", n, factorial(n));
    return 0;
}

int factorial(int n)
{
    if (n !=1)
    {
        return n*factorial(n-1);
    }
}