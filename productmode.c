#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "product.h"
#include "productmode.h"
#include <ctype.h>
#include "utils.h"
#include "filehandler.h"
void productMode()
{
    bool running = true;
    while (running)
    {
        printf("\n====================================\n");
        printf("          PRODUCT MENU\n");
        printf("====================================\n");
        printf("1. Add Product\n");
        printf("2. Edit Product\n");
        printf("3. Remove Product\n");
        printf("4. Search Product\n");
        printf("0. Back\n");
        printf("------------------------------------\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            delete();
            break;
        case 4:
            search();
            break;
        case 0:
            running = false;
            break;
        default:
            printf("\nInvalid choice!Please try again.\n");
            break;
        }
    }
}
void add()
{
    do
    {
        char item_name[255];
        float in_price, out_price;
        int quantity;
        char category[20];
        printf("\n========== ADD PRODUCT ==========\n");
        while (1)
        {
            printf("Enter item's name: ");
            fgets(item_name, sizeof(item_name), stdin);
            item_name[strcspn(item_name, "\n")] = '\0';
            rtrim(item_name);

            if (item_name == NULL || item_name[0] == '\0')
            {
                printf("Error: Empty product name.\n");
                continue;
            }
            break;
        }
        printf("Product name update successfully.\n");

        while (1)
        {
            in_price = getFloatInput("Enter cost expense: ");
            if (in_price <= 0)
            {
                printf("Enter cost expense again!");
                continue;
            }
            break;
        }
        printf("Cost price update successfully.\n");

        while (1)
        {
            out_price = getFloatInput("Enter selling price: ");
            if (out_price <= 0)
            {
                printf("Enter selling price again");
                continue;
            }
            break;
        }
        printf("Selling price update successfully.\n");

        while (1)
        {
            quantity = getIntInput("Enter item's quantity: ");
            if (quantity <= 0)
            {
                printf("Enter quantity again!");
                continue;
            }
            break;
        }
        printf("Quantity update successfully.\n");

        while (1)
        {
            printf("Choose category : (F)ood (D)rinks (S)nacks: ");
            scanf("%1s", category);
            while (getchar() != '\n')
                ;

            char c = toupper(category[0]);
            if (c == 'F' || c == 'D' || c == 'S')
            {
                printf("Category update successfully.\n");
                break;
            }
            printf("Error: Category must be F, D or S.\n");
        }
        // point
        AddProductResult result =
            addProduct(item_name,
                       in_price,
                       out_price,
                       quantity,
                       category);

        switch (result)
        {
        case ADD_PRODUCT_SUCCESS:
            saveData();
            printf("Product added successfully.\n");
            break;

        case ADD_PRODUCT_DUPLICATE:
            printf("Error: Product already exists.\n");
            break;

        case ADD_PRODUCT_FULL:
            printf("Error: Storage is full.\n");
            break;
        }
    } while (askAgain("Add another product"));
}
void edit()
{
    bool running = true;
    do
    {
        int stockID;

        printf("\n========== EDIT PRODUCT ==========\n");

        stockID = getIntInput("Enter Product ID: ");

        if (findStockIndexByID(stockID) == -1)
        {
            printf("Error: Product ID not found.\n");
            continue;
        }

        printf("\nWhat do you want to edit?\n");
        printf("1. Product Name\n");
        printf("2. Cost Price\n");
        printf("3. Selling Price\n");
        printf("4. Category\n");
        printf("0. Exit\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
        {
            char newName[255];

            while (1)
            {
                printf("Enter new product name: ");
                fgets(newName, sizeof(newName), stdin);

                newName[strcspn(newName, "\n")] = '\0';
                rtrim(newName);

                if (newName[0] == '\0')
                {
                    printf("Error: Empty product name.\n");
                    continue;
                }

                break;
            }

            if (editProductName(stockID, newName))
                printf("Product name updated successfully.\n");
                saveData();
            else
                printf("Failed to update product name.\n");

            break;
        }

        case 2:
        {
            float newCost;

            while (1)
            {
                newCost = getFloatInput("Enter new cost price: ");

                if (newCost > 0)
                    break;

                printf("Invalid cost price.\n");
            }

            if (editCostPrice(stockID, newCost))
                printf("Cost price updated successfully.\n");
                saveData();
            else
                printf("Failed to update cost price.\n");

            break;
        }

        case 3:
        {
            float newSell;

            while (1)
            {
                newSell = getFloatInput("Enter new selling price: ");

                if (newSell > 0)
                    break;

                printf("Invalid selling price.\n");
            }

            if (editSellingPrice(stockID, newSell))
                printf("Selling price updated successfully.\n");
                saveData();
            else
                printf("Failed to update selling price.\n");

            break;
        }

        case 4:
        {
            char category[20];

            while (1)
            {
                printf("Enter category (F/D/S): ");
                scanf("%1s", category);
                while (getchar() != '\n')
                    ;

                category[0] = toupper(category[0]);

                if (category[0] == 'F' ||
                    category[0] == 'D' ||
                    category[0] == 'S')
                {
                    break;
                }

                printf("Error: Category must be F, D or S.\n");
            }

            if (editCategory(stockID, category))
                printf("Category updated successfully.\n");
                saveData();
            else
                printf("Failed to update category.\n");

            break;
        }

        case 0:
            running = false;
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (running && askAgain("Edit another product"));
}
void delete()
{
    do
    {
        int stockID;

        printf("\n========== REMOVE PRODUCT ==========\n");

        stockID = getIntInput("Enter Product ID: ");

        if (findStockIndexByID(stockID) == -1)
        {
            printf("Error: Product ID not found.\n");
            continue;
        }

        if (askAgain("Are you sure you want to remove this product"))
        {
            removeProduct(stockID);
            printf("Product removed successfully.\n");
            saveData();
        }
        else
        {
            printf("Remove cancelled.\n");
        }
    } while (askAgain("Remove another product"));
}

void search()
{
    bool running = true;

    while (running)
    {
        printf("\n========== SEARCH PRODUCT ==========\n");
        printf("1. Search by Product ID\n");
        printf("2. Back\n");

        switch (getIntInput("Enter your choice: "))
        {
        case 1:
            searchByID();
            break;

        case 2:
            running = false;
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    return;
}
void searchByID()
{
    int stockID = getIntInput("Enter Product ID: ");

    int index = findStockIndexByID(stockID);

    if (index == -1)
    {
        printf("Product not found.\n");
        return;
    }

    Stock *product = &store.stockItem[index];

    printf("\n========== PRODUCT ==========\n");
    printf("ID          : %d\n", product->stockID);
    printf("Name        : %s\n", product->itemName);
    printf("Category    : %s\n",
           product->category[0] == 'F' ? "Food" : product->category[0] == 'D' ? "Drink"
                                                                              : "Snack");
    printf("Cost Price  : %.2f\n", product->costprice);
    printf("Sell Price  : %.2f\n", product->sellingcost);
    printf("Online      : %d\n", product->onlineStock);
    printf("Physical    : %d\n", product->physicalStock);
    printf("Total       : %d\n", product->quantity);
}