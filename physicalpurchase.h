#ifndef PHYSICAL_PURCHASE_H
#define PHYSICAL_PURCHASE_H

typedef enum
{
    PHYSICAL_PURCHASE_SUCCESS,
    PHYSICAL_PURCHASE_PRODUCT_NOT_FOUND,
    PHYSICAL_PURCHASE_OUT_OF_STOCK
} PhysicalPurchaseResult;

PhysicalPurchaseResult
simulatePhysicalPurchase(int stockID);

#endif