#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    uint8_t buffer[512];

    int counter = 0;

    FILE *cam = NULL;

    while (fread(buffer, 1, 512, card) == 512)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
            {

                if (cam != NULL)
                {
                    fclose(cam);
                }

                    char filename[8];
                    sprintf(filename, "%03i.jpg", counter);
                    cam = fopen(filename, "w");
                    counter++;
            }

            if (cam != NULL)
            {
                fwrite(buffer, 1, 512, cam);
            }
        }

        if (cam != NULL)
        {
            fclose(cam);
        }

        fclose(card);
    }
