#include <stdio.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "product.h"
#include "stockmanagement.h"
#include <ctype.h>
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

int editCategory(int stockID, const char newCategory)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return 0;
    }
    if (newCategory != 'F' && newCategory != 'D' && newCategory != 'S')
    {
        return 0;
    }
    store.stockItem[index].category[0] = newCategory;
    store.stockItem[index].category[1] = '\0';
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
    int duplicateIndex = findStockIndexByName(newName);

    if (duplicateIndex != -1 && duplicateIndex != index)
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

    if (newCostPrice <= 0)
    {
        return 0;
    }
    if (newCostPrice >= store.stockItem[index].sellingcost)
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

AddProductResult addProduct(char *itemName, float costprice, float sellingcost, int quantity, char category)
{
    if (itemName == NULL)
    {
        return 0;
    }
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
    productItem->category[0] = toupper(category);
    productItem->category[1] = '\0';
    allocateStock(productItem);

    productItem->onlineAlertPoint = 0;
    productItem->physicalAlertPoint = 0;

    productItem->stockArrivalDate = time(NULL);

    productItem->expiryDate = productItem->stockArrivalDate + (180 * 24 * 60 * 60);
    productItem->exchangeRequested = false;
    productItem->exchangeArrivalDate = 0;
    productItem->exchangeQuantity = 0;
    productItem->exchangeFeeRate = 0.10f;
    /*
    Update store counters.
    */
    store.nextStockID++;
    store.stockItemCount++;

    return ADD_PRODUCT_SUCCESS;
}
