#include <time.h>
#include "alert.h"
#include "product.h"
#include "data.h"

int isOnlineAlert(int stockID)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    return store.stockItem[index].onlineStock <= store.stockItem[index].onlineAlertPoint && store.stockItem[index].onlineAlertPoint > 0;
}

int isPhysicalAlert(int stockID)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    return store.stockItem[index].physicalStock <= store.stockItem[index].physicalAlertPoint && store.stockItem[index].physicalAlertPoint > 0 ;
}

int isExpiredStock(int stockID)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    double days =
    difftime(time(NULL),store.stockItem[index].stockArrivalDate) /86400.0;
    // diff =current - old
    return days >= 14; // 14 days expired stock rule
} // all return cmp meaning :true =1 ; else false=0