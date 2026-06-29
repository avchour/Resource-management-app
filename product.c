#include <stdio.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "product.h"
#include "stockmanagement.h"
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

int editCategory(int stockID, const char category[])
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }
    if (category == NULL || category[0] == '\0')
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
    // avoid same name sen jam do name
    if (newName == NULL || newName[0] == '\0')
    {
        return 0;
    }
    for (int i = 0; i < store.stockItemCount; i++)
    {
        if (i != index && strcmp(store.stockItem[i].itemName, newName) == 0)
        {
            return 0;
        }
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

    if (newCostPrice <= 0)
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

    if (newSellingPrice <= store.stockItem[index].costprice)
    {
        return 0;
    }

    store.stockItem[index].sellingcost = newSellingPrice;

    return 1;
}

AddProductResult addProduct(char *itemName, float costprice, float sellingcost, int quantity, char *category)
{

    if (store.stockItemCount >= MAX_STOCK)
    {
        return ADD_PRODUCT_FULL;
    }
    if (findStockIndexByName(itemName) != -1)
    {
        return ADD_PRODUCT_DUPLICATE;
    }

    Stock *productItem = &store.stockItem[store.stockItemCount]; // to avoid write long name so create new variable struct

    snprintf(productItem->itemName, sizeof(productItem->itemName), "%s", itemName); // strcpy (newItem->itemName,itemName);

    productItem->stockID = store.nextStockID;

    productItem->costprice = costprice;
    productItem->sellingcost = sellingcost;

    productItem->quantity = quantity;

    allocateStock(productItem);

    productItem->onlineAlertPoint = 0;
    productItem->physicalAlertPoint = 0;

    snprintf(productItem->category, sizeof(productItem->category), "%s", category);
    productItem->stockArrivalDate = time(NULL);
    productItem->exchangeFeeRate = 0.10f;
    /*
    Update store counters.
    */
    store.nextStockID++;
    store.stockItemCount++;

    return ADD_PRODUCT_SUCCESS;
}
