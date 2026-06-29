#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void rtrim(char *str)
{
    int len = strlen(str);

    while (len > 0 && isspace((unsigned char)str[len - 1]))
    {
        str[--len] = '\0';
    }
}
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
            while (getchar() != '\n')
                ;
            return value;
        }

        printf("Invalid input! Please enter a number.\n");

        while (getchar() != '\n')
            ;
    }
}
bool askAgain(const char *message)
{
    char choice;

    do
    {
        printf("%s (Y/N): ", message);
        scanf(" %c",&choice);

        while(getchar()!='\n');
        
        choice=toupper(choice);
        
        if (choice != 'Y' && choice != 'N')
        {
            printf("Invalid choice.\n");
        }
    }while(choice!='Y' && choice!='N');

    return choice=='Y';
}