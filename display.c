#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "display.h"
#include "customermenu.h"
#include "adminmenu.h"
#include <ctype.h>
void display_login() // verify
{
    bool login_running = true;

    do
    {
        printf("\n====================================\n");
        printf("          IDENTIFY YOUR ROLE\n");
        printf("====================================\n");
        printf("Please select your role:\n");
        printf("1. Login as Customer\n");
        printf("2. Login as Admin\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            customerMode();
            break;
        case 2:
            admin_identification();
            break;
        case 0:
            login_running = false;
            break;
        default:
            printf("\nInvalid choice!Please try again.\n");
            break;
        }

    } while (login_running);
}
