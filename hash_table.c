#include "struct.h"
#include "colour.h"

int db_created = 0;
int hashing_table(void)
{

    if (db_created)
    {
        printf("INFO : Database is already created\n");
        return FAILURE;
    }

    hash_t arr[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++)
    {
        arr[i].index = i;
        arr[i].hash_link = NULL;
    }
    db_created = 1;
    printf(GREEN "\nINFO : Hash table created successfully\n");
    return SUCCESS;
}
