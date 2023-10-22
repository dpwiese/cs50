/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 1 (Hacker Edition) - credit.c
 * Fall 2014
 * Due: Thursday 18-Sept (noon)
 *
 * NOTES ABOUT CREDIT CARDS:
 * AMERICAN EXPRESS: 15 digits, start with 34 or 37
 * VISA: 13 or 16 digits, start with 4
 * MASTER CARD: 16 digits, starts with 51, 52, 53, 54, 55
 **************************************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Function Prototypes
int GetCCLength(long long cc_number);
long long GetLeadingTwoDigits(long long cc_number);
int AddDoubleDigit(int double_digit);
int CheckLuhnsAlgorithm(long long cc_number);

// Main function
int main(void)
{
    // Prompt and obtain credit card number from user
    printf("Please enter a credit card number:\n");
    long long cc_number = get_long_long("");

    // Determine the length of the credit card number
    int cc_length = GetCCLength(cc_number);

    // Check that credit card is not an invalid length
    if (cc_length<13 || cc_length>16 || cc_length==14)
    {
        printf("INVALID \n");
        return 1;
    }

    // Check that the pattern of credit card number satisfies Luhns algorithm
    int is_luhns = CheckLuhnsAlgorithm(cc_number);

    // Check leading digits of the credit card number
    long long leading_digits = GetLeadingTwoDigits(cc_number);

    // Now just apply the conditions for the different cards and output the card type
    if (cc_length == 13 && is_luhns == 1)
    {
        // This length can be either VISA or INVALID
        if (leading_digits / 10 == 4)
        {
        printf("VISA \n");
        }
        else
        {
        printf("INVALD \n");
        return 1;
        }
    }
    else if (cc_length == 15 && is_luhns == 1)
    {
        // This length can be either AMEX or INVALID
        if (leading_digits == 34 || leading_digits == 37)
        {
        printf("AMEX \n");
        }
        else
        {
        printf("INVALID \n");
        return 1;
        }
    }
    else if (cc_length == 16 && is_luhns == 1)
    {
        // This length can be either VISA, MASTERCARD, or INVALID
        if (leading_digits / 10 == 4)
        {
        printf("VISA \n");
        }
        else if (leading_digits == 51 || leading_digits == 52 || leading_digits == 53 || leading_digits == 54 || leading_digits == 55)
        {
        printf("MASTERCARD \n");
        }
        else
        {
        printf("INVALID \n");
        return 1;
        }
    }
    else
    {
    printf("INVALID \n");
    return 1;
    }
    return 0;
}

// Function to determine length of credit card number
int GetCCLength(long long cc_number)
{
    // Initialize length counter and credit card variable which digit is truncated from on each loop
    int cc_length = 0;
    long long cc_temp = cc_number;
    while (cc_temp != 0)
    {
        cc_temp = cc_temp/10;
        cc_length++;
    }
    return cc_length;
}

// Function to get leading two digits of credit card number
long long GetLeadingTwoDigits(long long cc_number)
{
    // Call the function to get the length of the credit card number
    int cc_length = GetCCLength(cc_number);

    // Divide by multiple of 10 to truncate all but first two numbers
    long long x = pow((long long)10,(long long)(cc_length-2));
    long long leading_digits = cc_number/x;
    return leading_digits;
}

// Function to take a double digit number and sum the two digits
int AddDoubleDigit(int double_digit)
{
    int digit_one = double_digit % 10;
    double_digit /= 10;
    int digit_two = double_digit % 10;
    return digit_one + digit_two;
}

// Function to check Hans Peter Luhn algorithm
int CheckLuhnsAlgorithm(long long cc_number)
{
    // Declare some variables
    int sum = 0;
    int sum_one = 0;
    int sum_two = 0;

    // Loop through the credit card number truncating one digit at a time until we are done
    while(cc_number)
    {
    int num_one = cc_number % 10;
    cc_number /= 10;
    int num_two = cc_number % 10;
    cc_number /= 10;

    // Compute the Luhns sum
    int num_two_prime = AddDoubleDigit(num_two * 2);
    sum_two = sum_two + num_two_prime;
    sum_one = sum_one + num_one;
    sum = sum_one + sum_two;
    }

    // Check if the resulting Luhns sum satisfies Luhns condition
    if (sum % 10 == 0)
    {
    return 1;
    }
    else
    {
    return 0;
    }
}
