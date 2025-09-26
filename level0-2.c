#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim(char *str)
{
    int len = strlen(str);
    int start = 0, end = len - 1;
    while (start <= end && isspace((unsigned char)str[start]))
        start++;
    if (start > end)
        str[0] = '\0';
    while (end >= start && isspace((unsigned char)str[end]))
        end--;
    if (start > 0)
        memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

int main()
{
    FILE *file;
    char a[64][1024] = {0}; // 存储键
    char b[64][1024] = {0}; // 存储值
    int i = 0;

    file = fopen("data.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open data.txt.\n");
        return 1;
    }

    char d[1024];
    while (fgets(d, sizeof(d), file) != NULL && i < 64)
    {
        d[strcspn(d, "\n")] = '\0';
        trim(d);
        if (strlen(d) == 0)
            continue;
        char *maohao = strchr(d, ':');
        if (maohao == NULL)
            continue;
        *maohao = '\0';
        char *key = d;
        char *value = maohao + 1;

        trim(key);
        trim(value);

        if (strlen(key) > 0 && strlen(key) <= 10 &&
            strlen(value) > 0 && strlen(value) <= 10)
        {
            strcpy(a[i], key);
            strcpy(b[i], value);
            i++;
        }
    }
    fclose(file);
    while (1)
    {
        int j, found = 0;
        char c[1024];

        printf("Please enter the text : ");
        scanf("%s", c);

        if (strcmp(c, "Quit") == 0)
            break;

        for (j = 0; j < i; j++)
        {
            if (strcmp(a[j], c) == 0)
            {
                printf("%s\n", b[j]);
                found = 1;
                break;
            }
        }

        if (found != 1)
            printf("Error\n");
    }

    return 0;
}
