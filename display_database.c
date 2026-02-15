#include "struct.h"
#include "colour.h"

#define HASH_SIZE 27

hash_t arr[HASH_SIZE];
#include "struct.h"
#include <stdio.h>

int Display_database(filename_node **head)
{
    if (!db_created)
    {
        printf("INFO : Database not created\n");
        return FAILURE;
    }
    printf("\n---------------------------------------------------------------\n");
    printf("Index | Word       | File Count |   File Name      | Word Count\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < 27; i++)
    {
        main_node *mtemp = arr[i].hash_link;

        while (mtemp != NULL)
        {
            sub_node *stemp = mtemp->sub_link;

            while (stemp != NULL)
            {
                printf(VIOLET "  %2d  | %-11s|     %1d      |   %-14s |   %d\n", i, mtemp->word, mtemp->filename_count, stemp->filename, stemp->word_count);

                stemp = stemp->subnode_link;
            }
            printf("---------------------------------------------------------------\n");

            mtemp = mtemp->mainnode_link;
        }
    }
}
