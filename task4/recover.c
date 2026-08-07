
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
  
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover filename\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    FILE *img = NULL;
    char filename[8];
    int count = 0;

    
    while (fread(buffer, sizeof(BYTE), 512, input) == 512)
    {
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            if (img != NULL)
            {
                fclose(img);
            }
\

            sprintf(filename, "%03i.jpg", count++);
            img = fopen(filename, "w");
        }

      
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    
    if (img != NULL) fclose(img);
    fclose(input);

    return 0;
}

