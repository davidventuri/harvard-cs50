#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * caesar.c
 *
 * Encrypts messages using the Caesar cipher. Retrieves the message to encrypt via user prompt.
 * 
 * Usage: ./caesar key
 * 
 * where key is a non-negative integer that is the cipher key.
 * 
 * David Venturi
 */

int main(int argc, string argv[])
{
    // Check if the user did not enter a command line argument.
    if(argc == 1) {
        printf("You did not enter a command line argument for the Caesar encryption key!\n");
        printf("Please re-run the program and input one non-negative integer as a command line argument.");
        return 1;
    }
    
    // Check if the user entered more than one command line argument.
    else if (argc > 2){
        printf("You entered too many command line arguments for the Caesar encryption key!\n");
        printf("Please re-run the program and input one non-negative integer as a command line argument.");
        return 1;
    }
    
    else {
        // Declare key as an int. Assume that the user will only type integers at the prompt.
        int key = atoi(argv[1]);
        
        // The printf below is hidden to satisfy the CS50 automatic grader.
        // printf("Please enter the phrase you would like to encrypt:\n");
        string message = GetString();
        
        int ASCII_A = 65;
        int ascii_a = 97;
        int len_alphabet = 26;
        
        for (int i = 0, n = strlen(message); i < n; i++) {
        
            // Add key to uppercase letters.
            if (isupper(message[i]))
                printf("%c", ((message[i] - ASCII_A + key) % len_alphabet) + ASCII_A);
                
            // Add key to lowercase letters.
            else if (islower(message[i]))
                printf("%c", ((message[i] - ascii_a + key) % len_alphabet) + ascii_a);
            
            // Leave non-letters alone.
            else
                printf("%c", message[i]);
        }
    }
    
    // Exit cleanly.
    printf("\n");
    return 0;
}
