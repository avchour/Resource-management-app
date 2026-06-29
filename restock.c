#include "restock.h"
#include <time.h>
#include "data.h"
#include "product.h"
#include "alert.h"
#include "stockmanagement.h"
#include <stdbool.h>
#include "report.h"
#include "product.h"
#include "display1st.h"
#include "onlinePurchase.h"
#include "physicalPurchase.h"



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


time_t expiryDate;

bool exchangeRequested;

time_t exchangeArrivalDate;

int exchangeQuantity;

void autoProcessRestock()
{
    time_t now = time(NULL);

    for (int i = 0; i < store.restockOrderCount; i++)
    {
        RestockOrder *order = &store.restockOrderItem[i];

        // Wait until delivery date
        if (order->status != DELIVERY_IN_TRANSIT)
            continue;

        if (now < order->expectedArrivalAt)
            continue;

        int index = findStockIndexByID(order->stockID);

        if (index == -1)
            continue;

        // Add stock
        store.stockItem[index].quantity += order->quantity;

        // Automatically split into online & physical
        allocateStock(&store.stockItem[index]);

        // Delivery finished
        order->status = DELIVERY_CONFIRMED;
        order->confirmedAt = now;
    }
}


time_t expiryDate;

bool exchangeRequested;

time_t exchangeArrivalDate;

int exchangeQuantity;

void autoProcessExpiredItems()
{
    time_t now = time(NULL);

    for (int i = 0; i < store.stockItemCount; i++)
    {
        Stock *item = &store.stockItem[i];

        /* -----------------------------
           STEP 1
           Item has expired.
           Send it back to factory.
        ------------------------------*/
        if (item->expiryDate <= now &&
            !item->exchangeRequested)
        {
            // Remember how many items are being exchanged
            item->exchangeQuantity = item->quantity;

            // Remove expired stock immediately
            item->quantity = 0;
            item->onlineStock = 0;
            item->physicalStock = 0;

            // Create exchange request
            item->exchangeRequested = true;

            // Replacement arrives in 3 days
            item->exchangeArrivalDate = now + (3 * 24 * 60 * 60);
        }

        /* -----------------------------
           STEP 2
           Replacement has arrived.
        ------------------------------*/
        else if (item->exchangeRequested &&
                 now >= item->exchangeArrivalDate)
        {
            // Receive new stock
            item->quantity = item->exchangeQuantity;

            // Split into online and physical stock
            allocateStock(item);

            // New expiry date
            item->expiryDate = now + (180 * 24 * 60 * 60);

            // Reset exchange information
            item->exchangeRequested = false;
            item->exchangeArrivalDate = 0;
            item->exchangeQuantity = 0;
        }
    }
}


