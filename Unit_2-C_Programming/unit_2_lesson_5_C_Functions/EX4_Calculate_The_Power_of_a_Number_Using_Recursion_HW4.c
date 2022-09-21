#include <stdio.h>
int Power (int base, int power_number);

int main()
{
    int base, power_number;
    printf("Enter a base number: "); 
    scanf("%d", &base);
    printf("Enter power number: ");
    scanf("%d", &power_number);
    printf("%d ^ %d = %d", base, power_number, Power(base, power_number));
}

 int Power(int base, int power_number)
{
    if (power_number > 0)
    { 
            return (base * Power(base, power_number - 1));
    } 
  
   else
   return 1;
    
}