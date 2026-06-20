#include "restock.h"
#include <time.h>
#include "data.h"
#include "product.h"
#include "alert.h"
#include "stockmanagement.h"
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
int findRestockIndexByProductID(int stockID)
{
    for (int i = 0; i < store.restockOrderCount; i++)
    {
        if (store.restockOrderItem[i].stockID == stockID)
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
        order->expectedArrivalAt = order->requestedAt + (5 * 24 * 60 * 60);
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
RestockResult updateDeliveryStatus(int orderID, DeliveryStatus status)
{
    int index = findRestockIndexByID(orderID);

    if (index == -1)
    {
        return RESTOCK_ORDER_NOT_FOUND;
    }

    store.restockOrderItem[index].status = status;

    return RESTOCK_SUCCESS;
}
RestockResult editRestockQuantity(int orderID, int newQuantity)
{
    int index = findRestockIndexByID(orderID);

    if (index == -1)
    {
        return RESTOCK_ORDER_NOT_FOUND;
    }

    if (newQuantity <= 0)
    {
        return RESTOCK_INVALID_QUANTITY;
    }

    store.restockOrderItem[index].quantity = newQuantity;

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

    order->status = DELIVERY_CONFIRMED;

    order->confirmedAt = time(NULL);

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