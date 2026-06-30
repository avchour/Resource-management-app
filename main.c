#include "display.h"
#include "filehandler.h"
#include "restock.h"
#include "stdlib.h"
int main(void)
{
    srand((unsigned)time(NULL));
    loadData();
    autoProcessExpiredItems();
    autoProcessRestock();
    autoRequestLowStock();
    display_login();
    saveData();
    return 0;
}