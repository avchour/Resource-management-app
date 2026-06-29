#include <limits.h>
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

float getAverageSale()
{
    if(store.transactionCount==0)
        return 0;

    return calculateRevenue()/store.transactionCount;
}

float inventoryCostValue()
{
    float total=0;

    for(int i=0;i<store.stockItemCount;i++)
    {
        total+=store.stockItem[i].costprice*
               store.stockItem[i].quantity;
    }

    return total;
}

float inventorySellingValue()
{
    float total=0;

    for(int i=0;i<store.stockItemCount;i++)
    {
        total+=store.stockItem[i].sellingcost*
               store.stockItem[i].quantity;
    }

    return total;
}

int totalOnlineStock()
{
    int total=0;

    for(int i=0;i<store.stockItemCount;i++)
        total+=store.stockItem[i].onlineStock;

    return total;
}

int totalPhysicalStock()
{
    int total=0;

    for(int i=0;i<store.stockItemCount;i++)
        total+=store.stockItem[i].physicalStock;

    return total;
}

int getTotalTransactions()
{
    return store.transactionCount;
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
            }
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
    int leastSoldQty = INT_MAX; // high num int can also assume 999999

    for (int i = 0; i < store.stockItemCount; i++)
    {
        int totalSold = 0;

        for (int j = 0; j < store.transactionCount; j++)
        {
            if (store.transactionItem[j].stockID == store.stockItem[i].stockID)
            {
                totalSold += store.transactionItem[j].quantity;
            }
        }

        if (totalSold > 0 &&
            totalSold < leastSoldQty)
        {
            leastSoldQty = totalSold;
            leastSoldIndex = i;
        }
    }

    return leastSoldIndex;
}

int getMostSoldQuantity()
{
    int mostSoldQty = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        int totalSold = 0;

        for (int j = 0; j < store.transactionCount; j++)
        {
            if (store.transactionItem[j].stockID == store.stockItem[i].stockID)
            {
                totalSold += store.transactionItem[j].quantity;
            }
        }

        if (totalSold > mostSoldQty)
        {
            mostSoldQty = totalSold;
        }
    }

    return mostSoldQty;
}

int getLeastSoldQuantity()
{
    int leastSoldQty = INT_MAX;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        int totalSold = 0;

        for (int j = 0; j < store.transactionCount; j++)
        {
            if (store.transactionItem[j].stockID == store.stockItem[i].stockID)
            {
                totalSold += store.transactionItem[j].quantity;
            }
        }

        if (totalSold > 0 && totalSold < leastSoldQty)
        {
            leastSoldQty = totalSold;
        }
    }

    if (leastSoldQty == INT_MAX)
    {
        return 0;
    }

    return leastSoldQty;
}