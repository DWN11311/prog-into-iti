#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Q3 / Print the hex value of a number
    int integer;
    printf("Please enter a number: ");
    scanf("%i", &integer);
    printf("\nThe hexadecimal value for the number %i is: %x\n", integer, integer);
    return 0;
}
