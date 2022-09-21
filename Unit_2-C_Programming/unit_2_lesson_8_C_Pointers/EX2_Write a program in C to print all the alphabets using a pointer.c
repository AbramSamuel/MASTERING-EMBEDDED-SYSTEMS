#include <stdio.h>

int main(int argc, char **argv)
{
    char chs[27];
    char *p;
    p = chs;
    int i;
     for (i = 0; i < 26; i++)
    {
        *p = i+'A';
        p++;
    }
    p = chs;
    printf("\nThe Alphabets are :\n");
    for(i = 0; i < 26; i++)
    {
        printf("%c ", *p);
        p++;
    }
    printf("\n");
}