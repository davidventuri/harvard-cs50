/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // open memory card file
    FILE* inptr = fopen("card.raw", "r");
    FILE* outptr = NULL;
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    // create 512 byte block buffer
    typedef uint8_t  BYTE;
    BYTE buffer[512];
    BYTE firstfour[4];
    
    //BYTE jpgsig[4] = {0xff, 0xd8, 0xff, 0xe};
    
    int img_number = 0;
    char title[8];
    
    // read buffer block from card.raw
    while (fread(&buffer, sizeof(buffer), 1, inptr) > 0)
    {
        // Add first four bytes into the check buffer
		for(int i = 0; i < 4; i++)
		{
			firstfour[i] = buffer[i];
		}
				
				
        // check for jpg signature
        if (firstfour[0] == 0xff && firstfour[1] == 0xd8 && firstfour[2] == 0xff && ((firstfour[3] & 0xf0) >> 4) == 0xe)
        {
            // a jpg is not open yet
            if (outptr == NULL)
            {
                sprintf(title, "%03d.jpg", img_number);
                outptr = fopen(title, "a");
                fwrite(&buffer, sizeof(buffer), 1, outptr);
            }
            // a jpg is already open
            else
            {
                fclose(outptr);
                img_number++;
                sprintf(title, "%03d.jpg", img_number);
                outptr = fopen(title, "a");
                fwrite(&buffer, sizeof(buffer), 1, outptr);
            }
        }
        else
        {
            // jpg is already open
            if (outptr != NULL)
            {
                fwrite(&buffer, sizeof(buffer), 1, outptr);
            }
        }
    }
    fclose(inptr);
    fclose(outptr);
}
