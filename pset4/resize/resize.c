/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by a factor of n, where n is a postive integer less than or 
 * equal to 100. Uses the re-copy method (goes back to the start of the row
 * and repeats the horizontal resizing n times to resize vertically).
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // factor for resizing the image
    int n = atoi(argv[1]);
    
    if (n < 1 || n > 100)
    {
           printf("BMP resizing factor must be a postive integer less than or equal to 100.");
           return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // old biWidth (px), biHeight (px), padding (bytes)
    int old_biWidth = bi.biWidth;
    int old_biHeight = bi.biHeight;
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // new biWidth (px), biHeight (px), padding (bytes)
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    int new_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update biSizeImage, bfSize for new image (bytes)
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + new_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++)
    {
        for (int row_tracker = 0; row_tracker < n; row_tracker ++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < old_biWidth; j++)
            {
                for (int col_tracker = 0; col_tracker < n; col_tracker++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
        
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    
                    // move file pointer back one pixel if not at last pixel
                    if (col_tracker != (n-1))
                        fseek(inptr, -sizeof(RGBTRIPLE), SEEK_CUR);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, old_padding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int l = 0; l < new_padding; l++)
            {
                fputc(0x00, outptr);
            }
            
            // move file pointer back to the beginning of the row if not at last row
            if (row_tracker != (n-1))
                fseek(inptr, (-sizeof(RGBTRIPLE) * old_biWidth) - old_padding , SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
