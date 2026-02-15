#include "struct.h"
#include <string.h>
#include "colour.h"

int search_database()
{
    if (!db_created)
    {
        printf(RED "INFO : Database not created\n");
        return FAILURE;
    }

    char word[50];
    int pos;

    printf(GREEN "\nEnter the word to search: ");
    scanf("%s", word);

    if (word[0] >= 'a' && word[0] <= 'z')
        pos = word[0] - 'a';
    else if (word[0] >= 'A' && word[0] <= 'Z')
        pos = word[0] - 'A';
    else
        pos = 26;

    main_node *mtemp = arr[pos].hash_link;

    while (mtemp != NULL)
    {
        if (strcmp(word, mtemp->word) == 0)
        {
            sub_node *stemp = mtemp->sub_link;
            printf("\n----------------------------------------------------------\n");
            printf("Word   | File Count |   File Name      | Word Count\n");
            printf("----------------------------------------------------------\n");
            while (stemp != NULL)
            {
                printf(VIOLET "%-7s| %4d       |   %-14s |   %d\n", mtemp->word, mtemp->filename_count, stemp->filename, stemp->word_count);

                stemp = stemp->subnode_link;
            }
            printf("----------------------------------------------------------\n");
            return SUCCESS;
        }
        mtemp = mtemp->mainnode_link;
    }

    printf(RED "\nWord not found ❌\n");
    return FAILURE;
}
