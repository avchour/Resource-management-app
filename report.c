#include <stdio.h>
#include "report.h"
#include "finance.h"
#include "alert.h"
#include "data.h"

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
        printf("---------------------------------------------------------------------------------------\n");

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

        printf("---------------------------------------------------------------------------------------\n");
        printf("Total items: %d\n", store.stockItemCount);
    }
    // code to display all items in inventory
    // exit to adminMode_second
}
void lowStockReport()
{
       printf("\n===== LOW STOCK REPORT =====\n");

       for (int i = 0; i < store.stockItemCount; i++)
       {
              int stockID = store.stockItem[i].stockID;

              if (isOnlineAlert(stockID) || isPhysicalAlert(stockID))
              {
                     printf("\nID : %d\n",
                            stockID);

                     printf("Name : %s\n",
                            store.stockItem[i].itemName);

                     printf("Online Stock : %d\n",
                            store.stockItem[i].onlineStock);

                     printf("Physical Stock : %d\n",
                            store.stockItem[i].physicalStock);
              }
       }
}
void dailySalesReport()
{
       printf("\n===== DAILY SALES REPORT =====\n");

       printf("Total Transactions : %d\n",
              getTotalTransactions());

       printf("Total Items Sold   : %d\n",
              getTotalItemsSold());

       printf("Revenue            : $%.2f\n",
              calculateRevenue());

       printf("Expense            : $%.2f\n",
              calculateExpense());

       printf("Profit             : $%.2f\n",
              calculateProfit());
}
void monthlySalesReport()
{
       int most = getMostSoldProduct();
       int least = getLeastSoldProduct();

       printf("\n===== MONTHLY SALES REPORT =====\n");

       printf("Total Transactions : %d\n",
              getTotalTransactions());

       printf("Total Items Sold   : %d\n",
              getTotalItemsSold());

       printf("Revenue            : $%.2f\n",
              calculateRevenue());

       printf("Expense            : $%.2f\n",
              calculateExpense());

       printf("Profit             : $%.2f\n",
              calculateProfit());

       if (most != -1)
       {
              printf(
                  "Most Sold Product  : %s (%d sold)\n",
                  store.stockItem[most].itemName, getMostSoldQuantity());
       }

       if (least != -1)
       {
              printf(
                  "Least Sold Product : %s (%d sold)\n",
                  store.stockItem[least].itemName, getLeastSoldQuantity());
       }
}