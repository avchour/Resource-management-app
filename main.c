#include "display.h"
#include "filehandler.h"
#include "restock.h"
int main(void)
{
    loadData();
    autoProcessExpiredItems();
    autoProcessRestock();
    display_login();
    saveData();
    return 0;
}