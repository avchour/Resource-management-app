#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "physicalPurchase.h"
#include "product.h"
#include "data.h"
#include "filehandler.h"
#include "alert.h"
#include "restock.h"
PhysicalPurchaseResult simulatePhysicalPurchase(int stockID)
{
    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        return PHYSICAL_PURCHASE_PRODUCT_NOT_FOUND;
    }

    if (store.stockItem[index].physicalStock <= 0)
    {
        return PHYSICAL_PURCHASE_OUT_OF_STOCK;
    }
    // verify later with quantity
    int quantity = rand() % 5 + 1;

    if (quantity > store.stockItem[index].physicalStock)
    {
        quantity = store.stockItem[index].physicalStock;
    }

    store.stockItem[index].physicalStock -= quantity;
    store.stockItem[index].quantity -= quantity;
    afterStockChanged(stockID);

    if (isPhysicalAlert(stockID))
    {
        printf("WARNING: Physical stock is low.\n");
    }

    return PHYSICAL_PURCHASE_SUCCESS;
}
void simulateDailyPhysicalSales(void)
{
    if (store.stockItemCount == 0)
    {
        printf("No products available.\n");
        return;
    }

    int customerCount = rand() % 11; // 0-10 customers

    printf("\n====================================\n");
    printf(" TODAY'S PHYSICAL STORE ACTIVITY\n");
    printf("====================================\n");
    printf("Customers visited today: %d\n\n", customerCount);

    for (int i = 0; i < customerCount; i++)
    {
        int productIndex = rand() % store.stockItemCount;

        int stockID = store.stockItem[productIndex].stockID;
        PhysicalPurchaseResult result = simulatePhysicalPurchase(stockID);
        if (result == PHYSICAL_PURCHASE_SUCCESS)
        {
            printf("Customer %-2d bought %s\n",
                   i + 1,
                   store.stockItem[productIndex].itemName);
        }
        else
        {
            printf("Customer %-2d wanted %s but it was out of stock.\n",
                   i + 1,
                   store.stockItem[productIndex].itemName);
        }
    }

    saveData();

    printf("\nToday's physical sales completed.\n");
}