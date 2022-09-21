#include <stdio.h>

int main()
{
    int n, a[100], i,searched;

    printf("Enter no. of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("\n");
    printf("Enter the element to be searched: ");
    scanf("%d", &searched);
    printf("\n");
    for(i = 0; i < n; i++)
    {
        if (a[i] ==searched)
        {
            printf("Number found at location = %d", i+1);
           break;
        }
        
    }
}