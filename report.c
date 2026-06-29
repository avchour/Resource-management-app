#include <stdio.h>
#include "report.h"
#include "finance.h"
#include "alert.h"
#include "data.h"

void inventoryReport()
{
       // printf("\n===== INVENTORY REPORT =====\n");

       for (int i = 0; i < store.stockItemCount; i++)
       {
              printf("\nID : %d\n",
                     store.stockItem[i].stockID);

              printf("Name : %s\n",
                     store.stockItem[i].itemName);

              printf("%s",
                     store.stockItem[i].category == 'F' ? "Food" : store.stockItem[i].category == 'D' ? "Drink"
                                                                                                      : "Snack");

              printf("Total Stock : %d\n",
                     store.stockItem[i].quantity);

              printf("Online Stock : %d\n",
                     store.stockItem[i].onlineStock);

              printf("Physical Stock : %d\n",
                     store.stockItem[i].physicalStock);
       }
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