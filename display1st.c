#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "report.h"
#include "product.h"
#include "display1st.h"
#include "onlinePurchase.h"
#include "physicalPurchase.h"
#include "restock.h"
#include "utils.h"

void calculating_system(int stockID, int quantity);

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

        loging_in = getIntInput("Enter your choice: ");

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
    // admin_username[strcspn(admin_username, "\n")] = '\0'; // remove newline character from username
    printf("Enter the password: ");
    // admin_password[strcspn(admin_password, "\n")] = '\0'; // remove newline character from password
    fgets(admin_password, sizeof(admin_password), stdin);

    // if (strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "password123") == 0)

    // if (test == 1)

    // {
    printf("Login successful!\n");
    choosemode();
    // }
    // else
    // {
    //     printf("Invalid username or password. Access denied.\n");
    //     printf("Login again or Exit to main menu \n");
    //     // ask user to input again or exit to main menu
    //     char returnToMainChoice;
    //     printf("Do you want to try login again? (y/n): ");

    //     scanf(" %c", &returnToMainChoice);
    //     if (returnToMainChoice == 'n' || returnToMainChoice == 'N')
    //         display_login();
    //     else
    //     {
    //         admin_identification();
    //     }
    // }

    // if (admin_password matched ) ---> admin mode
}

void choosemode()
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

void adminMode_first()
//  if user input as admin then after enter the right password
{
    char item_name[58];
    float in_price, out_price;
    int quantity;
    char category[20];
    bool admin_mode1_running = true;

    while (admin_mode1_running)
    {
        printf("Enter item's name: ");
        fgets(item_name, sizeof(item_name), stdin);
        item_name[strcspn(item_name, "\n")] = '\0';
        in_price = getFloatInput("Enter cost expense: ");
        out_price = getFloatInput("Enter selling price: ");
        quantity = getIntInput("Enter item's quantity: ");
        printf("Choose category : (F)ood (D)rinks (S)nacks: ");
        scanf("%1s", category);
        while (getchar() != '\n')
            ;

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
    }

    choosemode();
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

// dol kleng vetanea

void displayallitems()
{
    if (store.stockItemCount == 0)
    {
        printf("\nNo items in inventory.\n");
        return;
    }
    else
    {
        printf("\n====================================\n");
        printf("        ALL ITEMS IN INVENTORY\n");
        printf("====================================\n");
        printf("%-6s %-20s %-10s %-10s %-10s %-8s %-8s %-10s\n", "ID", "Name", "Category", "Cost", "Sell", "Online", "Physical", "Total");
        printf("----------------------------------------------------------------\n");

        for (int i = 0; i < store.stockItemCount; i++)
        {
            Stock *mystock = &store.stockItem[i];
            printf("%-6d %-20s %-10s %-10.2f %-10.2f %-8d %-8d %-10d\n",
                   mystock->stockID,
                   mystock->itemName,
                   *mystock->category == 'F' ? "Food" : *mystock->category == 'D' ? "Drink"
                                                                                  : "Snack",
                   mystock->costprice,
                   mystock->sellingcost,
                   mystock->onlineStock,
                   mystock->physicalStock,
                   mystock->quantity);
        }

        printf("------------------------------------\n");
        printf("Total items: %d\n", store.stockItemCount);
    }
    // code to display all items in inventory
    // exit to adminMode_second
}

// checked

void viewlowstockitems()
{
    printf("\n====================================\n");
    printf("          LOW STOCK ITEMS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *mystock = &store.stockItem[i]; // use instead of using store.stockItem[i] many times

        if (mystock->onlineStock <= mystock->onlineAlertPoint && mystock->onlineAlertPoint > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-8s\n",
                       "ID", "Name", "Quantity", "Online");
                printf("----------------------------------------------------------------");
            }

            printf("%-6d %-20s %-10d %-8d\n", mystock->stockID, mystock->itemName, mystock->quantity, mystock->onlineStock);
            found++;
        }

        if (mystock->physicalStock <= mystock->physicalAlertPoint && mystock->physicalAlertPoint > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-8s\n",
                       "ID", "Name", "Quantity", "Physical");
                printf("----------------------------------------------------------------");
            }

            printf("%-6d %-20s %-10d %-8d\n", mystock->stockID, mystock->itemName, mystock->quantity, mystock->physicalStock);

            found++;
        }
    }

    if (found == 0)
        printf("No low stock items found.\n");
    else
        printf("----------------------------------------------------------------\n");

    printf("Low stock items: %d\n", found);

    // code to view low stock items
    // exit to adminMode_second
}

// checked

void viewoutofstockitems()
{
    printf("\n====================================\n");
    printf("        OUT OF STOCK ITEMS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *mystock = &store.stockItem[i];

        if (mystock->onlineStock <= 0 && mystock->physicalStock <= 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s\n", "ID", "Name");
                printf("----------------------------\n");
            }

            printf("%-6d %-20s\n", mystock->stockID, mystock->itemName);
            found++;
        }
    }

    if (found == 0)
        printf("No out of stock items found.\n");
    else
        printf("----------------------------\n");

    printf("Total out of stock items: %d\n", found);

    // code to view out of stock items
    // exit to adminMode_second
}

// checked
void viewPendingRestockOrders()
{
    printf("\n====================================\n");
    printf("        PENDING RESTOCK ORDERS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *myorder = &store.restockOrderItem[i];

        if (myorder->status != DELIVERY_IN_TRANSIT)
            continue;

        if (found == 0)
        {
            printf("%-10s %-10s %-10s %-10s %-10s %-10s\n",
                   "OrderID", "ProdID", "Type", "Qty", "Requested", "Expected");
            printf("------------------------------------------------------------\n");
        }

        char reqBuf[12], expBuf[12];
        strftime(reqBuf, sizeof(reqBuf), "%Y-%m-%d", localtime(&myorder->requestedAt));
        strftime(expBuf, sizeof(expBuf), "%Y-%m-%d", localtime(&myorder->expectedArrivalAt));

        printf("%-10d %-10d %-10s %-10d %-10s %-10s\n",
               myorder->orderId, myorder->stockID,
               myorder->type == RESTOCK_EMERGENCY ? "EMERGENCY" : "NORMAL",
               myorder->quantity, reqBuf, expBuf);

        found++;
    }

    if (found == 0)
        printf("No pending restock orders.\n");
    else
        printf("------------------------------------------------------------\n");

    printf("Total pending orders: %d\n", found);

    // code to view pending restock orders and their expected arrival dates
    // exit to adminMode_second
}

void calculatedaily_monthlysalesReport()
{
    if (store.transactionCount == 0)
    {
        printf("\nNo transactions recorded.\n");
        return;
    }

    int choice;
    printf("\n====================================\n");
    printf("           SALES REPORT\n");
    printf("====================================\n");
    printf("1. Daily report\n");
    printf("2. Monthly report\n");
    printf("------------------------------------\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        dailySalesReport();
        break;
    case 2:
        monthlySalesReport();
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

//----------------------------------------------------------------------------------------------------------------------------

// need cuustomer buying process function
void customerMode() // should be added exit mode
// if user choice is 2
{
    bool customer_mode_running = true;
    do
    {
        int customer_choice;
        printf("\n====================================\n");
        printf("           SELECT CATEGORY\n");
        printf("====================================\n");
        printf("1. Food\n");
        printf("2. Drinks\n");
        printf("3. Snacks\n");
        printf("4. Hot deal\n");
        printf("5. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &customer_choice);

        switch (customer_choice)
        {
        case 1:
            displayfooditems();
            break;
        case 2:
            displaydrinkitems();
            break;
        case 3:
            displaysnackitems();
            break;
        case 4:
            displayhotdealitems();
            break;
        case 5:
            customer_mode_running = false;
            printf("Exiting customer mode.\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }

    } while (customer_mode_running);
    display_login();
}

void displayfooditems()
{
    printf("\n====================================\n");
    printf("              FOOD\n");
    printf("====================================\n");

    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "F") == 0)
            printf("[%d] %s - $%.2f\n",
                   store.stockItem[i].stockID,
                   store.stockItem[i].itemName,
                   store.stockItem[i].sellingcost);
    }

    int stockID, quantity;
    printf("Enter item ID: ");
    scanf("%d", &stockID);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    OnlinePurchaseResult result =
        purchaseOnline(stockID, quantity);

    if (result == ONLINE_PURCHASE_SUCCESS)
    {
        calculating_system(stockID, quantity);
    }
}

void displaydrinkitems()
{
    printf("\n====================================\n");
    printf("             DRINKS\n");
    printf("====================================\n");

    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "D") == 0)
            printf("[%d] %s - $%.2f\n",
                   store.stockItem[i].stockID,
                   store.stockItem[i].itemName,
                   store.stockItem[i].sellingcost);
    }

    int stockID, quantity;
    printf("Enter item ID: ");
    scanf("%d", &stockID);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    OnlinePurchaseResult result =
        purchaseOnline(stockID, quantity);

    if (result == ONLINE_PURCHASE_SUCCESS)
    {
        calculating_system(stockID, quantity);
    }
    // code to display drink items
    // exit to customerMode
}

void displaysnackitems()
{
    printf("\n====================================\n");
    printf("             SNACKS\n");
    printf("====================================\n");

    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "S") == 0)
            printf("[%d] %s - $%.2f\n",
                   store.stockItem[i].stockID,
                   store.stockItem[i].itemName,
                   store.stockItem[i].sellingcost);
    }

    int stockID, quantity;
    printf("Enter item ID: ");
    scanf("%d", &stockID);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    OnlinePurchaseResult result =
        purchaseOnline(stockID, quantity);

    if (result == ONLINE_PURCHASE_SUCCESS)
    {
        calculating_system(stockID, quantity);
    }

    // code to display snack items
    // exit to customerMode
}

void displayhotdealitems()
{
    printf("\n====================================\n");
    printf("             HOT DEAL\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *s = &store.stockItem[i];
        double daysUntilExpiry = 14.0 - difftime(time(NULL), s->stockArrivalDate) / 86400.0;

        if (daysUntilExpiry <= 5.0 && daysUntilExpiry > 0)
        {
            printf("[%d] %s - $%.2f (Only %.0f days left!)\n",
                   s->stockID, s->itemName,
                   s->sellingcost, daysUntilExpiry);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No hot deal items at the moment.\n");
        return;
    }

    int stockID, quantity;
    printf("Enter item ID: ");
    scanf("%d", &stockID);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    OnlinePurchaseResult result =
        purchaseOnline(stockID, quantity);

    if (result == ONLINE_PURCHASE_SUCCESS)
    {
        calculating_system(stockID, quantity);
    }

    // code to display hot deal items
    // exit to customerMode
}

void calculating_system(int stockID, int quantity)
{
    int index = findStockIndexByID(stockID);
    if (index == -1)
        return;

    Stock *s = &store.stockItem[index];

    Transaction *t = &store.transactionItem[store.transactionCount];
    t->transactionId = store.transactionCount + 1;
    t->stockID = stockID;
    t->quantity = quantity;
    t->totalAmount = s->sellingcost * quantity;
    t->transactionDate = time(NULL);
    store.transactionCount++;
}
