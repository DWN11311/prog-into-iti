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

struct Employee
{
    int ssn;
    char name[18];
    int age;
    int salary;
    int deduction;
    int commission;
};

char* LineEditor(int _size,int col,int row, int startKey, int endKey){
    int first, curr, last;
    char *pFirst, *pCurr, *pLast;
    int flag = 0;
    //char text[30];

    char *textPtr = malloc(sizeof(char) * _size);

    char ch;
    first = col;
    curr = col;
    last = col;
    pFirst = textPtr;
    pCurr = textPtr;
    pLast = textPtr;
    _flushall();

    do
    {
        gotoxy(curr,row);
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
            *pLast = '\0';
            return textPtr;
            flag = 1;
            break;

        default:
            if(!isprint(ch))
                break;
            if(pCurr > pFirst + _size - 1)
                break;
            if(ch < startKey || ch > endKey)
                break;
            if(pCurr == pLast)
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
}

struct Employee AddEmployee()
{
    struct Employee emp;
    gotoxy(23, 1);
    // Draw the first screen
    // Row 1
    gotoxy(0,3);
    printf("SSN: ");
    gotoxy(50, 3);
    printf("Name: ");
    // Row 2
    gotoxy(0, 5);
    printf("Age: ");
    gotoxy(50, 5);
    printf("Salary: ");
    // Row 3
    gotoxy(0, 7);
    printf("Commission: ");
    gotoxy(50, 7);
    printf("Deduction: ");

    // Get the inputs
    // Row 1
    emp.ssn = atoi(LineEditor(5,5,3,48,57));
    strcpy(emp.name, LineEditor(18,56,3,65,122));
    // Row 2
    emp.age = atoi(LineEditor(3,5,5,48,57));
    emp.salary = atoi(LineEditor(7,58,5,48,57));
    //Row 3
    emp.commission = atoi(LineEditor(7,12,7,48,57));
    emp.deduction = atoi(LineEditor(7,61,7,48,57));

    return emp;
}

void PrintEmployee(struct Employee param)
{
    printf("SSN: %i\n",param.ssn);
    printf("Name: %s\n",param.name);
    printf("Age: %i\n",param.age);
    printf("Salary: %i\n",param.salary);
    printf("Deduction: %i\n",param.deduction);
    printf("Commission: %i\n",param.commission);
    printf("Net Salary: %i\n", (param.salary+param.commission)-param.deduction);
}

int main()
{
    char* aaa = LineEditor(18,56,3,65,122);
    system("CLS");
    printf("...\n");
    printf("%s", aaa);
    /*
    struct Employee e1 = AddEmployee();
    system("CLS");
    PrintEmployee(e1);*/
    return 0;
}
