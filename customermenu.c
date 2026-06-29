#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "data.h"
#include "filehandler.h"
#include "product.h"
#include "customermenu.h"
#include "utils.h"
#include <ctype.h>
#include "display.h"
#include "onlinepurchase.h"
void customerMode()
{
    bool customer_mode_running = true;
    do
    {

        printf("\n====================================\n");
        printf("           SELECT CATEGORY\n");
        printf("====================================\n");
        printf("1. Food\n");
        printf("2. Drinks\n");
        printf("3. Snacks\n");
        printf("4. Hot deal\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            displayCategory('F');
            break;

        case 2:
            displayCategory('D');
            break;

        case 3:
            displayCategory('S');
            break;

        case 4:
            displayhotdealitems();
            break;

        case 0:
            customer_mode_running = false;
            printf("Exiting customer mode.\n");
            break;
        }

    } while (customer_mode_running);
    display_login();
}

void purchaseItem()
{
    int stockID = getIntInput("Enter Product ID: ");
    int quantity = getIntInput("Enter Quantity: ");

    OnlinePurchaseResult result = purchaseOnline(stockID, quantity);

    switch (result)
    {
    case ONLINE_PURCHASE_SUCCESS:
        calculating_system(stockID, quantity);
        printf("Purchase successful.\n");
        saveData();
        break;

    case ONLINE_PURCHASE_PRODUCT_NOT_FOUND:
        printf("Product not found.\n");
        break;

    case ONLINE_PURCHASE_INVALID_QUANTITY:
        printf("Not enough stock.\n");
        break;
    case ONLINE_PURCHASE_OUT_OF_STOCK:
        printf("Product out of stock.\n");
        break;
    default:
        printf("Purchase failed.\n");
        break;
    }
}

void calculating_system(int stockID, int quantity)
{
    int index = findStockIndexByID(stockID);
    if (index == -1)
        return;

    Stock *s = &store.stockItem[index];
    if (store.transactionCount >= MAX_TRANSACTION)
    {
        return;
    }
    Transaction *t = &store.transactionItem[store.transactionCount];
    t->transactionId = store.transactionCount + 1;
    t->stockID = stockID;
    t->quantity = quantity;
    t->totalAmount = s->sellingcost * quantity;
    t->transactionDate = time(NULL);
    store.transactionCount++;
}

void displayCategory(const char category)
{
    printf("\n====================================\n");

    if (category == 'F')
        printf("               FOOD\n");
    if (category == 'D')
        printf("              DRINKS\n");
    if (category == 'S')
        printf("              SNACKS\n");

    printf("====================================\n");

    printf("%-6s %-20s %-10s %-10s\n",
           "ID", "Name", "Price", "Stock");

    printf("------------------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        if (toupper(item->category)!=toupper(category))
            continue;

        printf("%-6d %-20s %-10.2f %-10d\n",
               item->stockID,
               item->itemName,
               item->sellingcost,
               item->onlineStock);

        found = 1;
    }

    if (!found)
    {
        printf("No products found.\n");
        return;
    }

    purchaseItem();
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

    purchaseItem();
}
