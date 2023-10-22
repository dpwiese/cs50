/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 3 - helpers.c
 * Fall 2014
 * Due: Thursday 02-Oct (noon)
 ***************************************************************************************************
 *
 * helper functions for pset3: search and sort
 * sort takes a list of length n and sorts it smallest to largest
 * search uses binary search to look for given number once the list has been sorted
 *
 **************************************************************************************************/

// Include standard libraries and helpers
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

// Returns true if value is in array of n values, else false.
bool search(int value, int values[], int n)
{
    // First check that n is non-negative
    if (n < 0)
    {
        return false;
    }

    // I am still not clear on how pointers work, but I did this to make code work
    int * array = values;

    // Binary (phonebook) search
    while (array[1] != '\0')
    {
        // Find approximately middle of array
        int m = n / 2;

        // If the middle number of array is the number we are looking for, stop
        if (array[m] == value)
        {
            printf("needle is here \n");
            return true;
        }
        // If middle number is bigger than the number we are looking for that number is in left half
        else if (array[m] > value)
        {
            for (int j = 0; j < m; j++)
            {
                array[j] = values[j];
            }
            array[m] = '\0';
        }
        // If middle number is smaller than the number we are looking for that numbers in right half
        else if (array[m] < value)
        {
            for (int j = 0; j < n - m; j++)
            {
                array[j] = values[m + j + 1];
            }
            array[n-m] = '\0';
        }
        else
        {
            printf("error");
        }

        n = m;
    }
    return false;
}

// Function of O(n^2) sorting algorithm: Selection sort
// Selection sort looks through all values and swaps smaller values to put them at the beginning
void sort(int values[], int n)
{
    // Declare and initialize temp var that is used to swap values
    int temp = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[i])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    return;
}

/*    // Linear search*/
/*    for (int i = 0; i < n; i++)*/
/*    {*/
/*        if (values[i] == value)*/
/*        {*/
/*            return true;*/
/*        }*/
/*    }*/
