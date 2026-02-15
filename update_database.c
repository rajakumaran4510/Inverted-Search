#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colour.h"

int update_database(filename_node **head)
{
    if (!db_created)
    {
        printf("\nINFO : Database not created yet\n");
        return FAILURE;
    }

    char dbfile[50], line[300];
    char word[50], filename[50];
    int index, filecount, wordcount;

    for (int i = 0; i < HASH_SIZE; i++)
        arr[i].hash_link = NULL;

    printf(GREEN "\nEnter database filename: ");
    scanf("%s", dbfile);

    FILE *fp = fopen(dbfile, "r");
    if (!fp)
    {
        printf(RED "\nDatabase file not found\n");
        return FAILURE;
    }

    while (fgets(line, sizeof(line), fp))
    {
        char *token = strtok(line, "#;\n");
        if (!token)
            continue;

        index = atoi(token); // hash index
        if (index < 0 || index >= HASH_SIZE)
            continue;

        token = strtok(NULL, "#;\n");
        if (!token)
            continue;
        strcpy(word, token); // word

        token = strtok(NULL, "#;\n");
        if (!token)
            continue;
        filecount = atoi(token); // no of files

        main_node *main = calloc(1, sizeof(main_node));
        if (!main)
            return FAILURE;

        strcpy(main->word, word);
        main->filename_count = filecount;

        sub_node *sprev = NULL;

        for (int i = 0; i < filecount; i++)
        {
            token = strtok(NULL, "#;\n");
            if (!token)
                break;
            strcpy(filename, token); // filename

            token = strtok(NULL, "#;\n");
            if (!token)
                break;
            wordcount = atoi(token); // no of times word appear

            filename_node *t = *head, *p = NULL;
            while (t)
            {
                if (strcmp(t->str, filename) == 0)
                {
                    if (p)
                        p->file_link = t->file_link;
                    else
                        *head = t->file_link;
                    free(t);
                    break;
                }
                p = t;
                t = t->file_link;
            }

            sub_node *sub = calloc(1, sizeof(sub_node));
            if (!sub)
                return FAILURE;

            strcpy(sub->filename, filename);
            sub->word_count = wordcount;

            if (!sprev)
                main->sub_link = sub;
            else
                sprev->subnode_link = sub;
            sprev = sub;
        }

        if (!arr[index].hash_link)
            arr[index].hash_link = main;
        else
        {
            main_node *m = arr[index].hash_link;
            while (m->mainnode_link)
                m = m->mainnode_link;
            m->mainnode_link = main;
        }
    }

    fclose(fp);

    if (*head == NULL)
    {
        printf(GREEN "\nINFO : Database is already upto date\n");
        return SUCCESS;
    }
    printf(GREEN "\nINFO : Hash table updated successfully\n");
    printf(GREEN "INFO : Updated file linked list\n");
    return SUCCESS;
}
