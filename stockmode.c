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
#include "report.h"
#include "physicalpurchase.h"

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
        printf("1. Display all items in inventory\n");
        printf("2. View low stock items\n");
        printf("3. View out of stock items\n");
        printf("4. View pending restock orders and date\n");
        printf("5. Calculate daily and monthly sales report\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");

        switch (getIntInput("Enter your choice: "))
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
                   (mystock->category == 'F' ) ? "Food" : (mystock->category == 'D') ? "Drink" : "Snack",
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

        int lowOnline = (mystock->onlineStock <= mystock->onlineAlertPoint && mystock->onlineAlertPoint > 0);
        int lowPhysical = (mystock->physicalStock <= mystock->physicalAlertPoint && mystock->physicalAlertPoint > 0);

        if (lowOnline || lowPhysical)
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
    printf("     PENDING RESTOCK (3 DAYS)\n");
    printf("====================================\n");

    int found = 0;

    time_t now = time(NULL);

    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *order = &store.restockOrderItem[i];

        if (order->status != DELIVERY_IN_TRANSIT)
            continue;

        // still in delivery window
        if (now >= order->expectedArrivalAt)
            continue;

        int stockIndex = findStockIndexByID(order->stockID);
        if (stockIndex == -1)
            continue;

        Stock *item = &store.stockItem[stockIndex];

        if (found == 0)
        {
            printf("%-10s %-20s %-15s\n", "OrderID", "Item Name", "ETA");
            printf("------------------------------------------------\n");
        }

        char eta[20];
        strftime(eta, sizeof(eta), "%Y-%m-%d", localtime(&order->expectedArrivalAt));

        printf("%-10d %-20s %-15s\n",
               order->orderId,
               item->itemName,
               eta);

        found++;
    }

    if (found == 0)
    {
        printf("No pending restock orders.\n");
    }
    else
    {
        printf("------------------------------------------------\n");
        printf("Total pending: %d\n", found);
    }
}

void calculatedaily_monthlysalesReport() // verify
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
