#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
//user input
    string text = get_string("Text:");
// count for sentences.
    int SentenceNum = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            SentenceNum += 1;
        }
    }
    printf("You have %i sentence.\n", SentenceNum);
// count for words.
    int WordNum = 0;
    for (int j = 0; text[j] != '\0'; j++)
    {
        if (((text[j] >= 'a' && text[j] <= 'z') || (text[j] >= 'A' && text[j] <= 'Z')) &&
            (text[j + 1] == ' ' || text[j + 1] == '.' || text[j + 1] == '!' || text[j + 1] == '?' ||
             text[j + 1] == ',' || text[j + 1] == ':' || text[j + 1] == '\''))    //要在''內標示' 特殊符號要用\' 為了標示'(I've)
        {
            WordNum += 1;
        }
    }
    printf("You have %i words.\n", WordNum);

// count for letters
    int lettersNum = 0;
    for (int k = 0; text[k] != '\0'; k++)
    {
        if ((text[k] >= 'a' && text[k] <= 'z') || (text[k] >= 'A' && text[k] <= 'Z'))
        {
            lettersNum += 1;
        }
    }
    printf("You have %i letters.\n", lettersNum);
// calculate for readability.
    float index, L, S;
    L = lettersNum * 100 / WordNum;
    S = SentenceNum * 100 / WordNum;
    index = 0.0588 * L - 0.296 * S - 15.8;
//round needed
    if (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int grade = round(index);  //透過這樣轉int
        printf("Grade %i\n", grade);
    }

}