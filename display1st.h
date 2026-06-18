#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "product.h"

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
    fgets(admin_password, sizeof(admin_password), stdin);
    if (strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "password123") == 0)
    {
        printf("Login successful!\n");
        choosemode();
    }
    else
    {
        printf("Invalid username or password. Access denied.\n");
        printf("Login again or Exit to main menu \n");
        // ask user to input again or exit to main menu
        char returnToMainChoice;
        printf("Do you want to try login again? (y/n): ");
        scanf(" %c", &returnToMainChoice);
        if (returnToMainChoice == 'n' || returnToMainChoice == 'N')
            display_login();
        else
        {
            admin_identification();
        }
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
    printf("Enter mode (1 for first mode, 2 for second mode or 3 to exit): ");
    scanf("%d", &allmode);

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

    // design the admin mode if not gui
    // ask admin to input the item name, in price, out price, and quantity
    while (admin_mode1_running)
    {
        printf("Enter item name: \n");
        fgets(item_name, sizeof(item_name), stdin);
        printf("Enter in price: \n");
        scanf("%f", &in_price);
        printf("Enter out price: \n");
        scanf("%f", &out_price);
        printf("Enter quantity: \n");
        scanf("%d", &quantity);
        printf("Enter category (F)ood (D)rinks (S)nacks: \n");
        scanf("%s", &category);

        AddProductResult(addProduct(item_name, in_price, out_price, quantity, category)); // check if it invalid input or duplicate item name or full inventory
        // add something
        printf("Do you want to add another item? (y/n): ");
        char choice;
        scanf(" %c", &choice);
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
            calculatedaily_monthlysalesreport();
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
//--------------------------------------------------
void displayallitems()
{
    if (store.stockItemCount == 0)
    {
        printf("\nNo items in inventory.\n");
        return;
    }

    printf("\n====================================\n");
    printf("        ALL ITEMS IN INVENTORY\n");
    printf("====================================\n");
    printf("%-6s %-20s %-10s %-10s %-10s %-8s %-8s %-10s\n", "ID", "Name", "Category", "Cost", "Sell", "Online", "Physical", "Total");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *s = &store.stockItem[i];
        printf("%-6d %-20s %-10s %-10.2f %-10.2f %-8d %-8d %-10d\n",
               s->stockID,
               s->itemName,
               s->category,
               s->costprice,
               s->sellingcost,
               s->onlineStock,
               s->physicalStock,
               s->quantity);
    }

    printf("------------------------------------\n");
    printf("Total items: %d\n", store.stockItemCount);
    // code to display all items in inventory
    // exit to adminMode_second
}

void viewlowstockitems()
{
    printf("\n====================================\n");
    printf("          LOW STOCK ITEMS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *s = &store.stockItem[i];

        if (s->onlineStock <= s->onlineAlertPoint && s->onlineAlertPoint > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-8s\n",
                       "ID", "Name", "Category",
                       "Online");
                printf("----------------------------------------------------------------");
            }

            printf("%-6d %-20s %-10s %-8d\n", s->stockID, s->itemName, s->category, s->onlineStock);
            found++;
        }

        if (s->physicalStock <= s->physicalAlertPoint && s->physicalAlertPoint > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-8s\n",
                       "ID", "Name", "Category",
                       "Physical");
                printf("----------------------------------------------------------------");
            }

            printf("%-6d %-20s %-10s %-8d\n", s->stockID, s->itemName, s->category, s->physicalStock);

            found++;
        }
    }

    if (found == 0)
        printf("No low stock items found.\n");
    else
        printf("----------------------------------------------------------------\n");

    printf("Total low stock items: %d\n", found);

    // code to view low stock items
    // exit to adminMode_second
}

void viewoutofstockitems()
{
    printf("\n====================================\n");
    printf("        OUT OF STOCK ITEMS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *s = &store.stockItem[i];

        if (s->quantity > 0 && s->onlineStock <= 0 && s->physicalStock <= 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s\n", "ID", "Name");
                printf("----------------------------\n");
            }

            printf("%-6d %-20s\n", s->stockID, s->itemName);
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

void viewPendingRestockOrders()
{
    printf("\n====================================\n");
    printf("           PENDING RESTOCK \n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *o = &store.restockOrderItem[i];

        if (o->status == DELIVERY_IN_TRANSIT)
        {
            if (found == 0)
            {
                printf("%-8s %-8s %-10s %-10s %-6s %-20s %-20s\n",
                       "OrderID", "ProdID", "Type", "Status",
                       "Qty", "Requested At", "Expected At");
                printf("------------------------------------"
                       "------------------------------------\n");
            }

            /* Format requestedAt */
            char reqBuf[20], expBuf[20];
            struct tm *tmReq = localtime(&o->requestedAt);
            struct tm *tmExp = localtime(&o->expectedArrivalAt);
            strftime(reqBuf, sizeof(reqBuf), "%Y-%m-%d", tmReq);
            strftime(expBuf, sizeof(expBuf), "%Y-%m-%d", tmExp);

            printf("%-8ld %-8d %-10s %-10s %-6d %-20s %-20s\n",
                   o->orderId,
                   o->productId,
                   o->type == RESTOCK_EMERGENCY ? "EMERGENCY" : "NORMAL",
                   "IN TRANSIT",
                   o->quantity,
                   reqBuf,
                   expBuf);

            found++;
        }
    }

    if (found == 0)
        printf("No pending restock orders.\n");
    else
        printf("------------------------------------\n");

    printf("Total pending orders: %d\n", found);

    // code to view pending restock orders and date
    // exit to adminMode_second
}

void calculatedaily_monthlysalesreport()
{
    if (store.transactionCount == 0)
    {
        printf("\nNo transactions recorded.\n");
        return;
    }

    /* Ask user which report they want */
    int choice;
    printf("\n====================================\n");
    printf("          SALES REPORT\n");
    printf("====================================\n");
    printf("1. Daily report\n");
    printf("2. Monthly report\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("\n");

    time_t now = time(NULL);
    struct tm *tmNow = localtime(&now);

    float financeReport = 0.0f;
    int totalQty = 0;
    int txCount = 0;

    for (int i = 0; i < store.transactionCount; i++)
    {
        Transaction *t = &store.transactionItem[i];
        struct tm *tmTx = localtime(&t->transactionDate);

        int match = 0;

        if (choice == 1)
        {
            /* Same calendar day */
            match = (tmTx->tm_year == tmNow->tm_year &&
                     tmTx->tm_yday == tmNow->tm_yday);
        }
        else if (choice == 2)
        {
            /* Same month and year */
            match = (tmTx->tm_year == tmNow->tm_year &&
                     tmTx->tm_mon == tmNow->tm_mon);
        }

        if (match)
        {
            financeReport += t->totalAmount;
            totalQty += t->quantity;
            txCount++;
        }
    }

    if (choice == 1)
    {
        char dateBuf[20];
        strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", tmNow);
        printf("Daily Sales Report — %s\n", dateBuf);
    }
    else
    {
        char monthBuf[20];
        strftime(monthBuf, sizeof(monthBuf), "%B %Y", tmNow);
        printf("Monthly Sales Report — %s\n", monthBuf);
    }

    printf("------------------------------------\n");
    printf("Transactions  : %d\n", txCount);
    printf("Units sold    : %d\n", totalQty);
    printf("Total revenue : $%.2f\n", financeReport);

    /* Cost calculation for profit estimate */
    float totalCost = 0.0f;
    for (int i = 0; i < store.transactionCount; i++)
    {
        Transaction *t = &store.transactionItem[i];
        struct tm *tmTx = localtime(&t->transactionDate);

        int match = 0;
        if (choice == 1)
            match = (tmTx->tm_year == tmNow->tm_year &&
                     tmTx->tm_yday == tmNow->tm_yday);
        else
            match = (tmTx->tm_year == tmNow->tm_year &&
                     tmTx->tm_mon == tmNow->tm_mon);

        if (match)
        {
            int idx = findStockIndexByID(t->stockID);
            if (idx != -1)
                totalCost += store.stockItem[idx].costprice * t->quantity;
        }
    }

    printf("Estimated cost: $%.2f\n", totalCost);
    printf("Gross profit  : $%.2f\n", financeReport - totalCost);
    printf("====================================\n");
    // code to calculate daily and monthly sales reports
    // exit to adminMode_second
}
//------------------------------------------------------------------------------------------------------------------

void customerMode() // should be add exit mode
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
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "F") == 0)
        {
            printf("%s - %.2f\n", store.stockItem[i].itemName, store.stockItem[i].sellingcost);
        }
    }
    // code to display food items
    // exit to customerMode
}

void displaydrinkitems()
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "D") == 0)
        {
            printf("%s - %.2f\n", store.stockItem[i].itemName, store.stockItem[i].sellingcost);
        }
    }
    // code to display drink items
    // exit to customerMode
}

void displaysnackitems()
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "S") == 0)
        {
            printf("%s - %.2f\n", store.stockItem[i].itemName, store.stockItem[i].sellingcost);
        }
    }
    // code to display snack items
    // exit to customerMode
}

void displayhotdealitems()
{
    printf("\n====================================\n");
    printf("             HOT DEAL \n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *s = &store.stockItem[i];

        // calculate how many days since item arrived
        double daysInStock = difftime(time(NULL), s->stockArrivalDate) / 86400.0;

        // item expires at 14 days
        // so if 9 or more days passed, it will expire within 5 days
        double daysUntilExpiry = 14.0 - daysInStock;

        if (daysUntilExpiry <= 5.0 && daysUntilExpiry > 0)
        {
            printf("%s - %.2f (Only %.0f days left!)\n",
                   s->itemName,
                   s->sellingcost,
                   daysUntilExpiry);

            found++;
        }
    }

    if (found == 0)
        printf("No hot deal items at the moment.\n");

    // code to display hot deal items
    // exit to customerMode
}

//------------------------------------------------------------------------------------------------------------------

int main()
{
    display_login();
    return 0;
}