#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a+b;
}

int sub(int a, int b)
{
    return a-b;
}

int main()
{
    int a = 2;
    printf("%d\n", (a == 2 ? add : sub)(7,5));
    return EXIT_SUCCESS;
}
