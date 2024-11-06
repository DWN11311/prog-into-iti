#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Q2 / Read a character and printing its ASCII Value
    char ch;
    printf("Please enter a character: ");
    scanf("%c", &ch);
    printf("The ASCII Code for the entered character \"%c\" is: %i\n\n", ch, ch);
    return 0;
}
