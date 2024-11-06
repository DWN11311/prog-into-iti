#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool validateBirthDay(int birthYear, int birthMonth, int birthDay)
{

    // Validate February
    if(birthMonth == 2)
    {
        if(birthYear % 4 == 0)
        {
            if(birthDay >= 29)
                return false;
        }
        else
        {
            if(birthDay >= 28)
                return false;
        }
    }

    // Validate 31 day months
    if (birthMonth == 1 || birthMonth == 3 || birthMonth == 5 || birthMonth == 7 || birthMonth == 8 || birthMonth == 10 || birthMonth == 12)
    {
        if (birthDay > 31)
            return false;
    }

    // Validate 30 day months
    if (birthMonth == 4 || birthMonth == 6 || birthMonth == 9 || birthMonth == 11)
    {
        if (birthDay > 30)
            return false;
    }

    return true;
}

int getMonthDays(int year, int month)
{
    if(month == 2)
    {
        if(year % 4 == 0)
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
}

int main()
{
    int currYear = 2024;
    int currMonth = 10;
    int currDay = 28;

    int birthYear, birthMonth, birthDay;

    do
    {
        printf("Enter your birth year (1900-2024): ");
        scanf("%i", &birthYear);
        printf("\n");
    }
    while(birthYear<=1900 || birthYear>=2024);

    do
    {
        printf("Enter your birth month (1-12): ");
        scanf("%i", &birthMonth);
        printf("\n");
    }
    while(birthMonth>12 || birthMonth<1);

    do
    {
        printf("Enter your birth day (1-31): ");
        scanf("%i", &birthDay);
        printf("%i %i %i", birthYear, birthMonth, birthDay);
        printf("\n");
    }
    while(!validateBirthDay(birthYear, birthMonth, birthDay));

    int years, months, days;

    // Calculate days
    if ( birthDay > currDay )
    {
        currMonth--;
        currDay = getMonthDays(currMonth, currYear);
        days = currDay - birthDay;
    }
    else
    {
        days = currDay - birthDay;
    }

    // Calculate months
    // 15 12 2022
    if ( birthMonth > currMonth )
    {
        --currYear;
        currMonth += 12;
        months = currMonth - birthMonth;
    }
    else
    {
        months = currMonth - birthMonth;
    }

    // Calculate years
    years = currYear - birthYear;

    system("CLS");
    printf("--------------------------\nYou have been alive for:\n> %i Years.\n> %i Months.\n> %i Days.\n--------------------------",years, months, days);

    return 0;
}
