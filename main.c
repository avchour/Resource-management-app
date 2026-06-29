#include "display.h"
#include "filehandler.h"
int main(void)
{
    loadData ();
    display_login(); 
    saveData ();
    return 0;
}