/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 4 - whodunit.c
 * Fall 2014
 * Due: Thursday 09-Oct (noon)
 ***************************************************************************************************
 * Recovers JPEGs from a forensic image.
 *
 *       CHECK WITH VALGRIND BEFORE SUBMITTING
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // Ensure proper usage
    if (argc != 1)
    {
        printf("Usage: no command line arguments necessary \n");
        return 1;
    }

    // Open memory card input file
    FILE* rawfile = fopen("card.raw", "r");
    if (rawfile == NULL)
    {
        printf("Could not open card.raw.\n");
        return 2;
    }

    // Find beginning of first jpg " 0xff 0xd8 0xff 0xe0 " or " 0xff 0xd8 0xff 0xe1 " =>
    // 255 216 255 224 or 255 216 255 225

    // Make a buffer array with each element one byte
    uint8_t buffer[512] = {0};

    int start = 0;

    // Read in one buffer block at a time until the start of the first JPG is found
    while (start == 0)
    {
        fread(&buffer, 1, 512, rawfile);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            printf("found start of first jpg! \n");
            start = 1;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe1)
        {
            printf("found start of first jpg! \n");
            start = 1;
        }
    }

    // Open a new jpg (free me later)
    char* title = malloc(6);
    sprintf(title,"%d.jpg", 2);

    FILE* img = fopen(title, "a");
    if (img == NULL)
    {
        printf("Could not open %s.\n", title);
        return 2;
    }

    start = 0;

    // Write 512 bytes until new jpg is found
    while (start == 0)
    {
        fwrite(&buffer, 1, 512, img);
        fread(&buffer, 1, 512, rawfile);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            printf("found start of next jpg! \n");
            start = 1;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe1)
        {
            printf("found start of next jpg! \n");
            start = 1;
        }
    }

}
