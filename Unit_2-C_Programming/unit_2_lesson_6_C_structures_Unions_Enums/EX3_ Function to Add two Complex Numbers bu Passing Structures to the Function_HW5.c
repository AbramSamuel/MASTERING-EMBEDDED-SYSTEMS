#include <stdio.h>

struct SComplex
{
    double s_real, s_imag;
} n1, n2, result;

struct SComplex Add_Complex_Numbers(struct SComplex n1, struct SComplex n2);

int main(int argc, char **argv)
{
    printf("\nFor 1st complex number\n");
    printf("Enter real and imaginary values respectively: ");
    scanf("%lf %lf", &n1.s_real, &n1.s_imag);
    printf("\nFor 2nd complex number\n");
    printf("Enter real and imaginary values respectively: ");
    scanf("%lf %lf",&n2.s_real,&n2.s_imag);
    result = Add_Complex_Numbers(n1, n2);
    printf("Sum = %.1lf+%.1lfi\n",result.s_real, result.s_imag);
}

struct SComplex Add_Complex_Numbers(struct SComplex n1, struct SComplex n2)
{
    struct SComplex sum;
    sum.s_real = n1.s_real + n2.s_real;
    sum.s_imag = n1.s_imag + n2.s_imag;
    return sum;
}
