#include <ctype.h>
#include <stdio.h>
int main()
{
    char c;
    printf("Enter a character: ");
    scanf("%c", &c);
    if (isalpha(c))
    {
        printf("%c is alphabet",c);

    }
    else
    {
        printf("Entered value is not alphabet");
    }
     
}
