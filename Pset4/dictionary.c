// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define SIZE 14000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[SIZE];

// Creates hash function (thanks to github user rishabhs95)
int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // alphabet case
        if(isalpha(word[i]))
            n = word [i] - 'a' + 1;

        // comma case
        else
            n = 27;

        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;
}

// create a global variable to count size
int dictionarySize = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table to null
    for (int i = 0; i < SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO

        // increment dictionarySize
        dictionarySize++;

        // allocate memory for a new node
        node *new_node = malloc(sizeof(node));

        // if memory full abort, else put word in the new node
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);
        }

        // find what index of the array the word should go in
        int index = hash(word);

        // if hashtable is empty at index, insert
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
            new_node->next = NULL;
        }
        // if hashtable is not empty at index, append
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    // if dictionarySize greater than 0, return size
    if (dictionarySize > 0)
    {
        return dictionarySize;
    }
    // else return 0
    else
        return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // creates a temp variable that stores a lower case version of the word
    char temp[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';

    // find out what index of the array the word should be in
    int index = hash(temp);

    // if hashtable is empty at index, return false
    if (hashtable[index] == NULL)
    {
        return false;
    }

    // create cursor to compare to word
    node* cursor = hashtable[index];

    // if hashtable is not empty at index, iterate through words and compare
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor-> word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    // if the word is not found, return false
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // create a variable to go through the index
    int index = 0;

    // iterate through entire hashtable array
    while (index < SIZE)
    {
        // if hashtable is empty at index, go to next index
        if (hashtable[index] == NULL)
        {
            index++;
        }

        // if hashtable is not empty, iterate through the nodes and start freeing
        else
        {
            while(hashtable[index] != NULL)
            {
                node* cursor = hashtable[index];
                hashtable[index] = cursor->next;
                free(cursor);
            }

            // once hashtable is empty at index, go to next index
            index++;
        }
    }

    return true;
}