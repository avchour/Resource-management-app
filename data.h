#ifndef DATA_H
#define DATA_H

typedef struct
{
    char itemName[100];
    int stockID;
    float sellingcost;
    float costprice;
    int stock;
    int safetyStock;
    int alertPoint;
    int physicalReserve;
    int normalRestockQuantity;
    int emergencyRestockQuantity;
} Stock;
#endif