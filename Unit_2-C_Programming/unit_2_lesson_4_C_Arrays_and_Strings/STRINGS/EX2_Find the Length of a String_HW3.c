#include <string.h>
#include <stdio.h>

int main()
{
    char sentence[1000];
    int count = 0, i;
    printf("\nEnter a string: ");
    gets(sentence);
    for (i = 0; sentence[i] != '\0'; i++)
    {
            count++;
    }
    printf("\nLength of string: %d\n",count);
}