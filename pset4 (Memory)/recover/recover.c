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
    FILE *file = fopen(argv[1], "r");   //是指打開後存到 *file內嗎?  -->對 讀取argv的內容存到file內
    if (!file)
    {
        printf("Load file error..\n");
        return 1;
    }

    /////////////// easter egg XD //////////////////
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    char ch;

    while ((ch = fgetc(inptr)) != EOF){
    printf("%c", ch);
    }
    printf("\n");
    /////////////// easter egg XD //////////////////


    int num = 0;
    char filename[8]; //因為是 ###.jpg\0  所以共8碼
    int newjpeg = 0;
    FILE *img = NULL;
    //TODO Look for beginning of a JPEG
    while (fread(buffer, BufferSize, 1,  file) == 1)   //當可以讀取512byte時 代表還沒到file end
    {
        //Write 512 bytes until a new JPEG is found 代表為新的jpg file
        if (JPEGcheck())  //進入代表有新的jpeg 或是第一個jpeg檔案
        {
            if (newjpeg == 1)  //後續會進到這個條件表示JPEGcheck又進入了，表示有新的JPEG
            {
                fclose(img);
            }
            else              //只有第一個jpeg會進來這邊
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

        //一直寫入當前檔案 ，因為jpeg會在第一張之後接續存入，只要jpegcheck條件進入一次的話，後面就都是存進去了
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



    //直接用return 就可以直接判斷後面內容的 true false了!!

    //就不需要下面這裡
    //if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        //return true;
    //else
        //return false;
}