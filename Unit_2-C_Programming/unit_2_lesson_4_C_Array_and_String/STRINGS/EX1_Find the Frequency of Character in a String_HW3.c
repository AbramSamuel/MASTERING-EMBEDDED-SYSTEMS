#include <stdio.h>
#include <string.h>

int main()
{
    char sentence[1000],c;
    int count = 0,i; 
    printf("\nEnter a string: "); 
    gets( sentence);
    printf("\nEnter a character to find frequency: ");
    scanf("%c",&c);
    for (i=0; sentence[i]!='\0'; i++)
    {
        if (c == sentence[i])
        {
            count++;
        }
    }
    printf("\nfrequency of %c = %d\n",c,count);
}