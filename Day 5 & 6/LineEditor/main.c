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

void gotoxy( int column, int row )
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



int main()
{
    int first, curr, last;
    char *pFirst, *pCurr, *pLast;
    int flag = 0;
    char text[30];
    char ch;
    first = 0;
    curr = 0;
    last = 0;
    pFirst = text;
    pCurr = text;
    pLast = text;
    do
    {
        gotoxy(curr,0);
        ch = getch();
        switch(ch)
        {
        case -32:
            ch = getch();
            switch(ch)
            {
            case Right:
                if(pCurr < pLast)
                {
                    pCurr++;
                    curr++;
                }
                break;
            case Left:
                if(pCurr > pFirst)
                {
                    pCurr--;
                    curr--;
                }
                break;
            }
            break;

        case Enter:
        case ESC:
            system("CLS");
            *pLast = '\0';
            printf("Entered Text: %s\n", text);
            flag = 1;
            break;

        default:
            if(!isprint(ch))
                break;
            if(curr>=29)
                break;
            if(pCurr < pFirst+29)
            {
                *pCurr = ch;
                printf("%c",*pCurr);
                pCurr++;
                pLast++;
                curr++;
                last++;
            }
            else
            {
                *pCurr = ch;
                printf("%c",*pCurr);
                pCurr++;
                curr++;
            }
            break;
        }
    }
    while(flag != 1);

    return 0;
}
