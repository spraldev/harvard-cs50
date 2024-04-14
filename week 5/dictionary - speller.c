  // Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

unsigned int wordsize = 0;

// Hash table
node *table[N];





// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int val = hash(word);

    node *firstnode = table[val];

    for (node *temp = firstnode; temp != NULL; temp = temp->next) {
        if (strcasecmp(temp->word, word) == 0) {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        if (isalpha(word[i])) {
            char upletter = toupper(word[i]);
            int position = upletter - 'A' + 1;

            sum = sum * 7 + position;
        }

        if (word[i] == '\'') {
            sum += 27;
        }
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    for (int i = 0; i < 26; i++) {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");

    if(dict == NULL) {
        return false;
    }

    char word[LENGTH + 1];
    int result;

    while((result = fscanf(dict, "%s", word)) != EOF) {
        if (result != 1) {
            return false;
        }

        node *word_node = malloc(sizeof(node));

        if(word_node == NULL) {
            return false;
        }

        strcpy(word_node->word, word);
        int index = hash(word);


        if(table[index] == NULL) {
            word_node->next = NULL;
            table[index] = word_node;
        } else {
            word_node->next = table[index];
            table[index] = word_node;
        }

        wordsize++;

    }

    fclose(dict);

    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordsize;
}


void freefunc(node *fnode) {
    if(fnode == NULL) {
        return;
    }

    node *jnode = fnode->next;
    free(fnode);
    freefunc(jnode);
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        freefunc(table[i]);
    }
    return true;
}
