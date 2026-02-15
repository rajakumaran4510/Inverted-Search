#ifndef SLL_H
#define SLL_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1
#define HASH_SIZE 27



// decleration
struct sub_node;
struct main_node;

// main node
typedef struct main_node
{
    int filename_count;
    char word[50];
    struct sub_node *sub_link;
    struct main_node *mainnode_link;
} main_node;

// sub node
typedef struct sub_node
{
    char filename[20];
    int word_count;
    struct sub_node *subnode_link;
} sub_node;

// hash table
typedef struct hash_table
{
    int index;
    struct main_node*hash_link;
} hash_t;

// filename list
typedef struct filename_node
{
    char str[50];
    struct filename_node *file_link;
} filename_node;

extern hash_t arr[HASH_SIZE];
extern int db_created;

int Create_database(filename_node **head);
int Display_database(filename_node **head);
int search_database();
int update_database(filename_node **head);
int save_database();
int hashing_table();


#endif
