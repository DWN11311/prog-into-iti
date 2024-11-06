#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    // Print 2D array
    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf(" %i ", arr[i][j]);
        }
        printf("\n");
    } */

    int sum[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sum[i] += arr[j][i];
        }
    }

    for(int i = 0; i < 4; i++)
    {
        sum[i] /= 3;
    }

    printf(" %i ", sum[0]);
    printf(" %i ", sum[1]);
    printf(" %i ", sum[2]);
    printf(" %i ", sum[3]);

    return 0;
}
