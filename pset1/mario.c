#include <stdio.h>
#include <cs50.h>

/**
 * mario.c
 *
 * David Venturi
 * 
 * Prints Mario's half-pyramid of hashes of height >= 1 and <= 23.
 */

int main(void)
{
    int height, width, row_counter, col_counter;
    
    do
    {
        printf("Please give me an integer between 1 and 23: "); 
        height = GetInt();  
    }
    while (height < 1 || height > 23); // requests an integer from the user until the above request is satisfied 
    printf("Thank you for the integer!\nHere is Mario's half-pyramid of height %i:\n", height);
    
    width = height + 1; // +1 is necessary because the top row needs two hashes 
    for (row_counter = 1; row_counter <= height; row_counter++)  
    {
        for (col_counter = 1; col_counter <= width; col_counter++)
        {
            if (col_counter <= width - (row_counter + 1)) // the nth row has width-(n+1) spaces... 
                printf(" ");
            else
                printf("#"); // ...and (n+1) hashes
        }  
        printf("\n");
    } 
}
