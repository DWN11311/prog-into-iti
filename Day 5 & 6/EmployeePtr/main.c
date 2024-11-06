#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee{
    int id;
    char name[32];
};

int main()
{
    struct Employee e1;
    struct Employee *ptr;
    ptr = &e1;
    ptr->id = 5;
    strcpy(ptr->name, "Mohamed Ayman");
    printf("ID: %i\n", ptr->id);
    printf("Name: %s\n",ptr->name);
    return 0;
}
