#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * vigenere.c
 *
 * Encrypts messages using the Vigenere cipher. Retrieves the message to encrypt via user prompt.
 * 
 * Usage: ./vigenere keyword
 * 
 * where keyword is the cipher keyword that is entirely composed of alphabetical characters.
 * 
 * David Venturi
 */

int main(int argc, string argv[])
{
    // Check if the user did not enter a command line argument.
    if(argc == 1) {
        printf("You did not enter a command line argument for the Vigenere encryption keyword!\n");
        printf("Please re-run the program and input a keyword entirely composed of alphabetical characters as a command line argument.");
    }
    
    // Check if the user entered more than one command line argument.
    else if (argc > 2){
        printf("You entered too many command line arguments for the Vigenere encryption keyword!\n");
        printf("Please re-run the program and input a keyword entirely composed of alphabetical characters as a command line argument.");
    }
    
    else {
        // Declare keyword as a string. Assume that the user's keyword is entirely composed of alphabetical characters.
        string keyword = argv[1];
        int keyword_len = strlen(keyword);
        int keyword_index = 0;
        
        // Convert the keyword to all uppercase letters.
        for(int i = 0; keyword[i]; i++){
            keyword[i] = toupper(keyword[i]);
        }
        
        printf("Please enter the phrase you would like to encrypt:\n");
        string message = GetString();
        
        int ASCII_A = 65;
        int ascii_a = 97;
        int len_alphabet = 26;
        
        for (int i = 0, n = strlen(message); i < n; i++) {
            char keyword_map = keyword[(keyword_index % keyword_len)];            
            
            // Add key to uppercase letters and increment keyword index.
            if (isupper(message[i])) {
                printf("%c", ((phrase[i] - ASCII_A + (keyword_map - ASCII_A)) % len_alphabet) + ASCII_A);
                keyword_index++;
            }   
            // Add key to lowercase letters and increment keyword index.
            else if (islower(message[i])) {
                printf("%c", ((message[i] - ascii_a + (keyword_map - ASCII_A)) % len_alphabet) + ascii_a);
                keyword_index++;
            }
            
            // Leave non-letters and keyword index alone.
            else
                printf("%c", message[i]);
        }
    }
    
    // Exit cleanly.
    printf("\n");
    return 0;
}
