#include <stdio.h>

int main()
{
    int rows, cols, a[100][100], i, j;
    printf("Enter rows and columns of matrix: ");
    scanf("%d   %d", &rows, &cols);
    printf("\nEnter elements of matrix:\n");
    for ( i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Enter elements a%d%d: ", i+ 1, j+ 1);
            scanf("%d", &a[i][j]);
        }
    }
    printf("\n");
    printf("Entered Matrix:\n");
    for ( i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Transposed Matrix:\n");
    for(i=0;i<cols;i++)
    {
        for(j=0;j<rows;j++)
        {
            printf("%d\t", a[j][i]);
        }
        printf("\n");
    }
}