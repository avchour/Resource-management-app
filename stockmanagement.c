#include <stdio.h>
#include "stockmanagement.h"
#include "product.h"
#define ONLINE_RATIO 0.6
#define PHYSICAL_RATIO 0.4
void allocateStock(Stock *store)
{
    if (item == NULL)
        return;

    item->onlineStock = (int)(item->quantity * ONLINE_RATIO);
    item->physicalStock = (int)(item->quantity * PHYSICAL_RATIO);
}
void allocateAllStocks()
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        allocateStock(&store.stockItem[i]);
    }
}