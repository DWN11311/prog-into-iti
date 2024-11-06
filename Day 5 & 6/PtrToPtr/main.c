#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    int *ptr = &x;
    int* *ptrToPtr = &ptr;

    printf("Enter a number: ");
    scanf("%i", *ptrToPtr);

    printf("You entered: %i", **ptrToPtr);

    return 0;
}
