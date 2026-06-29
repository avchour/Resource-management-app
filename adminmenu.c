#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "display.h"
#include "productmode.h"
#include "adminmenu.h"
#include "stockmode.h"
#include <ctype.h>
#include "utils.h"
#include "report.h"

void admin_identification() // verify but the password not yet flow good
{

    char admin_username[20];
    char admin_password[18];
    // design the admin login system
    printf("Enter admin username: ");
    fgets(admin_username, sizeof(admin_username), stdin);
    // admin_username[strcspn(admin_username, "\n")] = '\0'; // remove newline character from username
    printf("Enter the password: ");
    // admin_password[strcspn(admin_password, "\n")] = '\0'; // remove newline character from password
    fgets(admin_password, sizeof(admin_password), stdin);

    // if (strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "password123") == 0)
    printf("Login successful!\n");
    choosemode();
    // }
    // else
    // {
    //     printf("Invalid username or password. Access denied.\n");
    //     printf("Login again or Exit to main menu \n");
    //     // ask user to input again or exit to main menu
    //     char returnToMainChoice[20];
    //     printf("Do you want to try login again? (y/n): ");

    //     scanf(" %1s", returnToMainChoice);
    //     if (returnToMainChoice == 'n' || returnToMainChoice == 'N')
    //         display_login();
    //     else
    //     {
    //         admin_identification();
    //     }
    // }

    // if (admin_password matched ) ---> admin mode
}
void choosemode() // verify
{
    bool running = true;
    do
    {
        printf("\n===============MODE===============\n");
        printf("------------------------------------\n");
        printf("1. Product Management\n");
        printf("2. Stock Management\n");
        printf("3. Reports\n");
        printf("0.Exit\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            productMode(); // add items
            break;
        case 2:
            stockMode(); // check inventory
            break;
        case 3:
            reportMode();
            break;
        case 0:
            running = false;
            printf("Exiting admin mode.\n");
            //display_login();
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (running);
}
