#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "colour.h"

int main(int argc, char *argv[])
{
    filename_node *head = NULL;

    if (argc > 1)
    {
        printf("\n");
        for (int i = 1; i < argc; i++)
        {
            if (strstr(argv[i], ".txt") != NULL)
            {
                FILE *fptr = fopen(argv[i], "r");
                if (fptr == NULL)
                {
                    printf(RED "\nThe %s is not there in 'ls' and file opening failed ❌\n\n", argv[i]);
                    continue;
                }

                printf(VIOLET "%s opened successfully\n", argv[i]);

                fseek(fptr, 0, SEEK_END);
                int content = ftell(fptr);

                if (content > 0)
                {
                    filename_node *newnode = malloc(sizeof(filename_node));
                    strcpy(newnode->str, argv[i]);
                    newnode->file_link = NULL;

                    if (head == NULL)
                        head = newnode;
                    else
                    {
                        filename_node *temp = head;
                        while (temp->file_link != NULL)
                            temp = temp->file_link;
                        temp->file_link = newnode;
                    }
                }
                fclose(fptr);
            }
        }
    }
    else
    {
        printf(YELLOW "\nUsage ./a.out <filename1.txt> <...> etc...\n\n");
        return 0;
    }

    filename_node *temp = head;
    printf("\n");
    while (temp != NULL)
    {
        printf(YELLOW "%s -> ", temp->str);
        temp = temp->file_link;
    }
    printf("NULL\n");
    hashing_table();

    while (1)
    {
        int x;
        printf(BLUE "\nPRESS 1 -> Create Database\nPRESS 2 -> Display Database\nPRESS 3 -> Search Database\n");
        printf("PRESS 4 -> Update Database\nPRESS 5 -> Save\nPRESS 6 -> Exit\n\n");
        printf(RED "Enter the choice: ");
        scanf("%d", &x);

        switch (x)
        {
        case 1:
            Create_database(&head);
            break;
        case 2:
            Display_database(&head);
            break;
        case 3:
            search_database();
            break;
        case 4:
            update_database(&head);
            break;
        case 5:
            save_database();
            break;
        case 6:
            printf(RED "\nExiting Database 👋👋\n\n");
            exit(0);
        default:
            printf(RED "Invalid choice ❌\n");
        }
    }
}
