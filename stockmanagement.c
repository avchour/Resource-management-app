#include <stdio.h>
#include "stockmanagement.h"
#define ONLINE_RATIO 0.6

void allocateStock(Stock *item)
{
    if (item == NULL)
        return;

    item->onlineStock = (int)(item->quantity * ONLINE_RATIO);
    item->physicalStock = item->quantity - item->onlineStock; // important cannot use ration multiplication it may lost 1 item due to bug convert integer
    item->onlineAlertPoint = 20;
    item->physicalAlertPoint = 20;
}
void allocateAllStocks()
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        allocateStock(&store.stockItem[i]);
    }
}