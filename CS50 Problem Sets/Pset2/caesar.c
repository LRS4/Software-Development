#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
	// a program to implement Caesar's cipher
	
    // check command line for one argument
    // then check argument characters are decimal digits
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else if (argc == 2)
    {
        string key = argv[1];
        
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isdigit(key[i]))
            {
                printf("Usage: %s key\n", argv[0]);
                return 1;
            }
        }
    }
    
    // convert to integer
    int k = atoi(argv[1]);
    
    // ensure digits are positive
    if (k <= 0)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    
    // if valid, print key
    printf("Success\n");
    printf("%i\n", k);
    
    // prompt user for a string
    string text = get_string("plaintext: ");
    
    // begin cipher to shift chars by 1
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", (((text[i] + k) - 65) % 26) + 65);
        }
        if (islower(text[i]))
        {
            printf("%c", (((text[i] + k) - 97) % 26) + 97);
        }
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
    }
    
    printf("\n");
    
    
    
    
    return 0;
}
