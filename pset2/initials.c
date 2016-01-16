#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/**
 * initials.c
 * 
 * David Venturi
 * 
 * Prompts the user for their name and then outputs their initials in uppercase
 * with no spaces or periods, followed by a newline (\n) and nothing more.
 * Assumes that the user’s input will contain only letters (uppercase and/or
 * lowercase) plus single spaces between words.
 */

int main(void)
{
    printf ("Please type in your full name: \n"); 
    string s = GetString();
    
    printf ("Your initials are: ");
    char* pch;
    pch = strtok (s, " ");
    while (pch != NULL)
    {
        char c = toupper(* pch);
        printf ("%c", c);
        pch = strtok (NULL, " ");
    }
    printf ("\n");
    return 0;
}
