#ifndef PRODUCT_H
#define PRODUCT_H

int findStockCountByCategory(
    const char category[]);

typedef enum
{
    ADD_PRODUCT_SUCCESS,
    ADD_PRODUCT_EMPTY_NAME,
    ADD_PRODUCT_INVALID_PRICE,
    ADD_PRODUCT_INVALID_QUANTITY,
    ADD_PRODUCT_DUPLICATE,
    ADD_PRODUCT_FULL,
    ADD_PRODUCT_EMPTY_CATEGORY

} AddProductResult;
int editProductName(int stockID,
                    const char newName[]);

int editProductCategory(int stockID,
                        const char newCategory[]);

int editCostPrice(int stockID,
                  float newCostPrice);

int editSellingPrice(int stockID,
                     float newSellingPrice);

int editQuantity(int stockID,
                 int newQuantity);
int findStockIndexByID(int stockID);

int findStockIndexByName(const char itemName[]);

int removeProduct(int stockID);

int purchaseProduct(int stockID);

AddProductResult addProduct(const char itemName[],
                            float costprice,
                            float sellingcost,
                            int quantity,
                            char category[]);

#endif