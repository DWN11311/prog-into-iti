#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int arr[10] = {4, 6, -10, 22, 4, 0, 4, 4, 33, 20};
    int found[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int num;
    bool exists = false;
    printf("Enter an element to search for: ");
    scanf("%i", &num);

    for (int i = 0; i < 10; i++)
    {
        if(arr[i] == num){
            exists = true;
            found[i] = i;
        }
    }

    if(exists){
        for(int i = 0; i < 10; i++)
        {
            if(found[i] != -1) printf("Found element at index %i.\n", i);
        }
    }
    else{
        printf("Could not find any occurrences of the element.");
    }

    return 0;
}
