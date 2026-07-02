#include "onlinePurchase.h"
#include "product.h"
#include "filehandler.h"
#include "data.h"
#include "alert.h"
#include "restock.h"
#include <stdio.h>
OnlinePurchaseResult purchaseOnline(int stockID, int quantity)
{
    int index = findStockIndexByID(stockID);

    if (index == -1) // connect with func findstockid not found return -1
    {
        return ONLINE_PURCHASE_PRODUCT_NOT_FOUND;
    }

    if (store.stockItem[index].onlineStock == 0)
    {
        return ONLINE_PURCHASE_OUT_OF_STOCK;
    }
    
    if (store.stockItem[index].onlineStock < quantity)
    {
        return ONLINE_PURCHASE_INVALID_QUANTITY;
    }

    store.stockItem[index].onlineStock -= quantity;
    store.stockItem[index].quantity -= quantity;
    afterStockChanged(stockID);
    saveData();
    
  /*  if (isOnlineAlert(stockID))
    {
        printf("WARNING: Online stock is low.\n");
    }*/
    return ONLINE_PURCHASE_SUCCESS;
}