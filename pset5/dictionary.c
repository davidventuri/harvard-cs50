/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stddef.h>

#include "dictionary.h"

// define struct for value-pointer pair, i.e., a node
    typedef struct node
    {
        char word[LENGTH + 1];
        struct node* next;
    }
    node;
    
// create array of pointer-to-nodes of size HASHTABLE_SIZE
node* hashtable[HASHTABLE_SIZE];

for (int i = 0; i < HASHTABLE_SIZE; i++)
{
    hashtable[i] = NULL;
}

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
 * Hash function via reddit user delipity:
 * https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
 */
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

/**
 * Loads dictionary into memory. Stores words in hash table. Returns true if
 * successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    while (true)
    {
        // malloc a node* for each new word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        fscanf(fp, "%s", new_node->word);
        new_node->next = NULL;
        
        if (feof(fp))
        {
            // hit end of file
            free(new_node);
            break;
        }

        int h = hash_it(new_node->word);
        // node* head = hashtable[h]; // hashtable[h] is a pointer to a key-value pair
        
        // if bucket is empty, insert the first node
        if (hashtable[h] == NULL)
        {
            hashtable[h] = new_node;
        }
        // if bucket is not empty, attach node to front of list
        else
        {
            new_node->next = hashtable[h]; // remember head is a pointer!
            hashtable[h] = new_node;
        }
        
        free(new_node);
    }
    
    // close dictionary
    fclose(dict);
    
    
    
    
    
    
    //node* = hashtable[500];
    
    // node* node1 = malloc(sizeof(node));
    // node* node2 = malloc(sizeof(node));
    // node1->word = "Hello";
    // node2->word = "World";
    // node1->next = node2;
    
    // new_node->word has the word from the dictionary
    // hashing new_node->word gives us the index of a bucket in the hash table
    // insert new_node into the linked list that corresponds to the index
    
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
