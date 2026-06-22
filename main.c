#include <accctrl.h>
#include <stdio.h>
#include "display1st.h"
#include "alert.h"
#include "product.h"
#include "stockmanagement.h"
#include "data.h"

int main()
{
    allocateallStocks(); // split stock into online and physical on startup
    display_login();

    return 0;
}
