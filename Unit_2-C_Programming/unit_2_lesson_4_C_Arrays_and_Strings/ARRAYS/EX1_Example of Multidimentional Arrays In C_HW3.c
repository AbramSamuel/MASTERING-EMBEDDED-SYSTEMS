#include <stdio.h>

int main()
{
    float a[2][2],b[2][2];
    int i, j;
    float sum[2][2];
    printf("Enter the elements of 1st Matrix\n");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            printf("Enter a%d%d:",i+1,j+1);
            scanf("%f",&a[i][j]);
        }
        
    }
    printf("\n");
    printf("Enter the elements of 2st Matrix\n");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("Enter b%d%d:", i+1, j+1);
            scanf("%f", &b[i][j]);
        }
    }
    for(i=0;i<2;i++)
    {
        for(j= 0;j<2;j++)
        {
            sum[i][j]=a[i][j]+b[i][j];

        }
    }
    printf("\nSum of Matrix:\n");
    for(i=0;i<2;i++)
    {
        for (j=0;j<2;j++)
        {
            printf("%.1f\t", sum[i][j]);
        }
        printf("\n");
    }
    

}