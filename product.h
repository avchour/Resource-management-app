#ifndef PRODUCT_H
#define PRODUCT_H

typedef enum
{
    ADD_PRODUCT_SUCCESS,
    ADD_PRODUCT_EMPTY_NAME,
    ADD_PRODUCT_INVALID_PRICE,
    ADD_PRODUCT_INVALID_QUANTITY,
    ADD_PRODUCT_DUPLICATE,
    ADD_PRODUCT_FULL

} AddProductResult;

int findStockIndexByID(int stockID);

int findStockIndexByName(const char itemName[]);

AddProductResult addProduct(const char itemName[],
                            float costprice,
                            float sellingcost,
                            int quantity);

#endif