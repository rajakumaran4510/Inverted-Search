#include "struct.h"
#include <string.h>
#include "colour.h"

int Create_database(filename_node **head)
{
    int pos;
    char word[50];

    filename_node *temp = *head;

    while (temp != NULL)
    {
        FILE *fp = fopen(temp->str, "r");
        if (fp == NULL)
        {
            printf(RED "%s file opened failed\n", temp->str);
            temp = temp->file_link;
            continue;
        }

        while (fscanf(fp, "%s", word) == 1)
        {
            if (word[0] >= 'a' && word[0] <= 'z')
                pos = word[0] - 'a';
            else if (word[0] >= 'A' && word[0] <= 'Z')
                pos = word[0] - 'A';
            else
                pos = 26;

            main_node *mtemp = arr[pos].hash_link;
            main_node *prev = NULL;

            // Traverse main nodes upto NULL
            while (mtemp != NULL)
            {
                if (strcmp(mtemp->word, word) == 0)
                {
                    // Traverse sub nodes upto NULL
                    sub_node *stemp = mtemp->sub_link;
                    sub_node *sprev = NULL;
                    // Same file for same word
                    while (stemp != NULL) // Does this file already exist? → Yes → increase count
                    {
                        if (strcmp(stemp->filename, temp->str) == 0)
                        {
                            stemp->word_count++;
                            break;
                        }
                        sprev = stemp;
                        stemp = stemp->subnode_link;
                    }

                    // New file for same word
                    if (stemp == NULL) // Does this file already exist? → No → create new sub_node for it
                    {
                        sub_node *sub = malloc(sizeof(sub_node));
                        strcpy(sub->filename, temp->str);
                        sub->word_count = 1;
                        sub->subnode_link = NULL;

                        sprev->subnode_link = sub;
                        mtemp->filename_count++;
                    }
                    break;
                }

                prev = mtemp;
                mtemp = mtemp->mainnode_link;
            }

            // for new word create separte main and subnode
            if (mtemp == NULL)
            {
                main_node *main = malloc(sizeof(main_node));
                strcpy(main->word, word);
                main->filename_count = 1;
                main->mainnode_link = NULL;

                sub_node *sub = malloc(sizeof(sub_node));
                strcpy(sub->filename, temp->str);
                sub->word_count = 1;
                sub->subnode_link = NULL;

                main->sub_link = sub;

                if (arr[pos].hash_link == NULL)
                    arr[pos].hash_link = main;
                else
                    prev->mainnode_link = main;
            }
        }

        fclose(fp);
        temp = temp->file_link;
    }
    printf(YELLOW "\nINFO:Database created successfully\n");
    return SUCCESS;
}
