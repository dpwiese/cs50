/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 5 - dictionary.c
 * Fall 2014
 * Due: Thursday 02-Oct (noon)
 ***************************************************************************************************
 * Implements a dictionary's functionality.
 ***************************************************************************************************
 * FROM SPELLER:
 *
 * Implements a spell-checker.
 *
 * ./speller "/home/jharvard/dans_text/dict" "/home/jharvard/dans_text/text"
 * ./speller ~cs50/pset5/dictionaries/large ~cs50/pset5/texts/austinpowers.txt
 *
 * ~cs50/pset5/challenge "/home/jharvard/Dropbox (MIT)/CS50/pset5"
 *
 * valgrind --leak-check=full ./speller ~cs50/pset5/texts/austinpowers.txt
 *
 * ./speller ./dictionaries/large ./texts/austinpowers.txt
 *
 * ./speller /Users/dpwiese/code/dpwiese/cs50/pset5/dictionaries/large /Users/dpwiese/code/dpwiese/cs50/pset5/texts/austinpowers.txt
 *
 **************************************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include  <stdlib.h>

typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

// Declare some global variables, including the root of trie and a cursor
int num_words;;
node * root;
node * cursor;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // Get the length of the word
    int len_word = strlen(word);

    // Initialize cursor to point to root
    cursor = root;

    // Declare and initialize vars for position in word, and corresponding index of letter in word
    int i_char, j_this;

    // Loop through characters of word diving down branch of trie
    for (i_char = 0; i_char < len_word; i_char++)
    {
        // Make word in question all lowercase one letter at a time
        int c = tolower(word[i_char]);

        j_this = c - 'a';
        cursor = cursor->children[j_this];
        if (cursor == NULL)
        {
            return false;
        }
    }

    // Now check that the end of the branch in the trie has is_word = true there
    if (cursor->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Try to open dictionary file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        // If dictionary file doesn't open
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    else
    {
        // If dictionary opens, start by allocating the root node of the trie, and a cursor
        root = malloc(sizeof(node));

        // Initialize the pointers in root node all to NULL
        for (int i = 0; i < 27; i++)
        {
            root->children[i] = NULL;
        }

        // Declare and initialize ints that hold each character as read from dictionary, and the
        // length of each dictionary word
        int len_word = 0, c = 0;

        // Declare array of characters which will be used to store each successive dictionary word
        char word[LENGTH+1];

        for (num_words = 0; c != EOF; num_words++)
        {
            // Initialize word array to null characters
            for (int i = LENGTH + 1; i > 0; i--)
            {
                word[i] = '\0';
            }

            // Iterate through a word until the end of the word is reached: character is not an
            // apostrophe or letter in alphabet
            for (c = fgetc(fp), len_word = 0; (isalpha(c) || (c == '\'' && len_word > 0)) && c != EOF ; c = fgetc(fp))
            {
                // Allow only alphabetical characters and apostrophes
                if (isalpha(c) || (c == '\'' && len_word > 0))
                {
                    // Make character lowercase and append it to word
                    c = tolower(c);
                    word[len_word] = c;
                    len_word++;
                }
            }

            // Declare ints to use for trie
            int i_char, j_this;

            // Start cursor at root of trie
            cursor = root;

            // Now loop through this word and put it into the trie
            for (i_char = 0; i_char < len_word + 1; i_char++)
            {
                // Make the index in the trie equal to 0 if letter is a, 1 if b, etc.
                j_this = word[i_char] - 'a';

                // Check that the character that cursor is pointing to of the word is not already in
                // trie, by seeing if the pointer there is not NULL if the first character of the
                // word is NOT in the trie, need to put it in the trie
                if (cursor->children[j_this] == NULL)
                {
                    // Check if the next letter in word is \n. if so word is done. set is_word to
                    // true, signifying this is a valid word
                    if (j_this == '\0' - 'a')
                    {
                        cursor->is_word = true;
                    }
                    // If the next letter is not \n, this letters index is used in the child node...
                    // put cursor there
                    else
                    {
                        cursor->children[j_this] = malloc(sizeof(node));
                        cursor = cursor->children[j_this];
                    }

                }
                // If the character the cursor is pointing to IS in the trie already, follow its
                // child to new node
                else
                {
                    // Check that the next letter is NULL. if so word is done. set is_word to true,
                    // signifying this is a valid word
                    if (j_this == '\0' - 'a')
                    {
                        cursor->is_word = true;
                    }
                    // If the next letter is not NULL, this letters index is used in the child node
                    else
                    {
                        cursor = cursor->children[j_this];
                    }
                }
            }
        }
    }
    // Leave the cursor pointing to the root node
    cursor = root;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return num_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

    // Go through all children of cursor
    for (int i = 0; i < 27; i++)
    {
        // If a pointer in children is not null, follow it to node and call unload again
        if (cursor->children[i] != NULL)
        {
            cursor = cursor->children[i];
            unload();
        }
        // Once all pointers are null, free the cursor and reset cursor to root to start over
        else
        {
            free(cursor->children[i]);
            // cursor = root;
        }
    }

    // USE VALGRIND TO CHECK AND FREE ALL THE MEMORY
    return true;
}
