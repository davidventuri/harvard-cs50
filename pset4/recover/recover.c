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
#include <string.h>

int main(int argc, char* argv[])
{
    // open memory card file
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    FILE* outptr = NULL;
    
    // create 512 byte buffer array
    typedef uint8_t  BYTE;
    BYTE buffer[512];
    
    // create array for first four bytes of the buffer
    BYTE firstfour[4];
    
    // the first 4 bytes of a jpg file (i.e. jpg signature)
    // the last four bits can range from 0-f and are hardcoded as zeros here
    BYTE jpgsig[4] = {0xff, 0xd8, 0xff, 0xe0};
    
    // keep track of jpg numbers for jpg filenames
    int jpgnumber = 0;
    char jpgfilename[8];
    
    // read a buffer from card.raw until EOF
    while (fread(&buffer, sizeof(buffer), 1, inptr) > 0)
    {
        // load first three bytes of the buffer into firstfour
	for (int i = 0; i < 4; i++)
	{
	    firstfour[i] = buffer[i];
	}
	
	// hardcode zeros into last four bits of fourth byte in firstfour
	firstfour[3] = (firstfour[3] >> 4) << 4;
	
        // if jpg signature is found
        if (memcmp(firstfour, jpgsig, sizeof(jpgsig)) == 0)
        {
            // a jpg is not open yet
            if (outptr == NULL)
            {
                sprintf(jpgfilename, "%03d.jpg", jpgnumber);
                outptr = fopen(jpgfilename, "a");
                fwrite(&buffer, sizeof(buffer), 1, outptr);
            }
            
            // a jpg is already open
            else
            {
                fclose(outptr);
                jpgnumber++;
                sprintf(jpgfilename, "%03d.jpg", jpgnumber);
                outptr = fopen(jpgfilename, "a");
                fwrite(&buffer, sizeof(buffer), 1, outptr);
            }
        }
        
        else
        {
            // a jpg is already open
            if (outptr != NULL)
            {
                fwrite(&buffer, sizeof(buffer), 1, outptr);
            }
        }
    }
    
    // close files and exit cleanly
    fclose(inptr);
    fclose(outptr);
    return 0;
}
