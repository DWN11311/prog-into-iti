#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rowSize, colSize;

    printf("Enter number of rows: ");
    scanf("%i", &rowSize);
    printf("Enter number of columns: ");
    scanf("%i", &colSize);

    // Dynamically allocate 2D array
    int **arrPtr = malloc(sizeof(int*) * rowSize);
    for(int i = 0; i < rowSize; i++)
    {
        arrPtr[i] = malloc(sizeof(int) * colSize);
    }

    // Read from user
    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            printf("Enter value for [%i, %i]: ",i,j);
            scanf("%i", &arrPtr[i][j]);
        }
    }

    // Display 2D array
    printf("\n");
    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            printf(" %i ", arrPtr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
