#include <stdio.h>
#include "filehandler.h"
#include "data.h"

void saveData(void)
{
    FILE *fp = fopen("store.bin", "wb");
    if (fp == NULL)
    {
        printf("Error: Cannot save data.\n");
        return;
    }

    fwrite(&store, sizeof(StoreData), 1, fp);

    fclose(fp);
}

void loadData(void)
{
    FILE *fp = fopen("store.bin", "rb");

    if (fp == NULL)
    {
        // First run, file doesn't exist yet.
        return;
    }

    fread(&store, sizeof(StoreData), 1, fp);

    fclose(fp);
}