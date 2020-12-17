#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue =  round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtRed = image[i][j].rgbtBlue;
        }
    }
    return;
}

void swap(RGBTRIPLE *front, RGBTRIPLE *end)
{
    RGBTRIPLE temp;
    temp = *front;
    *front = *end;
    *end = temp;
    return;
}

//TODO 反轉
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int reverse = width - 1;
        for (int j = 0; j < width; j++)
        {
            swap(&image[i][j], &image[i][reverse]);

            if (j == reverse || j == reverse - 1)
            {
                break;
            }

            reverse--;
        }
    }
    return;
}

float checkcornerside(int *i, int *j, int *newH, int *newW)  //這裏做的事有必要用指標嘛？
{
    //判斷corner左上，右上，左下，右下
    if ((*i == 1 && *j == 1) || (*i == 1 && *j == *newW - 2) || (*i == *newH - 2 && *j == 1) || (*i == *newH - 2 && *j == *newW - 2))
    {
        return 4.0;
    }
    //判斷邊邊，上，下，左，右
    else if ((*i == 1 && (*j > 1 && *j < *newW - 2)) || (*i == *newH - 2 && (*j > 1 && *j < *newW - 2)) || (*j == 1 && (*i > 1
             && *i < *newH - 2)) || (*j == *newW - 2 && (*i > 1 && *i < *newH - 2)))
    {
        return 6.0;
    }
    //剩下部分
    else
    {
        return 9.0;
    }
}

//處理邊緣爲0
void zerocornerside(int newH, int newW, RGBTRIPLE temp[newH][newW])
{
    for (int j = 0; j < newW; j++)
    {
        temp[0][j].rgbtBlue = temp[0][j].rgbtGreen = temp[0][j].rgbtRed = 0; //上方
        temp[newH - 1][j].rgbtBlue = temp[newH - 1][j].rgbtGreen = temp[newH - 1][j].rgbtRed = 0;//下方
    }
    //處理左右方
    for (int i = 0; i < newH; i++)
    {
        temp[i][0].rgbtBlue = temp[i][0].rgbtGreen = temp[i][0].rgbtRed = 0; //左方
        temp[i][newW - 1].rgbtBlue = temp[i][newW - 1].rgbtGreen = temp[i][newW - 1].rgbtRed = 0; //右方
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int newH = height + 2;
    int newW = width + 2;
    RGBTRIPLE temp[newH][newW];

    //temp[newH][newW] = *putcenter(height, width, image);
    //把old image 放在temp正中間
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            temp[i][j] = image[i - 1][j - 1];
        }
    }
    //這裏function包不起來QQ


    //處理邊緣爲0
    zerocornerside(newH, newW, temp);

    //模糊處理算法
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            float rgbtBlue, rgbtGreen, rgbtRed;
            rgbtBlue = rgbtGreen = rgbtRed = 0.0;
            float avg = checkcornerside(&i, &j, &newH, &newW);

            //計算，然後擺回去
            for (int k = -1; k <= 1; k++)
            {
                rgbtBlue += (temp[i + k][j - 1].rgbtBlue + temp[i + k][j].rgbtBlue + temp[i + k][j + 1].rgbtBlue);
                rgbtRed += (temp[i + k][j - 1].rgbtRed + temp[i + k][j].rgbtRed + temp[i + k][j + 1].rgbtRed);
                rgbtGreen += (temp[i + k][j - 1].rgbtGreen + temp[i + k][j].rgbtGreen + temp[i + k][j + 1].rgbtGreen);
            }

            image[i - 1][j - 1].rgbtBlue = round(rgbtBlue / avg);
            image[i - 1][j - 1].rgbtRed = round(rgbtRed / avg);
            image[i - 1][j - 1].rgbtGreen = round(rgbtGreen / avg);
        }
    }
    return;
}

////////////////////////////////////// Detect edges //////////////////////////////

//將9宮格pixel按照Sobel operator algorithm計算
int SobelCal(int i, int j, int newH, int newW, RGBTRIPLE temp[newH][newW], int a)
{
    float Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float Gnum = 0.0;


    for (int m = -1; m <= 1; m++)
    {
        for (int n = -1; n <= 1; n++)
        {
            if (a == 1)
            {
                Gnum += temp[i + m][j + n].rgbtBlue * Gx[1 + m][1 + n];
            }
            else if (a == 2)
            {
                Gnum += temp[i + m][j + n].rgbtGreen * Gx[1 + m][1 + n];
            }
            else if (a == 3)
            {
                Gnum += temp[i + m][j + n].rgbtRed * Gx[1 + m][1 + n];
            }
            else if (a == 4)
            {
                Gnum += temp[i + m][j + n].rgbtBlue * Gy[1 + m][1 + n];
            }
            else if (a == 5)
            {
                Gnum += temp[i + m][j + n].rgbtGreen * Gy[1 + m][1 + n];
            }
            else if (a == 6)
            {
                Gnum += temp[i + m][j + n].rgbtRed * Gy[1 + m][1 + n];
            }
        }
    }
    return Gnum;
}

//整合計算最後輸出RGB的值
float GValueCal(float GxRGB, float GyRGB)
{
    float GValue = 0.0;
    GValue = sqrt(GxRGB * GxRGB + GyRGB * GyRGB);
    if (GValue > 255)
    {
        return 255;
    }
    else if (GValue < 0)
    {
        return 0;
    }
    else
    {
        return GValue;
    }
}


//TODO
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //怎麼簡化 怎麼變成call function讓edges跟blur都可以用?

    int newH = height + 2;
    int newW = width + 2;
    RGBTRIPLE temp[newH][newW];

    //把old image 放在temp正中間
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            temp[i][j] = image[i - 1][j - 1];
        }
    }

    //處理邊緣爲0
    zerocornerside(newH, newW, temp);

    //edge detection algorithm calculation
    float GxRed, GyRed, GxBlue, GyBlue, GxGreen, GyGreen;
    GxRed = GyRed = GxBlue  = GyBlue = GxGreen = GyGreen  = 0.0;
    int a = 0;  //1 for GxBlue, 2 for GxGreen, 3 for GxRed, 4 for GyBlue, 5 for GyGreen, 6 for GyRed
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            //處理藍色
            a = 1;
            GxBlue = SobelCal(i, j, newH, newW, temp, a);
            a = 4;
            GyBlue = SobelCal(i, j, newH, newW, temp, a);
            image[i - 1][j - 1].rgbtBlue = round(GValueCal(GxBlue, GyBlue));

            //處理綠色
            a = 2;
            GxGreen = SobelCal(i, j, newH, newW, temp, a);
            a = 5;
            GyGreen = SobelCal(i, j, newH, newW, temp, a);
            image[i - 1][j - 1].rgbtGreen = round(GValueCal(GxGreen, GyGreen));

            //紅色
            a = 3;
            GxRed = SobelCal(i, j, newH, newW, temp, a);
            a = 6;
            GyRed = SobelCal(i, j, newH, newW, temp, a);
            image[i - 1][j - 1].rgbtRed = round(GValueCal(GxRed, GyRed));
            a = 0;
        }
    }
    return;
}
