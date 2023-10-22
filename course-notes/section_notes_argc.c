/***************************************************************************************************
 * section notes
 * args.c
 *
 * atoi() takes a string that is a number and interprets returns an integer
 * sprintf stores what you would print in a string
 * toupper capitalizes string
 *
 * ASCII is way to store characters in memory
 * Can define scope with curly braces
 * can avoid unused variable error by doing (void) variable
 *
 **************************************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Function prototypes here

// zeroth element of argv is the name of the file
// Main function

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("error. Usage: mario height \n");
        return 1;
    }

    printf("There are %d arguments. They are: \n", argc-1);

    for (int i = 1; i < argc; i++)
    {
        printf("%s \n", argv[i]);
    }

    return 0;
}
