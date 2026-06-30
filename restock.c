#include "restock.h"
#include <time.h>
#include "data.h"
#include "product.h"
#include "alert.h"
#include "filehandler.h"
#include "stockmanagement.h"
#include <stdbool.h>
#include "report.h"
#include <stdio.h>

int findRestockIndexByID(int orderID)
{
    for (int i = 0; i < store.restockOrderCount; i++)
    {
        if (store.restockOrderItem[i].orderId == orderID)
        {
            return i;
        }
    }
    return -1;
}

RestockResult cancelRestockOrder(int orderID)
{
    int index = findRestockIndexByID(orderID);

    if (index == -1)
    {
        return RESTOCK_ORDER_NOT_FOUND;
    }

    for (int i = index; i < store.restockOrderCount - 1; i++)
    {
        store.restockOrderItem[i] = store.restockOrderItem[i + 1];
    }

    store.restockOrderCount--;

    return RESTOCK_SUCCESS;
}

RestockResult createRestockOrder(int stockID, int quantity, RestockType type)
{
    int productIndex = findStockIndexByID(stockID);

    if (productIndex == -1)
    {
        return RESTOCK_PRODUCT_NOT_FOUND;
    }
    if (hasPendingRestockOrder(stockID))
    {
        return RESTOCK_EXISTS;
    }

    if (quantity <= 0)
    {
        return RESTOCK_INVALID_QUANTITY;
    }

    if (store.restockOrderCount >= MAX_ORDER)
    {
        return RESTOCK_FULL;
    }

    RestockOrder *order = &store.restockOrderItem[store.restockOrderCount];

    order->orderId = store.nextOrderId++;

    order->stockID = stockID;

    order->quantity = quantity;

    order->type = type;

    order->status = DELIVERY_IN_TRANSIT;

    order->requestedAt = time(NULL);

    if (type == RESTOCK_NORMAL)
    {
        order->expectedArrivalAt = order->requestedAt + (14 * 24 * 60 * 60);
    }
    else
    {
        order->expectedArrivalAt = order->requestedAt + (3 * 24 * 60 * 60);
    }

    order->confirmedAt = 0;
    order->transportCost = 0;

    store.restockOrderCount++;

    return RESTOCK_SUCCESS;
}

RestockResult confirmDelivery(int orderID)
{
    int orderIndex = findRestockIndexByID(orderID);

    if (orderIndex == -1)
    {
        return RESTOCK_ORDER_NOT_FOUND;
    }

    RestockOrder *order = &store.restockOrderItem[orderIndex];

    if (order->status == DELIVERY_CONFIRMED)
    {
        return RESTOCK_ALREADY_CONFIRMED;
    }

    int productIndex = findStockIndexByID(order->stockID);

    if (productIndex == -1)
    {
        return RESTOCK_PRODUCT_NOT_FOUND;
    }

    store.stockItem[productIndex].quantity += order->quantity;
    // call funct to split because ah nis order + ah total stock jg vea ot auto split stock management te jg yg hav derm bey split ruch kleng kron restock pleam auto split
    allocateStock(&store.stockItem[productIndex]);
    store.stockItem[productIndex].stockArrivalDate = time(NULL);

    store.stockItem[productIndex].expiryDate = time(NULL) + (30 * 24 * 60 * 60);
    order->status = DELIVERY_CONFIRMED;
    order->confirmedAt = time(NULL);
    saveData();
    return RESTOCK_SUCCESS;
}
int canRestock(int stockID)
{
    return isOnlineAlert(stockID) || isPhysicalAlert(stockID);
}
int isOutOfStock(int stockID)
{
    int index = findStockIndexByID(stockID);
    if (index == -1)
    {
        return 0;
    }
    return store.stockItem[index].onlineStock == 0 && store.stockItem[index].physicalStock == 0;
}
int hasPendingRestockOrder(int stockID) // prevent duplicate same product request order
{
    for (int i = 0; i < store.restockOrderCount; i++)
    {
        if (store.restockOrderItem[i].stockID == stockID &&
            store.restockOrderItem[i].status != DELIVERY_CONFIRMED)
        {
            return 1;
        }
    }

    return 0;
}
// helper function
void autoRequestLowStock(void)
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        if (item->quantity <= 20 &&
            !hasPendingRestockOrder(item->stockID))
        {
            int orderQty = 40 - item->quantity;

            createRestockOrder(
                item->stockID,
                orderQty,
                RESTOCK_EMERGENCY);
        }
    }
}

void autoProcessRestock(void)
{
    time_t now = time(NULL);

    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *order = &store.restockOrderItem[i];

        if (order->status != DELIVERY_IN_TRANSIT)
            continue;

        if (now < order->expectedArrivalAt)
            continue;

        int index = findStockIndexByID(order->stockID);

        if (index == -1)
            continue;

        Stock *item = &store.stockItem[index];

        item->quantity += order->quantity;

        allocateStock(item);

        item->stockArrivalDate = now;
        item->expiryDate = now + (30 * 24 * 60 * 60);
        order->status = DELIVERY_CONFIRMED;
        order->confirmedAt = now;
    }
    saveData();
}

void autoProcessExpiredItems(void)
{
    time_t now = time(NULL);

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        if (item->quantity > 0 && item->expiryDate <= now && !item->exchangeRequested)
        {
            item->exchangeQuantity = item->quantity;

            float fee =
                item->exchangeQuantity *
                item->costprice *
                item->exchangeFeeRate;

            printf("Exchange fee for %s: $%.2f\n",
                   item->itemName, fee);

            item->quantity = 0;
            item->onlineStock = 0;
            item->physicalStock = 0;

            item->exchangeRequested = true;

            item->exchangeArrivalDate = now + (3 * 24 * 60 * 60);
        }

        else if (item->exchangeRequested &&
                 now >= item->exchangeArrivalDate)
        {
            item->quantity = item->exchangeQuantity;

            allocateStock(item);

            item->stockArrivalDate = now;
            item->expiryDate = now + (30 * 24 * 60 * 60);
            printf("%s exchange completed.\n", item->itemName);
            item->exchangeRequested = false;
            item->exchangeArrivalDate = 0;
            item->exchangeQuantity = 0;
        }
    }
    saveData();
}
void afterStockChanged(int stockID)
{
    int index = findStockIndexByID(stockID);
    if (index == -1)
        return;

    Stock *item = &store.stockItem[index];

    if (item->quantity <= 20 &&
        !hasPendingRestockOrder(stockID))
    {
        createRestockOrder(
            stockID,
            40 - item->quantity,
            RESTOCK_EMERGENCY);
    }

    saveData();
}