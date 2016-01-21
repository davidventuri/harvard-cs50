/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int boolnum = 0;
    
    // Return false right away if n is negative.
    if (n < 1)
        return false;
        
    // Perform a linear search seeking value in values.
    for (int i = 0; i < n; i++) {
        if (values[i] == value) {
            boolnum = 1;
            break;
        }
    }
    
    if (boolnum == 1)
        return true;
    else
        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    return;
}
