#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
	// a program to implement Vigenere's cipher
	
    // check for one word which isalpha
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else if (argc == 2)
    {
        string key = argv[1];
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(key[i]))
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
    }
    
    // get key (k)
    string k = argv[1];
    
    // prompt user for a string
    string text = get_string("plaintext: ");

    // begin cipher to shift chars by k[i]
    printf("ciphertext: ");
    
    // increase by index of k modulo length of word to loop around end of key
    int index = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", (((((text[i]) - 65) + toupper(k[index])) - 65) % 26) + 65);
            index = (index + 1) % strlen(k);
        }
        if (islower(text[i]))
        {
            printf("%c", (((((text[i]) - 97) + tolower(k[index])) - 97) % 26) + 97);
            index = (index + 1) % strlen(k);
        }
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}

