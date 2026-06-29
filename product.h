#ifndef PRODUCT_H
#define PRODUCT_H

typedef enum
{
    ADD_PRODUCT_SUCCESS,
    ADD_PRODUCT_DUPLICATE,
    ADD_PRODUCT_FULL,

} AddProductResult;
int editProductName(int stockID, const char newName[]);

int editCategory(int stockID, const char newCategory[]);

int editCostPrice(int stockID, float newCostPrice);

int editSellingPrice(int stockID, float newSellingPrice);

int findStockIndexByID(int stockID);

AddProductResult addProduct(char *itemName, float costprice, float sellingcost, int quantity, char *category);

#endif