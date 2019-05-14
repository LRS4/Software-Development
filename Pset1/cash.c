#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // create variable
    float dollars;
    
    // ensure dollars is positive
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    
    // convert to cents
    int cents = round(dollars * 100);
    
    // print cents
    printf("Change owed: %i\n", cents);
    
    // initialise count to zero
    int count = 0;
    
    // for loop through conditions
    for (int i = 0; cents >= 25; i++)
    {
        cents = cents - 25;
        count++;
    }
    
    printf("-25c = %i\n", count);
    
    for (int i = 0; cents >= 10; i++)
    {
        cents = cents - 10;
        count++;
    }
    
    printf("-10c = %i\n", count);
    
    for (int i = 0; cents >= 5; i++)
    {
        cents = cents - 5;
        count++;
    }
    
    printf("-5c = %i\n", count);
    
    for (int i = 0; cents >= 1; i++)
    {
        cents = cents - 1;
        count++;
    }
    
    printf("-1c = %i\n", count);
    
    // print minimum number of coins possible
    printf("%i\n", count);
}
