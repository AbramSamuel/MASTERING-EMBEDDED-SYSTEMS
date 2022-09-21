#include <stdio.h>
void reverse();
int main()
{
    printf("Enter a sentence: ");
    reverse();
    return 0;
}

void reverse()
{
    char a;
    scanf("%c", &a);
    if(a != '\n')
    {
        reverse();
        printf("%c", a);
    }
}