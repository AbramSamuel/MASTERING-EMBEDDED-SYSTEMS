#include <stdio.h>

int main()
{
    int n;
    int sum = 0;
    printf("Enter an integer number: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    printf("Sum= %d\n",sum);
}