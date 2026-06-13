#include <stdio.h>
#include <string.h>

#include "data.h"
#include "product.h"

int findStockIndexByID(int stockID)
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (store.stockItem[i].stockID == stockID)
        {
            return i;
        }
    }

    return -1;
}

int findStockIndexByName(const char itemName[])
{
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].itemName,
                   itemName) == 0)
        {
            return i;
        }
    }

    return -1;
}

AddProductResult addProduct(const char itemName[],
                            float costprice,
                            float sellingcost,
                            int quantity)
{
    /*
        Validate input.
    */
    if (itemName == NULL || itemName[0] == '\0')
    {
        return ADD_PRODUCT_EMPTY_NAME;
    }

    if (costprice < 0 || sellingcost < 0)
    {
        return ADD_PRODUCT_INVALID_PRICE;
    }

    if (quantity < 0)
    {
        return ADD_PRODUCT_INVALID_QUANTITY;
    }

    /*
        Prevent writing outside the array.
    */
    if (store.stockItemCount >= MAX_STOCK)
    {
        return ADD_PRODUCT_FULL;
    }

    /*
        Do not create duplicate product names.
    */
    if (findStockIndexByName(itemName) != -1)
    {
        return ADD_PRODUCT_DUPLICATE;
    }

    /*
        Use the next unused position.
    */
    Stock *productItem =
        &store.stockItem[store.stockItemCount];

    /*
        Copy the product name safely.//snprintf(destination,destination_size,"%s",source);=
Safely copy source string into destination string.// can use strcpy but to prevent buffer overflow and crash program.
    */
    snprintf(productItem->itemName,
             sizeof(productItem->itemName),
             "%s",
             itemName);// strcpy (newItem->itemName,itemName);

    /*
        Assign automatic ID.
    */
    productItem->stockID = store.nextStockID;

    /*
        Prices.
    */
    productItem->costprice = costprice;
    productItem->sellingcost = sellingcost;

    /*
        Initial delivered quantity goes into storage.
    */
    productItem->quantity = quantity;

    /*
        Allocate these later using another feature.
    */
    productItem->onlineStock = 0;
    productItem->physicalStock = 0;

    /*
        Configure these later.
    */
    productItem->safetyStock = 0;

    productItem->onlineAlertPoint = 0;
    productItem->physicalAlertPoint = 0;

    productItem->normalRestockQuantity = 0;
    productItem->emergencyRestockQuantity = 0;

    /*
        Update store counters.
    */
    store.stockItemCount++;
    store.nextStockID++;

    return ADD_PRODUCT_SUCCESS;
}