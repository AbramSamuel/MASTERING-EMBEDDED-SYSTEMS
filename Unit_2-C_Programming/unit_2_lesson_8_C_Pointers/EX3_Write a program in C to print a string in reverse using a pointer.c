#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char str1[100],str2[100];
    char *p1,*p2;
    printf("\nInput a string: ");
    gets(str1);
    p1 = str1 + strlen(str1) - 1;
    p2 = str2;
   
    while(p1 >= str1)
    {
        *p2=*p1;
        p2++;
        p1--;
    }
    *p2 = '\0';
    
    printf("\nreverse of the string is: %s\n",str2);
    return 0;
}