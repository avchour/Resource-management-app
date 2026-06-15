#ifndef DATA_H
#define DATA_H
#include <time.h>
#define MAX_STOCK 100
#define MAX_ORDER 500 // for restock seller request when stock alert
typedef struct
{
    char itemName[100];
    char category[50];
    int stockID;
    float sellingcost; // dak louk
    float costprice;   // we owner go to buy stock
    int quantity;      // total stock
    int safetyStock;
    int onlineStock;
    int physicalStock;

    int onlineAlertPoint;
    int physicalAlertPoint;

    int normalRestockQuantity;    // standard coke :100
    int emergencyRestockQuantity; // emer: 10 immediet request->

    time_t stockArrivalDate;
    float exchangeFeeRate;
} Stock;
typedef enum // for restock schedule 5day per restock; otherwise got request emergency
{
    RESTOCK_NORMAL,
    RESTOCK_EMERGENCY
} RestockType;

typedef enum // transport 3days to reach storage
{
    DELIVERY_IN_TRANSIT,
    DELIVERY_ARRIVED,
    DELIVERY_CONFIRMED
} DeliveryStatus; // for restock request to supplier

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
} RestockOrder; // for track restock

typedef struct
{
    long transactionId;
    int stockID;
    int quantity;
    float totalAmount;
    time_t transactionDate;
} Transaction;

typedef struct
{
    int stockItemCount;
    int nextStockID;
    Stock stockItem[MAX_STOCK];
    int restockOrderCount;
    long nextOrderId;
    RestockOrder restockOrderItem[MAX_ORDER];
    Transaction transactionItem[MAX_TRANSACTION];
    int transactionCount;
} StoreData;
extern StoreData store;
#endif
