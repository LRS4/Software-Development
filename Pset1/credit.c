#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // user input for card digits
  
    long long card;
    
    do
    {
         card = get_long("Card number: ");
    }
    while (card < 0);
    
    // count and validate number of digits
    
    long long digits = card;
    int count = 0;
    
    while (digits > 0)
    {
        digits = digits / 10;
        count++;
    }
    //printf("Digits: %i\n", count);
    
    //  Find first digit of card
    int first = card / pow(10,(count-1));
    //printf("First digit: %i\n", first);
    
    //  Find first two digits of card
    int start = card / pow(10,(count-2));
    //printf("First digits: %i\n", start);
    
    // 1. Sum the digits starting with the last one
    long long number = card;
    int add = 0;
    for (int i = 0; i < count; i++)
    {
        add = add + (number % 10);
        number = number / 100;
    }
    
    // 2. Multiply every other digit by 2, starting with the second-to-last
    long long num = card / 10;
    int xcount = 0;
    for (int i = 0; i < count; i++)
    {
        xcount = xcount + ((num % 10) * 2);
        num = num / 100;
    }
    
    // 3. Sum these ouputs together
    int total = xcount + add;
    int checksum = total % 10;
    
    // 4. Validate card - number length, checksum then card type
    if ((count != 16) && (count != 13) && (count !=15) && (checksum != 0))
    {
        printf("INVALID\n");
    }
    else
    {
       if (start == 34 || start == 37)
       {
           printf("AMEX\n");
       }
       if (start == 51 || start == 52 || start == 53 || start == 54 || start == 55)
       {
           printf("MASTERCARD\n");
       }
       if (first == 4)
       {
           printf("VISA\n");
       }
       if(start != 34 && start != 37 && start != 51 && start != 52 && start != 53 && start != 54 && start != 55 && first != 4)
       {
           printf("INVALID\n");
       }
    }
    
    
    
    
    
    
    
    
    
    /* logic for finding digits -
    
    printf("%lli\n", card / 1 % 10);
           
    printf("%lli\n", card / 10 % 10);
    
    printf("%lli\n", card / 100 % 10);
    
    printf("%lli\n", card / 1000 % 10);
    
    printf("%lli\n", card / 10000 % 10);
    
    printf("%lli\n", card / 100000 % 10);
    
    printf("%lli\n", card / 1000000 % 10);
    
    printf("%lli\n", card / 10000000 % 10);
    
    printf("%lli\n", card / 100000000 % 10);
    
    printf("%lli\n", card / 1000000000 % 10);
    
    printf("%lli\n", card / 10000000000 % 10);
    
    printf("%lli\n", card / 100000000000 % 10);
    
    printf("%lli\n", card / 1000000000000 % 10);
    
    printf("%lli\n", card / 10000000000000 % 10);
    
    printf("%lli\n", card / 100000000000000 % 10);
    
    printf("%lli\n", card / 1000000000000000 % 10); */
    
    
}
