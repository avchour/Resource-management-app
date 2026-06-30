#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "display.h"
#include "productmode.h"
#include "adminmenu.h"
#include "stockmode.h"
#include <ctype.h>
#include "utils.h"
#include "reportmode.h"

void admin_identification() 
{
    char admin_username[20];
    char admin_password[18];
    char returnToMainChoice;
    int login_running = 1; // Condition flag: 1 means keep trying, 0 means stop

    while (login_running)
    {
        printf("\n=== Admin Verification ===\n");

        printf("Enter admin username: ");
        fgets(admin_username, sizeof(admin_username), stdin);
        admin_username[strcspn(admin_username, "\n")] = '\0'; 

        printf("Enter the password: ");
        fgets(admin_password, sizeof(admin_password), stdin); 
        admin_password[strcspn(admin_password, "\n")] = '\0'; 

        if (strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "password123") == 0)
        {
            printf("Login successful!\n");
            login_running = 0; // Break the loop condition
            choosemode();
        }
        else
        {
            printf("Invalid username or password. Access denied.\n");
            printf("Login again or Exit to main menu \n");
            printf("Do you want to try login again? (y/n): ");

            scanf(" %c", &returnToMainChoice);
            
            // Clean the input buffer so fgets doesn't get skipped on the next loop iteration
            while (getchar() != '\n'); 

            if (returnToMainChoice == 'n' || returnToMainChoice == 'N')
            {
                login_running = 0; // Set condition to false to exit the loop
                display_login();
            }
            // If they type 'y', login_running stays 1 and the loop naturally restarts
        }
    }
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
            // display_login();
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (running);
}
