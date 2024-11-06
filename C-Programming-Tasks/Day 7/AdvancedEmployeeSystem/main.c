#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>
#define EXTENDED -32
#define Enter 13
#define ESC 27
#define TAB 9
#define Up 72
#define Home 71
#define Down 80
#define End 79
#define Left 75
#define Right 77
#define Backspace 8

struct Employee
{
    int ssn;
    char name[18];
    int age;
    int salary;
    int deduction;
    int commission;
};

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

// return 0 means failure, 1 means success
int AddEmployee(struct Employee **empsPtr, int *sizePtr, struct Employee newEmp)
{
    int flag = 1;
    (*sizePtr)++;

    struct Employee *newEmpsPtr = realloc(*empsPtr, *sizePtr * sizeof(struct Employee));
    if(newEmpsPtr == NULL)
    {
        flag = 0;
        (*sizePtr)--;
        return flag;
    }

    *empsPtr = newEmpsPtr;
    (*empsPtr)[*sizePtr - 1] = newEmp;
    return flag;
}

int RemoveEmployee(struct Employee **empsPtr, int *sizePtr, int index)
{
    int flag = 1;
    int newEmpsiterator = 0;

    struct Employee *newEmpsPtr = malloc(((*sizePtr)-1) * sizeof(struct Employee));
    if(newEmpsPtr == NULL)
    {
        flag = 0;
        return flag;
    }

    for(int i = 0; i < *sizePtr; i++)
    {
        if(i != index)
        {
            newEmpsPtr[newEmpsiterator] = (*empsPtr)[i];
            newEmpsiterator++;
        }
    }

    free(*empsPtr);
    *empsPtr = newEmpsPtr;
    (*sizePtr)--;

    return 1;
}

void DisplayEmployees(struct Employee *employees, int *size)
{
    if (employees == NULL || *size == 0)
    {
        printf("No employees to display.\n");
        return;
    }
    // Draw table structure
    for(int i = 0; i < (*size * 2) + 2; i++)
    {
        gotoxy(10, i);
        printf("|");
        gotoxy(20, i);
        printf("|");
        gotoxy(38, i);
        printf("|");
        gotoxy(48, i);
        printf("|");
        gotoxy(60, i);
        printf("|");
        gotoxy(73, i);
        printf("|");
        gotoxy(88, i);
        printf("|");
    }

    for(int i = 0; i < 100; i++)
    {
        gotoxy(i, 1);
        printf("-");
    }

    // Header
    gotoxy(13, 0);
    printf("SSN");
    gotoxy(22, 0);
    printf("Name");
    gotoxy(40, 0);
    printf("Salary");
    gotoxy(50, 0);
    printf("Deduction");
    gotoxy(62, 0);
    printf("Commission");
    gotoxy(75, 0);
    printf("Net Salary");
    gotoxy(90, 0);
    printf("Age");

    // Fill Data
    int row = 0;
    for(int i = 0; i < *size; i++)
    {
        if(employees[i].ssn != -20)
        {
            gotoxy(4, row * 2 + 3);
            printf("%i", i);

            gotoxy(13, row * 2 + 3);
            printf("%i", employees[i].ssn);

            gotoxy(22, row * 2 + 3);
            printf("%s", employees[i].name);

            gotoxy(40, row * 2 + 3);
            printf("%d", employees[i].salary);

            gotoxy(50, row * 2 + 3);
            printf("%d", employees[i].deduction);

            gotoxy(62, row * 2 + 3);
            printf("%d", employees[i].commission);

            gotoxy(75, row * 2 + 3);
            printf("%d", (employees[i].salary + employees[i].commission) - employees[i].deduction);

            gotoxy(90, row * 2 + 3);
            printf("%d", employees[i].age);

            row++;
        }
    }
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

char** MultiLineEditor(int rows, int cols, int colPosition, int rowPosition)
{
    char **textPtr = malloc(sizeof(char*) * rows);
    int first[rows];
    int last[rows];
    int curr[rows];
    char* pFirst[rows];
    char* pLast[rows];
    char* pCurr[rows];
    int activeRow = 0;
    char* tempPtr;

    for(int i = 0; i < rows; i++)
    {
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

    // Clear editor area
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            gotoxy(rowPosition+j, colPosition+i);
            printf(" ");
        }
    }

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
                if(activeRow > 0)
                {
                    activeRow--;
                }
                break;
            case Down:
                if(activeRow < rows)
                {
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

struct Employee AddEmployeeScreen()
{
    struct Employee emp;
    gotoxy(0,0);
    printf("Enter Employee Details");
    gotoxy(0,1);
    printf("_____________________________________________________________________________________");
    gotoxy(2, 3);
    printf("SSN");
    gotoxy(2, 4);
    printf("Name");
    gotoxy(2, 5);
    printf("Age");
    gotoxy(2, 6);
    printf("Salary");
    gotoxy(2, 7);
    printf("Deduction");
    gotoxy(2, 8);
    printf("Commission");

    for(int i = 2; i < 10; i++)
    {
        gotoxy(13,i);
        printf("|");
    }

    int valid = 1;
    char** textDetails;
    do{
        valid = 1;
        textDetails = MultiLineEditor(6, 24, 3, 15);
        for(int i = 0; i < 6; i++)
        {
            if(i == 1) continue;
            for(int j = 0; j < strlen(textDetails[i]); j++)
            {
                if(textDetails[i][j] < 48 || textDetails[i][j] > 57)
                {
                    valid = 0;
                }
            }
        }
        if(valid != 1){
            gotoxy(40, 0);
            printf("Please enter valid parameters");
        }
    }while(valid != 1);

    emp.ssn = atoi(textDetails[0]);
    strcpy(emp.name, textDetails[1]);
    emp.age = atoi(textDetails[2]);
    emp.salary = atoi(textDetails[3]);
    emp.deduction = atoi(textDetails[4]);
    emp.commission = atoi(textDetails[5]);

    return emp;
}

void DrawMenuArt()
{
    textattr(4);
    printf(" ▒▓██▓                        █                         █    ▒▓██▓                        \n");
    printf(" ▒███▓                        █                         █    ▒███▓                        \n");
    printf("                              █                         █                                 \n");
    printf(" ▒██▓                         █_________________________█    ▒██▓                         \n");
    printf(" ▒████▒                       █                         █    ▒████▒                       \n");
    printf(" ▒████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▒    █                         █    ▒████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▒    \n");
    printf(" ▒███████████████████░░░░▓    █                         █    ▒███████████████████░░░░▓    \n");
    printf(" ▒████▓▓▓▓▓█████▓▓▓▓▓▓▒▒▓▒    █                         █    ▒████▓▓▓▓▓█████▓▓▓▓▓▓▒▒▓▒    \n");
    printf(" ▒████▓    █████▒             █                         █    ▒████▓    █████▒             \n");
    printf(" ▒████▓    █████▒   ▒████▓    █                         █    ▒████▓    █████▒   ▒████▓    \n");
    printf(" ▒████▓    █████▒   ▒████▓    █                         █    ▒████▓    █████▒   ▒████▓    \n");
    printf(" ▒████▓    █████▒   ▒████▓    █                         █    ▒████▓    █████▒   ▒████▓    \n");
    printf(" ▒████▓    █████▒   ▒████▓    █                         █    ▒████▓    █████▒   ▒████▓    \n");
    printf(" ▒████▓    █████▒   ▒████▓    █                         █    ▒████▓    █████▒   ▒████▓    \n");
    printf("  ▓███▓    █████▒   ▒████▓    █                         █     ▓███▓    █████▒   ▒████▓    \n");
    printf("   ▒▓▓▓    █████▒   ▒████▓    █                         █      ▒▓▓▓    █████▒   ▒████▓    \n");
    printf("           ▒████▒   ▒████▓    █                         █              ▒████▒   ▒████▓    \n");
    printf("            ▒▓██    ▒████▒    █                         █               ▒▓██    ▒████▒    \n");
    printf("                    ▒███▓     █                         █                       ▒███▓     \n");
    textattr(7);
}

// NOTE: Search functions edit a received array of employees and a size int that match the criteria
void SearchEmployeeBySSN(struct Employee *sourceEmployees, int size, struct Employee **resultEmployees, int *resultSize, int _ssn){
    *resultSize = 0;
    *resultEmployees = malloc(sizeof(struct Employee) * size);

    for(int i = 0; i < size; i++)
    {
        if(sourceEmployees[i].ssn == _ssn)
        {
            (*resultEmployees)[*resultSize] = sourceEmployees[i];
            (*resultSize)++;
        }
    }
};

void SearchEmployeeByName(struct Employee *sourceEmployees, int size, struct Employee **resultEmployees, int *resultSize, char *_name){
    *resultSize = 0;
    *resultEmployees = malloc(sizeof(struct Employee) * size);

    for(int i = 0; i < size; i++)
    {
        if(_strcmpi(sourceEmployees[i].name, _name) == 0)
        {
            (*resultEmployees)[*resultSize] = sourceEmployees[i];
            (*resultSize)++;
        }
    }
};

void SearchEmployeeByNetSalary(struct Employee *sourceEmployees, int size, struct Employee **resultEmployees, int *resultSize, int _minSalary, int _maxSalary){
    *resultSize = 0;
    *resultEmployees = malloc(sizeof(struct Employee) * size);

    for(int i = 0; i < size; i++)
    {
        int netSalary = (sourceEmployees[i].salary + sourceEmployees[i].commission) - sourceEmployees[i].deduction;
        if(netSalary >= _minSalary && netSalary <= _maxSalary)
        {
            (*resultEmployees)[*resultSize] = sourceEmployees[i];
            (*resultSize)++;
        }
    }
};

void SearchEmployeeByAge(struct Employee *sourceEmployees, int size, struct Employee **resultEmployees, int *resultSize, int _minAge, int _maxAge){
    *resultSize = 0;
    *resultEmployees = malloc(sizeof(struct Employee) * size);

    for(int i = 0; i < size; i++)
    {
        if(sourceEmployees[i].age >= _minAge && sourceEmployees[i].age <= _maxAge)
        {
            (*resultEmployees)[*resultSize] = sourceEmployees[i];
            (*resultSize)++;
        }
    }
};

void EnterAction(int cursor, int *sizePtr, struct Employee **employees, int *mainFlag)
{
    struct Employee newEmp;
    int secondaryCursor = 0;
    int secondaryFlag = 0;
    char ch;
    char searchOptions[5][24] = {" By SSN ", " By Name ", " By Net Salary Range ", " By Age Range ", " Return "};

    // Variables to store search results and search parameters
    struct Employee *searchResult = NULL;
    int searchResultSize = 0;
    int minSearchParam;
    int maxSearchParam;
    char stringSearchparam[32];

    switch(cursor)
    {
    // Add Employee
    case 0:
        system("CLS");
        newEmp = AddEmployeeScreen();
        system("CLS");
        if(AddEmployee(employees, sizePtr, newEmp) == 0)
        {
            printf("Failed to allocate new employee, please try again. press any key to continue");
            getch();
        }
        else
        {
            printf("Added Employee \"%s\" Successfully! Press any key to continue.",(*employees)[*sizePtr - 1].name);
            getch();
        }
        break;
    // Edit Employee
    case 1:
        secondaryCursor = 0;
        secondaryFlag = 0;
        system("CLS");
        if(*sizePtr == 0)
        {
            printf("No Employees to edit, press any key to continue");
            getch();
            break;
        }
        do
        {
            system("CLS");
            gotoxy(0,0);
            DrawMenuArt();
            gotoxy(37, 1);
            printf("Edit Employees");
            for(int i = 0; i < *sizePtr; i++)
            {
                if(secondaryCursor == i)
                    textattr(79);
                else
                    textattr(15);
                gotoxy(34, 5+i*2);
                printf("%s", (*employees)[i].name);
                textattr(15);
            }
            ch = getch();
            switch(ch)
            {
            case EXTENDED:
                ch = getch();
                switch(ch)
                {
                case Up:
                    if(secondaryCursor > 0)
                        secondaryCursor--;
                    else
                        secondaryCursor = *sizePtr-1;
                    break;
                case Down:
                    if (secondaryCursor < *sizePtr-1)
                        secondaryCursor++;
                    else
                        secondaryCursor = 0;
                    break;
                }
                break;
            case Enter:
                system("CLS");
                newEmp = AddEmployeeScreen();
                system("CLS");
                (*employees)[secondaryCursor] = newEmp;
                printf("Updated employee successfully! press any key to continue");
                getch();
                secondaryFlag = 1;
                break;
            case ESC:
                secondaryFlag = 1;
                break;
            }
        }
        while(secondaryFlag != 1);
        break;
    // Display Employees
    case 2:
        system("CLS");
        DisplayEmployees(*employees, sizePtr);
        getch();
        break;
    // Search Menu
    case 3:
        secondaryCursor = 0;
        secondaryFlag = 0;
        do{
            system("CLS");
            gotoxy(0, 0);
            DrawMenuArt();
            gotoxy(34, 1);
            printf("Choose Search Method");

            for(int i = 0; i < 5; i++)
            {
                if(secondaryCursor == i)
                    textattr(79);
                else
                    textattr(15);
                gotoxy(34, 5+i*2);
                printf("%s", searchOptions[i]);
                textattr(15);
            }

            ch = getch();

            switch(ch)
            {
            case EXTENDED:
                ch = getch();
                switch(ch)
                {
                case Up:
                    if(secondaryCursor > 0)
                        secondaryCursor--;
                    else
                        secondaryCursor = 4;
                    break;
                case Down:
                    if (secondaryCursor < 4)
                        secondaryCursor++;
                    else
                        secondaryCursor = 0;
                    break;
                }
                break;
            case Enter:
                switch(secondaryCursor){
                case 0:
                    system("CLS");
                    gotoxy(0, 0);
                    printf("Enter employee SSN: ");
                    scanf("%i", &minSearchParam);
                    SearchEmployeeBySSN(*employees, *sizePtr, &searchResult, &searchResultSize, minSearchParam);
                    if(searchResultSize > 0) {
                        system("CLS");
                        DisplayEmployees(searchResult, &searchResultSize);
                    }
                    else {
                        system("CLS");
                        printf("No matches found. Press any key to continue");
                    }
                    free(searchResult);
                    getch();
                    break;
                case 1:
                    system("CLS");
                    gotoxy(0, 0);
                    printf("Enter employee name: ");
                    _flushall();
                    gets(stringSearchparam);
                    SearchEmployeeByName(*employees, *sizePtr, &searchResult, &searchResultSize, stringSearchparam);
                    if(searchResultSize > 0) {
                        system("CLS");
                        DisplayEmployees(searchResult, &searchResultSize);
                    }
                    else {
                        system("CLS");
                        printf("No matches found. Press any key to continue");
                    }
                    free(searchResult);
                    getch();
                    break;
                case 2:
                    system("CLS");
                    gotoxy(0, 0);
                    printf("Enter employee minimum net salary: ");
                    scanf("%i", &minSearchParam);
                    printf("Enter employee maximum net salary: ");
                    scanf("%i", &maxSearchParam);
                    SearchEmployeeByNetSalary(*employees, *sizePtr, &searchResult, &searchResultSize, minSearchParam, maxSearchParam);
                    if(searchResultSize > 0) {
                        system("CLS");
                        DisplayEmployees(searchResult, &searchResultSize);
                    }
                    else {
                        system("CLS");
                        printf("No matches found. Press any key to continue");
                    }
                    free(searchResult);
                    getch();
                    break;
                case 3:
                    system("CLS");
                    gotoxy(0, 0);
                    printf("Enter employee minimum age: ");
                    scanf("%i", &minSearchParam);
                    printf("Enter employee maximum age: ");
                    scanf("%i", &maxSearchParam);
                    SearchEmployeeByAge(*employees, *sizePtr, &searchResult, &searchResultSize, minSearchParam, maxSearchParam);
                    if(searchResultSize > 0) {
                        system("CLS");
                        DisplayEmployees(searchResult, &searchResultSize);
                    }
                    else {
                        system("CLS");
                        printf("No matches found. Press any key to continue");
                    }
                    free(searchResult);
                    getch();
                    break;
                case 4:
                    secondaryFlag = 1;
                    break;
                }
                break;
            case ESC:
                secondaryFlag = 1;
                break;
            }
        }while(secondaryFlag != 1);
        break;
    // Delete employee
    case 4:
        system("CLS");
        if(*sizePtr == 0)
        {
            printf("No Employees to delete, press any key to continue");
            getch();
            break;
        }
        secondaryCursor = 0;
        do
        {
            system("CLS");
            gotoxy(0,0);
            DrawMenuArt();
            gotoxy(37, 1);
            printf("Delete Employee");
            for(int i = 0; i < *sizePtr; i++)
            {
                if(secondaryCursor == i)
                    textattr(79);
                else
                    textattr(15);
                gotoxy(34, 5+i*2);
                printf("%s", (*employees)[i].name);
                textattr(15);
            }
            ch = getch();
            switch(ch)
            {
            case EXTENDED:
                ch = getch();
                switch(ch)
                {
                case Up:
                    if(secondaryCursor > 0)
                        secondaryCursor--;
                    else
                        secondaryCursor = *sizePtr-1;
                    break;
                case Down:
                    if (secondaryCursor < *sizePtr-1)
                        secondaryCursor++;
                    else
                        secondaryCursor = 0;
                    break;
                }
                break;
            case Enter:
                system("CLS");
                printf("You are about to delete this employee:\n");
                printf("%i\n", secondaryCursor);
                PrintEmployee((*employees)[secondaryCursor]);
                printf("\nAre you sure you want to proceed? (y/n): ");
                _flushall();
                scanf("%s",stringSearchparam);
                if(stringSearchparam[0] == 'y' || stringSearchparam == 'Y')
                {
                    system("CLS");
                    if(RemoveEmployee(employees, sizePtr, secondaryCursor) == 1)
                    {
                        printf("Employee deletion was successful, Press any key to continue.");
                    }
                    else
                    {
                        printf("Employee deletion failed, Press any key to continue.");
                    }
                    secondaryFlag = 1;
                    getch();
                }
                break;
            case ESC:
                secondaryFlag = 1;
                break;
            }
        }
        while(secondaryFlag != 1);
        break;
    case 5:
        *mainFlag = 1;
        break;
    }
    system("CLS");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "en_US.UTF-8");

    char menu[6][30] = {" Add Employee ", " Edit Employee ", " Get All Employees ", " Search Employees ", " Delete Employee ", " Exit "};
    int cursor = 0;
    int flag = 0;
    int *flagPtr;
    flagPtr = &flag;
    char ch;
    int size = 0;
    int *sizePtr;
    sizePtr = &size;
    struct Employee *employees = NULL; // IDK why it has to be NULL but the code breaks without it...
    struct Employee newEmp;

    do
    {
        system("CLS");
        gotoxy(0, 0);
        DrawMenuArt();
        gotoxy(39, 1);
        printf("Main Menu");
        // First print menu items
        for(int i = 0; i < 6; i++)
        {
            if(cursor == i)
                textattr(79);
            else
                textattr(15);
            gotoxy(34, 5+i*2);
            printf("%s", menu[i]);
            textattr(15);
        }

        // Now get character and act according to clicked char
        ch = getch();
        switch (ch)
        {
        case EXTENDED:
            ch = getch();
            switch(ch)
            {
            case Up:
                if(cursor > 0)
                    cursor--;
                else
                    cursor = 5;
                break;
            case Down:
                if (cursor < 5)
                    cursor++;
                else
                    cursor = 0;
                break;
            }
            break;
        case TAB:
            if (cursor < 5)
                cursor++;
            else
                cursor = 0;
            break;
        case Enter:
            EnterAction(cursor, sizePtr, &employees, flagPtr);
            break;
        case ESC:
            flag = 1;
            break;
        }

    }
    while(flag != 1);

    gotoxy(30, 20);
    return 0;
}
