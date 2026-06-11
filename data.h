#ifndef DATA_H
#define DATA_H

typedef struct 
{
    char itemName [100];
    int stockID;
    int quantity;
    int cost;
    int minimum;
} Stock;

#endif