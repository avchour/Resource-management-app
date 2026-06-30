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

void viewoutofstockitems()
{
    printf("\n====================================\n");
    printf("        OUT OF STOCK ITEMS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *mystock = &store.stockItem[i];

        if (isOutOfStock(mystock->stockID))
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s\n", "ID", "Name", "Quantity");
                printf("------------------------------------\n");
            }

            printf("%-6d %-20s %-10d\n",
                   mystock->stockID,
                   mystock->itemName,
                   mystock->quantity);

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

void viewlowstockitems()
{
    printf("\n====================================\n");
    printf("          LOW STOCK ITEMS\n");
    printf("====================================\n");

    int found = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        // NEW RULE: fixed threshold = 20
        if (item->quantity <= 20 && item->quantity > 0)
        {
            if (found == 0)
            {
                printf("%-6s %-20s %-10s\n", "ID", "Name", "Quantity");
                printf("----------------------------------------\n");
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
        printf("No low stock items found.\n");
    }
    else
    {
        printf("----------------------------------------\n");
        printf("Total low stock items: %d\n", found);
    }
}
// checked

void viewPendingRestockOrders()
{
    printf("\n====================================\n");
    printf("       PENDING DELIVERIES\n");
    printf("====================================\n");

    int found = 0;

    printf("%-6s %-20s %-12s %-12s %-8s\n",
           "ID", "Item Name", "Reason", "Type", "Qty");
    printf("--------------------------------------------------------------\n");
    /* Pending Restock Orders */
    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *order = &store.restockOrderItem[i];

        if (order->status != DELIVERY_IN_TRANSIT)
            continue;

        int index = findStockIndexByID(order->stockID);
        Stock *item = &store.stockItem[index];
        if (index == -1)
            continue;

        printf("%-6d %-20s %-12s %-12s %-8d\n",
               item->stockID,
               item->itemName,
               item->quantity == 0 ? "Out Stock" : "Low Stock",
               "Restock",
               item->quantity);
        found++;
    }

    /* Pending Expired Item Exchanges */
    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        if (item->exchangeRequested)
        {
            printf("%-6d %-20s %-12s %-12s %-8d\n",
                   item->stockID,
                   item->itemName,
                   "Expired",
                   "Exchange",
                   item->exchangeQuantity);

            found++;
        }
    }

    if (found == 0)
    {
        printf("No pending deliveries.\n");
    }
    else
    {
        printf("------------------------------------------------\n");
        printf("Total pending deliveries: %d\n", found);
    }
}