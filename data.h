#ifndef DATA_H
#define DATA_H
#include <time.h>
#define MAX_STOCK 100
#define MAX_ORDER 500
typedef struct
{
    char itemName[100];
    int stockID;
    float sellingcost;
    float costprice;
    int stock;
    int safetyStock;
    int onlineStock;
    int physicalStock;

    int onlineAlertPoint;
    int physicalAlertPoint;

    int normalRestockQuantity;
    int emergencyRestockQuantity;
} Stock;
typedef enum
{
    RESTOCK_NORMAL,
    RESTOCK_EMERGENCY
} RestockType;

typedef enum
{
    DELIVERY_IN_TRANSIT,
    DELIVERY_ARRIVED,
    DELIVERY_CONFIRMED
} DeliveryStatus;

typedef struct
{
    long orderId;
    int productId;

    RestockType type;
    DeliveryStatus status;

    int quantity;

    time_t requestedAt;
    time_t expectedArrivalAt;
    time_t confirmedAt;

    double transportCost;
} RestockOrder;
typedef struct 
{
    int stockItemCount;
    int nextStockID;
    Stock stockitem[MAX_STOCK];
    int restockOrderCount;
    int nextOrderId;
    RestockOrder restockorderitem [MAX_ORDER];
}StoreData;
#endif