#ifndef  DISPLAY1ST_H
#define  DISPLAY1ST_H
void display_login();
/* Admin modules */


/* Inventory display functions */
void displayallitems();
void viewlowstockitems();
void viewoutofstockitems();
void viewPendingRestockOrders();
void calculatedaily_monthlysalesReport();

/* Customer system */
void customerMode();
void displayfooditems();
void displaydrinkitems();
void displaysnackitems();
void displayhotdealitems();
void calculating_system(int stockID, int quantity);

#endif