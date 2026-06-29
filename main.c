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
    display_login();
    saveData();
    return 0;
}