#include <stdlib.h>
#include <time.h>

#include "physicalPurchase.h"
#include "product.h"
#include "data.h"
#include "alert.h"
PhysicalPurchaseResult simulatePhysicalPurchase(int stockID)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return PHYSICAL_PURCHASE_PRODUCT_NOT_FOUND;
    }

    if (store.stockItem[index].physicalStock <= 0)
    {
        return PHYSICAL_PURCHASE_OUT_OF_STOCK;
    }
    // verify later with quantity
    int quantity = rand() % 5 + 1;

    if (quantity > store.stockItem[index].physicalStock)
    {
        quantity = store.stockItem[index].physicalStock;
    }

    store.stockItem[index].physicalStock -= quantity;
    if (isPhysicalAlert(stockID))
    {
        printf(
            "WARNING: Physical stock is low.\n");
    }

    return PHYSICAL_PURCHASE_SUCCESS;
}