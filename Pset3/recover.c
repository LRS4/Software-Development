#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // a program to recover jpeg files (which begin )

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open the input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s. \n", infile);
        return 2;
    }

    BYTE buffer[512];
    int ImageCount = 0;

    char filename[8];
    FILE *outptr = NULL;

    while (true)
    {

        // read a block of the memory card image
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

        // break out of loop when end of the card image is reached
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

        // check if a JPEG is found
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        // if another JPEG is found, close the previous file
        if (containsJpegHeader && outptr != NULL)
        {
            fclose(outptr);
            ImageCount++;
        }

        // if a JPEG is found, open the file for writing
        if (containsJpegHeader)
        {
            sprintf(filename, "%03i.jpg", ImageCount);
            outptr = fopen(filename, "w");
        }

        // write anytime there is an open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }
    }

    // close last jpeg file
    fclose(outptr);

    // close infile;
    fclose(inptr);

    // success
    return 0;

}
