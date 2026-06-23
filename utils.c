#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getIntInput(const char *prompt)
{
    int value;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%d", &value) == 1)
        {
            while (getchar() != '\n')
                ;
            return value;
        }

        printf("Invalid input! Please enter a number.\n");

        while (getchar() != '\n')
            ;
    }
}
float getFloatInput(const char *prompt)
{
    float value;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%f", &value) == 1)
        {
            while (getchar() != '\n');
            return value;
        }

        printf("Invalid input! Please enter a number.\n");

        while (getchar() != '\n');
    }
}