#include "data.h"
#ifndef RESTOCK_H
#define RESTOCK_H
int findRestockIndexByID(int orderID);
typedef enum
{
    ADD_Restock_SUCCESS,
    ADD_Restock_EMPTY_NAME,
    ADD_Restock_INVALID_PRICE,
    ADD_Restock_INVALID_QUANTITY,
    ADD_Restock_DUPLICATE,
    ADD_Restock_FULL,
    ADD_Restock_EMPTY_CATEGORY
} AddRestockResult;
AddRestockResult addRestock(const char itemName[], float costprice, float sellingcost, int quantity, const char category[])
{
}

int createRestockOrder(int stockID, int quantity, RestockType type);

int editRestockQuantity(int orderID, int newQuantity);

int updateDeliveryStatus(int orderID, DeliveryStatus status);

int confirmDelivery(int orderID);

int cancelRestockOrder(int orderID);
#endif
