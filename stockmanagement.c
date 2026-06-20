#include <stdio.h>
#include "stockmanagement.h"
#define ONLINE_RATIO 0.6
#define PHYSICAL_RATIO 0.4
void allocateStock(Stock *item)
{
    if (item == NULL)
        return;

    item->onlineStock = (int)(item->quantity * ONLINE_RATIO);
    item->physicalStock = item->quantity - item->onlineStock; // important cannot use ration multiplication it may lost 1 item due to bug convert integer
    item->onlineAlertPoint = (int)(item->onlineStock * 0.4);
    item->physicalAlertPoint = (int)(item->physicalStock * 0.4);
}
void allocateAllStocks()
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        allocateStock(&store.stockItem[i]);
    }
}