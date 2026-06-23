#ifndef display1st
#define display1st
#include "data.h"
#include "product.h"
#include "display1st.h"

/* Login & role selection */
void display_login();
void admin_identification();
void choosemode();

/* Admin modules */
void adminMode_first();
void adminMode_second();

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
void calculating_system();

#endif