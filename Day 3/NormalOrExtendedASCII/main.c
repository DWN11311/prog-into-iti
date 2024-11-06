#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;
    do
    {
        printf("Enter a character: ");
        ch=getch();
        printf("\n");

        if(ch==-32)
        {
            ch=getch();
            printf("You entered \"%c\" which is an extended character with ASCII: %i\n",ch, ch);
        }
        else
        {
            printf("You entered \"%c\" which is a normal character with ASCII: %i\n",ch, ch);
        }
    }
    while(ch != 65);
        return 0;
}
