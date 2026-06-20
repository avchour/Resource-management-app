#include "finance.h"
#include "data.h"
#include "product.h"

float calculateRevenue()
{
    float totalRevenue = 0;

    for (int i = 0; i < store.transactionCount; i++)
    {
        totalRevenue += store.transactionItem[i].totalAmount;
    }

    return totalRevenue;
}
float calculateExpense()
{
    float totalExpense = 0;

    for (int i = 0; i < store.transactionCount; i++)
    {
        int stockIndex = findStockIndexByID(store.transactionItem[i].stockID);

        if (stockIndex != -1)
        {
            totalExpense += store.stockItem[stockIndex].costprice * store.transactionItem[i].quantity;
        }
    }

    return totalExpense;
}
float calculateProfit()
{
    return calculateRevenue() - calculateExpense();
}
int getTotalItemsSold()
{
    int totalItemsSold = 0;

    for (int i = 0; i < store.transactionCount; i++)
    {
        totalItemsSold += store.transactionItem[i].quantity;
    }

    return totalItemsSold;
}
int getMostSoldProduct()
{
    int mostSoldIndex = -1;
    int mostSoldQty = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        int totalSold = 0;

        for (int j = 0; j < store.transactionCount; j++)
        {
            if (store.transactionItem[j].stockID == store.stockItem[i].stockID)
            {
                totalSold += store.transactionItem[j].quantity;
            }// STORE SAME ID ITEM 
        }

        if (totalSold > mostSoldQty)
        {
            mostSoldQty = totalSold;
            mostSoldIndex = i;
        }
    }

    return mostSoldIndex;
}
int getLeastSoldProduct()
{
    int leastSoldIndex = -1;
    int leastSoldQty = 999999;

    for(int i = 0; i < store.stockItemCount; i++)
    {
        int totalSold = 0;

        for(int j = 0; j < store.transactionCount; j++)
        {
            if(store.transactionItem[j].stockID == store.stockItem[i].stockID)
            {
                totalSold +=store.transactionItem[j].quantity;
            }
        }

        if(totalSold > 0 && totalSold < leastSoldQty)
        {
            leastSoldQty = totalSold;
            leastSoldIndex = i;
        }
    }

    return leastSoldIndex;
}
