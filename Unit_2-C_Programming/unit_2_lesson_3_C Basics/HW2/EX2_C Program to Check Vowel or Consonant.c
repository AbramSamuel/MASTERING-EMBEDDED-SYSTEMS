#include <stdio.h>

int main()
{
    char x;
    printf("Enter an alphabet: ");
    scanf("%c", &x);
    if (x == 'a' || x == 'e'|| x == 'i'|| x == 'o'|| x == 'u'|| x == 'A'|| x == 'E'|| x == 'I' ||  x == 'N' || x == 'O'|| x == 'U')
        printf("%c is a vowel.", x);
    else
        printf("%c is consonant.", x);
}