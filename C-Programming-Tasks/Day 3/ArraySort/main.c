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

    // Bubble sort array
    int temp;
    for(int i = 0; i < 9; i++)
    {
        for(int j = i; j < 10; j++)
        {
            if(arr[i] > arr[j]){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            }
        }
    }

    // Display elements
    printf("\nArray: {");
    for(int i = 0; i < 10; i++)
    {
        printf(" %i ", arr[i]);
        if ( i < 9 ) printf(",");
    }
    printf("}.\n");

    return 0;
}
