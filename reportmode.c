#include "reportmode.h"
#include <stdio.h>
#include "utils.h"
#include "data.h"
#include "report.h"


void reportMode()
{
    bool running = true;

    while (running)
    {
        printf("\n====================================\n");
        printf("         REPORT MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Sales Report\n");
        printf("2. Inventory Report\n");
        printf("0. Back\n");
        printf("------------------------------------\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            if (store.transactionCount == 0)
            {
                printf("\nNo transactions recorded.\n");
            }
            else
            {
                printf("\n====================================\n");
                printf("          SALES REPORT\n");
                printf("====================================\n");
                printf("1. Daily Report\n");
                printf("2. Monthly Report\n");
                printf("0. Back\n");
                printf("------------------------------------\n");

                switch (getIntInput("Enter your choice: "))
                {
                case 1:
                    dailySalesReport();
                    break;

                case 2:
                    monthlySalesReport();
                    break;

                case 0:
                    break;

                default:
                    printf("Invalid choice.\n");
                    break;
                }
            }
            break;

        case 2:
            displayallitems();
            break;

        case 0:
            running = false;
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    }
}