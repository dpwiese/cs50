/***************************************************************************************************
* section notes
 *
 * int array1[3] = {1, 2, 3}; // good practice to initialize array with size in addition to elements
 * int array2[3] = {0}; // initialize every element to zero
 *
 **************************************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Function prototypes here
void PrintString(string string_name);

// Main function
int main(void)
{
    string string_name = GetString();
    PrintString(string_name);
    return 0;
}

// PrintString function
void PrintString(string string_name)
{
    // Loop through each character of string printing one at a time
    // Don't forget its semicolons between arguments in for
    for (int i = 0, string_length = strlen(string_name); i < string_length; i++)
    {
        printf("%c \n", string_name[i]);
    }
}
