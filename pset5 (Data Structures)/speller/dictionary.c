// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#include "dictionary.h"

#define ACSII 65
#define N 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];    //LENGTH = 45, set the max len = 45
    struct node *next;
}
node;

// Number of buckets in hash table
// Hash table   n default is 1, change N if make hash table bigger
node *table[N];



//original

bool check(const char *word)
{

    // Creates copy of word on which hash function can be performed

    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    // Adds null terminator to end string
    word_copy[n] = '\0';


    int slot = hash(word_copy);


    node *cursor = table[slot];

    while (cursor != NULL)
    {
        // Returns true if word is in dictionary else false
        if (strcasecmp(cursor->word, word_copy) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int word_len = strlen(word);     //use word len to hash
    for (; i < word_len; i++)
    {
        //printf("key[]\n", key[i]);   
        //ex:"em" key[0] = e, key[1] = m; in ACSII, key[0] = 101, key[1] =109
        value = value * 37 + word[i];  

        //value = (value << 2) ^ word[i];
        //it gets 101* 37 + 109 = 3846
    }
    //printf("alphabet:%d \n", alphabet);
    value = value % N;
    return value;

    // unsigned int value = 0;
    // for (int i = 0, n = strlen(word); i < n; i++)
    // {
    //     value = (value << 2) ^ word[i];
    // }
    // return value % N;
}

// Loads dictionary into memory, returning true if successful else false

int countword = 0;

bool load(const char *dictionary)
{
    // 1. Open the dictionary file
    FILE *ftr = fopen(dictionary, "r");
    if (!ftr)
    {
        printf("load dictionary error.");
        return false;
    }

    // 2. Read String from file
    char dic[LENGTH + 1];

    while (fscanf(ftr, "%s", dic) != EOF)
    {
        // 3. Create a New node
        node *newword = malloc(sizeof(node));
        if (newword == NULL)
        {
            printf("New node doesn't get malloc memory.");
            return false;
        }
        strcpy(newword->word, dic);
        newword->next = NULL;

        // 4. Hash the word
        int slot;
        slot = hash(newword->word);

        // 5. Insert Node into Hash table
        if (table[slot] == NULL)
        {
            table[slot] = newword;
            countword++;
        }
        else
        {
            newword->next = table[slot];    //make newword the first
            table[slot] = newword;
            countword++;
        }


    }

    fclose(ftr);

    return true;
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return countword;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    node *cursor;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }

    }
    return true;
}
