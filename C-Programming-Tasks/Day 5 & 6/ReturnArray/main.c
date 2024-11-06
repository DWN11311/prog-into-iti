#include <stdio.h>
#include <stdlib.h>

int* GetArray(){
    static int arr[5] = {1, 2 ,3 ,4, 5};
    return arr;
}

int main()
{

    int *ptr;

    ptr = GetArray();

    printf("Array: ");
    for(int i = 0; i < 5; i++)
    {
        printf(" %i ", ptr[i]);
    }

    return 0;
}
