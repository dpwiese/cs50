/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 3 - find.c
 * Fall 2014
 * Due: Thursday 02-Oct (noon)
 ***************************************************************************************************
 * Prompts user for as many as MAX values until EOF (ctrl-d) is reached,
 * then proceeds to search that "haystack" of values for given needle.
 *
 * Usage: ./find <needle>
 * where needle is the value to find in a haystack of values
 * ./generate 1000 | ./find 42 <- this generates 1000 pseudorandom numbers then searches them for 42
 *
 **************************************************************************************************/

// Include standard libraries and helpers
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// Declare and initialize maximum amount of hay
const int MAX = 65536;

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./find needle\n");
        return -1;
    }

    // Remember needle
    int needle = atoi(argv[1]);

    // Fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // Wait for hay until EOF
        printf("\nhaystack[%d] = ", size);
        int straw = get_int("");
        if (straw == INT_MAX)
        {
            break;
        }

        // Add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // Sort the haystack
    sort(haystack, size);

    for (int i = 0; i < size; i++)
    {
        printf("Haystack is: %i \n", haystack[i]);
    }

    // Try to find needle in haystack
    if (search(needle, haystack, size))
    {
        printf("\nFound needle in haystack!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find needle in haystack.\n\n");
        return 1;
    }
}
