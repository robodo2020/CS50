#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("height:");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i = i + 1)
    {
        for (int j = height - i; j > 0; j = j - 1)
        {
            printf(" ") ;
        }
        for (int k = 1; k < i + 1 ; k = k + 1)
        {
            printf("#");
        }
        printf("\n");
    }

}