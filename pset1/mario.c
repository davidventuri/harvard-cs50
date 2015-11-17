#include <stdio.h>
#include <cs50.h>

/**
 * mario.c
 *
 * David Venturi
 * 
 * Prints Mario's half-pyramid of hashes of user-inputted height >= 1 and <= 23.
 */

int main(void)
{
    int height, width, row_counter, col_counter;
    
    // requests an integer from the user until the height requirement is satisfied 
    do
    {
        printf("Please give me a non-negative integer no greater than 23: "); 
        height = GetInt();  
    }
    while (height < 0 || height > 23);
    printf("Thank you for the valid integer!\nHere is Mario's half-pyramid of height %i:\n", height);
    
    // the top row needs two hashes
    width = height + 1;
    
    for (row_counter = 1; row_counter <= height; row_counter++)  
    {
        for (col_counter = 1; col_counter <= width; col_counter++)
        {
            // the nth row has width-(n+1) spaces and (n+1) hashes
            if (col_counter <= width - (row_counter + 1))
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
    return 0;
}
