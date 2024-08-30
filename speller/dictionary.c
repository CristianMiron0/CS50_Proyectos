// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 52;

// Hash table
node *table[N];

// Word in dictionary
unsigned int wordsNumber = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    for (node *n = table[index]; n != NULL; n = n->next)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashNumber = 0;
    // TODO: Improve this hash function
    for (int i = 0; word[i] != '\0'; i++)
    {
        hashNumber += tolower(word[i]);
    }

    return hashNumber % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("Cant open\n");
        return false;
    }

    char c[LENGTH + 1];
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return false;
    }

    // read each word from dictionary
    while (fscanf(dict, "%s", c) != EOF)
    {
        // add the words one by one in the hash table
        strcpy(n->word, c);
        int index = hash(n->word);
        n->next = table[index];
        table[index] = n;

        wordsNumber++;

        n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }
    }

    free(n);
    //close the dictionary file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (wordsNumber > 0)
    {
        return wordsNumber;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];

        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        if (n != NULL)
        {
            return false;
        }

    }

    return true;
}
