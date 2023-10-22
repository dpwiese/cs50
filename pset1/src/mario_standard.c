/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 1 (Standard Edition) - mario.c
 * Fall 2014
 * Due: Thursday 18-Sept (noon)
 *
 **************************************************************************************************/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Main function
int main(void)
{
    // Prompt the user and take as input from the user the desired pyramid height
    printf("Please enter the desired height of the half pyramid, between 0 and 23 inclusive: ");
    int height = get_int("");

    // Check that the input height is within desired range, if not prompt user to enter height again
    while (height >23 || height < 0)
    {
        printf("Retry: ");
        height = get_int("");
    }

    // Based on desired height, loop through each of the rows of the pyramid
    for (int i = 0; i < height; i++)
    {
        // On each row, loop through columns placing necessary number of spaces then hash characters
        for (int j = 0; j < height + 1; j++)
        {
            if (j < height - ( i + 1 ))
            {
            printf(" ");
            }
            else
            {
            printf("#");
            }
        }
        // Once we finish a row, want to jump to next row before next iteration
        printf("\n");
    }
    return 0;
}
