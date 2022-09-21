#include <stdio.h>
#define MAX 15
void reverse_elements(int arr[MAX])
{
    int size,i;
    int *p;
    p =&arr[0];
   
    printf("\nnput the number of elements to store in the array (max 15) : ");
    scanf("%d", &size);
    printf("\nInput 5 number of elements in the array :\n");
    
    for (int i = 0; i <size; i++)
    {
        printf("element-%d : ", i + 1);
        scanf("%d", p);
        p++;
    }
   p = &arr[size-1];
    printf("\nThe elements of array in reverse order are : ");
    for (i = size; i > 0; i--)
    {
        printf("\nelement-%d : %d", i, *p);
        p--;
    }
}
int main(int argc, char **argv)
{
    int arr[MAX];
    reverse_elements(arr);
}

