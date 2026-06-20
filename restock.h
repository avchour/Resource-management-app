#include "data.h"
#ifndef RESTOCK_H
#define RESTOCK_H
int findRestockIndexByID(int orderID);
int findRestockIndexByProductID(int stockID);
int isOutOfStock(int stockID);
int hasPendingRestockOrder(int stockID);
int canRestock(int stockID);
typedef enum
{
    RESTOCK_SUCCESS,
    RESTOCK_PRODUCT_NOT_FOUND,
    RESTOCK_ORDER_NOT_FOUND,
    RESTOCK_INVALID_QUANTITY,
    RESTOCK_FULL,
    RESTOCK_EXISTS,
    RESTOCK_ALREADY_CONFIRMED
} RestockResult;
RestockResult createRestockOrder(int stockID, int quantity, RestockType type);

RestockResult editRestockQuantity(int orderID, int newQuantity);

RestockResult updateDeliveryStatus(int orderID, DeliveryStatus status);

RestockResult confirmDelivery(int orderID);

RestockResult cancelRestockOrder (int orderID);

#endif
