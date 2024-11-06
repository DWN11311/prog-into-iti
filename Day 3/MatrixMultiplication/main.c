#include <stdio.h>
#include <stdlib.h>

int main()
{
    int mat1[3][3] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int mat2[3][3] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int newMat[3][3] = {{0},{0},{0}};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                newMat[i][j] += (mat1[k][j] * mat2[i][k]);
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %i ", newMat[i][j]);
        }
        printf("\n");
    }

    return 0;
}
