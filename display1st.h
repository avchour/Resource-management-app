#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "product.h"
#include "display1st.h"

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
    printf("\n===============MODE===============\n");
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
        Stock *s = &store.stockItem[i]; // use instead of using store.stockItem[i] many times

        if (s->onlineStock <= s->onlineAlertPoint && s->onlineAlertPoint > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-8s\n",
                       "ID", "Name", "Quantity", "Online");
                printf("----------------------------------------------------------------");
            }

            printf("%-6d %-20s %-10s %-8d\n", s->stockID, s->itemName, s->quantity, s->onlineStock);
            found++;
        }

        if (s->physicalStock <= s->physicalAlertPoint && s->physicalAlertPoint > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-8s\n",
                       "ID", "Name", "Quantity", "Physical");
                printf("----------------------------------------------------------------");
            }

            printf("%-6d %-20s %-10d %-8d\n", s->stockID, s->itemName, s->quantity, s->physicalStock);

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

// checked

void viewPendingRestockOrders()
{
    printf("\n====================================\n");
    printf("        PENDING RESTOCK ORDERS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *o = &store.restockOrderItem[i];

        if (o->status == DELIVERY_IN_TRANSIT)
        {
            if (found == 0)
            {
                printf("%-8s %-8s %-12s %-6s %-12s %-12s\n",
                       "OrderID", "ProdID", "Type", "Qty", "Requested", "Expected");
                printf("------------------------------------------------------------\n");
            }

            char reqBuf[12], expBuf[12];
            struct tm *tmReq = localtime(&o->requestedAt);
            struct tm *tmExp = localtime(&o->expectedArrivalAt);
            strftime(reqBuf, sizeof(reqBuf), "%Y-%m-%d", tmReq);
            strftime(expBuf, sizeof(expBuf), "%Y-%m-%d", tmExp);

            printf("%-8ld %-8d %-12s %-6d %-12s %-12s\n",
                   o->orderId,
                   o->productId,
                   o->type == RESTOCK_EMERGENCY ? "EMERGENCY" : "NORMAL",
                   o->quantity,
                   reqBuf,
                   expBuf);

            found++;
        }
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
    printf("Enter choice: ");
    scanf("%d", &choice);

    time_t now = time(NULL);
    struct tm *tmNow = localtime(&now);

    float totalRevenue = 0.0f;
    float totalCost = 0.0f;
    int totalUnits = 0;
    int txCount = 0;

    for (int i = 0; i < store.transactionCount; i++)
    {
        Transaction *t = &store.transactionItem[i];
        struct tm *tmTx = localtime(&t->transactionDate);

        int match = 0;
        if (choice == 1)
            match = (tmTx->tm_year == tmNow->tm_year &&
                     tmTx->tm_yday == tmNow->tm_yday);
        else if (choice == 2)
            match = (tmTx->tm_year == tmNow->tm_year &&
                     tmTx->tm_mon == tmNow->tm_mon);

        if (match)
        {
            totalRevenue += t->totalAmount;
            totalUnits += t->quantity;
            txCount++;

            int idx = findStockIndexByID(t->stockID);
            if (idx != -1)
                totalCost += store.stockItem[idx].costprice * t->quantity;
        }
    }

    if (choice == 1)
    {
        char dateBuf[20];
        strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", tmNow);
        printf("\nDaily Sales Report - %s\n", dateBuf);
    }
    else
    {
        char monthBuf[20];
        strftime(monthBuf, sizeof(monthBuf), "%B %Y", tmNow);
        printf("\nMonthly Sales Report - %s\n", monthBuf);
    }

    printf("------------------------------------\n");
    printf("Transactions  : %d\n", txCount);
    printf("Units sold    : %d\n", totalUnits);
    printf("Total revenue : $%.2f\n", totalRevenue);
    printf("Estimated cost: $%.2f\n", totalCost);
    printf("Gross profit  : $%.2f\n", totalRevenue - totalCost);
    printf("====================================\n");

    // code to calculate daily and monthly sales report
    // exit to adminMode_second
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
        {
            printf("%s - %.2f\n", store.stockItem[i].itemName, store.stockItem[i].sellingcost);
        }
    }

    calculating_system(); // call the calculating_system function to allow customer to buy the item
    // code to display food items
    // exit to customerMode
}

void displaydrinkitems()
{
    printf("\n====================================\n");
    printf("             DRINKS\n");
    printf("====================================\n");

    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, "D") == 0)
        {
            printf("%s - %.2f\n", store.stockItem[i].itemName, store.stockItem[i].sellingcost);
        }
    }

    calculating_system(); // call the calculating_system function to allow customer to buy the item
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
        {
            printf("%s - %.2f\n", store.stockItem[i].itemName, store.stockItem[i].sellingcost);
        }
    }

    calculating_system(); // call the calculating_system function to allow customer to buy the item
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
    {
        printf("No hot deal items at the moment.\n");
    }

    calculating_system(); // call the calculating_system function to allow customer to buy the item

    // code to display hot deal items
    // exit to customerMode
}

void calculating_system()
{
    int stockID;
    int quantity;

    printf("\n------------------------------------\n");
    printf("Enter item ID to purchase (0 to cancel): ");
    scanf("%d", &stockID);

    if (stockID == 0)
    {
        printf("Purchase cancelled.\n");
        return;
    }

    int index = findStockIndexByID(stockID);
    if (index == -1)
    {
        printf("Item not found.\n");
        return;
    }

    Stock *s = &store.stockItem[index];

    int channel;
    printf("Purchase via:\n");
    printf("1. Physical store (available: %d)\n", s->physicalStock);
    printf("2. Online         (available: %d)\n", s->onlineStock);
    printf("Enter choice: ");
    scanf("%d", &channel);

    if (channel == 1)
    {
        PhysicalPurchaseResult res = simulatePhysicalPurchase(stockID);

        switch (res)
        {
        case PHYSICAL_PURCHASE_SUCCESS:
            printf("Purchase successful!\n");
            break;
        case PHYSICAL_PURCHASE_OUT_OF_STOCK:
            printf("Sorry, out of stock in physical store.\n");
            return;
        case PHYSICAL_PURCHASE_PRODUCT_NOT_FOUND:
            printf("Item not found.\n");
            return;
        }
    }
    else if (channel == 2)
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        OnlinePurchaseResult res = purchaseOnline(stockID, quantity);

        switch (res)
        {
        case ONLINE_PURCHASE_SUCCESS:
            break;
        case ONLINE_PURCHASE_PRODUCT_NOT_FOUND:
            printf("Item not found.\n");
            return;
        case ONLINE_PURCHASE_INVALID_QUANTITY:
            printf("Invalid quantity.\n");
            return;
        case ONLINE_PURCHASE_OUT_OF_STOCK:
            printf("Not enough online stock. Available: %d\n", s->onlineStock);
            return;
        }

        printf("\n====================================\n");
        printf("             RECEIPT\n");
        printf("====================================\n");
        printf("Item     : %s\n", s->itemName);
        printf("Quantity : %d\n", quantity);
        printf("Price    : %.2f each\n", s->sellingcost);
        printf("Total    : %.2f\n", s->sellingcost * quantity);
        printf("====================================\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }

    // code to handle the purchase process, including checking stock availability and updating stock levels
    // exit to customerMode
}

//------------------------------------------------------------------------------------------------------------------

int main()
{
    display_login();
    return 0;
}