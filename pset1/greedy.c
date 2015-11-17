#include <stdio.h>
#include <cs50.h>
#include <math.h>

/**
 * greedy.c
 *
 * David Venturi
 *
 * Asks the user how much change is owed (in $) and prints the minimum number of coins with which said change can be made.
 */

int main(void)
{
    float dollars;
    int cents, leftover, quarter_count, dime_count, nickel_count, penny_count, coin_count;
    int quarter = 25, dime = 10, nickel = 5;
    
    // requests a non-negative float from the user
    do
    {
        printf("How much change is owed? Note: 4.21 represents 4 dollars and 21 cents.\n");
        dollars = GetFloat();    
    }
    while (dollars < 0);
    
    // converts dollars (float) to cents (integer) to avoid floating point errors
    cents = (int)round(dollars * 100);
    
    quarter_count = cents / quarter;
    leftover = cents % quarter;
    
    dime_count = leftover / dime;
    leftover = leftover % dime;
    
    nickel_count = leftover / nickel;
    leftover = leftover % nickel;
    
    penny_count = leftover;
    
    coin_count = quarter_count + dime_count + nickel_count + penny_count;
    printf("%i is the minimum number of coins with which $%.2f worth of change can be made (quarter count = %i, 
            dime count = %i, nickel count = %i, penny count = %i).\n", coin_count, dollars, quarter_count, dime_count, 
            nickel_count, penny_count);
}
