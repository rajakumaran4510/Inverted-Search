#include "struct.h"
#include <stdio.h>
#include <string.h>
#include "colour.h"

int save_database()
{
    if (!db_created)
    {
        printf("INFO : No database to save\n");
        return FAILURE;
    }

    char filename[50];
    printf(RED "\nEnter the filename for database file: ");
    scanf("%s", filename);
    if (strstr(filename, ".txt") != NULL)
    {
        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Database file opening failed\n");
            return FAILURE;
        }

        for (int i = 0; i < 27; i++)
        {
            if (arr[i].hash_link != NULL)
            {
                main_node *mtemp = arr[i].hash_link;

                while (mtemp != NULL)
                {
                    fprintf(fp, "# %d;%s;%d;", i, mtemp->word, mtemp->filename_count);
                    sub_node *stemp = mtemp->sub_link;

                    while (stemp != NULL)
                    {
                        fprintf(fp, "%s;%d;", stemp->filename, stemp->word_count);
                        stemp = stemp->subnode_link;
                    }
                    fprintf(fp, "#\n");
                    mtemp = mtemp->mainnode_link;
                }
            }
        }

        fclose(fp);
        printf(GREEN "\nDatabase saved SUCCESSFULLY\n");
        return SUCCESS;
    }
    printf(GREEN "\nDatabase file must be .txt file\n");
    return FAILURE;
}
