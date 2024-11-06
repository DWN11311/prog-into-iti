#include <stdio.h>
#include <stdlib.h>
void SetArray(int *ptr, int size){
    for(int i = 0; i < size; i++)
    {
        printf("Enter array elem #%i: ", i);
        scanf("%i", &ptr[i]);
    }
}

void PrintArray(int *ptr, int size){
    printf("Array: ");
    for(int i = 0; i < size; i++)
    {
        printf(" %i ", ptr[i]);
    }
}

int main()
{
    int arr[5];
    SetArray(arr, 5);
    PrintArray(arr, 5);

    return 0;
}
