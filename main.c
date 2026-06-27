#include <stdio.h>
#include "alert.h"
#include "data.h"
#include "display1st.h"
#include "finance.h"
#include "onlinePurchase.h"
#include "physicalPurchase.h"
#include "product.h"
#include "stockmanagement.h"
#include "restock.h"
#include <stdbool.h>

int main(void)
{
    bool running = true;

    while (running)
    {
        running = display_login(); // returns false when user chooses Exit
    }

    return 0;
}
