#include <stdio.h>
#include <stdlib.h>

int main()
{
    int _size;
    printf("Enter array size: ");
    scanf("%i", &_size);

    int *arrPtr = malloc(sizeof(int) * _size);

    for(int i = 0; i < _size; i++)
    {
        printf("Enter array element #%i: ", i);
        scanf("%i", &arrPtr[i]);
    }

    printf("Array: ");
    for(int i = 0; i < _size; i++)
    {
        printf(" %i ", arrPtr[i]);
    }

    return 0;
}
