#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char *day[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char *user[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

char current_user[10] = "";
char seats[7][5][4][4] = {0};
const char *data_file = "lib_data.dat";

int find_day(const char *d)
{
    for (int i = 0; i < 7; i++)
        if (strcmp(d, day[i]) == 0)
            return i;
    return -1;
}

void load_data()
{
    FILE *fp = fopen(data_file, "rb");
    if (fp)
    {
        fread(seats, sizeof(seats), 1, fp);
        fclose(fp);
    }
}

void save_data()
{
    FILE *fp = fopen(data_file, "wb");
    if (fp)
    {
        fwrite(seats, sizeof(seats), 1, fp);
        fclose(fp);
    }
}

int main()
{
    load_data();
    while (1)
    {
        char a[32], p1[32], p2[32], p3[32];
        int num1, num2, num3;

        printf("Please enter the instruction:");
        scanf("%s", a);

        if (strcmp(a, "Quit") == 0)
        {
            save_data();
            printf("Program exited\n");
            return 0;
        }

        else if (strcmp(a, "Exit") == 0)
        {
            if (current_user[0] == '\0')
            {
                printf("You are not logged in\n");
                continue;
            }
            current_user[0] = '\0';
            printf("Logged out\n");
        }

        else if (strcmp(a, "Login") == 0)
        {
            char name[10];
            int login_ok = 0;

            while (!login_ok)
            {
                printf("Username:");
                scanf("%s", name);
                if (strcmp(name, "Admin") == 0)
                {
                    strcpy(current_user, name);
                    printf("Login success\n");
                    login_ok = 1;
                }
                else
                {
                    for (int i = 0; i < 26; i++)
                    {
                        if (strcmp(name, user[i]) == 0)
                        {
                            strcpy(current_user, name);
                            printf("Login success\n");
                            login_ok = 1;
                            break;
                        }
                    }
                }

                if (!login_ok)
                    printf("Invalid username (use A-Z or Admin)\n");
            }
        }
        else if (find_day(a) != -1)
        {
            if (current_user[0] == '\0')
            {
                printf("Please login first\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            int d = find_day(a);
            if (scanf("%s %d", p1, &num1) != 2 || strcmp(p1, "Floor") != 0 || num1 < 1 || num1 > 5)
            {
                printf("Invalid command (example: Monday Floor 1)\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            for (int r = 0; r < 4; r++)
            {
                for (int c = 0; c < 4; c++)
                {
                    char s = seats[d][num1 - 1][r][c];
                    if (s == 0)
                        printf("0");
                    else if (strcmp(current_user, "Admin") == 0)
                        printf("%c", s);
                    else if (s == current_user[0])
                        printf("2");
                    else
                        printf("1");
                }
                printf("\n");
            }
        }

        else if (strcmp(a, "Reserve") == 0)
        {
            if (current_user[0] == '\0')
            {
                printf("Please login first\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            if (scanf("%s %s %d %s %d %d", p1, p2, &num1, p3, &num2, &num3) != 6 ||
                find_day(p1) == -1 || strcmp(p2, "Floor") != 0 ||
                strcmp(p3, "Seat") != 0 || num1 < 1 || num1 > 5 ||
                num2 < 1 || num2 > 4 || num3 < 1 || num3 > 4)
            {
                printf("Invalid command (example: Reserve Monday Floor 1 Seat 1 2)\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            int d = find_day(p1);
            if (seats[d][num1 - 1][num2 - 1][num3 - 1] != 0)
            {
                printf("Seat occupied\n");
                continue;
            }

            seats[d][num1 - 1][num2 - 1][num3 - 1] =
                (strcmp(current_user, "Admin") == 0) ? 'A' : current_user[0];
            printf("OK\n");
            save_data();
        }

        else if (strcmp(a, "Reservation") == 0)
        {
            if (current_user[0] == '\0')
            {
                printf("Please login first\n");
                continue;
            }

            char target = (strcmp(current_user, "Admin") == 0) ? 'A' : current_user[0];
            int has_res = 0;

            for (int d = 0; d < 7; d++)
                for (int f = 0; f < 5; f++)
                    for (int r = 0; r < 4; r++)
                        for (int c = 0; c < 4; c++)
                            if (seats[d][f][r][c] == target)
                            {
                                printf("%s Floor %d Seat %d %d\n",
                                       day[d], f + 1, r + 1, c + 1);
                                has_res = 1;
                            }

            if (!has_res)
                printf("No reservations\n");
        }

        else if (strcmp(a, "Clear") == 0)
        {
            if (strcmp(current_user, "Admin") != 0)
            {
                printf("No permission\n");
                continue;
            }

            memset(seats, 0, sizeof(seats));
            save_data();
            printf("Data cleared\n");
        }

        else
        {
            if (current_user[0] == '\0')
                printf("Please login first\n");
            else
                printf("Invalid instruction\n");
            while (getchar() != '\n')
                ;
        }
    }
}