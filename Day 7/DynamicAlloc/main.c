#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr = malloc(sizeof(int));

    printf("Enter a number: ");
    scanf("%i", ptr);

    printf("Address of dynamically allocated integer: %x.\n", ptr);
    printf("Value of dynamically allocated integer: %i.\n", *ptr);

    return 0;
}
