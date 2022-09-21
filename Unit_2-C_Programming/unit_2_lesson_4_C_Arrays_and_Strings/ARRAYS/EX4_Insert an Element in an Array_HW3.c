#include <stdio.h>

int main()
{
    int n, a[100], i,inserted,index;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("\n");
    printf("Enter the element to be inserted: ");
    scanf("%d", &inserted);
    printf("\n");
    printf("Enter the location: ");
    scanf("%d", &index);
    printf("\n");
    for(i = n; i >=index; i--)
    {
        a[i]= a[i-1];
    }
    a[index-1]=inserted;
    for(i = 0; i <=n; i++)
    {
        printf(" %d ", a[i]);
    }

}