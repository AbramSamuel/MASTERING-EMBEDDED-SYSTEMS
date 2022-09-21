#include <stdio.h>
#include <string.h>

int main()
{
    char string[1000],reversed_string[1000];
    int i,j;
    printf("\nEnter a string: ");
    gets(string);
    int n =strlen(string);
    for (i = 0,j=n-1; i < n && j>=0; i++,j--)
    {
        reversed_string[j] = string[i];
    }
    printf("\nReversed string: %s",reversed_string);
    
}