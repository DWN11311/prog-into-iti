#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

void gotoxy( int column, int row )
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

int main()
{
    int size;
    do{
        printf("Enter an odd number larger than 1: ");
        scanf("%i", &size);
    }while(size % 2 == 0 || size == 1);

    system("CLS");

    int row, col;
    row = 1;
    col = size / 2 + 1;
    for (int i = 1; i <= size * size; i++)
    {
        gotoxy(col*3, row*3);
        printf("%i", i);
        if ( i % size != 0)
        {
            col--;
            row--;
            if(col<1) col = size;
            if(row<1) row = size;
        }
        else {
            row++;
        }
    }
    for(int i = 0; i < 5; i++)
    {
        printf("\n");
    }
    printf("-----------------------------------");
    return 0;
}
