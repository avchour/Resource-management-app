#ifndef DATA_H
#define DATA_H
#include <time.h>
#define MAX_STOCK 100
#define MAX_ORDER 500 // for restock seller request when stock alert
#define MAX_TRANSACTION 10000
typedef struct
{
    char itemName[100];
    char category[50];
    int stockID;
    float sellingcost; // dak louk
    float costprice;   // we owner go to buy stock
    int quantity;      // total stock
    int onlineStock;
    int physicalStock;
    int onlineAlertPoint;
    int physicalAlertPoint;
    time_t stockArrivalDate;
    float exchangeFeeRate;
} Stock;
typedef enum // for restock schedule 7day per restock; otherwise got request emergency
{
    RESTOCK_NORMAL,
    RESTOCK_EMERGENCY
} RestockType;

typedef enum // transport 3days to reach storage
{
    DELIVERY_IN_TRANSIT,
    DELIVERY_CONFIRMED
} DeliveryStatus; // for restock request to supplier

typedef struct
{
    int orderId; // requestID
    int stockID; // productID

    RestockType type;
    DeliveryStatus status;

    int quantity;

    time_t requestedAt;
    time_t expectedArrivalAt;
    time_t confirmedAt;
    

    float transportCost;
} RestockOrder; // for track restock

typedef struct
{
    int transactionId;
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
    int nextOrderId;
    RestockOrder restockOrderItem[MAX_ORDER];
    Transaction transactionItem[MAX_TRANSACTION];
    int transactionCount;
} StoreData;
extern StoreData store;
#endif
