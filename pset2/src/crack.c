/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 2 - crack.c
 * Fall 2014
 * Due: Thursday 25-Sept (noon)
 ***************************************************************************************************
 * This program accepts a single command-line argument: an encrypted password.
 * Assume that users' passwords, as plaintext, are composed of printable ASCII characters and are no
 * longer than eight characters long.
 *
 * clang -o crack crack.c -lcrypt -lm
 **************************************************************************************************/

#include <stdio.h>
#include <cs50.h>
// Include unistd.h instead of crypt.h on OSX to get crypt()
#include <unistd.h>
// #include <crypt.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <math.h>

// I don't know why this needs to be outside of main, but I had to do this for pointer to dictionary
// file
FILE *file_pointer;

// Main function
int main(int argc, string argv[])
{
    // Check that there is only one command line argument (program name and encrypted password)
    if (argc != 2)
    {
        printf("Error. Enter encrypted password next time. \n");
        return 1;
    }

    // Some initial stuff
    int asciimin = 32;
    int asciimax = 126;
    int wordlength = 8;

    // Get the input from the user
    char *cipher_in = argv[1];

    // Make the salt string from the combination of two characters
    char salt_in[3];
    salt_in[0] = cipher_in[0];
    salt_in[1] = cipher_in[1];
    salt_in[2] = '\0';

    // A pointer to the salt string
    char *salt = salt_in;

    // Stuff to use with fopen to tell it which file to open, and that its read only
    // Path is relative to the directory from which crack is called
    char *path = "american-english";
    char *mode = "r";
    char line[80];
    char user_pw[wordlength + 1];

    // The last character in this array of chars denotes end of string
    user_pw[wordlength] = '\0';

    // Open dictionary file and then test if the cipher for each of those words matches the given
    // cipher, and stop if it does
    file_pointer = fopen(path, mode);
    while(fgets(line, 80, file_pointer) != NULL)
    {
        sscanf(line, "%s", user_pw);

        char *pw_guess = user_pw;
        char *cipher_guess = crypt(pw_guess, salt);

        // This is a list of some of the answers I have found to the passwords, but still need to
        // find two more
        // cipher_in = "50q/EEJnOmtxc"; // belindazeng : puzzles
        // cipher_in = "50zPJlUFIYY0o"; // caesar : 13
        // cipher_in = "50yoN9fp966dU"; // jharvard : crimson
        // cipher_in = "50q.zrL5e0Sak"; // malan : password
        // cipher_in = "50NwUtF.OmQNY"; // zamyla : 1337

        // Loop through and see if the guessed cipher matches the input cipher
        if (strcmp(cipher_guess,cipher_in) == 0)
        {
            printf("The password was: %s \n", pw_guess);
            return 0;
        }
    }

    // If the dictionary doesn't produce matching cipher, just loop through all possible
    // combinations of 8 character passwords with ASCII characters from 32 to 126
    printf("Haven't found password from the dictionary search. Going to try all combinations for a string of printable ASCII characters of up to length 8. \n");

    // Reset the password before doing brute force of all 95 characters
    for (int i = 0; i < wordlength; i++)
    {
        user_pw[i] = (char) asciimin;
    }
    user_pw[1] = '\0';

    // Number of ascii chars to consider
    int num_ascii_chars = asciimax - asciimin + 1;

    // This is the counter that specifies how many total iterations we have to do to loop through
    // every combination of strings up to length 8.
    long long counter_max = powl(num_ascii_chars, 8) - 1;

    // Now loop through each possible combination of up to 8 character strings
    // This loop is basically just counting: starting with all ASCII 32 (space character) then
    // adding one each time to the first index. Once the maximum is reached (126) the next count
    // causes this to rolls over to 32 and increment next entry in string, just like when we count
    // from 9 to 10.
    for (long long i = 0; i < counter_max; i++)
    {
        // Add one to first index each time we loop
        user_pw[0] = (char) ((int) user_pw[0] + 1);

        // Check when this first "digit" maxes, and then propagate this "roll over" to the other
        // elements in string
        for (int j = 0; j < wordlength - 1; j++)
        {
            if ((int) user_pw[j] == asciimax + 1)
            {
                user_pw[j] = (char) asciimin;
                if (user_pw[j + 1] == '\0')
                {
                    user_pw[j + 1] = (char) asciimin;
                    user_pw[j + 2] = '\0';
                }
                user_pw[j + 1] = (char) ((int) user_pw[j + 1] + 1);
            }
        }

        // Calculate the cipher resulting from this "random" string of characters
        char *pw_guess = user_pw;
        char *cipher_guess = crypt(pw_guess, salt);

        // Compare this "random" cipher to the given input cipher, and if it matches, display the
        // corresponding password and stop the program.
        if (strcmp(cipher_guess, cipher_in) == 0)
        {
            printf("%s \n%s \n", cipher_in, cipher_guess);
            printf("done \n");
            printf("The password was: %s \n", pw_guess);
            return 0;
        }
    }

    // If the program reaches this point, we have unsuccessfuly tried all of the combinations and
    // something didn't work and we couldn't match the cipher to find the user's password
    printf("Something didn't work and we didn't get the password");
    return 0;
}
