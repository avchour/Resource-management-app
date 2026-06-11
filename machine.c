#include <stdio.h>
#include "data.h"
#define Item 20

//List 
/*
ID  1001water 
    1002potato crisp
    1003coke
    1004salad
    1005apple
    1006orange
    1007tomato
    1008carrot
    1009gabbage
    1010starbuck latte
    1011noodle
    1012rice
    1013banana
    1014grape
    1015raddish
    1016beer
    1017milk
    1018cucumber
    1019durain
    1020 chicken
    1021 beef


*/

void addProduct (){
    Stock stock[Item];
    // We can add only 20 items;
    printf ("Enter every item into stock");
    for (int i=0;i<Item;i++){
    scanf ("%s",stock[i].itemName);
    }
}
void productStock(Stock *stock)
{
    printf("%d", stock->stockID);
}
void checkStock()
{
}
void alert()
{
    printf("Hello World");
}
