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
    char word[LENGTH + 1];    //LENGTH = 45程式自動設定的?為啥是45(設定單字最長不能超過45)
    struct node *next;
}
node;

// Number of buckets in hash table
//要改只能從這裡改 不能從程式加上去

// Hash table   n會預設成1 之後要讓hash table 更大 就改變N
node *table[N];



//original

bool check(const char *word)
{

    //為何一定要加\0才能被檢測到? 為何需要\0 跟tolower?
    //原因: 因為dictionary裡面字元全部都是小寫，在hash()內有針對每個字母去計算對應數值，所以就算兩個字 字數相同，但還是會放到不同bucket
    //那這邊為了要還原回去 照著dictionary(全部都小寫)的方式去hash() 所以才會需要用到tolower
    //  \0則是跟記憶體儲存方式有關
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
    unsigned int word_len = strlen(word);     //用字的長度去hash
    for (; i < word_len; i++)
    {
        //printf("key[]\n", key[i]);   比如"em" key[0] = e, key[1] = m; ACSII碼下，key[0] = 101, key[1] =109
        value = value * 37 + word[i];  //why *37? 算是一種整理hash function的方式，實際使用不一定需要

        //value = (value << 2) ^ word[i];
        //上面會得到101* 37 + 109 = 3846
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

// Loads dictionary into memory, returning true if successful else false 用字母第一位

int countword = 0;

bool load(const char *dictionary)
{
    // TODO 1. Open the dictionary file
    FILE *ftr = fopen(dictionary, "r");
    if (!ftr)
    {
        printf("load dictionary error.");
        return false;
    }

    //TODO 2. Read String from file
    char dic[LENGTH + 1];

    while (fscanf(ftr, "%s", dic) != EOF)
    {
        //TODO 3. Create a New node
        node *newword = malloc(sizeof(node));
        if (newword == NULL)
        {
            printf("New node doesn't get malloc memory.");
            return false;
        }
        strcpy(newword->word, dic);
        newword->next = NULL;

        //TODO 4. Hash the word
        int slot;
        slot = hash(newword->word);

        //Todo 5. Insert Node into Hash table
        if (table[slot] == NULL)
        {
            table[slot] = newword;
            countword++;
        }
        else
        {
            newword->next = table[slot];    //讓newword當第一個
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
