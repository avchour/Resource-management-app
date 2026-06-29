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
        Stock *mystock = &store.stockItem[i]; // use instead of using store.stockItem[i] many times

   /*this line */     if (mystock->onlineStock <= mystock->onlineAlertPoint && mystock->onlineAlertPoint > 0) 
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
        printf("No low online stock items found.\n");
    else
        printf("----------------------------------------------------------------\n");

    printf("Low online stock items: %d\n", found);

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

        if (isOutOfStock(mystock->stockID))
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
