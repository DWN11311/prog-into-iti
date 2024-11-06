#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define Enter 13
#define ESC 27
#define Left 75
#define Home 71
#define Right 77
#define End 79
#define Up 72
#define Down 80
#define Backspace 8

void gotoxy( int column, int row)
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

char** MultiLineEditor(int rows, int cols, int colPosition, int rowPosition){
    char **textPtr = malloc(sizeof(char*) * rows);
    int first[rows];
    int last[rows];
    int curr[rows];
    char* pFirst[rows];
    char* pLast[rows];
    char* pCurr[rows];
    int activeRow = 0;
    char* tempPtr;

    for(int i = 0; i < rows; i++){
        textPtr[i] = malloc(sizeof(char) * cols);
        first[i] = 0;
        last[i] = 0;
        curr[i] = 0;
        pFirst[i] = textPtr[i];
        pLast[i] = textPtr[i];
        pCurr[i] = textPtr[i];
    }

    int flag = 0;
    char ch;
    _flushall();

    do
    {
        gotoxy(curr[activeRow]+rowPosition,activeRow+colPosition);
        ch = getch();
        switch(ch)
        {
        case -32:
            ch = getch();
            switch(ch)
            {
            case Right:
                if(pCurr[activeRow] < pLast[activeRow])
                {
                    pCurr[activeRow]++;
                    curr[activeRow]++;
                }
                break;
            case Left:
                if(pCurr[activeRow] > pFirst[activeRow])
                {
                    pCurr[activeRow]--;
                    curr[activeRow]--;
                }
                break;
            case Up:
                if(activeRow > 0){
                    activeRow--;
                }
                break;
            case Down:
                if(activeRow < rows){
                    activeRow++;
                }
                break;
            }
            break;

        case Enter:
        case ESC:
            for(int i = 0; i < rows; i++)
            {
                *pLast[i] = '\0';
            }
            return textPtr;
            flag = 1;
            break;
        case Backspace:
            if(pCurr[activeRow] == pLast[activeRow] && pCurr[activeRow] != pFirst[activeRow])
            {
                curr[activeRow]--;
                pCurr[activeRow]--;
                pLast[activeRow]--;
                last[activeRow]--;
                gotoxy(curr[activeRow]+rowPosition, activeRow+colPosition);
                printf(" ");
            }
            else if(pCurr[activeRow] != pFirst[activeRow])
            {
                tempPtr = pCurr[activeRow]-1;
                gotoxy(curr[activeRow]-1+rowPosition, activeRow+colPosition);
                while(tempPtr < pLast[activeRow]-1)
                {
                    *tempPtr = *(tempPtr+1);
                    printf("%c", *tempPtr);
                    tempPtr++;
                }
                curr[activeRow]--;
                pCurr[activeRow]--;
                pLast[activeRow]--;
                last[activeRow]--;
                printf(" ");
            }
            break;

        default:
            if(!isprint(ch))
                break;
            if(pCurr[activeRow] > pFirst[activeRow] + cols - 1)
                break;
            if(pCurr[activeRow] == pLast[activeRow])
            {
                *pCurr[activeRow] = ch;
                printf("%c",*pCurr[activeRow]);
                pCurr[activeRow]++;
                pLast[activeRow]++;
                curr[activeRow]++;
                last[activeRow]++;
            }
            else
            {
                *pCurr[activeRow] = ch;
                printf("%c",*pCurr[activeRow]);
                pCurr[activeRow]++;
                curr[activeRow]++;
            }
            break;
        }
    }
    while(flag != 1);

    return textPtr;
}

void DisplayText(char** textPtr, int rowCount){
    for(int i = 0; i < rowCount; i++)
    {
        printf("%s\n", textPtr[i]);
    }
}

int main()
{
    char **text = MultiLineEditor(6, 30, 0, 0);
    system("CLS");
    printf("This is the result of the entered multi line text:\n");
    DisplayText(text, 6);
    return 0;
}
