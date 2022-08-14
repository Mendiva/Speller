// Implements a dictionary's functionality
//TODO
//1.load function: Load all the words like a hash table
//2.hash: take a word and run hash function, returning a number
//3.size: returns how many words are there in your dictionary
//4.check: is this word in your dictionary, true or false
//5.unload: free memory  

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int word_count;
unsigned int hash_value;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash_value = hash(word);
    node *cursor = table[hash_value];
    
    while(cursor != 0)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long total = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    // TODO: Improve this hash function
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open the dictionary file-if file cannot opened return NULL
    //Read strings
    FILE *file = fopen(dictionary,"r");
    if(file == NULL){

        printf("Unable to open %s\n", dictionary);
        return false;
         
    }
    //declare var called word
    char word[LENGTH + 1];
    //Scan dictionary
    while(fscanf(file, "%s", word) != EOF)
    {
    //Allocade memory for new node
    node *n = malloc(sizeof(node));
    if(n == NULL)
    {
        return false;
    }
     strcpy(n->word, word);
     hash_value = hash(word);
     n->next = table[hash_value];
     table[hash_value] = n;
     word_count++;
    }
    fclose(file);
    return true;
}
    //if malloc is null return false
    
    //Copy word into node
   


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp); 
        }
        if(cursor == NULL)
        {
            return true;    
        }
    }
    return false;
}
