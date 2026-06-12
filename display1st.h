#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"

void display_login()
{
    bool login_running = true;

    do
    {
        int loging_in;
        printf("\n====================================\n");
        printf("          IDENTIFY YOUR ROLE\n");
        printf("====================================\n");
        printf("Please select your role:\n");
        printf("1. Login as Customer\n");
        printf("2. Login as Admin\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d", &loging_in);

        switch (loging_in)
        {
        case 1:
            customerMode();
            break;
        case 2:
            admin_identification();
            break;
        default:
            printf("\nInvalid choice!Please try again.\n");
            break;
        }

    } while (login_running);
}

void admin_identification()
{
    char admin_username[20];
    char admin_password[18];
    // design the admin login system
    printf("Enter admin username: ");
    fgets(admin_username, sizeof(admin_username), stdin);
    printf("Enter the password: ");
    scanf("%s", admin_password);
    if (strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "password123") == 0)
    {
        printf("Login successful!\n");
        choosemode();
    }
    else
    {
        printf("Invalid username or password. Access denied.\n");
    }

    // if (admin_password matched ) ---> admin mode
}

void choosemode()
{
    int allmode;
    printf("\n===============NOTE===============\n");
    printf("------------------------------------\n");
    printf("First mode: Add items to inventory\n");
    printf("Second mode: Check inventory\n");
    printf("Enter mode (1 for first mode, 2 for second mode): ");
    scanf("%d", &allmode);

    switch (allmode)
    {
    case 1:
        adminMode_first();
        break;
    case 2:
        adminMode_second();
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
}

void adminMode_first()
//  if user input as admin then after enter the right password
{
    char item_name[58];
    float in_price, out_price;
    int quantity;
    bool admin_mode1_running = true;

    // design the admin mode if not gui
    // ask admin to input the item name, in price, out price, and quantity
    while (admin_mode1_running)
    {
        printf("Enter item name: ");
        fgets(item_name, sizeof(item_name), stdin);
        printf("Enter in price: ");
        scanf("%f", &in_price);
        printf("Enter out price: ");
        scanf("%f", &out_price);
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        // change conditon to stop the loop when admin finish inputing the item(admin mode running false)
    }
}

void adminMode_second()
{
    bool admin_mode2_running = true;
    do
    {
        int admin_choice;
        printf("\n====================================\n");
        printf("          CHECK INVENTORY\n");
        printf("====================================\n");
        printf("1. Display all items in inventory\n");
        printf("2. view low stock items\n");
        printf("3. view out of stock items\n");
        printf("4. View pending restock orders and date\n");
        printf("5. calculate daily and monthly sales report\n");
        printf("6. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &admin_choice);
        switch (admin_choice)
        {
        case 1:
            displayallitems();
            break;
        case 2:
            viewlowstockitems();
            break;
        case 3:
            viewoutofstockitems();
            break;
        case 4:
            viewpendingrestockorders();
            break;
        case 5:
            calculatedailysalesreport();
            break;
        case 6:
            admin_mode2_running = false;
            printf("Exiting inventory check mode.\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (admin_mode2_running);
}

void displayallitems()
{
    // code to display all items in inventory
}

void viewlowstockitems()
{
    // code to view low stock items
}

void viewoutofstockitems()
{
    // code to view out of stock items
}

void viewpendingrestockorders()
{
    // code to view pending restock orders and date
}

void calculatedailysalesreport()
{
    // code to calculate daily sales report
}

void calculatemonthlysalesreport()
{
    // code to calculate monthly sales report
}

void customerMode() // should be add exit mode
// if user choice is 2
{
    // user has to choose one of 4 categories: 1. food, 2. drink......
    // design the customer mode
}

int main()
{
    display_login();
    return 0;
}