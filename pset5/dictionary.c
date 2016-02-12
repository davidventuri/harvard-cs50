/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false. Case-insensitive.
 * Assume that check is only passed strings with alphabetical characters and/or
 * apostrophes.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Stores words in hash table. Returns true if
 * successful else false.
 */
bool load(const char* dictionary)
{
    // define struct for value-pointer pair, i.e., a node
    typedef struct node
    {
        char word[LENGTH + 1];
        struct node* next;
    }
    node;
    
    // open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }
    
    // read word from dictionary
    // malloc a node* for each new word
    while (true)
    {
        node* new_node = malloc(sizeof(node));
        fscanf(fp, "%s", new_node->word);
        free(new_node);
        
        if (feof(fp))
        {
            // hit end of file
            break;
        }
    }
    
    // close dictionary
    fclose(dict);
    
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
