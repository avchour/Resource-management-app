#ifndef ONLINEPURCHASE_H
#define ONLINEPURCHASE_H

typedef enum
{
    ONLINE_PURCHASE_SUCCESS,
    ONLINE_PURCHASE_PRODUCT_NOT_FOUND,
    ONLINE_PURCHASE_INVALID_QUANTITY,
    ONLINE_PURCHASE_OUT_OF_STOCK
} OnlinePurchaseResult;

OnlinePurchaseResult purchaseOnline(
    int stockID,
    int quantity);

#endif