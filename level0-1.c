#include <string.h>
#include <stdio.h>
int main()
{
    while (1)
    {
        char a[20];
        printf("Please enter the text:");
        scanf("%s", a);
        if (strcmp(a, "Dian") == 0)
            printf("2002\n");
        else if (strcmp(a, "Langya") == 0)
            printf("Error\n");
        else if (strcmp(a, "Quit") == 0)
            return 0;
        else
            printf("There is a spelling issue,please re-enter it.\n");
    }
    return 0;
}