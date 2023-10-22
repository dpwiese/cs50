/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * Class notes: Wed 24-Sept
 * Fall 2014
 * Week 3 Lecture 2
 ***************************************************************************************************
 * bubble sort: (n-1) + (n-2) + ... + 1 = n(n-1)/2 => O(n^2)
 * big-O notation
 * O(n)
 * ex: finding biggest number in a list
 * O(log n)
 * ex: finding someone in phonebook
 *   - assumed list was sorted
 * O(1) - takes constant number of steps, independent of n "constant time algorithm"
 * ex: taking first element of array
 * $\Omega(n)$ - LOWER BOUND
 * ex: bubble sort, best case list is already sorted, but need n operations to check this
 * $\Omega(1)$
 * ex: finding someone in phone book - get lucky on first guess when opening book
 * if $O = \Omega$ we can say it has order $\Theta$
 * Selection sort
 *   O(n^2)
 *   => Omega(n^2)
 * Insertion sort
 *   O(n^2)
 *   Omega(n^2)
 * Bogosort "stupid sort" randomly rearranges list until it gets lucky
 *
 * RECURSION
 * merge sort
 *   O(n log n)
 **************************************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <crypt.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <math.h>

// Function Prototypes

// Main function
int main(int argc, string argv[])
{
    // Check that there is only one command line argument
    if (argc != 2)
    {
        printf("Error. \n");
        return 1;
    }
}
