#include <stdio.h>
#include <string.h>
#include <time.h>
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
        if (strcmp(store.stockItem[i].itemName, itemName) == 0)
        {
            return i;
        }
    }

    return -1;
}
int findStockCountByCategory(const char category[])
{
    int count = 0;

    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (strcmp(store.stockItem[i].category, category) == 0)
        {
            count++;
        }
    }

    return count;
}
int editQuantity(int stockID, int newQuantity)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    if (newQuantity < 0)
    {
        return 0;
    }

    store.stockItem[index].quantity = newQuantity;

    return 1;
}
int editCategory(int stockID, const char category[])
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    snprintf(store.stockItem[index].category, sizeof(store.stockItem[index].category), "%s", category);

    return 1;
}
int editProductName(int stockID, const char newName[])
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    snprintf(store.stockItem[index].itemName, sizeof(store.stockItem[index].itemName), "%s", newName);

    return 1;
}
int editCostPrice(int stockID, float newCostPrice)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    if (newCostPrice < 0)
    {
        return 0;
    }

    store.stockItem[index].costprice = newCostPrice;

    return 1;
}
int editSellingPrice(int stockID, float newSellingPrice)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    if (newSellingPrice < 0)
    {
        return 0;
    }

    store.stockItem[index].sellingcost = newSellingPrice;

    return 1;
}
int removeProduct(int stockID)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }

    for (int i = index; i < store.stockItemCount - 1; i++)
    {
        store.stockItem[i] = store.stockItem[i + 1];
    }

    store.stockItemCount--;

    return 1;
}

AddProductResult addProduct(const char itemName[], float costprice, float sellingcost, int quantity, const char category[])
{
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

    if (category == NULL || category[0] == '\0')
    {
        return ADD_PRODUCT_EMPTY_CATEGORY;
    }

    Stock *productItem = &store.stockItem[store.stockItemCount];// to avoid write long name so create new variable struct

    /*
        Copy the product name safely.//snprintf(destination,destination_size,"%s",source);=
Safely copy source string into destination string.// can use strcpy but to prevent buffer overflow and crash program.
    */
    snprintf(productItem->itemName, sizeof(productItem->itemName), "%s", itemName); // strcpy (newItem->itemName,itemName);

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

    snprintf(productItem->category, sizeof(productItem->category), "%s", category);
    productItem->stockArrivalDate = time(NULL);
    productItem->exchangeFeeRate = 0.10f;
    /*
        Update store counters.
    */
    store.stockItemCount++;
    store.nextStockID++;

    return ADD_PRODUCT_SUCCESS;
}