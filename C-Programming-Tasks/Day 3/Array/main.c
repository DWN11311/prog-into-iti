#include <stdio.h>
#include <stdlib.h>

int main()
{
    int mat1[3][2] = {{1, 2},{4, 5},{7, 8}};
    int mat2[2][1] = {{1},{4}};
    int newMat[3][1] = {{0},{0},{0}};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                newMat[i][j] += (mat1[i][k] * mat2[k][j]);
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            printf(" %i ", newMat[i][j]);
        }
        printf("\n");
    }

    return 0;
}
