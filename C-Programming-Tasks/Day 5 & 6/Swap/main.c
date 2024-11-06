#include <stdio.h>
#include <stdlib.h>

void Swap(int *left, int *right){
    int tmp = *left;
    *left = *right;
    *right = tmp;
}

int main()
{
    int x = 5;
    int y = 7;

    printf("Before swapping: (X: %i, Y: %i)\n",x, y);
    Swap(&x, &y);
    printf("After swapping: (X: %i, Y: %i)\n",x, y);

    return 0;
}
