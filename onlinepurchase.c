#include "onlinePurchase.h"
#include "product.h"
#include "data.h"
#include "alert.h"
#include <stdio.h>
OnlinePurchaseResult purchaseOnline(
    int stockID,
    int quantity)
{
    int index =findStockIndexByID(stockID);

    if (index == -1) // connect with func findstockid not found return -1
    {
        return ONLINE_PURCHASE_PRODUCT_NOT_FOUND;
    }

    if (quantity <= 0)
    {
        return ONLINE_PURCHASE_INVALID_QUANTITY;
    }

    if (store.stockItem[index].onlineStock < quantity)
    {
        return ONLINE_PURCHASE_OUT_OF_STOCK;
    }

    store.stockItem[index].onlineStock -= quantity;
    if (isOnlineAlert(stockID))
    {
        printf("WARNING: Online stock is low.\n");
    }
    return ONLINE_PURCHASE_SUCCESS;
}