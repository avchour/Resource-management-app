#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "roleAdmin.h"
#include "data.h"
#include "display1st.h"
#include "product.h"

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
    int allmode;
    printf("\n===============MODE===============\n");
    printf("------------------------------------\n");
    printf("1. Add items to inventory\n");
    printf("2. Check inventory\n");
    printf("3.Exit\n");

    allmode = getIntInput("Enter your choice: ");

    switch (allmode)
    {
    case 1:
        adminMode_first(); // add items
        break;
    case 2:
        adminMode_second(); // check inventory
        break;
    case 3:
        printf("Exiting admin mode.\n");
        display_login();
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
}
void adminMode_first() // error
//  if user input as admin then after enter the right password
{
    char item_name[58];
    float in_price, out_price;
    int quantity;
    char category[20];
    bool admin_mode1_running = true;

    while (admin_mode1_running)
    {
        while (1)
        {
            printf("Enter item's name: ");
            fgets(item_name, sizeof(item_name), stdin);
            item_name[strcspn(item_name, "\n")] = '\0';
            if (strlen(item_name) > 0)
                break;
            printf("Error: Empty product name.\n");
        }
        in_price = getFloatInput("Enter cost expense: ");

        out_price = getFloatInput("Enter selling price: ");

        quantity = getIntInput("Enter item's quantity: ");

         while (1)
        {
            printf("Choose category : (F)ood (D)rinks (S)nacks: ");
            scanf("%1s", category);
            while (getchar() != '\n');

            char c = toupper(category[0]);
            if (c == 'F' || c == 'D' || c == 'S')
                break;
            printf("Error: Category must be F, D or S.\n");
        }

        AddProductResult result =
            addProduct(item_name,
                       in_price,
                       out_price,
                       quantity,
                       category);

        switch (result)
        {
        case ADD_PRODUCT_SUCCESS:
            printf("Product added successfully.\n");
            break;

        case ADD_PRODUCT_EMPTY_NAME:
            printf("Error: Empty product name.\n");
            break;

        case ADD_PRODUCT_INVALID_PRICE:
            printf("Error: Invalid price.\n");
            break;

        case ADD_PRODUCT_INVALID_QUANTITY:
            printf("Error: Invalid quantity.\n");
            break;

        case ADD_PRODUCT_EMPTY_CATEGORY:
            printf("Error: Empty category.\n");
            break;

        case ADD_PRODUCT_INVALID_CATEGORY:
            printf("\nError: Category must be F, D or S.\n");
            break;

        case ADD_PRODUCT_DUPLICATE:
            printf("Error: Product already exists.\n");
            break;

        case ADD_PRODUCT_FULL:
            printf("Error: Storage is full.\n");
            break;
        }

        char choice;

        do
        {
            printf("Do you want to add another item? (y/n): ");
            scanf(" %c", &choice);
            while (getchar() != '\n')
                ;
        } while (choice != 'y' && choice != 'Y' &&
                 choice != 'n' && choice != 'N');

        if (choice == 'n' || choice == 'N')
        {
            admin_mode1_running = false;
        }
        choosemode();
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
        admin_choice = getIntInput("Enter your choice: ");
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
            viewPendingRestockOrders();
            break;
        case 5:
            calculatedaily_monthlysalesReport();
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

    choosemode();
}