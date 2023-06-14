#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)      //check command line argument
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    unsigned char buffer[512];
    char *filename = malloc(8 * sizeof(char));      //filename allocated enough buffer
    FILE *Opfile;
    int Cimg = 0;

    while (fread(buffer, sizeof(char), 512, file))
    {
        //check JPEG first to fourth byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", Cimg);

            Opfile = fopen(filename, "w");
            Cimg++;
        }
        // write file
        (Opfile != 0) ? fwrite(buffer, sizeof(char), 512, Opfile) : 0;

    }
    // measure against leaking memory
    free(filename);
    fclose(file);
    fclose(Opfile);
}