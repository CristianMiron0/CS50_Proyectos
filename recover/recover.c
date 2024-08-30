#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf ("Usage: ./return card.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Cant open file\n");
        return 1;
    }

    uint8_t buffer[512];
    FILE *img = NULL;
    char imageName[8];
    int counter = 0;

    while(fread(&buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(imageName, "%03i.jpg", counter++);
            img = fopen(imageName, "w");
        }

        if (img != NULL)
        {
            fwrite(&buffer, 1, 512, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
}
