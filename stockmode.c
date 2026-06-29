#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "display.h"
#include "productmode.h"
#include "restock.h"
#include "stockmode.h"
#include "data.h"
#include <ctype.h>
#include "utils.h"
#include "physicalpurchase.h"
#include "alert.h"
#include "product.h"

void stockMode()
{
    static bool todaySimulated = false;
    if (!todaySimulated)
    {
        simulateDailyPhysicalSales();
        todaySimulated = true;
    }
    bool admin_mode2_running = true;
    do
    {
        printf("\n====================================\n");
        printf("          CHECK INVENTORY\n");
        printf("====================================\n");
        printf("1. Check low stock items\n");
        printf("2. Check out of stock items\n");
        printf("3. Check pending restock orders and date\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            viewlowstockitems();
            break;
        case 2:
            viewoutofstockitems();
            break;
        case 3:
            viewPendingRestockOrders();
            break;
        case 0:
            admin_mode2_running = false;
            printf("Exiting inventory check mode.\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (admin_mode2_running);

    return;
}

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
                   (mystock->category == 'F') ? "Food" : (mystock->category == 'D') ? "Drink"
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
        Stock *mystock = &store.stockItem[i];

        if (isOnlineAlert || isPhysicalAlert)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s %-10s %-10s\n",
                       "ID", "Name", "Quantity", "Online", "Physical");
                printf("------------------------------------------------------------\n");
            }
            printf("%-6d %-20s %-10d %-10d %-10d\n",
                   mystock->stockID,
                   mystock->itemName,
                   mystock->quantity,
                   mystock->onlineStock,
                   mystock->physicalStock);

            found++;
        }
    }

    if (found == 0)
    {
        printf("No low stock items found.\n");
    }
    else
    {
        printf("------------------------------------------------------------\n");
        printf("Total low stock items: %d\n", found);
    }
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
        Stock *item = &store.stockItem[i];

        if (item->quantity == 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s\n", "ID", "Name", "Quantity");
                printf("------------------------------------\n");
            }

            printf("%-6d %-20s %-10d\n",
                   item->stockID,
                   item->itemName,
                   item->quantity);

            found++;
        }
    }

    if (found == 0)
    {
        printf("No out of stock items found.\n");
    }
    else
    {
        printf("------------------------------------\n");
        printf("Total out of stock items: %d\n", found);
    }
}

// checked

void viewPendingRestockOrders()
{
    printf("\n====================================\n");
    printf("      PENDING DELIVERIES\n");
    printf("====================================\n");

    int found = 0;

    printf("%-20s %-12s\n", "Item Name", "Type");
    printf("-------------------------------------\n");

    /* Pending Restock Orders */
    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *order = &store.restockOrderItem[i];

        if (order->status != DELIVERY_IN_TRANSIT)
            continue;

        int index = findStockIndexByID(order->stockID);

        if (index == -1)
            continue;

        printf("%-20s %-12s\n",
               store.stockItem[index].itemName,
               "Restock");

        found++;
    }

    /* Pending Expired Exchanges */
    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        if (item->exchangeRequested)
        {
            printf("%-20s %-12s\n",
                   item->itemName,
                   "Exchange");

            found++;
        }
    }

    if (found == 0)
    {
        printf("No pending deliveries.\n");
    }
    else
    {
        printf("-------------------------------------\n");
        printf("Total pending deliveries: %d\n", found);
    }
}