/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 3 - generate.c
 * Fall 2014
 * Due: Thursday 02-Oct (noon)
 ***************************************************************************************************
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 *
 * ./generate 1000 | ./find 42 <- this generates 1000 pseudorandom numbers then searches them for 42
 * ./generate 1000 50 | ./find 127 <- generates 1000 pseudorandom numbers with seed of 50 then
 * searches them for 42
 *
 **************************************************************************************************/

// Include standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Check proper usage else inform user of the usage and exit program
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Takes the second input and convert it from string to an integer
    int n = atoi(argv[1]);

    // If argc=3, argv[2] is seed, else if argc=2 use current time as seed for srand48.
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // drand48 returns a number between 0 and 1, so that is multiplied by the max limit for an
    // integer to get a number between 0 at 65536 (16 bits)
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // Success
    return 0;
}
