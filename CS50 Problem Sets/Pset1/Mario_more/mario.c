#include <cs50.h>
#include <stdio.h>

int main(void)
{
	// a program to print a double pyramid to a specified height
	
    int height;
    
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    for (int i = 0; i < height; i++)
    {
        // loop for spaces
        for (int spaces = height - 1; spaces > i; spaces--)
        {
            printf(" ");
        }
        
        // loop for first set of hashes
        for (int hashes = 1; hashes < i + 1; hashes++)
        {
            printf("#");
        }
        
      printf("#  #");
        
        // loop for second set of hashes
        for (int hashes = 1; hashes < i + 1; hashes++)
        {
            printf("#");
        }
        
      printf("\n");
        
    }
}
