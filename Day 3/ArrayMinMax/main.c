#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[10];

    // Read elements
    for(int i = 0; i < 10; i++)
    {
        printf("Enter value for index #%i: ", i);
        scanf("%i", &arr[i]);
        printf("\n");
    }

    // Get min and max
    int min = arr[0];
    int max = arr[0];

    for(int i = 0; i < 10; i++)
    {
        if ( arr[i] > max) max = arr[i];
        if ( arr[i] < min) min = arr[i];
    }

    //  Display result
    printf("Min: %i\n", min);
    printf("Max: %i\n", max);

    return 0;
}
