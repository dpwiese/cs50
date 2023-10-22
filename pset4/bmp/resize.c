/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 4 - resize.c
 * Fall 2014
 * Due: Thursday 09-Oct (noon)
 ***************************************************************************************************
 * Usage: ./resize n small.bmp large.bmp
 * Takes the given small bmp and magnifies it by factor of n where n is between 1 and 100 inclusive
 * Passes valgrind test: valgrind ./resize
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize magnification infile outfile\n");
        return 1;
    }

    // Remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (n < 1 || n > 100)
    {
        printf("n should be between 1 and 100 inclusve! \n");
        return 5;
    }

    // Open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Determine padding for scanlines
    int originalpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Save original width
    int originalwidth = bi.biWidth;

    // Modify the headers of output file
    bi.biSizeImage = bi.biSizeImage * n * n;
    bf.bfSize = 54 + bi.biSizeImage;
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine new padding for scanlines
    int newpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines: this is iteration down each of the original images rows
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Temporary storage
        RGBTRIPLE triple[originalwidth];

        // Iterate over pixels in scanline: on each row of original image iterate across the columns
        for (int j = 0; j < originalwidth; j++)
        {
            // Read RGB triple from infile for each column
            fread(&triple[j], sizeof(RGBTRIPLE), 1, inptr);
        }

        // Skip over padding, if any
        fseek(inptr, originalpadding, SEEK_CUR);

        // Now that the colors for a whole row of original image are stored in vector, they need to
        // be written as n rows to expand image vertically
        for (int i = 0; i < n; i++)
        {
            // Loop through each element of the array, which correspond to a pixel of original image
            for (int j = 0; j < originalwidth; j++)
            {
                // For each pixel of given small image, we need to write n of these pixels to the
                // new image in each line expanding image horizontally
                for (int k = 0; k < n; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple[j], sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Put padding back
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Done
    return 0;
}
