#include <cs50.h>
#include <stdio.h>

int main(void)
{
	// a program to print a pyramid to specified height
	
    // get height of pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // for (initialization; condition; update) i++ (equal to i = i + 1)
    for (int i = 0; i < height; i++)
    {
        // print spaces
        for (int spaces = (height -(i)) ; spaces > 1; spaces--)
        {
            printf(" ");    
        }
        
        // print hashes
        for (int hashes = 0; hashes < (i + 1); hashes++)
        {
            printf("#");    
        }
        
        // print new line
        printf("\n");
    }
}
