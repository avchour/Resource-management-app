#ifndef display1st
#define display1st
#include <stdbool.h>
#include "data.h"
#include "product.h"
#include "display1st.h"

/* Login & role selection */
void display_login(void);
void admin_identification(void);
void choosemode(void);

/* Admin modules */
void adminMode_first(void);
void adminMode_second(void);

/* Inventory display functions */
void displayallitems(void);
void viewlowstockitems(void);
void viewoutofstockitems(void);
void viewPendingRestockOrders(void);
void calculatedaily_monthlysalesReport(void);

/* Customer system */
void customerMode(void);
void displayfooditems(void);
void displaydrinkitems(void);
void displaysnackitems(void);
void displayhotdealitems(void);
void calculating_system(void);

#endif