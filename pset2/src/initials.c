/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 2 - initials.c
 * Fall 2014
 * Due: Thursday 25-Sept (noon)
 **************************************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Main function
int main(void)
{
    // Prompt the user to enter their name
    printf("What's your name? ");
    string users_name = get_string("");

    // Initialize an integer assuming the first letter is zeroth index of string
    int first_letter = 0;

    // Loop through the string until first non-space character is found. this is first letter of
    // person's name
    while (users_name[first_letter] == 32)
    {
        first_letter++;
    }

    // Capitalize and print the first letter of the person's name
    printf("%c", toupper(users_name[first_letter]));

    // Loop through the remaining letters of the persons name, and once space is found, characte to
    // right is start of next word of name.
    for (int i = first_letter + 1; i < strlen(users_name); i++)
    {
        if (users_name[i] == 32 && users_name[i + 1] != 32)
        {
            printf("%c", toupper(users_name[i + 1]));
        }
    }

    printf("\n");
    return 0;
};
