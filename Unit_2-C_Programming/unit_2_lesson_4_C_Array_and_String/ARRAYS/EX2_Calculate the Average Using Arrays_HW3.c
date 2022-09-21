#include <stdio.h>

int main()
{
    int n;
    float array[100],sum=0;
    printf("Enter number of data: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        printf("%d.Enter number: ",i+1);
        scanf("%f", &array[i]);
        sum += array[i];
    }
    printf("Average= %.2f\n",sum/n);

}