#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BufferSize 512
typedef uint8_t BYTE;

bool JPEGcheck(void);
BYTE buffer[BufferSize];

int main(int argc, char *argv[])
{

//TODO Open Memory card
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");   
    if (!file)
    {
        printf("Load file error..\n");
        return 1;
    }

    /////////////// easter egg  //////////////////
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    char ch;

    while ((ch = fgetc(inptr)) != EOF){
    printf("%c", ch);
    }
    printf("\n");
    /////////////// easter egg //////////////////


    int num = 0;
    char filename[8]; //since the file name is ###.jpg\0 , it's filename[8]
    int newjpeg = 0;
    FILE *img = NULL;
    // Look for beginning of a JPEG
    while (fread(buffer, BufferSize, 1,  file) == 1)   //when read 512byte, means haven't reachfile end
    {
        //Write 512 bytes until a new JPEG is found 
        if (JPEGcheck())  //if there's new jpeg file
        {
            if (newjpeg == 1)  //if there's new JPEG
            {
                fclose(img);
            }
            else              //only the first jpeg file goes here
            {
                newjpeg = 1;
            }

            sprintf(filename, "%03i.jpg", num);
            img = fopen(filename, "w");
            if (!file)
            {
                printf("Load image error..\n");
                return 1;
            }

            num++;
        }

        //keep writing the current file since the jpeg file will save continously after the first jpeg file
        //when jpegcheck is true, save every jpeg file after
        if (newjpeg == 1)
        {
            fwrite(buffer, BufferSize, 1, img);
        }
    }

//Stop at end of file
    fclose(file);
    fclose(img);

    return 0;

}


bool JPEGcheck(void)
{
    //printf("%03x, %03x %03x\n", buffer[0], buffer[1], buffer[2]);
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);

    //if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        //return true;
    //else
        //return false;
}