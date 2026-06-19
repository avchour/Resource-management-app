#include "restock.h"
#include <stdio.h>
#include <time.h>
#include "data.h"

int findRestockIndexByID(int orderID)
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (store.restockOrderItem[i].orderId == orderID)
        {
            return i;
        }
    }
    return -1;
}
int findRestockIndexByProductID(int stockID)
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
       if (store.restockOrderItem[i].stockID == stockID)
        {
            return i;
        }
    }
    return -1;
}


int cancelRestockOrder(int orderID)
{
    int index = findStockIndexByID(orderID);

    if (index == -1)
    {
        return 0;
    }

    for (int i = index; i < store.stockItemCount - 1; i++)
    {
        store.stockItem[i] = store.stockItem[i + 1];
    }

    store.stockItemCount--;

    return 1;
}
