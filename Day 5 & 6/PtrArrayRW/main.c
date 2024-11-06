#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[5];
    int *ptr;
    ptr = arr;

    // First method
    printf("First Method\n");
    for(int i = 0; i < 5; i++)
    {
        printf("Enter array elem #%i: ", i);
        scanf("%i", ptr);
        ptr++;
    }
    ptr = arr;

    printf("Array: ");
    for (int i =0; i < 5; i++)
    {
        printf(" %i ", *ptr);
        ptr++;
    }
    printf("\nPress any key to continue\n");
    getch();

    // Second method
    system("CLS");
    printf("Second Method\n");
    ptr = arr;
    for(int i = 0; i < 5; i++)
    {
        printf("Enter array elem #%i: ", i);
        scanf("%i", ptr+i);
    }

    printf("Array: ");
    for (int i =0; i < 5; i++)
    {
        printf(" %i ", *(ptr+i));
    }
    printf("\nPress any key to continue\n");
    getch();


    //Third Method
    system("CLS");
    printf("Third Method\n");
    ptr = arr;
    for(int i = 0; i < 5; i++)
    {
        printf("Enter array elem #%i: ", i);
        scanf("%i", &ptr[i]);
    }

    printf("Array: ");
    for (int i =0; i < 5; i++)
    {
        printf(" %i ", ptr[i]);
    }
    return 0;
}
